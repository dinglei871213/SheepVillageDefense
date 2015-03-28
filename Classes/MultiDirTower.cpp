

#include "MultiDirTower.h"
#include "GameManager.h"
#include <algorithm>

bool MultiDirTower::init()
{
    if (!TowerBase::init())
	{
		return false;
	}
    
    setScope(60);
	setTowerValue(600);
    setLethality(0.5);
    setRate(3);
    tower= Sprite::createWithSpriteFrameName("tower3_1.png");
    this->addChild(tower);
    
    this->schedule(schedule_selector(MultiDirTower::createBullet6), 0.8f);
	return true;
}


BulletBase* MultiDirTower::MultiDirTowerBullet()
{
	auto bullet = BulletBase::create();
    bullet->setPosition(0, tower->getContentSize().height /2 );
    this->addChild(bullet);
    
    return bullet;
}

void MultiDirTower::createBullet6(float dt)
{
	GameManager *instance = GameManager::getInstance();
    auto bulletVector = instance->bulletVector;
    int dirTotal = 10;
	this->checkNearestEnemy();
	if(nearestEnemy != NULL && nearestEnemy->getCurrHp() > 0 )
    {
		for(int i = 0; i < dirTotal; i++)
		{
			auto currBullet = MultiDirTowerBullet();
			instance->bulletVector.pushBack(currBullet);
            
			auto moveDuration = getRate();
            
			Point shootVector;
			shootVector.x = 1;
			shootVector.y = tan( i * 2 * M_PI / dirTotal );
			Point normalizedShootVector;
			shootVector.normalize();
			if( i >= dirTotal / 2 )
			{
				normalizedShootVector = shootVector;
			}else{
				normalizedShootVector = -shootVector;
			}
			auto farthestDistance = Director::getInstance()->getWinSize().width;
			Point overshotVector = normalizedShootVector * farthestDistance;
			Point offscreenPoint = (currBullet->getPosition() - overshotVector);
            
			currBullet->runAction(Sequence::create(MoveTo::create(moveDuration, offscreenPoint),
												   CallFuncN::create(CC_CALLBACK_1(MultiDirTower::removeBullet, this)),
												   NULL));
			currBullet = NULL;
		}
	}
}


void MultiDirTower::removeBullet(Node* pSender)
{
    GameManager *instance = GameManager::getInstance();
    auto bulletVector = instance->bulletVector;
    
	BulletBase *sprite = (BulletBase *)pSender;
    instance->bulletVector.eraseObject(sprite);
    sprite->removeFromParent();
}