#ifndef __SheepVillageDefense__PoisonTower__
#define __SheepVillageDefense__PoisonTower__

#include "TowerBase.h"
#include "UpTowerPanleLayer.h"
#include "Bullet.h"
//毒气塔类
class PoisonTower:public TowerBase
{
public:
    
    virtual bool init() ;
	CREATE_FUNC(PoisonTower);

	void shoot(float dt);//射击
	void removeBullet(Node* pSender);//移除子弹节点
	BulletBase* PoisonTowerBullet();//创建子弹
	bool upTower();//升级防御塔
	bool sellTower();//出售防御塔
	bool evolve1Tower();//防御塔进化1
	bool evolve2Tower();//防御塔进化2

private:
	Sprite* tower;//塔精灵
	CC_SYNTHESIZE(int, towerPoisonHp, TowerPoisonHp);   // 毒气塔减血量
	CC_SYNTHESIZE(int, towerPoisonHpTime, TowerPoisonHpTime);   // 毒气塔减血时间
    
};

#endif /* defined(__SheepVillageDefense__PoisonTower__) */
