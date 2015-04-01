#include "PlaySetting.h"
#include <iostream>
#include "LoadLevelInfo.h"
using namespace std;
PlaySetting::PlaySetting()
:settingSprite(NULL)
, resumeBtn(NULL)
, quitBtn(NULL)
, restartBtn(NULL)
, musicLabel(NULL)
, musicBtn(NULL)
, effectLabel(NULL)
, effectBtn(NULL)
, musicOn(false)
{}

PlaySetting::~PlaySetting()
{}

Scene* PlaySetting::createSettingScene(RenderTexture *renderTexture)
{
	Size winSize = Director::getInstance()->getWinSize();

	//Director::getInstance()->getTextureCache()->addImage("buttonOn.png");
	//Director::getInstance()->getTextureCache()->addImage("buttonOff.png");

	Scene *settingScene = Scene::create();
	PlaySetting *settingLayer = PlaySetting::create();
	settingScene->addChild(settingLayer);

	settingLayer->settingSprite = Sprite::createWithTexture(renderTexture->getSprite()->getTexture());
	settingLayer->settingSprite->setPosition(Point(winSize.width / 2, winSize.height / 2));
	settingLayer->settingSprite->setFlipY(true);
	settingLayer->settingSprite->setColor(cocos2d::Color3B::GRAY);
	settingScene->addChild(settingLayer->settingSprite);
	/*
	Sprite *settingBg = Sprite::create("village.jpg");
	settingBg->setPosition(Point(winSize.width / 2, winSize.height / 2));
	settingScene->addChild(settingBg);**/

	//settingLayer->musicAddEffectButton();
	/*
	settingLayer->resumeBtn = Sprite::create();
	settingLayer->resumeBtn->setSpriteFrame("playbutton1.png");
	settingLayer->resumeBtn->setPosition(Point(winSize.width / 2, winSize.height / 1.9));
	settingLayer->settingSprite->addChild(settingLayer->resumeBtn);

	settingLayer->quitBtn = Sprite::create();
	settingLayer->quitBtn->setSpriteFrame("playbutton1.png");
	settingLayer->quitBtn->setPosition(Point(winSize.width / 2, winSize.height / 2.7));
	settingLayer->settingSprite->addChild(settingLayer->quitBtn);

	settingLayer->restartBtn = Sprite::create();
	settingLayer->restartBtn->setSpriteFrame("playbutton1.png");
	settingLayer->restartBtn->setPosition(Point(winSize.width / 2, winSize.height / 4.8));
	settingLayer->settingSprite->addChild(settingLayer->restartBtn);**/
	/*
	settingLayer->musicLabel = CCLabelTTF::create("MUSIC", "MarkerFelt-Thin", 30);
	settingLayer->musicLabel->setPosition(Point(winSize.width / 2.4, winSize.height / 1.2));
	settingLayer->musicLabel->setColor(cocos2d::Color3B::ORANGE);
	settingLayer->settingSprite->addChild(settingLayer->musicLabel);**/

	settingLayer->musicText = Sprite::create();
	settingLayer->musicText->setTexture("musicText.png");
	settingLayer->musicText->setPosition(Point(winSize.width / 2.4, winSize.height / 1.2));
	settingLayer->settingSprite->addChild(settingLayer->musicText);
	/*
	settingLayer->musicOffBg = Sprite::create();
	settingLayer->musicOffBg->setSpriteFrame("playbutton1.png");
	settingLayer->musicOffBg->setPosition(Point(winSize.width / 2.2, winSize.height / 1.1));
	settingLayer->settingSprite->addChild(settingLayer->musicOffBg);

	settingLayer->musicOnBg = Sprite::create();
	settingLayer->musicOnBg->setSpriteFrame("playbutton1.png");
	settingLayer->musicOnBg->setPosition(Point(winSize.width / 1.8, winSize.height / 1.1));
	settingLayer->settingSprite->addChild(settingLayer->musicOnBg);**/

	settingLayer->musicBtn = Sprite::create();
	settingLayer->musicBtn->setPosition(Point(winSize.width / 1.7, winSize.height / 1.2));
	settingLayer->settingSprite->addChild(settingLayer->musicBtn);

	if (SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
	{
		settingLayer->musicBtn->setTexture("buttonOn.png");
		settingLayer->musicOn = true;
	}
	else{
		settingLayer->musicBtn->setTexture("buttonOff.png");
	}
	/*
	settingLayer->effectLabel = CCLabelTTF::create("EFFECT", "MarkerFelt-Thin", 30);
	settingLayer->effectLabel->setPosition(Point(winSize.width / 2.4, winSize.height / 1.4));
	settingLayer->effectLabel->setColor(cocos2d::Color3B::ORANGE);
	settingLayer->settingSprite->addChild(settingLayer->effectLabel);**/

	settingLayer->effectText = Sprite::create();
	settingLayer->effectText->setTexture("musicText.png");
	settingLayer->effectText->setPosition(Point(winSize.width / 2.4, winSize.height / 1.4));
	settingLayer->settingSprite->addChild(settingLayer->effectText);

	/*
	settingLayer->effectOffBg = Sprite::create();
	settingLayer->effectOffBg->setSpriteFrame("playbutton1.png");
	settingLayer->effectOffBg->setPosition(Point(winSize.width / 2.2, winSize.height / 1.3));
	settingLayer->settingSprite->addChild(settingLayer->effectOffBg);

	settingLayer->effectOnBg = Sprite::create();
	settingLayer->effectOnBg->setSpriteFrame("playbutton1.png");
	settingLayer->effectOnBg->setPosition(Point(winSize.width / 1.8, winSize.height / 1.3));
	settingLayer->settingSprite->addChild(settingLayer->effectOnBg);**/

	settingLayer->effectBtn = Sprite::create();
	settingLayer->effectBtn->setPosition(Point(winSize.width / 1.7, winSize.height / 1.4));
	settingLayer->settingSprite->addChild(settingLayer->effectBtn);

	settingLayer->instance = GameManager::getInstance();

	if (settingLayer->instance->getEffectOn() == true)
	{
		settingLayer->effectBtn->setTexture("buttonOn.png");
	}
	else{
		settingLayer->effectBtn->setTexture("buttonOff.png");
	}

	settingLayer->setMenu();

	settingLayer->setListener();

	return settingScene;
}

//设置界面下方的三个按钮
void PlaySetting::setMenu()
{
	Size winSize = Director::getInstance()->getWinSize();
	Sprite *resumeBtn01 = Sprite::create();
	resumeBtn01->setTexture("resumeOn.png");
	Sprite *resumeBtn02 = Sprite::create();
	resumeBtn02->setTexture("resumeDown.png");
	MenuItemSprite *resumeItem = MenuItemSprite::create(resumeBtn01, resumeBtn02, CC_CALLBACK_1(PlaySetting::resumeCallback, this));
	Sprite *quitBtn01 = Sprite::create();
	quitBtn01->setTexture("quitOn.png");
	Sprite *quitBtn02 = Sprite::create();
	quitBtn02->setTexture("quitDown.png");
	MenuItemSprite *quitItem = MenuItemSprite::create(quitBtn01, quitBtn02, CC_CALLBACK_1(PlaySetting::quitCallback, this));
	Sprite *restartBtn01 = Sprite::create();
	restartBtn01->setTexture("restartOn.png");
	Sprite *restartBtn02 = Sprite::create();
	restartBtn02->setTexture("restartDown.png");

	MenuItemSprite *restartItem = MenuItemSprite::create(restartBtn01, restartBtn02, CC_CALLBACK_1(PlaySetting::restartCallback, this));

	auto menu = Menu::create(resumeItem, quitItem, restartItem, NULL);

	menu->alignItemsVertically();

	menu->setPosition(Point(winSize.width / 2, winSize.height / 3));

	settingSprite->addChild(menu);
}

//添加监听事件
void PlaySetting::setListener()
{
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(PlaySetting::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

//监听事件回调函数
bool PlaySetting::onTouchBegan(Touch *touch, Event *event)
{
	auto location = touch->getLocation();
	/*
	Point reallyPoint01 = resumeBtn->getParent()->convertToNodeSpace(location);
	Rect rect01 = resumeBtn->getBoundingBox();
	Point reallyPoint02 = quitBtn->getParent()->convertToNodeSpace(location);
	Rect rect02 = quitBtn->getBoundingBox();
	Point reallyPoint03 = restartBtn->getParent()->convertToNodeSpace(location);
	Rect rect03 = restartBtn->getBoundingBox();
	**/
	Point reallyPoint04 = musicBtn->getParent()->convertToNodeSpace(location);
	Rect rect04 = musicBtn->getBoundingBox();
	Point reallyPoint05 = effectBtn->getParent()->convertToNodeSpace(location);
	Rect rect05 = effectBtn->getBoundingBox();
	/*
	if (rect01.containsPoint(reallyPoint01))
	{
		Director::getInstance()->popScene();
	}
	else if (rect02.containsPoint(reallyPoint02))
	{
		auto blockScene = BlockScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(0.1f, blockScene));
	}
	else if (rect03.containsPoint(reallyPoint03))
	{
		auto playLayer = PlayLayer::createScene();
		GameManager *instance = GameManager::getInstance();
		instance->clear();
		Director::getInstance()->replaceScene(TransitionFade::create(0.1f, playLayer));
	}**/
	if (rect04.containsPoint(reallyPoint04))
	{
		if (musicOn == true)
		{
			SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
			musicBtn->setTexture("buttonOff.png");
			musicOn = false;
		}
		else
		{
			SimpleAudioEngine::sharedEngine()->rewindBackgroundMusic();
			musicBtn->setTexture("buttonOn.png");
			musicOn = true;
		}

	}
	else if (rect05.containsPoint(reallyPoint05))
	{
		if (instance->getEffectOn() == true)
		{
			effectBtn->setTexture("buttonOff.png");
			instance->setEffectOn(false);
		}
		else
		{
			effectBtn->setTexture("buttonOn.png");
			instance->setEffectOn(true);
		}
	}
	return true;
}

/*
void  PlaySetting::musicAddEffectButton()
{
Size winSize = Director::getInstance()->getWinSize();

ControlPotentiometer* potentiometer = ControlPotentiometer::create("base.png", "bar.png", "button.png");
potentiometer->setPosition(Point(winSize.width / 3, winSize.height / 2));
potentiometer->setMaximumValue(10);
potentiometer->setMinimumValue(0);
float f = SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume();
potentiometer->setValue(SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume());
potentiometer->addTargetWithActionForControlEvents(this, cccontrol_selector(PlaySetting::onValueChange), Control::EventType::VALUE_CHANGED);
settingSprite->addChild(potentiometer);
}

void PlaySetting::onValueChange(Ref* psender, Control::EventType event)
{
ControlPotentiometer* potentiometer = (ControlPotentiometer*)psender;
SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(potentiometer->getValue() / 10.0f);
SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}**/

//继续游戏按钮回调函数
void PlaySetting::resumeCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
}

//结束关卡按钮回调函数
void PlaySetting::quitCallback(Ref* pSender)
{

	auto blockScene = BlockScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.1f, blockScene));
	SimpleAudioEngine::getInstance()->playBackgroundMusic(FileUtils::getInstance()->fullPathForFilename("sound/theme.mp3").c_str(), true);
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.1f);
}

//重新开始按钮回调函数
void PlaySetting::restartCallback(Ref* pSender)
{
	//获得当前关卡对应资源文件名
	int i = UserDefault::getInstance()->getIntegerForKey("currBlock");
	char fnext[10];
	sprintf(fnext, "%d", i);
	string fnid = fnext;
	string currName = "levelInfo_" + fnid + ".plist";
	//载入关卡资源
	GameManager::getInstance()->clear();
	LoadLevelinfo::createLoadLevelinfo(currName.c_str())->readLevelInfo();
	Director::getInstance()->replaceScene(TransitionFadeBL::create(0.1f, PlayLayer::createScene()));
}