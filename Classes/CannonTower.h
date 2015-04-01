#ifndef __SheepVillageDefense__CannonTower__
#define __SheepVillageDefense__CannonTower__

#include "TowerBase.h"
#include "UpTowerPanleLayer.h"
#include "Bullet.h"

//炮塔类
class CannonTower :public TowerBase
{
public:

	virtual bool init();
	CREATE_FUNC(CannonTower);

	void shoot(float dt);//射击
	void removeBullet(Node* pSender);//移除子弹节点
	BulletBase* CannonTowerBullet();//创建子弹
	bool upTower();//升级防御塔
	bool sellTower();//出售防御塔
	bool evolve1Tower();//防御塔进化1
	bool evolve2Tower();//防御塔进化2
	void updateShootTime();//更新射击定时器

private:
	Sprite* tower;//塔精灵
	CC_SYNTHESIZE(int, towerBombRange, TowerBombRange);   // 毒气塔减血量
	CC_SYNTHESIZE(int, towerBombHp, TowerBombHp);   // 毒气塔减血时间

};

#endif /* defined(__SheepVillageDefense__CannonTower__) */
