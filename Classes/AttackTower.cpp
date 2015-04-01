

#include "AttackTower.h"
#include "GameManager.h"

bool AttackTower::init()
{
    if (!TowerBase::init())
	{
		return false;
	}
    
    setScope(90);
	setTowerValue(200);
    setLethality(1);
    setRate(2);
	setTowerLevel(1);
	setTowerUpValue(100);
	setTowerSellValue(75);
    tower= Sprite::createWithSpriteFrameName("tower1_1.png");
    this->addChild(tower);
    
    schedule(schedule_selector(AttackTower::shoot), 0.8f);
	return true;
}


BulletBase* AttackTower::AttackTowerBullet()
{
	auto bullet = Bullet2::create();
	bullet->setPosition(tower->getPosition());
	bullet->setBulletLethality(lethality);
	bullet->setPoisonHp(1);
	bullet->setPoisonHpTime(4);
    this->addChild(bullet);    
    return bullet;
}

void AttackTower::shoot(float dt)
{
    GameManager *instance = GameManager::getInstance();
    auto bulletVector = instance->bulletVector;

	auto enemyVector = instance->enemyVector;
	//检测炮塔视线范围内距离羊村最近的敌人。
	checkNearestEnemy(enemyVector);
    if(nearestEnemy!=NULL && nearestEnemy->getCurrHp() > 0 )
    {
        auto currBullet = AttackTowerBullet();
        instance->bulletVector.pushBack(currBullet);
        
        auto moveDuration = getRate();
        Point shootVector = nearestEnemy->sprite->getPosition() - this->getPosition();
		shootVector.normalize();
		Point normalizedShootVector = -shootVector;
        
        auto farthestDistance = Director::getInstance()->getWinSize().width;
		Point overshotVector = normalizedShootVector * farthestDistance;
		Point offscreenPoint = (tower->getPosition() - overshotVector);
        
		currBullet->runAction(Sequence::create(MoveTo::create(moveDuration, offscreenPoint),
                                               CallFuncN::create(CC_CALLBACK_1(AttackTower::removeBullet, this)),
                                               NULL));
        currBullet = NULL;
    }
}

void AttackTower::removeBullet(Node* pSender)
{
    GameManager *instance = GameManager::getInstance();
    
    auto bulletVector = instance->bulletVector;
    
	BulletBase *sprite = (BulletBase *)pSender;
    instance->bulletVector.eraseObject(sprite);
    sprite->removeFromParent();
}


bool AttackTower::upTower()
{

	towerLevel++;
	char buffer[20] = { 0 };
	sprintf(buffer, "_%i.png", towerLevel);
	std::string str1 = "tower1";
	std::string str = str1 + buffer;
	SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
	tower->setSpriteFrame(frame);


	setScope(120);
	setLethality(2);
	setRate(2);
	towerUpValue += 50;
	towerSellValue += 25;


	return true;

}

bool AttackTower::sellTower()
{
	GameManager *instance = GameManager::getInstance();
	auto bulletVector = instance->bulletVector;
	Vector<BulletBase*> bulletNeedToDelete;
	for (int i = 0; i < bulletVector.size(); i++)
	{
		auto bullet = bulletVector.at(i);
		if (bullet->getParent()->getPosition() == this->getPosition())
		{
			bulletNeedToDelete.pushBack(bullet);
		}
	}
	for (BulletBase* bulletTemp : bulletNeedToDelete)
	{
		instance->bulletVector.eraseObject(bulletTemp);
		bulletTemp->removeFromParent();
	}
	bulletNeedToDelete.clear();
	removeFromParent();
	return true;
}

