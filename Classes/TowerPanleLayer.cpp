
#include "TowerPanleLayer.h"

bool TowerPanleLayer::init()
{
    if (!Layer::init())
	{
		return false;
	}
    setChooseTowerType(TowerType::ANOTHER);
	TTFConfig ttfConfig;
	ttfConfig.fontFilePath = "fonts/msyhbd.ttf";
	ttfConfig.fontSize = 15;
	ttfConfig.distanceFieldEnabled = false;
	ttfConfig.outlineSize = 0;
	ttfConfig.glyphs = GlyphCollection::DYNAMIC;
	ttfConfig.customGlyphs = nullptr;
	//����5�����飬�ֱ��Ƿ�����λ�ÿ򡢼������ж�����������������
    auto sprite = Sprite::createWithSpriteFrameName("towerPos1.png");
    sprite->setPosition(Point(0, 0));
    this->addChild(sprite);

	/*auto spriteCircle = Sprite::createWithSpriteFrameName("circle.png");
	spriteCircle->setPosition(Point(0, 0));
	this->addChild(spriteCircle);*/

    //��ʾ������1����ͼ�Ǯ
    sprite1 = Sprite::createWithSpriteFrameName("tower1.png");
	sprite1->setAnchorPoint( Point(0.5f, 0));
    sprite1->setPosition(Point(-sprite->getContentSize().width, sprite->getContentSize().height/2));
    this->addChild(sprite1);

	tower1MoneyLabel = Label::createWithTTF(ttfConfig, " ");
	tower1MoneyLabel->setTextColor(Color4B::WHITE);
	tower1MoneyLabel->setPosition(Point(-sprite->getContentSize().width, sprite->getContentSize().height / 2));
	tower1MoneyLabel->setAnchorPoint(Point(0.5f, 0));
	this->addChild(tower1MoneyLabel);


	//��ʾ������2����ͼ�Ǯ
    sprite2 = Sprite::createWithSpriteFrameName("tower2.png");
	sprite2->setAnchorPoint( Point(0.5f, 0));
	sprite2->setPosition(Point(sprite->getContentSize().width, sprite->getContentSize().height / 2));
    this->addChild(sprite2);

	tower2MoneyLabel = Label::createWithTTF(ttfConfig, " ");
	tower2MoneyLabel->setTextColor(Color4B::WHITE);
	tower2MoneyLabel->setPosition(Point(sprite->getContentSize().width, sprite->getContentSize().height / 2));
	tower2MoneyLabel->setAnchorPoint(Point(0.5f, 0));
	this->addChild(tower2MoneyLabel);


	//��ʾ������3����ͼ�Ǯ
	sprite3 = Sprite::createWithSpriteFrameName("tower3.png");
	sprite3->setAnchorPoint( Point(0.5f, 1));
    sprite3->setPosition(Point(-sprite->getContentSize().width, -sprite->getContentSize().height/2));
    this->addChild(sprite3);

	tower3MoneyLabel = Label::createWithTTF(ttfConfig, " ");
	tower3MoneyLabel->setTextColor(Color4B::WHITE);
	tower3MoneyLabel->setPosition(Point(-sprite->getContentSize().width, -sprite->getContentSize().height*1.5));
	tower3MoneyLabel->setAnchorPoint(Point(0.5f, 0));
	this->addChild(tower3MoneyLabel);

	//��ʾ������4����ͼ�Ǯ
	sprite4 = Sprite::createWithSpriteFrameName("tower4.png");
	sprite4->setAnchorPoint(Point(0.5f, 1));
	sprite4->setPosition(Point(sprite->getContentSize().width, -sprite->getContentSize().height / 2));
	this->addChild(sprite4);

	tower4MoneyLabel = Label::createWithTTF(ttfConfig, " ");
	tower4MoneyLabel->setTextColor(Color4B::WHITE);
	tower4MoneyLabel->setPosition(Point(sprite->getContentSize().width, -sprite->getContentSize().height *1.5));
	tower4MoneyLabel->setAnchorPoint(Point(0.5f, 0));
	this->addChild(tower4MoneyLabel);
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




void TowerPanleLayer::setMoneyText(int tower1Money, int tower2Money, int tower3Money, int tower4Money)
{
	auto tower1MoneyText = std::to_string(tower1Money); 
	auto tower2MoneyText = std::to_string(tower2Money);
	auto tower3MoneyText = std::to_string(tower3Money);
	auto tower4MoneyText = std::to_string(tower4Money);
	tower1MoneyLabel->setString(tower1MoneyText);
	tower2MoneyLabel->setString(tower2MoneyText);
	tower3MoneyLabel->setString(tower3MoneyText);
	tower4MoneyLabel->setString(tower4MoneyText);
}