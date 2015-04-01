#include "ArrowTower.h"
#include "GameManager.h"

bool ArrowTower::init()
{
    if (!TowerBase::init())
	{
		return false;
	}
    
    setScope(90);//攻击范围
    setLethality(1);//杀伤力
	setTowerValue(200);//塔价值
    setRate(400);//子弹速度
	setTowerLevel(1);//防御塔等级
	setTowerUpValue(100);//升级价钱
	setTowerSellValue(100);//出售价钱
	setTowerEvolve1Value(100);
	setTowerEvolve2Value(100);
	dirTotal = 0;
	tower = Sprite::createWithSpriteFrameName("tower1_1.png");
	addChild(tower);
	schedule(schedule_selector(ArrowTower::shoot), shootTime);
	return true;
}

//创建子弹
BulletBase* ArrowTower::ArrowTowerBullet()
{
    auto bullet = Bullet1::create();
	bullet->setPosition(tower->getPosition());
	bullet->setBulletLethality(lethality); 
    addChild(bullet);   
    return bullet;
}
//射击
void ArrowTower::shoot(float dt)
{

    GameManager *instance = GameManager::getInstance();
	auto bulletVector = instance->bulletVector;
	auto enemyVector = instance->enemyVector;
	//检测炮塔视线范围内距离羊村最近的敌人。
	checkNearestEnemy(enemyVector);
	//最近敌人存在，生命值不为0，则创建子弹射向离羊村最近的敌人
	//计算子弹的执行MoveTo动作的两个参数
    if(nearestEnemy!=NULL && nearestEnemy->getCurrHp() > 0 )
    {

		//怪物和塔的角度
		auto moveDuration = (scope + 32) / rate;
		auto farthestDistance = scope + 32;
		Point normalizedShootVector;
		Point shootVector;
		if (towerEvolve1Level > 0)
		{
			for (int i = 0; i < dirTotal; i++)
			{
				auto currBullet = ArrowTowerBullet();
				instance->bulletVector.pushBack(currBullet);

				shootVector.x = 1;
				shootVector.y = tan(i * 2 * M_PI / dirTotal);
				shootVector.normalize();
				if (i >= dirTotal / 2)
				{
					normalizedShootVector = shootVector;
				}
				else{
					normalizedShootVector = -shootVector;
				}
				Point overshotVector = normalizedShootVector * farthestDistance;
				Point offscreenPoint = (currBullet->getPosition() - overshotVector);

				currBullet->runAction(Sequence::create(MoveTo::create(moveDuration, offscreenPoint),
					CallFuncN::create(CC_CALLBACK_1(ArrowTower::removeBullet, this)),
					NULL));
				currBullet = NULL;
			}
		}
		else 
		{
			auto currBullet = ArrowTowerBullet();
			instance->bulletVector.pushBack(currBullet);
			//currBullet->setBulletSpeed(rate);
			//currBullet->setTargetEnemy(nearestEnemy);
			//currBullet->setIsFollow(TRUE);
			shootVector = nearestEnemy->sprite->getPosition() - this->getPosition();
			shootVector.normalize();
			normalizedShootVector = -shootVector;
			Point overshotVector = normalizedShootVector * farthestDistance;
			Point offscreenPoint = (currBullet->getPosition() - overshotVector);

			currBullet->runAction(cocos2d::Sequence::create(MoveTo::create(moveDuration, offscreenPoint),
				CallFuncN::create(CC_CALLBACK_1(ArrowTower::removeBullet, this)),
				NULL));
			currBullet = NULL;
		}		
		}
    }
//移除子弹，同时需要从bulletVector中去除
void ArrowTower::removeBullet(Node* pSender)
{
	GameManager *instance = GameManager::getInstance();

	auto bulletVector = instance->bulletVector;

	BulletBase *sprite = (BulletBase *)pSender;
	instance->bulletVector.eraseObject(sprite);
	sprite->removeFromParent();
}


//出售防御塔
bool ArrowTower::upTower()
{

	towerLevel++;//防御塔等级增加
	char buffer[20] = { 0 };
	sprintf(buffer, "_%i.png", towerLevel);
	std::string str1 = "tower1";
	std::string str = str1 + buffer ;
	SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
	tower->setSpriteFrame(frame);//更换防御塔图片

	//属性增加
	scope=scope+30;
	lethality = lethality+1;
	//修改升级金钱和出售金钱
	towerSellValue += towerUpValue / 2;
	towerUpValue += 50;
	towerEvolve1Value = towerUpValue;
	towerEvolve2Value = towerUpValue;

	return true;

}

//出售防御塔
bool ArrowTower::sellTower()
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



bool ArrowTower::evolve1Tower()
{
	towerEvolve1Level++;
	if (towerEvolve1Level <= 2)
	{
		char buffer[20] = { 0 };
		sprintf(buffer, "_%i.png", towerEvolve1Level+4);
		std::string str1 = "tower1";
		std::string str = str1 + buffer;
		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		tower->setSpriteFrame(frame);//更换防御塔图片
	}
	//属性增加
	dirTotal += 4;
	//修改升级金钱和出售金钱
	towerSellValue += towerEvolve1Value / 2;
	towerEvolve1Value += 100;
	return true;
}
bool ArrowTower::evolve2Tower()
{
	towerEvolve2Level++;
	//属性增加
	lethality += 1;
	//修改升级金钱和出售金钱
	towerSellValue += towerEvolve2Value / 2;
	towerEvolve2Value += 100;
	return true;
}

//更新射击定时器
void ArrowTower::updateShootTime()
{
	unschedule(schedule_selector(ArrowTower::shoot));
	schedule(schedule_selector(ArrowTower::shoot), shootTime);
}
