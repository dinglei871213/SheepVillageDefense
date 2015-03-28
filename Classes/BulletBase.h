#ifndef __SheepVillageDefense__BulletBase__
#define __SheepVillageDefense__BulletBase__
#include <iostream>
#include "cocos2d.h"
//#include "GameManager.h"
#include "EnemyBase.h"

USING_NS_CC;
//�ӵ�����
class BulletBase : public Sprite
{
public:
	virtual bool init();
	CREATE_FUNC(BulletBase);
	void followEnemy(float dt);
	void reduceProperty(EnemyBase* reduceEnemy);
	void bulletToDelet();

protected:
	//CC_SYNTHESIZE(int, bulletScope, BulletScope);  // �ӵ���Χ
	CC_SYNTHESIZE(int, bulletLethality, BulletLethality);   // �ӵ�ɱ����
	CC_SYNTHESIZE(int, slowSpeed, SlowSpeed);  // �ӵ�����
	CC_SYNTHESIZE(int, slowSpeedTime, SlowSpeedTime);  // �ӵ�����ʱ��
	CC_SYNTHESIZE(int, poisonHp, PoisonHp);  // �ӵ��ж���Ѫ��
	CC_SYNTHESIZE(int, poisonHpTime, PoisonHpTime);  // �ӵ��ж�ʱ��
	CC_SYNTHESIZE(Sprite *, bulletSprite, BulletSprite);  // �ӵ�
	CC_SYNTHESIZE(int, bombRange, BombRange);  // �ӵ���ը��Χ
	CC_SYNTHESIZE(int, bombHp, BombHp);  // �ӵ���ը��Ѫ��
	CC_SYNTHESIZE(EnemyBase*, targetEnemy, TargetEnemy);  // Ŀ�����
	CC_SYNTHESIZE(int, bulletSpeed, BulletSpeed);  // �ӵ��ٶ�
	CC_SYNTHESIZE(bool, toDelete, ToDelete);  // ��Ҫ��ɾ��
	CC_SYNTHESIZE(bool, isFollow, IsFollow);  // �Ƿ����

};
#endif /* defined(__SheepVillageDefense__BulletBase__) */
