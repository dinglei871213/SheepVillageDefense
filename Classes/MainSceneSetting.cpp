#include "MainSceneSetting.h"
#include <iostream>

using namespace std;

MainSceneSetting::MainSceneSetting()
:settingSprite(NULL)
, resetBtn(NULL)
, musicBtn(NULL)
, effectBtn(NULL)
, setBg(NULL)
, musicOn(false)
{}

MainSceneSetting::~MainSceneSetting()
{}

Scene* MainSceneSetting::createSettingScene(RenderTexture *renderTexture)
{
	Size winSize = Director::getInstance()->getWinSize();

	Scene *settingScene = Scene::create();
	MainSceneSetting *settingLayer = MainSceneSetting::create();

	settingScene->addChild(settingLayer);

	settingLayer->settingSprite = Sprite::createWithTexture(renderTexture->getSprite()->getTexture());
	settingLayer->settingSprite->setPosition(Point(winSize.width / 2, winSize.height / 2));
	settingLayer->settingSprite->setFlipY(true);
	settingLayer->settingSprite->setColor(cocos2d::Color3B::GRAY);
	settingScene->addChild(settingLayer->settingSprite);

	settingLayer->setBg = Sprite::create();
	settingLayer->setBg->setTexture("setBg.png");
	settingLayer->setBg->setPosition(Point(winSize.width / 2, winSize.height / 2));
	settingLayer->settingSprite->addChild(settingLayer->setBg);

	Size setBgSize = settingLayer->setBg->getContentSize();

	settingLayer->musicText = Sprite::create();
	settingLayer->musicText->setTexture("musicText.png");
	settingLayer->musicText->setPosition(Point(setBgSize.width / 4, setBgSize.height * 4 / 5));
	settingLayer->setBg->addChild(settingLayer->musicText);

	settingLayer->musicBtn = Sprite::create();
	settingLayer->musicBtn->setPosition(Point(setBgSize.width * 2 / 3, setBgSize.height * 4 / 5));
	settingLayer->setBg->addChild(settingLayer->musicBtn);

	if (SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
	{
		settingLayer->musicBtn->setTexture("buttonOn.png");
		settingLayer->musicOn = true;
	}
	else{
		settingLayer->musicBtn->setTexture("buttonOff.png");
	}

	settingLayer->effectText = Sprite::create();
	settingLayer->effectText->setTexture("effectText.png");
	settingLayer->effectText->setPosition(Point(setBgSize.width / 4, setBgSize.height * 2 / 3));
	settingLayer->setBg->addChild(settingLayer->effectText);

	settingLayer->effectBtn = Sprite::create();
	settingLayer->effectBtn->setPosition(Point(setBgSize.width * 2 / 3, setBgSize.height * 2 / 3));
	settingLayer->setBg->addChild(settingLayer->effectBtn);

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
void MainSceneSetting::setMenu()
{
	Size winSize = Director::getInstance()->getWinSize();
	Size setBgSize = setBg->getContentSize();

	Sprite *resumeBtn01 = Sprite::create();
	resumeBtn01->setTexture("resumeOn.png");
	Sprite *resumeBtn02 = Sprite::create();
	resumeBtn02->setTexture("resumeDown.png");
	MenuItemSprite *resumeItem = MenuItemSprite::create(resumeBtn01, resumeBtn02, CC_CALLBACK_1(MainSceneSetting::resumeCallback, this));

	Sprite *resetBtn01 = Sprite::create();
	resetBtn01->setTexture("resetOn.png");
	Sprite *resetBtn02 = Sprite::create();
	resetBtn02->setTexture("resetDown.png");
	MenuItemSprite *resetItem = MenuItemSprite::create(resetBtn01, resetBtn02, CC_CALLBACK_1(MainSceneSetting::resetCallback, this));

	auto menu = Menu::create(resumeItem, resetItem, NULL);

	menu->alignItemsVertically();

	menu->setPosition(Point(setBgSize.width / 2, setBgSize.height / 3));

	setBg->addChild(menu);
}

//添加监听事件
void MainSceneSetting::setListener()
{
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(MainSceneSetting::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

//监听事件回调函数
bool MainSceneSetting::onTouchBegan(Touch *touch, Event *event)
{
	auto location = touch->getLocation();

	Point reallyPoint04 = musicBtn->getParent()->convertToNodeSpace(location);
	Rect rect04 = musicBtn->getBoundingBox();
	Point reallyPoint05 = effectBtn->getParent()->convertToNodeSpace(location);
	Rect rect05 = effectBtn->getBoundingBox();

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

void MainSceneSetting::resumeCallback(Ref* pSender)
{
	auto scene = HelloWorld::createScene();
	Director::sharedDirector()->replaceScene(scene);
}

//继续游戏按钮回调函数
void MainSceneSetting::resetCallback(Ref* pSender)
{
	Size winSize = Director::getInstance()->getWinSize();
	RenderTexture *renderTexture = RenderTexture::create(winSize.width, winSize.height);
	renderTexture->begin();
	this->getParent()->visit();
	renderTexture->end();
	Director::getInstance()->pushScene(CheckScene::createCheckScene(renderTexture));

}

