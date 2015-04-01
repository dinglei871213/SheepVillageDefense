#ifndef __SheepVillageDefense__PoisonTower__
#define __SheepVillageDefense__PoisonTower__

#include "TowerBase.h"
#include "UpTowerPanleLayer.h"
#include "Bullet.h"
//��������
class PoisonTower:public TowerBase
{
public:
    
    virtual bool init() ;
	CREATE_FUNC(PoisonTower);

	void shoot(float dt);//���
	void removeBullet(Node* pSender);//�Ƴ��ӵ��ڵ�
	BulletBase* PoisonTowerBullet();//�����ӵ�
	bool upTower();//����������
	bool sellTower();//���۷�����
	bool evolve1Tower();//����������1
	bool evolve2Tower();//����������2
	void updateShootTime();//���������ʱ��

private:
	Sprite* tower;//������
	CC_SYNTHESIZE(int, towerPoisonHp, TowerPoisonHp);   // ��������Ѫ��
	CC_SYNTHESIZE(int, towerPoisonHpTime, TowerPoisonHpTime);   // ��������Ѫʱ��
    
};

#endif /* defined(__SheepVillageDefense__PoisonTower__) */
