

#include "CannonTower.h"
#include "GameManager.h"

bool CannonTower::init()
{
	if (!TowerBase::init())
	{
		return false;
	}

	setScope(130);//攻击范围
	setTowerValue(400);//塔价值
	setLethality(3);//杀伤力
	setRate(300);//子弹速度
	setTowerLevel(1);//防御塔等级
	setTowerUpValue(200);//升级价钱
	setTowerSellValue(200);//出售价钱
	setShootTime(1.2);//设置射击时间
	setTowerEvolve1Value(200);
	setTowerEvolve2Value(200);
	setTowerBombRange(30);
	setTowerBombHp(1);
	setTowerBombRange(30);
	setTowerBombHp(1);

	tower = Sprite::createWithSpriteFrameName("tower4_1.png");
	this->addChild(tower);

	schedule(schedule_selector(CannonTower::shoot), shootTime);
	return true;
}

//创建子弹
BulletBase* CannonTower::CannonTowerBullet()
{
	auto bullet = Bullet4::create();
	bullet->setPosition(tower->getPosition());
	bullet->setBulletLethality(lethality);
	if (towerEvolve1Level>0||towerEvolve2Level>0)
	{
		bullet->setBombRange(towerBombRange);
		bullet->setBombHp(towerBombHp);
	}	
	this->addChild(bullet);
	return bullet;
}

void CannonTower::shoot(float dt)
{
	GameManager *instance = GameManager::getInstance();
	auto bulletVector = instance->bulletVector;
	auto enemyVector = instance->enemyVector;
	//检测炮塔视线范围内距离羊村最近的敌人。
	checkNearestEnemy(enemyVector);
	//最近敌人存在，生命值不为0，则创建子弹，射向离羊村最近的敌人
	//计算子弹的执行MoveTo动作的两个参数
	if (nearestEnemy != NULL && nearestEnemy->getCurrHp() > 0)
	{
		auto currBullet = CannonTowerBullet();
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
			CallFuncN::create(CC_CALLBACK_1(CannonTower::removeBullet, this)),
			NULL));
		currBullet = NULL;
	}
}
//移除子弹，同时需要从bulletVector中去除
void CannonTower::removeBullet(Node* pSender)
{
	GameManager *instance = GameManager::getInstance();

	auto bulletVector = instance->bulletVector;

	BulletBase *sprite = (BulletBase *)pSender;
	instance->bulletVector.eraseObject(sprite);
	sprite->removeFromParent();
}

//出售防御塔
bool CannonTower::upTower()
{

	towerLevel++;//防御塔等级增加
	char buffer[20] = { 0 };
	sprintf(buffer, "_%i.png", towerLevel);
	std::string str1 = "tower4";
	std::string str = str1 + buffer;
	SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
	tower->setSpriteFrame(frame);//更换防御塔图片
	//属性增加
	scope = scope + 40;
	lethality = lethality + 2;
	//修改升级金钱和出售金钱
	towerSellValue += towerUpValue / 2;
	towerUpValue += 100;
	towerEvolve1Value = towerUpValue;
	towerEvolve2Value = towerUpValue;


	return true;

}
//出售防御塔
bool CannonTower::sellTower()
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

bool CannonTower::evolve1Tower()
{
	towerEvolve1Level++;
	if (towerEvolve1Level <= 2)
	{
		char buffer[20] = { 0 };
		sprintf(buffer, "_%i.png", towerEvolve1Level + 4);
		std::string str1 = "tower4";
		std::string str = str1 + buffer;
		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		tower->setSpriteFrame(frame);//更换防御塔图片
	}
	//属性增加
	towerBombRange += 35;
	//修改升级金钱和出售金钱
	towerSellValue += towerEvolve1Value / 2;
	towerEvolve1Value += 150;
	return true;
}
bool CannonTower::evolve2Tower()
{
	towerEvolve2Level++;
	//属性增加	
	towerBombHp += 4;
	//修改升级金钱和出售金钱
	towerSellValue += towerEvolve2Value / 2;
	towerEvolve2Value += 150;
	return true;
}

void CannonTower::updateShootTime()
{
	unschedule(schedule_selector(CannonTower::shoot));
	schedule(schedule_selector(CannonTower::shoot), shootTime);
}