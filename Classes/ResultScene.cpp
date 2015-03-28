#include "ResultScene.h"
#include "BlockScene.h"
#include "cocostudio/CocoStudio.h"
#include "extensions/cocos-ext.h" 
#include "LoadLevelInfo.h"
#include "PlayLayer.h"
#include <iostream>
//cocos2dx 3.x版本 CCControl更改为Control ，CCObject更改为Ref ！！！！！！


USING_NS_CC;
using namespace std;
using namespace extension;//Control类所需要声明的命名空间
using namespace cocostudio;
using namespace cocostudio::timeline;

//初始化静态资源项，作为全局变量引用

Button* ResultScene::retrybtn = new Button();
Button* ResultScene::leavebtn = new Button();
Button* ResultScene::nextbtn = new Button();
Sprite* ResultScene::starpic = new Sprite();


Scene* ResultScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = ResultScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool ResultScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	//加载资源文件生成根节点，对应场景图中的根节点
	auto rootNode = CSLoader::createNode("ResultScene.csb");
	this->addChild(rootNode);
	
	return true;
}




Layer* ResultScene::popFailure(){
	//加载资源文件生成图层
	Layer* failurelayer = (Layer*)CSLoader::createNode("FailureResultLayer.csb");

	//设置图层中心位置
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint pointCenter = ccp(winSize.width / 2 - 320, winSize.height / 2 - 240);
	failurelayer->setPosition(pointCenter);


	//获取图层中按钮对象
	retrybtn = (Button*)failurelayer->getChildByName("retry");
	leavebtn = (Button*)failurelayer->getChildByName("leave");



	//为按钮添加点击触发事件
	retrybtn->addTouchEventListener(CC_CALLBACK_2(ResultScene::retryTouchDown, this));
	leavebtn->addTouchEventListener(CC_CALLBACK_2(ResultScene::leaveTouchDown, this));


	return failurelayer;
}

Layer* ResultScene::popSuccess(){

	//加载资源文件生成图层
	Layer* successlayer = (Layer*)CSLoader::createNode("SuccessResultLayer.csb");

	//设置图层中心位置
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint pointCenter = ccp(winSize.width / 2 - 320, winSize.height / 2 - 240);
	successlayer->setPosition(pointCenter);

	//获取图层中按钮对象
	retrybtn = (Button*)successlayer->getChildByName("retry");
	leavebtn = (Button*)successlayer->getChildByName("leave");
	nextbtn = (Button*)successlayer->getChildByName("next");
	starpic = (Sprite*)successlayer->getChildByName("starpic");

	//获取本关所得星星数量
	char sn[10];
	sprintf(sn,"%d",UserDefault::getInstance()->getIntegerForKey("currStar"));
	string spic = sn;
	starpic->setTexture(spic+"star.png");

	//为按钮添加点击触发事件
	retrybtn->addTouchEventListener(CC_CALLBACK_2(ResultScene::retryTouchDown, this));
	leavebtn->addTouchEventListener(CC_CALLBACK_2(ResultScene::leaveTouchDown, this));
	nextbtn->addTouchEventListener(CC_CALLBACK_2(ResultScene::nextTouchDown, this));

	return successlayer;

}




void  ResultScene::retryTouchDown(Control::Ref* pSender, Widget::TouchEventType type){
	//获得当前关卡对应资源文件名
	string fileName = UserDefault::getInstance()->getStringForKey("currLevelFile");
	//根据按下类型进行响应
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		break;
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:
	{
	//载入关卡资源
	LoadLevelinfo::createLoadLevelinfo(fileName.c_str())->readLevelInfo();
	Director::getInstance()->replaceScene(TransitionFadeBL::create(0.1f, PlayLayer::createScene()));
	}
	case Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

//返回上一层响应函数
void  ResultScene::leaveTouchDown(Control::Ref* pSender, Widget::TouchEventType type){
	//跳转至相应图层
	auto blockscene = BlockScene::createScene();
	//重置图层数量
	Director::sharedDirector()->replaceScene(blockscene);
}

//开始下一关响应函数
void  ResultScene::nextTouchDown(Control::Ref* pSender, Widget::TouchEventType type){
	//获得当前关卡对应资源文件名
	string fileName = UserDefault::getInstance()->getStringForKey("nextLevelFile");
	//载入关卡资源
	LoadLevelinfo::createLoadLevelinfo(fileName.c_str())->readLevelInfo();
	Director::getInstance()->replaceScene(TransitionFadeBL::create(0.1f, PlayLayer::createScene()));
}
