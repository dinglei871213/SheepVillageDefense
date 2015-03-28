#include "HelloWorldScene.h"
#include "BlockScene.h"
#include "cocostudio/CocoStudio.h"
#include "extensions/cocos-ext.h"
#include "LevelLayer.h"
#include "LevelSelectPage.h"
//cocos2dx 3.x�汾 CCControl����ΪControl ��CCObject����ΪRef ������������

USING_NS_CC;
using namespace extension;//Control������Ҫ�����������ռ�
using namespace cocostudio ;
using namespace cocostudio::timeline;


//��ʼ����̬��Դ���Ϊȫ�ֱ�������
Button* HelloWorld::startgamebtn	= new Button();
Button* HelloWorld::rankbtn			= new Button();
Button* HelloWorld::settingbtn		= new Button();
Button* HelloWorld::helpbtn			= new Button();
Button* HelloWorld::aboutbtn		= new Button();
Button* HelloWorld::storybtn		= new Button();
Button* HelloWorld::challengebtn	= new Button();
Button* HelloWorld::backbtn			= new Button();

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

	//������Դ�ļ����ɸ��ڵ㣬��Ӧ����ͼ�еĸ��ڵ�
	auto rootNode = CSLoader::createNode("MainScene.csb");
	this->addChild(rootNode);

	//ͨ�����ڵ�õ���Ӧ��ʶ���ƵĿؼ���ת��Ϊ��Ӧ���͵Ķ���
	//�˴�ע��ڵ�Ĳ㼶��ϵ��������Ϊ��㣬��������
	startgamebtn =	(Button*)rootNode->getChildByName("startgame");
	rankbtn		 =	(Button*)rootNode->getChildByName("rank");
	settingbtn	 =	(Button*)rootNode->getChildByName("setting");
	helpbtn		 =	(Button*)rootNode->getChildByName("help");
	aboutbtn	 =	(Button*)rootNode->getChildByName("about");



	//Ϊ��ť����Ӧ�Ĵ����¼�
	startgamebtn	->	addTouchEventListener(CC_CALLBACK_2(HelloWorld::startgameTouchDown,this));
	rankbtn			->	addTouchEventListener(CC_CALLBACK_2(HelloWorld::rankTouchDown, this));
	settingbtn		->	addTouchEventListener(CC_CALLBACK_2(HelloWorld::settingTouchDown, this));
	helpbtn			->	addTouchEventListener(CC_CALLBACK_2(HelloWorld::helpTouchDown, this));
	aboutbtn		->	addTouchEventListener(CC_CALLBACK_2(HelloWorld::aboutTouchDown, this));
	
    return true;
}


//��ť�İ�����Ӧ�¼�
void  HelloWorld::startgameTouchDown(Control::Ref* pSender, Widget::TouchEventType type){
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		popUpMode();
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
	
}

void  HelloWorld::rankTouchDown(Control::Ref* pSender, Widget::TouchEventType type){
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		rankbtn->setRotation(60.00);
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
	
}
void  HelloWorld::settingTouchDown(Control::Ref* pSender, Widget::TouchEventType type){
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		rankbtn->setColor(Color3B::BLUE);
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
	CCDictionary* plistDic = CCDictionary::createWithContentsOfFile("chinese.plist");//��plist�ļ��ж�ȡ������ص������ַ�	
	CCString* back = (CCString *)plistDic->objectForKey("helpback");
	button->setTitleText(back->getCString());
	button->setTitleColor(Color3B::BLUE);
	button->setTitleFontName("girl.ttf");
	button->setTitleFontSize(50);
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
	rankbtn->setBright(true);
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


void HelloWorld::popUpMode(){

	//������Դ�ļ�����ͼ��
	LayerRGBA* layer = (LayerRGBA*)CSLoader::createNode("gamemode.csb");
	//����ͼ������λ��
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint pointCenter = ccp(winSize.width/2-320, winSize.height/2-272);
	layer->setPosition(pointCenter);
	this->addChild(layer);

	//��ȡͼ���а�ť����
	storybtn = (Button*)layer->getChildByName("story");
	challengebtn = (Button*)layer->getChildByName("challenge");
	backbtn = (Button*)layer->getChildByName("back");

	
	//Ϊ��ť��ӵ�������¼�
	storybtn->addTouchEventListener(CC_CALLBACK_2(HelloWorld::storyTouchDown,this));
	backbtn->addTouchEventListener(CC_CALLBACK_2(HelloWorld::backTouchDown, this));

	//auto rootNode = CSLoader::createNode("MainScene.csb");
}