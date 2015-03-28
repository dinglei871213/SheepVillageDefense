#include "ResultScene.h"
#include "BlockScene.h"
#include "cocostudio/CocoStudio.h"
#include "extensions/cocos-ext.h" 
#include "LoadLevelInfo.h"
#include "PlayLayer.h"
#include <iostream>
//cocos2dx 3.x�汾 CCControl����ΪControl ��CCObject����ΪRef ������������


USING_NS_CC;
using namespace std;
using namespace extension;//Control������Ҫ�����������ռ�
using namespace cocostudio;
using namespace cocostudio::timeline;

//��ʼ����̬��Դ���Ϊȫ�ֱ�������

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

	//������Դ�ļ����ɸ��ڵ㣬��Ӧ����ͼ�еĸ��ڵ�
	auto rootNode = CSLoader::createNode("ResultScene.csb");
	this->addChild(rootNode);
	
	return true;
}




Layer* ResultScene::popFailure(){
	//������Դ�ļ�����ͼ��
	Layer* failurelayer = (Layer*)CSLoader::createNode("FailureResultLayer.csb");

	//����ͼ������λ��
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint pointCenter = ccp(winSize.width / 2 - 320, winSize.height / 2 - 240);
	failurelayer->setPosition(pointCenter);


	//��ȡͼ���а�ť����
	retrybtn = (Button*)failurelayer->getChildByName("retry");
	leavebtn = (Button*)failurelayer->getChildByName("leave");



	//Ϊ��ť��ӵ�������¼�
	retrybtn->addTouchEventListener(CC_CALLBACK_2(ResultScene::retryTouchDown, this));
	leavebtn->addTouchEventListener(CC_CALLBACK_2(ResultScene::leaveTouchDown, this));


	return failurelayer;
}

Layer* ResultScene::popSuccess(){

	//������Դ�ļ�����ͼ��
	Layer* successlayer = (Layer*)CSLoader::createNode("SuccessResultLayer.csb");

	//����ͼ������λ��
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint pointCenter = ccp(winSize.width / 2 - 320, winSize.height / 2 - 240);
	successlayer->setPosition(pointCenter);

	//��ȡͼ���а�ť����
	retrybtn = (Button*)successlayer->getChildByName("retry");
	leavebtn = (Button*)successlayer->getChildByName("leave");
	nextbtn = (Button*)successlayer->getChildByName("next");
	starpic = (Sprite*)successlayer->getChildByName("starpic");

	//��ȡ����������������
	char sn[10];
	sprintf(sn,"%d",UserDefault::getInstance()->getIntegerForKey("currStar"));
	string spic = sn;
	starpic->setTexture(spic+"star.png");

	//Ϊ��ť��ӵ�������¼�
	retrybtn->addTouchEventListener(CC_CALLBACK_2(ResultScene::retryTouchDown, this));
	leavebtn->addTouchEventListener(CC_CALLBACK_2(ResultScene::leaveTouchDown, this));
	nextbtn->addTouchEventListener(CC_CALLBACK_2(ResultScene::nextTouchDown, this));

	return successlayer;

}




void  ResultScene::retryTouchDown(Control::Ref* pSender, Widget::TouchEventType type){
	//��õ�ǰ�ؿ���Ӧ��Դ�ļ���
	string fileName = UserDefault::getInstance()->getStringForKey("currLevelFile");
	//���ݰ������ͽ�����Ӧ
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		break;
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:
	{
	//����ؿ���Դ
	LoadLevelinfo::createLoadLevelinfo(fileName.c_str())->readLevelInfo();
	Director::getInstance()->replaceScene(TransitionFadeBL::create(0.1f, PlayLayer::createScene()));
	}
	case Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

//������һ����Ӧ����
void  ResultScene::leaveTouchDown(Control::Ref* pSender, Widget::TouchEventType type){
	//��ת����Ӧͼ��
	auto blockscene = BlockScene::createScene();
	//����ͼ������
	Director::sharedDirector()->replaceScene(blockscene);
}

//��ʼ��һ����Ӧ����
void  ResultScene::nextTouchDown(Control::Ref* pSender, Widget::TouchEventType type){
	//��õ�ǰ�ؿ���Ӧ��Դ�ļ���
	string fileName = UserDefault::getInstance()->getStringForKey("nextLevelFile");
	//����ؿ���Դ
	LoadLevelinfo::createLoadLevelinfo(fileName.c_str())->readLevelInfo();
	Director::getInstance()->replaceScene(TransitionFadeBL::create(0.1f, PlayLayer::createScene()));
}
