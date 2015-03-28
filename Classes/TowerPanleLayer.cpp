
#include "TowerPanleLayer.h"

bool TowerPanleLayer::init()
{
    if (!Layer::init())
	{
		return false;
	}
    setChooseTowerType(TowerType::ANOTHER);
	//����5�����飬�ֱ��Ƿ�����λ�ÿ򡢼������ж�����������������
    auto sprite = Sprite::createWithSpriteFrameName("towerPos1.png");
    sprite->setPosition(Point(0, 0));
    this->addChild(sprite);
    
    sprite1 = Sprite::createWithSpriteFrameName("tower2_1.png");
	sprite1->setAnchorPoint( Point(0.5f, 0));
    sprite1->setPosition(Point(-sprite->getContentSize().width, sprite->getContentSize().height/2));
    this->addChild(sprite1);
    
    sprite2 = Sprite::createWithSpriteFrameName("tower1_1.png");
	sprite2->setAnchorPoint( Point(0.5f, 0));
	sprite2->setPosition(Point(sprite->getContentSize().width, sprite->getContentSize().height / 2));
    this->addChild(sprite2);
    
	sprite3 = Sprite::createWithSpriteFrameName("tower3_1.png");
	sprite3->setAnchorPoint( Point(0.5f, 1));
    sprite3->setPosition(Point(-sprite->getContentSize().width, -sprite->getContentSize().height/2));
    this->addChild(sprite3);

	sprite4 = Sprite::createWithSpriteFrameName("tower4_1.png");
	sprite4->setAnchorPoint(Point(0.5f, 1));
	sprite4->setPosition(Point(sprite->getContentSize().width, -sprite->getContentSize().height / 2));
	this->addChild(sprite4);
	// �����¼�������
    auto touchListener = EventListenerTouchOneByOne::create();
	// �����Ƿ����´��ݴ�����true��ʾ�����´�����
	touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(TowerPanleLayer::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(TowerPanleLayer::onTouchEnded, this);
	//Ϊÿ��ѡ��󶨴����¼�
	//�������ٴ�ʹ���¼���������ʱ����Ҫʹ�� clone() �������¿�¡һ����
	//��Ϊÿ������������ӵ��¼���������ʱ������Ϊ�����һ����ע��ı�ǣ����ʹ�������ܹ�����Ӷ��
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, sprite1);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), sprite2);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), sprite3);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), sprite4);
	return true;
}

//����Ҵ�����ĳѡ��ʱ������������͸���ȣ�����ұ��������Ǳ�ѡ�еģ�
bool TowerPanleLayer::onTouchBegan(Touch *touch, Event *event)
{
	//���ش����¼���ǰ���õ�Ŀ��ڵ㡣
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	//��touch�����б������Ļ����ת����GL���꣬��ת����Ŀ��ڵ�ı��������¡� 
	//convertTouchToNodeSpace����������԰���Ļ����ϵת����GL����ϵ����ת�������ڵ�ı��������¡�
    Point locationInNode = target->convertTouchToNodeSpace(touch);
	//����Ŀ��ڵ�ľ�������
    Size size = target->getContentSize();
    Rect rect = Rect(0, 0, size.width, size.height);
	//�жϴ������ڲ���Ŀ��ڵ�ľ��������ڣ����ж��Ƿ�ѡ�С�
    if (rect.containsPoint(locationInNode))
    {
        target->setOpacity(180);
        return true;
    }
    return false;
}

//������ɿ���ʱ��ȷ����ѡ����������ͣ��������Ǻ���Ļ�ȡ��ʹ�á�
void TowerPanleLayer::onTouchEnded(Touch* touch, Event* event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	//����ѡ���Ŀ��ȷ�����������͡�
	if (target == sprite1)
    {
        chooseTowerType = ARROW_TOWER;
    }
    else if(target == sprite2)
    {
		chooseTowerType = POISON_TOWER;
    }
	else if(target == sprite3)
    {
		chooseTowerType = SLOW_TOWER;
	}
	else if (target == sprite4)
	{
		chooseTowerType = CANNON_TOWER;
	}
    else{
        chooseTowerType = ANOTHER;
    }
}

