#ifndef __SheepVillageDefense__CannonTower__
#define __SheepVillageDefense__CannonTower__

#include "TowerBase.h"
#include "UpTowerPanleLayer.h"
#include "Bullet.h"

//������
class CannonTower :public TowerBase
{
public:

	virtual bool init();
	CREATE_FUNC(CannonTower);

	void shoot(float dt);//���
	void removeBullet(Node* pSender);//�Ƴ��ӵ��ڵ�
	BulletBase* CannonTowerBullet();//�����ӵ�
	bool upTower();//����������
	bool sellTower();//���۷�����
	bool evolve1Tower();//����������1
	bool evolve2Tower();//����������2

private:
	Sprite* tower;//������
	CC_SYNTHESIZE(int, towerBombRange, TowerBombRange);   // ��������Ѫ��
	CC_SYNTHESIZE(int, towerBombHp, TowerBombHp);   // ��������Ѫʱ��

};

#endif /* defined(__SheepVillageDefense__CannonTower__) */
