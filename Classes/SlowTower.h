

#ifndef __SheepVillageDefense__SlowTower__
#define __SheepVillageDefense__SlowTower__

#include "TowerBase.h"
#include "UpTowerPanleLayer.h"
#include "Bullet.h"
//��������
class SlowTower :public TowerBase
{
public:

	virtual bool init();
	CREATE_FUNC(SlowTower);

	void shoot(float dt);//���
	void removeBullet(Node* pSender);//�Ƴ��ӵ��ڵ�
	BulletBase* slowTowerBullet();//�����ӵ�
	bool upTower();//����������
	bool sellTower();//���۷�����
	bool evolve1Tower();//����������1
	bool evolve2Tower();//����������2
	void updateShootTime();//���������ʱ��

private:
	Sprite* tower;//������
	CC_SYNTHESIZE(int, towerSlowSpeed, TowerSlowSpeed);   // ���������ٱ�����1,2,3�ֱ��Ӧ����1/4��2/4��3/4
	CC_SYNTHESIZE(int, towerSlowSpeedTime, TowerSlowSpeedTime);   // ����������ʱ��

};

#endif /* defined(__SheepVillageDefense__SlowTower__) */
