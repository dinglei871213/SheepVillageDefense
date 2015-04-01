
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
	//设置字体
	TTFConfig ttfConfig;
	ttfConfig.fontFilePath = "fonts/msyhbd.ttf"; 
	ttfConfig.fontSize = 15;
	ttfConfig.distanceFieldEnabled = false;
	ttfConfig.outlineSize = 0;
	ttfConfig.glyphs = GlyphCollection::DYNAMIC;
	ttfConfig.customGlyphs = nullptr;


	//创建防御塔位置框，升级精灵，出售精灵，升级金钱文本，出售金钱文本
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

//当玩家触碰到某选项时，重新设置其透明度，向玩家表明该项是被选中的；
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

//当玩家松开手时，确定其选择是升级还是出售。
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

//重新设置金钱文本
void UpTowerPanleLayer::setMoneyText(int upMoney,int sellMoney)
{

	auto sellMoneyText = std::to_string(sellMoney);
	auto upMoneyText = std::to_string(upMoney);
	upMoneyLabel->setString(upMoneyText);
	sellMoneyLabel->setString(sellMoneyText);
}

//显示塔升级后的防御范围
void UpTowerPanleLayer::setUpScopeCircle(int upScopeCircle)
{
	auto scopeSprite2 = Sprite::create("yuan.png");
	scopeSprite2->setScale((upScopeCircle-16) / 50.0);
	this->addChild(scopeSprite2,-1);;
}
//显示塔的的防御范围
void UpTowerPanleLayer::setScopeCircle(int scope)
{
	auto scopeSprite1 = Sprite::create("yuan.png");
	scopeSprite1->setScale((scope-16) / 50.0);
	scopeSprite1->setOpacity(180);
	this->addChild(scopeSprite1,-1);
}


