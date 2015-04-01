

#ifndef __SheepVillageDefense__SlowTower__
#define __SheepVillageDefense__SlowTower__

#include "TowerBase.h"
#include "UpTowerPanleLayer.h"
#include "Bullet.h"
//减速塔类
class SlowTower :public TowerBase
{
public:

	virtual bool init();
	CREATE_FUNC(SlowTower);

	void shoot(float dt);//射击
	void removeBullet(Node* pSender);//移除子弹节点
	BulletBase* slowTowerBullet();//创建子弹
	bool upTower();//升级防御塔
	bool sellTower();//出售防御塔
	bool evolve1Tower();//防御塔进化1
	bool evolve2Tower();//防御塔进化2
	void updateShootTime();//更新射击定时器

private:
	Sprite* tower;//塔精灵
	CC_SYNTHESIZE(int, towerSlowSpeed, TowerSlowSpeed);   // 减速塔减速比例，1,2,3分别对应减速1/4，2/4和3/4
	CC_SYNTHESIZE(int, towerSlowSpeedTime, TowerSlowSpeedTime);   // 减速塔减速时间

};

#endif /* defined(__SheepVillageDefense__SlowTower__) */
