
#include "EvolveTowerPanelLayer.h"

bool EvolveTowerPanleLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	setEvolve1Tower(false);
	setEvolve2Tower(false);
	setSellTower(false);
	//setUpMoney(0);
	//setSellMoney(0);
	//��������
	TTFConfig ttfConfig;
	ttfConfig.fontFilePath = "fonts/msyhbd.ttf";
	ttfConfig.fontSize = 10;
	ttfConfig.distanceFieldEnabled = false;
	ttfConfig.outlineSize = 0;
	ttfConfig.glyphs = GlyphCollection::DYNAMIC;
	ttfConfig.customGlyphs = nullptr;


	//����������λ�ÿ��������飬���۾��飬������Ǯ�ı������۽�Ǯ�ı�
	auto sprite = Sprite::createWithSpriteFrameName("towerPos1.png");
	sprite->setPosition(Point(0, 0));
	this->addChild(sprite);


	sprite1 = Sprite::create("up.png");
	sprite1->setAnchorPoint(Point(0.5f, 0));
	sprite1->setPosition(Point(-sprite->getContentSize().width , sprite->getContentSize().height / 2));
	this->addChild(sprite1);


	evolve1MoneyLabel = Label::createWithTTF(ttfConfig, " ");
	evolve1MoneyLabel->setTextColor(Color4B::WHITE);
	evolve1MoneyLabel->setPosition(Point(-sprite->getContentSize().width, sprite->getContentSize().height / 2));
	evolve1MoneyLabel->setAnchorPoint(Point(0.5f, 0));
	this->addChild(evolve1MoneyLabel);


	sprite2 = Sprite::create("up.png");
	sprite2->setAnchorPoint(Point(0.5f, 0));
	sprite2->setPosition(Point(sprite->getContentSize().width, sprite->getContentSize().height / 2));
	this->addChild(sprite2);


	evolve2MoneyLabel = Label::createWithTTF(ttfConfig, " ");
	evolve2MoneyLabel->setTextColor(Color4B::WHITE);
	evolve2MoneyLabel->setPosition(Point(sprite->getContentSize().width, sprite->getContentSize().height / 2));
	evolve2MoneyLabel->setAnchorPoint(Point(0.5f, 0));
	this->addChild(evolve2MoneyLabel);


	sprite3 = Sprite::create("sell.png");
	//sprite2 = Sprite::createWithSpriteFrameName("sell.png");
	sprite3->setAnchorPoint(Point(0.5f, 1));
	sprite3->setPosition(Point(0 , -sprite->getContentSize().height / 2));
	this->addChild(sprite3);

	sellMoneyLabel = Label::createWithTTF(ttfConfig, " ");
	sellMoneyLabel->setTextColor(Color4B::WHITE);
	sellMoneyLabel->setPosition(Point(0, -sprite->getContentSize().height *1.5));
	sellMoneyLabel->setAnchorPoint(Point(0.5f, 0));
	this->addChild(sellMoneyLabel);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(EvolveTowerPanleLayer::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(EvolveTowerPanleLayer::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, sprite1);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), sprite2);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), sprite3);
	return true;
}

//����Ҵ�����ĳѡ��ʱ������������͸���ȣ�����ұ��������Ǳ�ѡ�еģ�
bool EvolveTowerPanleLayer::onTouchBegan(Touch *touch, Event *event)
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
void EvolveTowerPanleLayer::onTouchEnded(Touch* touch, Event* event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	if (target == sprite1)
	{
		setEvolve1Tower(true);
	}
	else if (target == sprite2)
	{
		setEvolve2Tower(true);
	}
	else if (target == sprite3)
	{
		setSellTower(true);
	}
	else{
		setEvolve1Tower(false);
		setEvolve2Tower(false);
		setSellTower(false);
	}
}

//�������ý�Ǯ�ı�
void EvolveTowerPanleLayer::setMoneyText(int evolve1Money, int evolve2Money, int sellMoney)
{

	auto sellMoneyText = std::to_string(sellMoney);
	auto evolve1MoneyText = std::to_string(evolve1Money);
	evolve1MoneyLabel->setString(evolve1MoneyText);
	auto evolve2MoneyText = std::to_string(evolve2Money);
	evolve2MoneyLabel->setString(evolve2MoneyText);
	sellMoneyLabel->setString(sellMoneyText);
}

//��ʾ���ķ�����Χ
void EvolveTowerPanleLayer::setScopeCircle(int scope)
{
	auto scopeSprite1 = Sprite::create("yuan.png");
	scopeSprite1->setScale((scope - 16) / 50.0);
	scopeSprite1->setOpacity(180);
	this->addChild(scopeSprite1, -1);
}


