

#ifndef __SheepVillageDefense__MultiDirTower__
#define __SheepVillageDefense__MultiDirTower__

#include "TowerBase.h"
#include "Bullet.h"

class MultiDirTower:public TowerBase
{
public:
    
    virtual bool init() ;
    CREATE_FUNC(MultiDirTower);
    
    void shoot(float dt);
    void removeBullet(Node* pSender);
	BulletBase* MultiDirTowerBullet();
    void createBullet6(float dt);
private:
    Sprite* tower;
    
};

#endif /* defined(__SheepVillageDefense__MultiDirTower__) */
