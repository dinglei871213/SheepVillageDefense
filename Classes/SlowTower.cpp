#include "SlowTower.h"
#include "GameManager.h"

bool SlowTower::init()
{
	if (!TowerBase::init())
	{
		return false;
	}
	//设置塔的基础属性
	setScope(90);
	setLethality(1);//杀伤力
	setTowerValue(200);
	setRate(400);
	setTowerLevel(1);
	setTowerUpValue(100);
	setTowerSellValue(100);
	setTowerEvolve1Value(100);
	setTowerEvolve2Value(100);
	setTowerSlowSpeed(1);
	setTowerSlowSpeedTime(4);
	/*
	auto baseplate = Sprite::createWithSpriteFrameName("baseplate.png");
	addChild(baseplate);*/

	tower = Sprite::createWithSpriteFrameName("tower3_1.png");
	//rotateArrow->setPosition(0, baseplate->getContentSize().height /4  );
	addChild(tower);



	schedule(schedule_selector(SlowTower::shoot), shootTime);

	return true;
}


//创建子弹
BulletBase* SlowTower::slowTowerBullet()
{
	auto bullet = Bullet3::create();
	bullet->setPosition(tower->getPosition());
	bullet->setBulletLethality(lethality);
	//设置子弹特殊属性
	bullet->setSlowSpeed(towerSlowSpeed);
	bullet->setSlowSpeedTime(towerSlowSpeedTime);
	addChild(bullet);
	return bullet;
}

void SlowTower::shoot(float dt)
{
	GameManager *instance = GameManager::getInstance();
	auto bulletVector = instance->bulletVector;

	//检测炮塔视线范围内距离羊村最近的敌人。
	checkNearestEnemy();
	//最近敌人存在，生命值不为0，则创建子弹，射向离羊村最近的敌人
	//计算子弹的执行MoveTo动作的两个参数
	if (nearestEnemy != NULL && nearestEnemy->getCurrHp() > 0)
	{
		auto currBullet = slowTowerBullet();
		instance->bulletVector.pushBack(currBullet);
		auto moveDuration = (scope + 32) / rate;
		Point shootVector = nearestEnemy->sprite->getPosition() - this->getPosition();
		shootVector.normalize();
		Point normalizedShootVector = -shootVector;
		//子弹的最大射程长度为攻击距离+32
		auto farthestDistance = scope + 32;
		//最终位置 ＝ 起始位置 － 单位向量 * 射程长度
		Point overshotVector = normalizedShootVector * farthestDistance;
		Point offscreenPoint = (tower->getPosition() - overshotVector);

		currBullet->runAction(Sequence::create(MoveTo::create(moveDuration, offscreenPoint),
												CallFuncN::create(CC_CALLBACK_1(SlowTower::removeBullet, this)),
												NULL));
		currBullet = NULL;
	}
}
//移除子弹，同时需要从bulletVector中去除
void SlowTower::removeBullet(Node* pSender)
{
	GameManager *instance = GameManager::getInstance();

	auto bulletVector = instance->bulletVector;

	BulletBase *sprite = (BulletBase *)pSender;
	instance->bulletVector.eraseObject(sprite);
	sprite->removeFromParent();
}


//出售防御塔
bool SlowTower::upTower()
{

	towerLevel++;//防御塔等级增加
	char buffer[20] = { 0 };
	sprintf(buffer, "_%i.png", towerLevel);
	std::string str1 = "tower3";
	std::string str = str1 + buffer;
	SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
	tower->setSpriteFrame(frame);//更换防御塔图片
	//属性增加
	scope = scope + 30;
	lethality = lethality + 1;
	//修改升级金钱和出售金钱
	towerUpValue += 50;
	towerSellValue += 25;


	return true;

}
//出售防御塔
bool SlowTower::sellTower()
{
	GameManager *instance = GameManager::getInstance();
	//当出售防御塔时，需要同时去除防御塔和子弹及相关的bulletVector中的内容。
	auto bulletVector = instance->bulletVector;
	Vector<BulletBase*> bulletNeedToDelete;
	//检测与防御塔相关的子弹，并且把子弹存入bulletNeedToDelete
	for (int i = 0; i < bulletVector.size(); i++)
	{
		auto bullet = bulletVector.at(i);
		if (bullet->getParent()->getPosition() == this->getPosition())
		{
			bulletNeedToDelete.pushBack(bullet);
		}
	}
	//从bulletVector中去除bulletNeedToDelete中的子弹
	for (BulletBase* bulletTemp : bulletNeedToDelete)
	{
		instance->bulletVector.eraseObject(bulletTemp);
		bulletTemp->removeFromParent();
	}
	bulletNeedToDelete.clear();
	//去除防御塔精灵
	removeFromParent();
	return true;
}

bool SlowTower::evolve1Tower()
{
	towerEvolve1Level++;
	//属性增加
	towerSlowSpeed += 1;
	//修改升级金钱和出售金钱
	towerEvolve1Value += 0;
	towerSellValue += 50;
	return true;
}
bool SlowTower::evolve2Tower()
{
	towerEvolve2Level++;
	//属性增加
	towerSlowSpeedTime += 2;
	//修改升级金钱和出售金钱
	towerEvolve2Value += 0;
	towerSellValue += 50;
	return true;
}

