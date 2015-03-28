

#ifndef __SheepVillageDefense__ArrowTower__
#define __SheepVillageDefense__ArrowTower__

#include "TowerBase.h"
#include "UpTowerPanleLayer.h"
#include "Bullet.h"
//������
class ArrowTower:public TowerBase
{
public:
    
    virtual bool init() ;
    CREATE_FUNC(ArrowTower);

    //void rotateAndShoot(float dt);//��ת�������ȴ����
	void shoot(float dt);//���
    void removeBullet(Node* pSender);//�Ƴ��ӵ��ڵ�
    BulletBase* ArrowTowerBullet();//�����ӵ�
	bool upTower();//����������
	bool sellTower();//���۷�����
	bool evolve1Tower();//����������1
	bool evolve2Tower();//����������2
    
private:
    Sprite* tower;//������
	int dirTotal;//�����ӵ���
};

#endif /* defined(__SheepVillageDefense__ArrowTower__) */
