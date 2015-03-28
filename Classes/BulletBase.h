#ifndef __SheepVillageDefense__BulletBase__
#define __SheepVillageDefense__BulletBase__
#include <iostream>
#include "cocos2d.h"
//#include "GameManager.h"
#include "EnemyBase.h"

USING_NS_CC;
//子弹基类
class BulletBase : public Sprite
{
public:
	virtual bool init();
	CREATE_FUNC(BulletBase);
	void followEnemy(float dt);
	void reduceProperty(EnemyBase* reduceEnemy);
	void bulletToDelet();

protected:
	//CC_SYNTHESIZE(int, bulletScope, BulletScope);  // 子弹范围
	CC_SYNTHESIZE(int, bulletLethality, BulletLethality);   // 子弹杀伤力
	CC_SYNTHESIZE(int, slowSpeed, SlowSpeed);  // 子弹减速
	CC_SYNTHESIZE(int, slowSpeedTime, SlowSpeedTime);  // 子弹减速时间
	CC_SYNTHESIZE(int, poisonHp, PoisonHp);  // 子弹中毒减血量
	CC_SYNTHESIZE(int, poisonHpTime, PoisonHpTime);  // 子弹中毒时间
	CC_SYNTHESIZE(Sprite *, bulletSprite, BulletSprite);  // 子弹
	CC_SYNTHESIZE(int, bombRange, BombRange);  // 子弹爆炸范围
	CC_SYNTHESIZE(int, bombHp, BombHp);  // 子弹爆炸减血量
	CC_SYNTHESIZE(EnemyBase*, targetEnemy, TargetEnemy);  // 目标敌人
	CC_SYNTHESIZE(int, bulletSpeed, BulletSpeed);  // 子弹速度
	CC_SYNTHESIZE(bool, toDelete, ToDelete);  // 需要被删除
	CC_SYNTHESIZE(bool, isFollow, IsFollow);  // 是否跟踪

};
#endif /* defined(__SheepVillageDefense__BulletBase__) */
