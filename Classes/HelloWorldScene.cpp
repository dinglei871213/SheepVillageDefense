#include "HelloWorldScene.h"
#include "BlockScene.h"
#include "cocostudio/CocoStudio.h"
#include "cocos-ext.h"
#include "LevelLayer.h"
#include "LevelSelectPage.h"
#include "SimpleAudioEngine.h"
#include "InfoHandle.h"
#include "LoadLevelInfo.h"
#include "PlayLayer.h"
//cocos2dx 3.x�汾 CCControl����ΪControl ��CCObject����ΪRef ������������

USING_NS_CC;
using namespace extension;//Control������Ҫ�����������ռ�
using namespace cocostudio ;
using namespace cocostudio::timeline;
using namespace CocosDenshion;

//��ʼ����̬��Դ���Ϊȫ�ֱ�������
Button* HelloWorld::startgamebtn	= new Button();
Button* HelloWorld::settingbtn		= new Button();
Button* HelloWorld::helpbtn			= new Button();
Button* HelloWorld::aboutbtn		= new Button();
Button* HelloWorld::storybtn		= new Button();
Button* HelloWorld::challengebtn	= new Button();
Button* HelloWorld::backbtn			= new Button();
Button* HelloWorld::soundonbtn = new Button();
Button* HelloWorld::soundoffbtn = new Button();
Button* HelloWorld::musiconbtn = new Button();
Button* HelloWorld::musicoffbtn = new Button();
Button* HelloWorld::restartbtn = new Button();

HelloWorld* HelloWorld::instance01;

HelloWorld *HelloWorld::getInstance()
{
	if (instance01 != NULL){
		return instance01;
	}
	return  NULL;
}


Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	instance01 = this;

	instance = GameManager::getInstance();
	instance->setEffectOn(true);
	instance->setMusicOn(true);
	//������Դ�ļ����ɸ��ڵ㣬��Ӧ����ͼ�еĸ��ڵ�
	auto rootNode = CSLoader::createNode("MainScene.csb");
	this->addChild(rootNode);

	//ͨ�����ڵ�õ���Ӧ��ʶ���ƵĿؼ���ת��Ϊ��Ӧ���͵Ķ���
	//�˴�ע��ڵ�Ĳ㼶��ϵ��������Ϊ��㣬��������
	startgamebtn =	(Button*)rootNode->getChildByName("startgame");
	settingbtn	 =	(Button*)rootNode->getChildByName("setting");
	helpbtn		 =	(Button*)rootNode->getChildByName("help");
	aboutbtn	 =	(Button*)rootNode->getChildByName("about");



	//Ϊ��ť����Ӧ�Ĵ����¼�
	startgamebtn	->	addTouchEventListener(CC_CALLBACK_2(HelloWorld::startgameTouchDown,this));
	settingbtn		->	addTouchEventListener(CC_CALLBACK_2(HelloWorld::settingTouchDown, this));
	helpbtn			->	addTouchEventListener(CC_CALLBACK_2(HelloWorld::helpTouchDown, this));
	aboutbtn		->	addTouchEventListener(CC_CALLBACK_2(HelloWorld::aboutTouchDown, this));
	
    return true;
}


//��ť�İ�����Ӧ�¼�
void  HelloWorld::startgameTouchDown(Control::Ref* pSender, Widget::TouchEventType type){
	Size winSize = Director::getInstance()->getWinSize();
	RenderTexture *renderTexture = RenderTexture::create(winSize.width, winSize.height);
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:{
														
														renderTexture->begin();
														this->getParent()->visit();
														renderTexture->end();
														Director::getInstance()->pushScene(HelloWorld::popUpMode(renderTexture));
	}
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
	
}


void  HelloWorld::settingTouchDown(Control::Ref* pSender, Widget::TouchEventType type){
	Size winSize = Director::getInstance()->getWinSize();
	RenderTexture *renderTexture = RenderTexture::create(winSize.width, winSize.height);
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:{
														renderTexture->begin();
														this->getParent()->visit();
														renderTexture->end();
														Director::getInstance()->pushScene(MainSceneSetting::createSettingScene(renderTexture));
	}
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
	
}

//������ť�Ĵ�����Ӧ�¼�
void  HelloWorld::helpTouchDown(Control::Ref* pSender, Widget::TouchEventType type){
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:{
		popUpHelp();
	}
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}



void HelloWorld::popUpHelp(){
	LevelLayer* scrollView = new LevelLayer();
	scrollView->init();
	//�������������ڵ㣬���������ͼ��
	auto page0 = LevelSelectPage::create("selectLevelBg.png", 0);
	page0->setTag(0);
	scrollView->addNode(page0);
	auto page1 = LevelSelectPage::create("selectLevelBg1.png", 1);
	page1->setTag(1);
	scrollView->addNode(page1);
	auto page2 = LevelSelectPage::create("selectLevelBg2.png", 2);
	page2->setTag(2);
	scrollView->addNode(page2);
	

	//���ɱ���ͼƬ
	Sprite* spritebg = Sprite::create("playbg.png");
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint pointCenter = ccp(winSize.width / 2, winSize.height/2);
	spritebg->setPosition(pointCenter);
	this->addChild(spritebg);

	this->addChild(scrollView);

	//page_mark1,page_mark2��ͼ����plist���棬�ڴ���spriteʱ��Ҫ�Ƚ���ͼ���뵽�ڴ���
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Play.plist", "Play.png");

	auto width = Sprite::createWithSpriteFrameName("page_mark1.png")->getContentSize().width;
	auto posX = (winSize.width - width * 3) / 2;

	for (int i = 0; i < 3; i++)
	{//����ʾҳ���СԲ�㶼����Ϊ���ĵ�
		Sprite* sprite = Sprite::createWithSpriteFrameName("page_mark1.png");
		sprite->setPosition(Vec2(posX + i * width, winSize.height / 7));
		addChild(sprite);
	}

	//����ʾ��ǰ��ʾ��ҳ��Ŀ���СԲ����ʵ��СԲ�㸲��
	Sprite* spriteMark = Sprite::createWithSpriteFrameName("page_mark2.png");
	spriteMark->setPosition(Vec2(posX, winSize.height / 7));
	spriteMark->setTag(888);
	addChild(spriteMark);

	//��ӷ��ذ�ť
	Button *button = Button::create();
	button->loadTextures("fanhui2.png","fanhui.png","fanhui.png");
	button->setPosition(ccp(900.0,44.0));
	//CCDictionary* plistDic = CCDictionary::createWithContentsOfFile("towerlib.plist");//��plist�ļ��ж�ȡ������ص������ַ�	
	//CCString* back = (CCString *)plistDic->objectForKey("helpback");
	//button->setTitleText(back->getCString());
	//button->setTitleColor(Color3B::BLUE);
	//button->setTitleFontName("girl.ttf");
	//button->setTitleFontSize(50);
	button->setScale(0.3);
	this->addChild(button);
	button->addTouchEventListener(CC_CALLBACK_2(HelloWorld::exitHelpTouchDown, this));
	return ;

}
//�������淵�ش����¼�
void HelloWorld::exitHelpTouchDown(Control::Ref* pSender, Widget::TouchEventType type){
	auto menuScene = HelloWorld::createScene();
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		Director::sharedDirector()->replaceScene(menuScene);
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void  HelloWorld::aboutTouchDown(Control::Ref* pSender, Widget::TouchEventType type){
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:{
		popUpHelp();
	}
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void  HelloWorld::storyTouchDown(Control::Ref* pSender, Widget::TouchEventType type){
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:{
		auto blockscene = BlockScene::createScene();
		Director::sharedDirector()->replaceScene(blockscene);
	} 
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
	
}

//�ر�ģʽѡ�񴰿�
void  HelloWorld::backTouchDown(Control::Ref* pSender, Widget::TouchEventType type){
	auto scene = HelloWorld::createScene();
	Director::sharedDirector()->replaceScene(scene);
}


Scene *HelloWorld::popUpMode(RenderTexture *renderTexture){

	Scene *modeSelectScene = Scene::create();
	Sprite* modeSelectSprite = Sprite::createWithTexture(renderTexture->getSprite()->getTexture());
	//������Դ�ļ�����ͼ��
	LayerRGBA* layer = (LayerRGBA*)CSLoader::createNode("gamemode.csb");
	//����ͼ������λ��
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	modeSelectSprite->setPosition(Point(winSize.width / 2, winSize.height / 2));
	CCPoint pointCenter = ccp(winSize.width / 2 - 320, winSize.height / 2 - 272);
	layer->setPosition(pointCenter);
	modeSelectSprite->setFlipY(true);
	modeSelectScene->addChild(modeSelectSprite);
	modeSelectScene->addChild(layer);

	//this->addChild(layer);

	//��ȡͼ���а�ť����
	storybtn = (Button*)layer->getChildByName("story");
	challengebtn = (Button*)layer->getChildByName("challenge");
	backbtn = (Button*)layer->getChildByName("back");


	//Ϊ��ť��ӵ�������¼�
	storybtn->addTouchEventListener(CC_CALLBACK_2(HelloWorld::storyTouchDown, this));
	backbtn->addTouchEventListener(CC_CALLBACK_2(HelloWorld::backTouchDown, this));
	challengebtn->addTouchEventListener(CC_CALLBACK_2(HelloWorld::challengeTouchDown, this));
	//auto rootNode = CSLoader::createNode("MainScene.csb");
	return modeSelectScene;
}

/*
Scene *HelloWorld::popUpSetting(RenderTexture *renderTexture){
	Scene *settingScene = Scene::create();
	Sprite* settingSprite = Sprite::createWithTexture(renderTexture->getSprite()->getTexture());

	//������Դ�ļ�����ͼ��
	LayerRGBA* layer = (LayerRGBA*)CSLoader::createNode("SettingLayer.csb");
	//����ͼ������λ��
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint pointCenter = ccp(winSize.width / 2 - 320, winSize.height / 2 - 272);
	settingSprite->setPosition(Point(winSize.width/2,winSize.height/2));
	settingSprite->setFlippedY(true);
	layer->setPosition(pointCenter);
	settingScene->addChild(settingSprite);
	settingSprite->addChild(layer);
	//this->addChild(layer);

	//��ȡͼ���а�ť����
	musiconbtn = (Button*)layer->getChildByName("musicon");
	musicoffbtn = (Button*)layer->getChildByName("musicoff");
	soundonbtn = (Button*)layer->getChildByName("soundon");
	soundoffbtn = (Button*)layer->getChildByName("soundoff");
	restartbtn = (Button*)layer->getChildByName("restartbtn");
	backbtn = (Button*)layer->getChildByName("backbtn");

	//Ϊ��ť��ӵ�������¼�
	musiconbtn->addTouchEventListener(CC_CALLBACK_2(HelloWorld::musiconTouchDown, this));
	musicoffbtn->addTouchEventListener(CC_CALLBACK_2(HelloWorld::musicoffTouchDown, this));
	soundonbtn->addTouchEventListener(CC_CALLBACK_2(HelloWorld::soundonTouchDown, this));
	soundoffbtn->addTouchEventListener(CC_CALLBACK_2(HelloWorld::soundoffTouchDown, this));
	restartbtn->addTouchEventListener(CC_CALLBACK_2(HelloWorld::restartTouchDown, this));
	backbtn->addTouchEventListener(CC_CALLBACK_2(HelloWorld::backTouchDown, this));

	return settingScene;
}**/

void  HelloWorld::musiconTouchDown(Control::Ref* pSender, Widget::TouchEventType type){
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:{
														SimpleAudioEngine::sharedEngine()->rewindBackgroundMusic();
														GameManager::getInstance()->setMusicOn(true);
	}
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void  HelloWorld::challengeTouchDown(Control::Ref* pSender, Widget::TouchEventType type){
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
	{
													   
													   SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/button.wav").c_str(), false);
													   SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Play.plist");

													  
													   string plistname = "challenge.plist";

													   //����ؿ���Դ
													   LoadLevelinfo::createLoadLevelinfo(plistname.c_str())->readLevelInfo();
													   Director::getInstance()->replaceScene(TransitionFadeBL::create(0.1f, PlayLayer::createScene()));
													   SimpleAudioEngine::getInstance()->playBackgroundMusic(FileUtils::getInstance()->fullPathForFilename("sound/block1bgm.mp3").c_str(), true);
													   SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.1f);
	}
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

	void  HelloWorld::musicoffTouchDown(Control::Ref* pSender, Widget::TouchEventType type){
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			break;
		case cocos2d::ui::Widget::TouchEventType::MOVED:
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:{
															SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
															GameManager::getInstance()->setMusicOn(false);
		}
		case cocos2d::ui::Widget::TouchEventType::CANCELED:
			break;
		default:
			break;
		}
}

	
	void  HelloWorld::soundonTouchDown(Control::Ref* pSender, Widget::TouchEventType type){
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			break;
		case cocos2d::ui::Widget::TouchEventType::MOVED:
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:{
															
															GameManager::getInstance()->setEffectOn(true);
		}
		case cocos2d::ui::Widget::TouchEventType::CANCELED:
			break;
		default:
			break;
		}
	}

	void  HelloWorld::soundoffTouchDown(Control::Ref* pSender, Widget::TouchEventType type){
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			break;
		case cocos2d::ui::Widget::TouchEventType::MOVED:
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:{
															
															GameManager::getInstance()->setEffectOn(false);
		}
		case cocos2d::ui::Widget::TouchEventType::CANCELED:
			break;
		default:
			break;
		}
	}

	void  HelloWorld::restartTouchDown(Control::Ref* pSender, Widget::TouchEventType type){
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			break;
		case cocos2d::ui::Widget::TouchEventType::MOVED:
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:{
															InfoHandle handle;
															User user = handle.getUserInfo();
															user.setUpgradeNumber(0);
															user.setBlockNumber(0);
															user.setNickName("litdon");
															user.setStarNumber(0);
															handle.updateUserInfo(user);

															for (int i = 0; i < 9;i++)
															{
																Block block = handle.getBlockInfo(i);
																block.setBlockId(i);
																block.setBlockStar(0);
																handle.updateBlockInfo(block);
															}
		}
		case cocos2d::ui::Widget::TouchEventType::CANCELED:
			break;
		default:
			break;
		}
	}

