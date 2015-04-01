

#include "PoisonTower.h"
#include "GameManager.h"

bool PoisonTower::init()
{
    if (!TowerBase::init())
	{
		return false;
	}
    //���û�������
    setScope(90);
	setTowerValue(200);
    setLethality(1);
    setRate(400);
	setTowerLevel(1);
	setTowerUpValue(100);
	setTowerSellValue(75);
	setTowerEvolve1Value(100);
	setTowerEvolve2Value(100);
	setTowerPoisonHp(0);
	setTowerPoisonHpTime(2);
    tower= Sprite::createWithSpriteFrameName("tower2_1.png");
    this->addChild(tower);
    
    schedule(schedule_selector(PoisonTower::shoot), shootTime);
	return true;
}

//�����ӵ�
BulletBase* PoisonTower::PoisonTowerBullet()
{
	auto bullet = Bullet2::create();
	bullet->setPosition(tower->getPosition());
	bullet->setBulletLethality(lethality);
	//�����ӵ���������
	bullet->setPoisonHp(towerPoisonHp);
	bullet->setPoisonHpTime(towerPoisonHpTime);
    this->addChild(bullet);    
    return bullet;
}

void PoisonTower::shoot(float dt)
{
    GameManager *instance = GameManager::getInstance();
    auto bulletVector = instance->bulletVector;

	auto enemyVector = instance->enemyVector;
	//����������߷�Χ�ھ����������ĵ��ˡ�
	checkNearestEnemy(enemyVector);
	//������˴��ڣ�����ֵ��Ϊ0���򴴽��ӵ����������������ĵ���
	//�����ӵ���ִ��MoveTo��������������
    if(nearestEnemy!=NULL && nearestEnemy->getCurrHp() > 0 )
    {
        auto currBullet = PoisonTowerBullet();
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
                                               CallFuncN::create(CC_CALLBACK_1(PoisonTower::removeBullet, this)),
                                               NULL));
        currBullet = NULL;
    }
}
//�Ƴ��ӵ���ͬʱ��Ҫ��bulletVector��ȥ��
void PoisonTower::removeBullet(Node* pSender)
{
    GameManager *instance = GameManager::getInstance();
    
    auto bulletVector = instance->bulletVector;
    
	BulletBase *sprite = (BulletBase *)pSender;
    instance->bulletVector.eraseObject(sprite);
    sprite->removeFromParent();
}

//���۷�����
bool PoisonTower::upTower()
{

	towerLevel++;//�������ȼ�����
	char buffer[20] = { 0 };
	sprintf(buffer, "_%i.png", towerLevel);
	std::string str1 = "tower2";
	std::string str = str1 + buffer;
	SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
	tower->setSpriteFrame(frame);//����������ͼƬ

	//��������
	scope = scope + 30;
	lethality = lethality + 1;
	//�޸�������Ǯ�ͳ��۽�Ǯ
	towerSellValue += towerUpValue / 2;
	towerUpValue += 50;
	towerEvolve1Value = towerUpValue;
	towerEvolve2Value = towerUpValue;

	return true;

}
//���۷�����
bool PoisonTower::sellTower()
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

bool PoisonTower::evolve1Tower()
{
	towerEvolve1Level++;
	if (towerEvolve1Level <= 2)
	{
		char buffer[20] = { 0 };
		sprintf(buffer, "_%i.png", towerEvolve1Level + 4);
		std::string str1 = "tower2";
		std::string str = str1 + buffer;
		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		tower->setSpriteFrame(frame);//����������ͼƬ
	}
	//��������
	towerPoisonHpTime += 2;
	//�޸�������Ǯ�ͳ��۽�Ǯ
	towerSellValue += towerEvolve1Value / 2;
	towerEvolve1Value += 50;
	return true;
}
bool PoisonTower::evolve2Tower()
{
	towerEvolve2Level++;
	//��������
	towerPoisonHp += 1;
	//�޸�������Ǯ�ͳ��۽�Ǯ
	towerSellValue += towerEvolve2Value / 2;
	towerEvolve2Value += 50;
	return true;
}


void PoisonTower::updateShootTime()
{
	unschedule(schedule_selector(PoisonTower::shoot));
	schedule(schedule_selector(PoisonTower::shoot), shootTime);
}