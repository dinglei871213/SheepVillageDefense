#include "LevelLayer.h"
#include <math.h>
#include "cocos2d.h"
#include "HelloWorldScene.h"
USING_NS_CC;

//用于滑动界面跳转
LevelLayer::LevelLayer()
:pageNode(0)
, curPageNode(0)
{
}

LevelLayer::~LevelLayer()
{
}


bool LevelLayer::init()
{
	this->setTouchEnabled(true);
	//this->setTouchMode(TouchDispatchMode::AllAtOnce);
	if (!Layer::init())
	{
		return false;
	}

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(LevelLayer::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(LevelLayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(LevelLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	WINDOW_WIDTH = Director::getInstance()->getWinSize().width;
	WINDOW_HEIGHT = Director::getInstance()->getWinSize().height;
	//WINDOW_WIDTH = 480;
	//WINDOW_HEIGHT = 320;

	return true;
}

//添加一个节点到LevelLayer上，节点大小固定，大小依次排开
void LevelLayer::addNode(Node* level){
	if (level)
	{
		level->setContentSize(Size::Size(WINDOW_WIDTH, WINDOW_HEIGHT));
		level->setPosition(Vec2(WINDOW_WIDTH * pageNode, 0));
		this->addChild(level);
		pageNode++;
	}
}

void LevelLayer::goToCurNode(){
	//跳转到当前子页面，为什么是负的？？
	this->runAction(MoveTo::create(0.4f,Vec2(-curPageNode*WINDOW_WIDTH, 0)));//持续的时间0.4f
}

bool LevelLayer::onTouchBegan(Touch* touch, Event* Event){
	touchDownPoint = touch->getLocation(); //触摸事件开始时记录下按下点
	touchCurPoint = touchDownPoint;
	return true;
}

void LevelLayer::onTouchMoved(Touch* touch, Event* event){
	Vec2 touchPoint = touch->getLocation();

	//touchPoint.X - touchCurPoint.X即滑动的距离
	auto currX = this->getPositionX() + touchPoint.x - touchCurPoint.x;
	Vec2 posPoint = Vec2(currX, getPositionY());

	//abs(int类型的绝对值)，fabs(double类型的绝对值)，fabsf(float类型的绝对值)
	auto dis = fabsf(touchPoint.x - touchCurPoint.x);

	//如果滑动的距离超过给出的最短滑动长度，那就设置LevelLayer的位置到移动的地方
	if (dis >= SHORTEST_SLIDE_LENGTH)
	{
		this->setPosition(posPoint);
	}
	touchCurPoint = touchPoint;
}

void LevelLayer::onTouchEnded(Touch* Touch, Event* Event){
	touchUpPoint = Touch->getLocation();
	auto dis = touchUpPoint.getDistance(touchDownPoint);
	auto sprite1 = Sprite::createWithSpriteFrameName("page_mark1.png");
	auto width = sprite1->getContentSize().width; 
	if (dis >= SHORTEST_SLIDE_LENGTH) 
	{   //在结束触摸时，同样记录抬起的点并计算按下点与抬起点的之间的距离
		//当这一距离大于给定的SHORTEST_SLIDE_LENGTH时，根据具体情况跳转到其他位置
		int offset = getPositionX() - curPageNode * (-WINDOW_WIDTH);
		if (offset > width){
			if (curPageNode > 0){
				--curPageNode;
				Sprite* sprite = (Sprite*)HelloWorld::getInstance()->getChildByTag(888);
				sprite->setPosition(Point(sprite->getPositionX() - width, sprite->getPositionY()));
			}
		}
		else if (offset < -width){
			if (curPageNode < (pageNode-1)){
				++curPageNode;
				Sprite* sprite = (Sprite*)HelloWorld::getInstance()->getChildByTag(888);
				sprite->setPosition(Point(sprite->getPositionX()+width, sprite->getPositionY()));
			}
		}
		//跳转到当前的子页面
		goToCurNode();
	}
}