#include "HelloWorldScene.h"
#include "BlockScene.h"
#include "cocostudio/CocoStudio.h"
#include "extensions/cocos-ext.h"
#include "LevelLayer.h"
#include "LevelSelectPage.h"
//cocos2dx 3.x版本 CCControl更改为Control ，CCObject更改为Ref ！！！！！！

USING_NS_CC;
using namespace extension;//Control类所需要声明的命名空间
using namespace cocostudio ;
using namespace cocostudio::timeline;


//初始化静态资源项，作为全局变量引用
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

	//加载资源文件生成根节点，对应场景图中的根节点
	auto rootNode = CSLoader::createNode("MainScene.csb");
	this->addChild(rootNode);

	//通过根节点得到对应标识名称的控件，转化为对应类型的对象。
	//此处注意节点的层级关系，如若分为多层，需逐层调用
	startgamebtn =	(Button*)rootNode->getChildByName("startgame");
	rankbtn		 =	(Button*)rootNode->getChildByName("rank");
	settingbtn	 =	(Button*)rootNode->getChildByName("setting");
	helpbtn		 =	(Button*)rootNode->getChildByName("help");
	aboutbtn	 =	(Button*)rootNode->getChildByName("about");



	//为按钮绑定相应的触发事件
	startgamebtn	->	addTouchEventListener(CC_CALLBACK_2(HelloWorld::startgameTouchDown,this));
	rankbtn			->	addTouchEventListener(CC_CALLBACK_2(HelloWorld::rankTouchDown, this));
	settingbtn		->	addTouchEventListener(CC_CALLBACK_2(HelloWorld::settingTouchDown, this));
	helpbtn			->	addTouchEventListener(CC_CALLBACK_2(HelloWorld::helpTouchDown, this));
	aboutbtn		->	addTouchEventListener(CC_CALLBACK_2(HelloWorld::aboutTouchDown, this));
	
    return true;
}


//按钮的按下响应事件
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

//帮助按钮的触发响应事件
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

	//生成三个滑动节点，添加至滑动图层
	auto page0 = LevelSelectPage::create("selectLevelBg.png", 0);
	page0->setTag(0);
	scrollView->addNode(page0);
	auto page1 = LevelSelectPage::create("selectLevelBg1.png", 1);
	page1->setTag(1);
	scrollView->addNode(page1);
	auto page2 = LevelSelectPage::create("selectLevelBg2.png", 2);
	page2->setTag(2);
	scrollView->addNode(page2);
	

	//生成背景图片
	Sprite* spritebg = Sprite::create("playbg.png");
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint pointCenter = ccp(winSize.width / 2, winSize.height/2);
	spritebg->setPosition(pointCenter);
	this->addChild(spritebg);

	this->addChild(scrollView);

	//page_mark1,page_mark2的图都在plist里面，在创建sprite时需要先将大图载入到内存中
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Play.plist", "Play.png");

	auto width = Sprite::createWithSpriteFrameName("page_mark1.png")->getContentSize().width;
	auto posX = (winSize.width - width * 3) / 2;

	for (int i = 0; i < 3; i++)
	{//将表示页面的小圆点都设置为空心的
		Sprite* sprite = Sprite::createWithSpriteFrameName("page_mark1.png");
		sprite->setPosition(Vec2(posX + i * width, winSize.height / 7));
		addChild(sprite);
	}

	//将表示当前显示的页面的空心小圆点用实心小圆点覆盖
	Sprite* spriteMark = Sprite::createWithSpriteFrameName("page_mark2.png");
	spriteMark->setPosition(Vec2(posX, winSize.height / 7));
	spriteMark->setTag(888);
	addChild(spriteMark);

	//添加返回按钮
	Button *button = Button::create();
	button->loadTextures("fanhui2.png","fanhui.png","fanhui.png");
	button->setPosition(ccp(900.0,44.0));
	CCDictionary* plistDic = CCDictionary::createWithContentsOfFile("chinese.plist");//从plist文件中读取资料相关的中文字符	
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
//帮助界面返回触发事件
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

//关闭模式选择窗口
void  HelloWorld::backTouchDown(Control::Ref* pSender, Widget::TouchEventType type){
	auto scene = HelloWorld::createScene();
	Director::sharedDirector()->replaceScene(scene);
}


void HelloWorld::popUpMode(){

	//加载资源文件生成图层
	LayerRGBA* layer = (LayerRGBA*)CSLoader::createNode("gamemode.csb");
	//设置图层中心位置
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint pointCenter = ccp(winSize.width/2-320, winSize.height/2-272);
	layer->setPosition(pointCenter);
	this->addChild(layer);

	//获取图层中按钮对象
	storybtn = (Button*)layer->getChildByName("story");
	challengebtn = (Button*)layer->getChildByName("challenge");
	backbtn = (Button*)layer->getChildByName("back");

	
	//为按钮添加点击触发事件
	storybtn->addTouchEventListener(CC_CALLBACK_2(HelloWorld::storyTouchDown,this));
	backbtn->addTouchEventListener(CC_CALLBACK_2(HelloWorld::backTouchDown, this));

	//auto rootNode = CSLoader::createNode("MainScene.csb");
}