#ifndef __SheepVillageDefense__TowerBase__
#define __SheepVillageDefense__TowerBase__
#include <iostream>
#include "cocos2d.h"
#include "EnemyBase.h"
#include "BulletBase.h"
#include "Tower.h"
//#include "InfoHandle.h"
using namespace std;
USING_NS_CC;
class TowerBase : public Sprite
{
public:
	TowerBase();

	virtual bool init();
	CREATE_FUNC(TowerBase);

	void checkNearestEnemy(Vector<EnemyBase*> enemyVector);

	CC_SYNTHESIZE(int, scope, Scope);  // 塔的视线范围
	CC_SYNTHESIZE(int, lethality, Lethality);   // 杀伤力
	CC_SYNTHESIZE(int, towerValue, TowerValue);  //塔的价钱
	CC_SYNTHESIZE(float, rate, Rate);//塔的子弹射击速度
	CC_SYNTHESIZE(float, shootTime, ShootTime);//塔的射击时间间隔


	CC_SYNTHESIZE(int, towerMaxLevel, TowerMaxLevel);   // 塔的最高等级
	CC_SYNTHESIZE(int, towerLevel, TowerLevel);   // 塔的等级
	CC_SYNTHESIZE(int, towerUpValue, TowerUpValue);  //塔的升级价钱
	CC_SYNTHESIZE(float, towerSellValue, TowerSellValue);//塔的出售价钱
	CC_SYNTHESIZE(float, towerEvolve1Value, TowerEvolve1Value);//塔的进化方向1价钱
	CC_SYNTHESIZE(float, towerEvolve2Value, TowerEvolve2Value);//塔的进化方向2价钱
	CC_SYNTHESIZE(int, towerMaxEvolveLevel, TowerMaxEvolveLevel);   // 塔的进化最高等级
	CC_SYNTHESIZE(int, towerEvolve1Level, TowerEvolve1Level);   // 塔的进化1等级
	CC_SYNTHESIZE(int, towerEvolve2Level, TowerEvolve2Level);   // 塔的进化1等级
	virtual bool upTower(){ return true; }
	virtual bool sellTower(){ return true; }
	virtual bool evolve1Tower(){ return true; }
	virtual bool evolve2Tower(){ return true; }
	virtual void updateShootTime(){ };
	void setTowerInfo(Tower tower);
protected:
	EnemyBase* nearestEnemy;    // 塔子视野内离羊村最近的敌人
};
#endif /* defined(__SheepVillageDefense__TowerBase__) */
