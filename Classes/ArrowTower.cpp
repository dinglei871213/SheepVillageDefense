#include "ArrowTower.h"
#include "GameManager.h"

bool ArrowTower::init()
{
    if (!TowerBase::init())
	{
		return false;
	}
    
    setScope(90);//������Χ
    setLethality(1);//ɱ����
	setTowerValue(200);//����ֵ
    setRate(400);//�ӵ��ٶ�
	setTowerLevel(1);//�������ȼ�
	setTowerUpValue(100);//������Ǯ
	setTowerSellValue(100);//���ۼ�Ǯ
	setTowerEvolve1Value(100);
	setTowerEvolve2Value(100);
	dirTotal = 0;
	tower = Sprite::createWithSpriteFrameName("tower2_1.png");
	addChild(tower);
	schedule(schedule_selector(ArrowTower::shoot), shootTime);
	return true;
}

//�����ӵ�
BulletBase* ArrowTower::ArrowTowerBullet()
{
    auto bullet = Bullet1::create();
	bullet->setPosition(tower->getPosition());
	bullet->setBulletLethality(lethality); 
    addChild(bullet);   
    return bullet;
}
//���
void ArrowTower::shoot(float dt)
{

    GameManager *instance = GameManager::getInstance();
    auto bulletVector = instance->bulletVector;
	//����������߷�Χ�ھ����������ĵ���
	checkNearestEnemy();
	//������˴��ڣ�����ֵ��Ϊ0���򴴽��ӵ��������������ĵ���
	//�����ӵ���ִ��MoveTo��������������
    if(nearestEnemy!=NULL && nearestEnemy->getCurrHp() > 0 )
    {

		//��������ĽǶ�
		auto moveDuration = (scope + 32) / rate;
		auto farthestDistance = scope + 32;
		Point normalizedShootVector;
		Point shootVector;
		if (towerEvolve1Level > 0)
		{
			for (int i = 0; i < dirTotal; i++)
			{
				auto currBullet = ArrowTowerBullet();
				instance->bulletVector.pushBack(currBullet);

				shootVector.x = 1;
				shootVector.y = tan(i * 2 * M_PI / dirTotal);
				shootVector.normalize();
				if (i >= dirTotal / 2)
				{
					normalizedShootVector = shootVector;
				}
				else{
					normalizedShootVector = -shootVector;
				}
				Point overshotVector = normalizedShootVector * farthestDistance;
				Point offscreenPoint = (currBullet->getPosition() - overshotVector);

				currBullet->runAction(Sequence::create(MoveTo::create(moveDuration, offscreenPoint),
					CallFuncN::create(CC_CALLBACK_1(ArrowTower::removeBullet, this)),
					NULL));
				currBullet = NULL;
			}
		}
		else 
		{
			auto currBullet = ArrowTowerBullet();
			instance->bulletVector.pushBack(currBullet);
			//currBullet->setBulletSpeed(rate);
			//currBullet->setTargetEnemy(nearestEnemy);
			//currBullet->setIsFollow(TRUE);
			shootVector = nearestEnemy->sprite->getPosition() - this->getPosition();
			shootVector.normalize();
			normalizedShootVector = -shootVector;
			Point overshotVector = normalizedShootVector * farthestDistance;
			Point offscreenPoint = (currBullet->getPosition() - overshotVector);

			currBullet->runAction(cocos2d::Sequence::create(MoveTo::create(moveDuration, offscreenPoint),
				CallFuncN::create(CC_CALLBACK_1(ArrowTower::removeBullet, this)),
				NULL));
			currBullet = NULL;
		}		
		}
    }
//�Ƴ��ӵ���ͬʱ��Ҫ��bulletVector��ȥ��
void ArrowTower::removeBullet(Node* pSender)
{
	GameManager *instance = GameManager::getInstance();

	auto bulletVector = instance->bulletVector;

	BulletBase *sprite = (BulletBase *)pSender;
	instance->bulletVector.eraseObject(sprite);
	sprite->removeFromParent();
}


//���۷�����
bool ArrowTower::upTower()
{

	towerLevel++;//�������ȼ�����
	char buffer[20] = { 0 };
	sprintf(buffer, "_%i.png", towerLevel);
	std::string str1 = "tower2";
	std::string str = str1 + buffer ;
	SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
	tower->setSpriteFrame(frame);//����������ͼƬ

	//��������
	scope=scope+30;
	lethality = lethality+1;
	//�޸�������Ǯ�ͳ��۽�Ǯ
	towerUpValue+=0;
	towerSellValue+=50;


	return true;

}

//���۷�����
bool ArrowTower::sellTower()
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



bool ArrowTower::evolve1Tower()
{
	towerEvolve1Level++;
	//��������
	dirTotal += 4;
	//�޸�������Ǯ�ͳ��۽�Ǯ
	towerEvolve1Value += 0;
	towerSellValue += 50;
	return true;
}
bool ArrowTower::evolve2Tower()
{
	towerEvolve2Level++;
	//��������
	lethality += 1;
	//�޸�������Ǯ�ͳ��۽�Ǯ
	towerEvolve2Value += 0;
	towerSellValue += 50;
	return true;
}

