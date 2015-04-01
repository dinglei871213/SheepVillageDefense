

#include "CannonTower.h"
#include "GameManager.h"

bool CannonTower::init()
{
	if (!TowerBase::init())
	{
		return false;
	}

	setScope(130);//������Χ
	setTowerValue(400);//����ֵ
	setLethality(3);//ɱ����
	setRate(300);//�ӵ��ٶ�
	setTowerLevel(1);//�������ȼ�
	setTowerUpValue(200);//������Ǯ
	setTowerSellValue(200);//���ۼ�Ǯ
	setShootTime(1.2);//�������ʱ��
	setTowerEvolve1Value(200);
	setTowerEvolve2Value(200);
	setTowerBombRange(30);
	setTowerBombHp(1);
	setTowerBombRange(30);
	setTowerBombHp(1);

	tower = Sprite::createWithSpriteFrameName("tower4_1.png");
	this->addChild(tower);

	schedule(schedule_selector(CannonTower::shoot), shootTime);
	return true;
}

//�����ӵ�
BulletBase* CannonTower::CannonTowerBullet()
{
	auto bullet = Bullet4::create();
	bullet->setPosition(tower->getPosition());
	bullet->setBulletLethality(lethality);
	if (towerEvolve1Level>0||towerEvolve2Level>0)
	{
		bullet->setBombRange(towerBombRange);
		bullet->setBombHp(towerBombHp);
	}	
	this->addChild(bullet);
	return bullet;
}

void CannonTower::shoot(float dt)
{
	GameManager *instance = GameManager::getInstance();
	auto bulletVector = instance->bulletVector;
	auto enemyVector = instance->enemyVector;
	//����������߷�Χ�ھ����������ĵ��ˡ�
	checkNearestEnemy(enemyVector);
	//������˴��ڣ�����ֵ��Ϊ0���򴴽��ӵ����������������ĵ���
	//�����ӵ���ִ��MoveTo��������������
	if (nearestEnemy != NULL && nearestEnemy->getCurrHp() > 0)
	{
		auto currBullet = CannonTowerBullet();
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
			CallFuncN::create(CC_CALLBACK_1(CannonTower::removeBullet, this)),
			NULL));
		currBullet = NULL;
	}
}
//�Ƴ��ӵ���ͬʱ��Ҫ��bulletVector��ȥ��
void CannonTower::removeBullet(Node* pSender)
{
	GameManager *instance = GameManager::getInstance();

	auto bulletVector = instance->bulletVector;

	BulletBase *sprite = (BulletBase *)pSender;
	instance->bulletVector.eraseObject(sprite);
	sprite->removeFromParent();
}

//���۷�����
bool CannonTower::upTower()
{

	towerLevel++;//�������ȼ�����
	char buffer[20] = { 0 };
	sprintf(buffer, "_%i.png", towerLevel);
	std::string str1 = "tower4";
	std::string str = str1 + buffer;
	SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
	tower->setSpriteFrame(frame);//����������ͼƬ
	//��������
	scope = scope + 40;
	lethality = lethality + 2;
	//�޸�������Ǯ�ͳ��۽�Ǯ
	towerSellValue += towerUpValue / 2;
	towerUpValue += 100;
	towerEvolve1Value = towerUpValue;
	towerEvolve2Value = towerUpValue;


	return true;

}
//���۷�����
bool CannonTower::sellTower()
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

bool CannonTower::evolve1Tower()
{
	towerEvolve1Level++;
	if (towerEvolve1Level <= 2)
	{
		char buffer[20] = { 0 };
		sprintf(buffer, "_%i.png", towerEvolve1Level + 4);
		std::string str1 = "tower4";
		std::string str = str1 + buffer;
		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		tower->setSpriteFrame(frame);//����������ͼƬ
	}
	//��������
	towerBombRange += 35;
	//�޸�������Ǯ�ͳ��۽�Ǯ
	towerSellValue += towerEvolve1Value / 2;
	towerEvolve1Value += 150;
	return true;
}
bool CannonTower::evolve2Tower()
{
	towerEvolve2Level++;
	//��������	
	towerBombHp += 4;
	//�޸�������Ǯ�ͳ��۽�Ǯ
	towerSellValue += towerEvolve2Value / 2;
	towerEvolve2Value += 150;
	return true;
}

void CannonTower::updateShootTime()
{
	unschedule(schedule_selector(CannonTower::shoot));
	schedule(schedule_selector(CannonTower::shoot), shootTime);
}