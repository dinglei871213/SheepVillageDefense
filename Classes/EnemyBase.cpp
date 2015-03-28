#include "EnemyBase.h"

EnemyBase::EnemyBase()
	:sprite(NULL)
	,hpBgSprite(NULL)
	,pointCounter(0)
	,animationRight(NULL)
	,animationLeft(NULL)
	,animationExplode(NULL)
	,pointsVector(NULL)
	,runSpeed(0)
	,maxHp(0)
	,currHp(0)
	,changeRote(false)
	,changeFinish(true)
	,hpPercentage(100)
	,hpBar(NULL)
	, enemySuccessful(false)
	, preSpeed(0)
{
}

EnemyBase::~EnemyBase()
{
}

bool EnemyBase::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	return true;
}
//创建血条
void EnemyBase::createAndSetHpBar()
{
	hpBgSprite = Sprite::createWithSpriteFrameName("HP_Bg1.png");
	hpBgSprite->setPosition(Point(sprite->getContentSize().width / 2, sprite->getContentSize().height ));
	sprite->addChild(hpBgSprite);

	hpBar = CCProgressTimer::create(Sprite::createWithSpriteFrameName("HP_1.png"));
	hpBar->setType(ProgressTimer::Type::BAR);
	hpBar->setMidpoint(Point(0, 0.5f));
	hpBar->setBarChangeRate(Point(1, 0));
	hpBar->setPercentage(hpPercentage);
	hpBar->setPosition(Point(hpBgSprite->getContentSize().width / 2, hpBgSprite->getContentSize().height / 3 * 2 ));
	hpBgSprite->addChild(hpBar);
}

//创建动画
Animation* EnemyBase::createAnimation(std::string prefixName, int framesNum, float delay)
{
	Vector<SpriteFrame*> animFrames;

	for (int i = 1; i <= framesNum; i++)
	{
		char buffer[20] = { 0 };
		sprintf(buffer, "_%i.png",  i);
		std::string str =  prefixName + buffer;
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}
	return Animation::createWithSpriteFrames(animFrames, delay);
}
//获得敌人当前所处的路径点
Node* EnemyBase::currPoint()
{
	//返回向量(vector)中位置为'pointCounter'的元素
	if(pointsVector.size() > 0){
		return this->pointsVector.at(pointCounter);
	}else{
		return NULL;
	}
}
//敌人下一个移动点
Node* EnemyBase::nextPoint()
{
	int maxCount = this->pointsVector.size();
	pointCounter++;
	if (pointCounter < maxCount  ){
		auto node =this->pointsVector.at(pointCounter);
		return node;
	}
	else{
		setEnemySuccessful(true);
	}
	return NULL;
}

void EnemyBase::changeFinished()
{
	changeFinish=true;
	runFllowPoint();
}
//让敌人前进
void EnemyBase::runFllowPoint()
{
	if(changeRote)
	{
		changeFinish=false;
		Point originPoint=this->pointsVector.at(0)->getPosition();
		Point currPoint=sprite->getPosition();
		auto duration=currPoint.getDistance(originPoint)/300;
		sprite->runAction(Sequence::create(MoveTo::create(duration, originPoint)
			, CallFuncN::create(CC_CALLBACK_0(EnemyBase::changeFinished, this))
			, NULL));
		changeRote=false;
		pointCounter=0;
	}
	if(changeFinish==true)
	{
		//如果精灵未出现则在第一个对象点处建立精灵
		if (pointCounter == 0)
		{
			sprite->setPosition(currPoint()->getPosition());
		}
		auto point = pointsVector.at(pointCounter);
		//如果精灵位置和对象点位置重合则计算下一对象点
		if (sprite->getPosition().getDistance(point->getPosition()) == 0)
		{
			point = nextPoint();

		}
		//如果点不为空，则执行动作
		if (point != NULL){
			//使用了3种类型的action
			//1. MoveTo: 让敌人从一点移动到另一点，getRunSpeed()是移动过程花费的时间，point->getPosition()是移动地目标位置。
			//2. CallFuncN: 为某个执行此action的对象指定一个回调函数，这里的回调函数是：runFllowPoint本身。
			//   所以这个函数就会重复地调用自身，不断地判断计算得到下一个路径点，让敌人MoveTo到那个路径点地位置.
			//3. Sequence: 把一系列的action组成一个action序列，并且这些acton可以按顺序执行。一次执行完所有的action。
			auto duration = sprite->getPosition().getDistance(point->getPosition()) / getRunSpeed();
			sprite->stopAllActions();
			sprite->runAction(Sequence::create(MoveTo::create(duration, point->getPosition())
				, CallFuncN::create(CC_CALLBACK_0(EnemyBase::runFllowPoint, this))
				, NULL));
		}
	}
}


//void EnemyBase::setPointsVector(Vector<Node*> points)
//{
//	this->pointsVector = points;
//}

void EnemyBase::enemyReduceHp(int reduceHp)//减血
{
	currHp -= reduceHp;
	auto offHp = reduceHp * 100 / maxHp;
	hpPercentage -= offHp;
	if (hpPercentage < 0){
		hpPercentage = 0;
	}
	hpBar->setPercentage(hpPercentage);
}

void EnemyBase::enemyPoison(int poisonHpBullet, int poisonHpTimeBullet)//中毒
{
	poisonHp = poisonHpBullet;
	poisonHpTime = poisonHpTimeBullet;
	//重置中毒定时器
	unschedule(schedule_selector(EnemyBase::enemyPoison));
	schedule(schedule_selector(EnemyBase::enemyPoison), 1.0f, (poisonHpTime - 1), 1.0f);
	//延时1s后执行enemyPoison，并且重复调用(poisonHpTime-1)次
}


//减速
void  EnemyBase::enemySlow(int slowSpeed, int slowSpeedTime)
{
	//减速前速度为0，或者减速前速度=现在速度，则将敌人减速，并重新设置动作
	if (preSpeed == 0 || preSpeed == runSpeed)
	{
		preSpeed = runSpeed;
		runSpeed = runSpeed *(4 - slowSpeed) / 4;
		//在slowSpeedTime时间后，调用resumeSpeed恢复初始速度
		scheduleOnce(schedule_selector(EnemyBase::resumeSpeed), slowSpeedTime*1.0f);
		runFllowPoint();
	}
	else//其他情况（连续中减速弹）则重置定时器
	{
		unschedule(schedule_selector(EnemyBase::enemyPoison));
		scheduleOnce(schedule_selector(EnemyBase::resumeSpeed), slowSpeedTime*1.0f);
	}
}

//中毒
void  EnemyBase::enemyPoison(float dt)
{
	//中毒减血
	currHp -= poisonHp;
	auto offHp = poisonHp * 100 / getMaxHp();
	hpPercentage -= offHp;
	if (hpPercentage < 0)
	{
		hpPercentage = 0;
	}
	hpBar->setPercentage(hpPercentage);
	if (currHp <= 0)
	{
		unschedule(schedule_selector(EnemyBase::enemyPoison));
	}
}

//减速恢复
void  EnemyBase::resumeSpeed(float dt)
{
	if (currHp > 0)
	{
		runSpeed = preSpeed;
		runFllowPoint();
	}
}

