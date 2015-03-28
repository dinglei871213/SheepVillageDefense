
#include "TowerPanleLayer.h"

bool TowerPanleLayer::init()
{
    if (!Layer::init())
	{
		return false;
	}
    setChooseTowerType(TowerType::ANOTHER);
	//创建5个精灵，分别是防御塔位置框、箭塔、中毒塔、减速塔、炮塔
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
	// 创建事件监听器
    auto touchListener = EventListenerTouchOneByOne::create();
	// 设置是否向下传递触摸，true表示不向下触摸。
	touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(TowerPanleLayer::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(TowerPanleLayer::onTouchEnded, this);
	//为每个选项绑定触摸事件
	//当我们再次使用事件监听器的时候，需要使用 clone() 方法重新克隆一个，
	//因为每个监听器在添加到事件调度器中时，都会为其添加一个已注册的标记，这就使得它不能够被添加多次
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, sprite1);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), sprite2);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), sprite3);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), sprite4);
	return true;
}

//当玩家触碰到某选项时，重新设置其透明度，向玩家表明该项是被选中的；
bool TowerPanleLayer::onTouchBegan(Touch *touch, Event *event)
{
	//返回触摸事件当前作用的目标节点。
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	//把touch对象中保存的屏幕坐标转换到GL坐标，再转换到目标节点的本地坐标下。 
	//convertTouchToNodeSpace这个函数可以把屏幕坐标系转换到GL坐标系，再转换到父节点的本地坐标下。
    Point locationInNode = target->convertTouchToNodeSpace(touch);
	//计算目标节点的矩形区域。
    Size size = target->getContentSize();
    Rect rect = Rect(0, 0, size.width, size.height);
	//判断触碰点在不在目标节点的矩形区域内，即判断是否被选中。
    if (rect.containsPoint(locationInNode))
    {
        target->setOpacity(180);
        return true;
    }
    return false;
}

//当玩家松开手时，确定其选择的炮塔类型，方便我们后面的获取和使用。
void TowerPanleLayer::onTouchEnded(Touch* touch, Event* event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	//根据选择的目标确定炮塔的类型。
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

