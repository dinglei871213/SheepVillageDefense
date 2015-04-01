#include "BulletBase.h"


bool BulletBase::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	setBulletLethality(0);
	setSlowSpeed(0);
	setSlowSpeedTime(0);
	setPoisonHp(0);
	setPoisonHpTime(0);
	setBombRange(0);
	setBombHp(0); 
	setToDelete(false);
	setIsFollow(false);
	setTargetEnemy(NULL);
	//schedule(schedule_selector(BulletBase::followEnemy), 0.1f);
	return true;
}



void BulletBase::followEnemy(float dt)
{
	if (isFollow)
	{
		if (targetEnemy->getCurrHp() > 0)
		{
			auto point1 = targetEnemy->sprite->getPosition();
			auto point2 = this->getParent()->getPosition();
			auto point3 = this->getPosition();

			Point shootVector = targetEnemy->sprite->getPosition() - this->getParent()->getPosition();
			shootVector.normalize();
			Point normalizedShootVector = -shootVector;
			//����λ�� �� ��ʼλ�� �� ��λ���� * ��̳���
			Point overshotVector = normalizedShootVector *  bulletSpeed * 0.4;
			Point offscreenPoint = (this->getPosition() - overshotVector);

			/*auto point = targetEnemy->sprite->getPosition(); 
			auto point1 = this->getPosition();
			auto point2 = this->getParent()->getPosition();
			auto point3 = point1 + point2;
			auto kkk = point3.getDistance(point);
			auto moveDuration = point3.getDistance(point) / bulletSpeed;*/
			this->runAction(Sequence::create(MoveTo::create(0.4, offscreenPoint),
				CallFuncN::create(CC_CALLBACK_0(BulletBase::bulletToDelet, this)),
				NULL));
		}
		else
		{
			setIsFollow(false);
		}
	}
}

void BulletBase::reduceProperty(EnemyBase* reduceEnemy)
{
	//��Ѫ
	reduceEnemy->enemyReduceHp(bulletLethality);
	//����
	if (slowSpeed > 0){
		reduceEnemy->enemySlow(slowSpeed, slowSpeedTime);
	}
	//�ж�
	if (poisonHp > 0)
	{
		reduceEnemy->enemyPoison(poisonHp, poisonHpTime);
	}
}

void BulletBase::bulletToDelet()
{
	toDelete = true;
}



