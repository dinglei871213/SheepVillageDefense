#include "TowerBase.h"
#include "GameManager.h"

TowerBase::TowerBase()
:scope(0)
,towerValue(0)
,lethality(0)
,rate(0)
,nearestEnemy(NULL)
,towerLevel(1)
,towerUpValue(0)
,towerSellValue(0)
,towerMaxLevel(3)
,shootTime(0.8)
,towerEvolve1Value(0)
, towerEvolve2Value(0)
, towerMaxEvolveLevel(2)
, towerEvolve1Level(0)
, towerEvolve2Level(0)
{
}

bool TowerBase::init()
{
	if (!Sprite::init())
	{
		return false;
	}
    //scheduleUpdate();
	return true;
}

//������������ĵ���
void TowerBase::checkNearestEnemy()
{
    GameManager *instance = GameManager::getInstance();
    auto enemyVector = instance->enemyVector;
	auto pointCounter = 0;
	auto currMinDistant = this->scope;

	Node* currPoint = NULL;
    
    EnemyBase *enemyTemp = NULL;
	for(int i = 0; i < enemyVector.size(); i++)
	{
		auto enemy = enemyVector.at(i);
		double distance = this->getPosition().getDistance(enemy->sprite->getPosition());      
		if (distance < scope) {
			if (pointCounter < enemy->getPointCounter())
			{
				pointCounter = enemy->getPointCounter();
				currPoint = enemy->getPointsVector().at(pointCounter);
				currMinDistant = currPoint->getPosition().getDistance(enemy->sprite->getPosition());
				enemyTemp = enemy;
			}
			else if (pointCounter = enemy->getPointCounter())
			{
				if (currMinDistant > currPoint->getPosition().getDistance(enemy->sprite->getPosition()))
				{ 
					currMinDistant = currPoint->getPosition().getDistance(enemy->sprite->getPosition());
					enemyTemp = enemy;
				}

			}
		}
	}
    nearestEnemy = enemyTemp;
}








