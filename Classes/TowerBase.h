#ifndef __SheepVillageDefense__TowerBase__
#define __SheepVillageDefense__TowerBase__
#include <iostream>
#include "cocos2d.h"
#include "EnemyBase.h"
#include "Bullet.h"
USING_NS_CC;
class TowerBase : public Sprite
{
public:
	TowerBase();

	virtual bool init();
	CREATE_FUNC(TowerBase);

	void checkNearestEnemy();

	CC_SYNTHESIZE(int, scope, Scope);  // �������߷�Χ
	CC_SYNTHESIZE(int, lethality, Lethality);   // ɱ����
	CC_SYNTHESIZE(int, towerValue, TowerValue);  //���ļ�Ǯ
	CC_SYNTHESIZE(float, rate, Rate);//�����ӵ�����ٶ�
	CC_SYNTHESIZE(float, shootTime, ShootTime);//�������ʱ����


	CC_SYNTHESIZE(int, towerMaxLevel, TowerMaxLevel);   // ������ߵȼ�
	CC_SYNTHESIZE(int, towerLevel, TowerLevel);   // ���ĵȼ�
	CC_SYNTHESIZE(int, towerUpValue, TowerUpValue);  //����������Ǯ
	CC_SYNTHESIZE(float, towerSellValue, TowerSellValue);//���ĳ��ۼ�Ǯ
	CC_SYNTHESIZE(float, towerEvolve1Value, TowerEvolve1Value);//���Ľ�������1��Ǯ
	CC_SYNTHESIZE(float, towerEvolve2Value, TowerEvolve2Value);//���Ľ�������2��Ǯ
	CC_SYNTHESIZE(int, towerMaxEvolveLevel, TowerMaxEvolveLevel);   // ���Ľ�����ߵȼ�
	CC_SYNTHESIZE(int, towerEvolve1Level, TowerEvolve1Level);   // ���Ľ���1�ȼ�
	CC_SYNTHESIZE(int, towerEvolve2Level, TowerEvolve2Level);   // ���Ľ���1�ȼ�
	virtual bool upTower(){ return true; }
	virtual bool sellTower(){ return true; }
	virtual bool evolve1Tower(){ return true; }
	virtual bool evolve2Tower(){ return true; }
protected:
	EnemyBase* nearestEnemy;    // ������Ұ�����������ĵ���
};
#endif /* defined(__SheepVillageDefense__TowerBase__) */
