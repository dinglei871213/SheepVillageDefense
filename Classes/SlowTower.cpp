#include "SlowTower.h"
#include "GameManager.h"

bool SlowTower::init()
{
	if (!TowerBase::init())
	{
		return false;
	}
	//�������Ļ�������
	setScope(90);
	setLethality(1);//ɱ����
	setTowerValue(200);
	setRate(400);
	setTowerLevel(1);
	setTowerUpValue(100);
	setTowerSellValue(100);
	setTowerEvolve1Value(100);
	setTowerEvolve2Value(100);
	setTowerSlowSpeed(1);
	setTowerSlowSpeedTime(4);
	/*
	auto baseplate = Sprite::createWithSpriteFrameName("baseplate.png");
	addChild(baseplate);*/

	tower = Sprite::createWithSpriteFrameName("tower3_1.png");
	//rotateArrow->setPosition(0, baseplate->getContentSize().height /4  );
	addChild(tower);



	schedule(schedule_selector(SlowTower::shoot), shootTime);

	return true;
}


//�����ӵ�
BulletBase* SlowTower::slowTowerBullet()
{
	auto bullet = Bullet3::create();
	bullet->setPosition(tower->getPosition());
	bullet->setBulletLethality(lethality);
	//�����ӵ���������
	bullet->setSlowSpeed(towerSlowSpeed);
	bullet->setSlowSpeedTime(towerSlowSpeedTime);
	addChild(bullet);
	return bullet;
}

void SlowTower::shoot(float dt)
{
	GameManager *instance = GameManager::getInstance();
	auto bulletVector = instance->bulletVector;

	//����������߷�Χ�ھ����������ĵ��ˡ�
	checkNearestEnemy();
	//������˴��ڣ�����ֵ��Ϊ0���򴴽��ӵ����������������ĵ���
	//�����ӵ���ִ��MoveTo��������������
	if (nearestEnemy != NULL && nearestEnemy->getCurrHp() > 0)
	{
		auto currBullet = slowTowerBullet();
		instance->bulletVector.pushBack(currBullet);
		auto moveDuration = (scope + 32) / rate;
		Point shootVector = nearestEnemy->sprite->getPosition() - this->getPosition();
		shootVector.normalize();
		Point normalizedShootVector = -shootVector;
		//�ӵ��������̳���Ϊ��������+32
		auto farthestDistance = scope + 32;
		//����λ�� �� ��ʼλ�� �� ��λ���� * ��̳���
		Point overshotVector = normalizedShootVector * farthestDistance;
		Point offscreenPoint = (tower->getPosition() - overshotVector);

		currBullet->runAction(Sequence::create(MoveTo::create(moveDuration, offscreenPoint),
												CallFuncN::create(CC_CALLBACK_1(SlowTower::removeBullet, this)),
												NULL));
		currBullet = NULL;
	}
}
//�Ƴ��ӵ���ͬʱ��Ҫ��bulletVector��ȥ��
void SlowTower::removeBullet(Node* pSender)
{
	GameManager *instance = GameManager::getInstance();

	auto bulletVector = instance->bulletVector;

	BulletBase *sprite = (BulletBase *)pSender;
	instance->bulletVector.eraseObject(sprite);
	sprite->removeFromParent();
}


//���۷�����
bool SlowTower::upTower()
{

	towerLevel++;//�������ȼ�����
	char buffer[20] = { 0 };
	sprintf(buffer, "_%i.png", towerLevel);
	std::string str1 = "tower3";
	std::string str = str1 + buffer;
	SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
	tower->setSpriteFrame(frame);//����������ͼƬ
	//��������
	scope = scope + 30;
	lethality = lethality + 1;
	//�޸�������Ǯ�ͳ��۽�Ǯ
	towerUpValue += 50;
	towerSellValue += 25;


	return true;

}
//���۷�����
bool SlowTower::sellTower()
{
	GameManager *instance = GameManager::getInstance();
	//�����۷�����ʱ����Ҫͬʱȥ�����������ӵ�����ص�bulletVector�е����ݡ�
	auto bulletVector = instance->bulletVector;
	Vector<BulletBase*> bulletNeedToDelete;
	//������������ص��ӵ������Ұ��ӵ�����bulletNeedToDelete
	for (int i = 0; i < bulletVector.size(); i++)
	{
		auto bullet = bulletVector.at(i);
		if (bullet->getParent()->getPosition() == this->getPosition())
		{
			bulletNeedToDelete.pushBack(bullet);
		}
	}
	//��bulletVector��ȥ��bulletNeedToDelete�е��ӵ�
	for (BulletBase* bulletTemp : bulletNeedToDelete)
	{
		instance->bulletVector.eraseObject(bulletTemp);
		bulletTemp->removeFromParent();
	}
	bulletNeedToDelete.clear();
	//ȥ������������
	removeFromParent();
	return true;
}

bool SlowTower::evolve1Tower()
{
	towerEvolve1Level++;
	//��������
	towerSlowSpeed += 1;
	//�޸�������Ǯ�ͳ��۽�Ǯ
	towerEvolve1Value += 0;
	towerSellValue += 50;
	return true;
}
bool SlowTower::evolve2Tower()
{
	towerEvolve2Level++;
	//��������
	towerSlowSpeedTime += 2;
	//�޸�������Ǯ�ͳ��۽�Ǯ
	towerEvolve2Value += 0;
	towerSellValue += 50;
	return true;
}

