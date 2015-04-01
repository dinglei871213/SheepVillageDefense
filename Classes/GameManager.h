
#ifndef __SheepVillageDefense__GameManager__
#define __SheepVillageDefense__GameManager__

#include <iostream>
#include "cocos2d.h"
#include "EnemyBase.h"
#include "TowerBase.h"
#include "GroupEnemy.h"
#include "BulletBase.h"
#include "InfoHandle.h"


USING_NS_CC;

class GameManager
{
public:
    
	Vector<EnemyBase*> enemyVector;
	Vector<BulletBase*> bulletVector;//×Óµ¯
    Vector<TowerBase*> towerVector;
    Vector<GroupEnemy*> groupVector;
    
	CC_SYNTHESIZE(int, money, Money);
	CC_SYNTHESIZE(int, groupNum, GroupNum);
	CC_SYNTHESIZE(std::string, curMapName, CurMapName);
	CC_SYNTHESIZE(std::string, currLevelFile, CurrLevelFile);
	CC_SYNTHESIZE(std::string, nextLevelFile, NextLevelFile);
	CC_SYNTHESIZE(int, currBlock, CurrBlock);
	CC_SYNTHESIZE(int, currStar, CurrStar);
	CC_SYNTHESIZE(bool, isFinishedAddGroup, IsFinishedAddGroup);
	CC_SYNTHESIZE(std::string, curBgName, CurBgName);
	CC_SYNTHESIZE(bool, effectOn, EffectOn);
    
    bool init();
	void clear();
    
	static GameManager* getInstance();
	void setTowerInfo();


	Tower towerInfo[8];
	Wolf wolfInfo[8];
    
private:
	static GameManager * instance;
};
#endif /* defined(__thiefTD__GameManager__) */
