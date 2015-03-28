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
//����Ѫ��
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

//��������
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
//��õ��˵�ǰ������·����
Node* EnemyBase::currPoint()
{
	//��������(vector)��λ��Ϊ'pointCounter'��Ԫ��
	if(pointsVector.size() > 0){
		return this->pointsVector.at(pointCounter);
	}else{
		return NULL;
	}
}
//������һ���ƶ���
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
//�õ���ǰ��
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
		//�������δ�������ڵ�һ������㴦��������
		if (pointCounter == 0)
		{
			sprite->setPosition(currPoint()->getPosition());
		}
		auto point = pointsVector.at(pointCounter);
		//�������λ�úͶ����λ���غ��������һ�����
		if (sprite->getPosition().getDistance(point->getPosition()) == 0)
		{
			point = nextPoint();

		}
		//����㲻Ϊ�գ���ִ�ж���
		if (point != NULL){
			//ʹ����3�����͵�action
			//1. MoveTo: �õ��˴�һ���ƶ�����һ�㣬getRunSpeed()���ƶ����̻��ѵ�ʱ�䣬point->getPosition()���ƶ���Ŀ��λ�á�
			//2. CallFuncN: Ϊĳ��ִ�д�action�Ķ���ָ��һ���ص�����������Ļص������ǣ�runFllowPoint����
			//   ������������ͻ��ظ��ص����������ϵ��жϼ���õ���һ��·���㣬�õ���MoveTo���Ǹ�·�����λ��.
			//3. Sequence: ��һϵ�е�action���һ��action���У�������Щacton���԰�˳��ִ�С�һ��ִ�������е�action��
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

void EnemyBase::enemyReduceHp(int reduceHp)//��Ѫ
{
	currHp -= reduceHp;
	auto offHp = reduceHp * 100 / maxHp;
	hpPercentage -= offHp;
	if (hpPercentage < 0){
		hpPercentage = 0;
	}
	hpBar->setPercentage(hpPercentage);
}

void EnemyBase::enemyPoison(int poisonHpBullet, int poisonHpTimeBullet)//�ж�
{
	poisonHp = poisonHpBullet;
	poisonHpTime = poisonHpTimeBullet;
	//�����ж���ʱ��
	unschedule(schedule_selector(EnemyBase::enemyPoison));
	schedule(schedule_selector(EnemyBase::enemyPoison), 1.0f, (poisonHpTime - 1), 1.0f);
	//��ʱ1s��ִ��enemyPoison�������ظ�����(poisonHpTime-1)��
}


//����
void  EnemyBase::enemySlow(int slowSpeed, int slowSpeedTime)
{
	//����ǰ�ٶ�Ϊ0�����߼���ǰ�ٶ�=�����ٶȣ��򽫵��˼��٣����������ö���
	if (preSpeed == 0 || preSpeed == runSpeed)
	{
		preSpeed = runSpeed;
		runSpeed = runSpeed *(4 - slowSpeed) / 4;
		//��slowSpeedTimeʱ��󣬵���resumeSpeed�ָ���ʼ�ٶ�
		scheduleOnce(schedule_selector(EnemyBase::resumeSpeed), slowSpeedTime*1.0f);
		runFllowPoint();
	}
	else//��������������м��ٵ��������ö�ʱ��
	{
		unschedule(schedule_selector(EnemyBase::enemyPoison));
		scheduleOnce(schedule_selector(EnemyBase::resumeSpeed), slowSpeedTime*1.0f);
	}
}

//�ж�
void  EnemyBase::enemyPoison(float dt)
{
	//�ж���Ѫ
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

//���ٻָ�
void  EnemyBase::resumeSpeed(float dt)
{
	if (currHp > 0)
	{
		runSpeed = preSpeed;
		runFllowPoint();
	}
}

