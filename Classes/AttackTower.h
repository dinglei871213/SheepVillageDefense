#ifndef __SheepVillageDefense__AttackTowerTower__
#define __SheepVillageDefense__AttackTowerTower__

#include "TowerBase.h"
#include "UpTowerPanleLayer.h"
#include "Bullet.h"

class AttackTower:public TowerBase
{
public:
    
    virtual bool init() ;
    CREATE_FUNC(AttackTower);

    void shoot(float dt);
    void removeBullet(Node* pSender);
	BulletBase* AttackTowerBullet();
	bool upTower();
	bool sellTower();
    
private:
    Sprite* tower;
    
};

#endif /* defined(__SheepVillageDefense__AttackTower__) */
