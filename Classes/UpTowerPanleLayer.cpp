
#include "UpTowerPanleLayer.h"

bool UpTowerPanleLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	setUpTower(false);
	setSellTower(false);
	//setUpMoney(0);
	//setSellMoney(0);
	//��������
	TTFConfig ttfConfig;
	ttfConfig.fontFilePath = "fonts/msyhbd.ttf"; 
	ttfConfig.fontSize = 15;
	ttfConfig.distanceFieldEnabled = false;
	ttfConfig.outlineSize = 0;
	ttfConfig.glyphs = GlyphCollection::DYNAMIC;
	ttfConfig.customGlyphs = nullptr;


	//����������λ�ÿ��������飬���۾��飬������Ǯ�ı������۽�Ǯ�ı�
	auto sprite = Sprite::createWithSpriteFrameName("towerPos1.png");
	sprite->setPosition(Point(0, 0));
	this->addChild(sprite);

	//sprite1 = Sprite::createWithSpriteFrameName("up.png");
	sprite1 = Sprite::createWithSpriteFrameName("up.png");
	sprite1->setAnchorPoint(Point(0.5f, 0));
	sprite1->setPosition(Point(-sprite->getContentSize().width, -sprite->getContentSize().height/2));
	this->addChild(sprite1);


	upMoneyLabel = Label::createWithTTF(ttfConfig, " ");
	upMoneyLabel->setTextColor(Color4B::WHITE);
	upMoneyLabel->setPosition(Point(-sprite->getContentSize().width, -sprite->getContentSize().height / 2));
	upMoneyLabel->setAnchorPoint(Point(0.5f, 0));
	this->addChild(upMoneyLabel);


	sprite2 = Sprite::createWithSpriteFrameName("sell.png");
	//sprite2 = Sprite::createWithSpriteFrameName("sell.png");
	sprite2->setAnchorPoint(Point(0.5f, 0));
	sprite2->setPosition(Point(sprite->getContentSize().width, -sprite->getContentSize().height / 2));
	this->addChild(sprite2);

	sellMoneyLabel = Label::createWithTTF(ttfConfig, " ");
	sellMoneyLabel->setTextColor(Color4B::WHITE);
	sellMoneyLabel->setPosition(Point(sprite->getContentSize().width, -sprite->getContentSize().height / 2));
	sellMoneyLabel->setAnchorPoint(Point(0.5f, 0));
	this->addChild(sellMoneyLabel);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(UpTowerPanleLayer::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(UpTowerPanleLayer::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, sprite1);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), sprite2);
	return true;
}

//����Ҵ�����ĳѡ��ʱ������������͸���ȣ�����ұ��������Ǳ�ѡ�еģ�
bool UpTowerPanleLayer::onTouchBegan(Touch *touch, Event *event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());

	Point locationInNode = target->convertTouchToNodeSpace(touch);
	Size size = target->getContentSize();
	Rect rect = Rect(0, 0, size.width, size.height);

	if (rect.containsPoint(locationInNode))
	{
		target->setOpacity(180);
		return true;
	}
	return false;
}

//������ɿ���ʱ��ȷ����ѡ�����������ǳ��ۡ�
void UpTowerPanleLayer::onTouchEnded(Touch* touch, Event* event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	if (target == sprite1)
	{
		setUpTower(true);
	}
	else if (target == sprite2)
	{
		setSellTower(true);
	} 
	else{
		setUpTower(false);
		setSellTower(false);
	}
}

//�������ý�Ǯ�ı�
void UpTowerPanleLayer::setMoneyText(int upMoney,int sellMoney)
{

	auto sellMoneyText = std::to_string(sellMoney);
	auto upMoneyText = std::to_string(upMoney);
	upMoneyLabel->setString(upMoneyText);
	sellMoneyLabel->setString(sellMoneyText);
}

//��ʾ��������ķ�����Χ
void UpTowerPanleLayer::setUpScopeCircle(int upScopeCircle)
{
	auto scopeSprite2 = Sprite::create("yuan.png");
	scopeSprite2->setScale((upScopeCircle-16) / 50.0);
	this->addChild(scopeSprite2,-1);;
}
//��ʾ���ĵķ�����Χ
void UpTowerPanleLayer::setScopeCircle(int scope)
{
	auto scopeSprite1 = Sprite::create("yuan.png");
	scopeSprite1->setScale((scope-16) / 50.0);
	scopeSprite1->setOpacity(180);
	this->addChild(scopeSprite1,-1);
}


