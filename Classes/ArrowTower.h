

#ifndef __SheepVillageDefense__ArrowTower__
#define __SheepVillageDefense__ArrowTower__

#include "TowerBase.h"
#include "UpTowerPanleLayer.h"
#include "Bullet.h"
//箭塔类
class ArrowTower:public TowerBase
{
public:
    
    virtual bool init() ;
    CREATE_FUNC(ArrowTower);

    //void rotateAndShoot(float dt);//旋转弓箭，等待射击
	void shoot(float dt);//射击
    void removeBullet(Node* pSender);//移除子弹节点
    BulletBase* ArrowTowerBullet();//创建子弹
	bool upTower();//升级防御塔
	bool sellTower();//出售防御塔
	bool evolve1Tower();//防御塔进化1
	bool evolve2Tower();//防御塔进化2
    
private:
    Sprite* tower;//塔精灵
	int dirTotal;//发射子弹数
};

#endif /* defined(__SheepVillageDefense__ArrowTower__) */
