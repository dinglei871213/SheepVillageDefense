#include "PlaySetting.h"
#include "BlockScene.h"
#include "PlayLayer.h"
#include "LoadLevelInfo.h"
#include <iostream>
using namespace std;

PlaySetting::PlaySetting()
:settingSprite(NULL)
, resumeBtn(NULL)
, quitBtn(NULL)
, restartBtn(NULL)
, musicLabel(NULL)
, musicOnBg(NULL)
, musicOnBtn(NULL)
, musicOffBg(NULL)
, musicOffBtn(NULL)
, effectLabel(NULL)
, effectOnBg(NULL)
, effectOnBtn(NULL)
, effectOffBg(NULL)
, effectOffBtn(NULL)
, musicOn(false)
, effectOn(false)
{}

PlaySetting::~PlaySetting()
{}

Scene* PlaySetting::createSettingScene(RenderTexture *renderTexture)
{
	Size winSize = Director::getInstance()->getWinSize();

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

	settingLayer->musicAddEffectButton();

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
	settingLayer->settingSprite->addChild(settingLayer->restartBtn);

	settingLayer->musicLabel = CCLabelTTF::create("MUSIC", "MarkerFelt-Thin", 30);
	settingLayer->musicLabel->setPosition(Point(winSize.width / 3.0, winSize.height / 1.1));
	settingLayer->musicLabel->setColor(cocos2d::Color3B::ORANGE);
	settingLayer->settingSprite->addChild(settingLayer->musicLabel);
	/*
	settingLayer->musicOffBg = Sprite::create();
	settingLayer->musicOffBg->setSpriteFrame("playbutton1.png");
	settingLayer->musicOffBg->setPosition(Point(winSize.width / 2.2, winSize.height / 1.1));
	settingLayer->settingSprite->addChild(settingLayer->musicOffBg);

	settingLayer->musicOnBg = Sprite::create();
	settingLayer->musicOnBg->setSpriteFrame("playbutton1.png");
	settingLayer->musicOnBg->setPosition(Point(winSize.width / 1.8, winSize.height / 1.1));
	settingLayer->settingSprite->addChild(settingLayer->musicOnBg);**/

	settingLayer->musicOffBtn = Sprite::create();
	settingLayer->musicOffBtn->setPosition(Point(winSize.width / 2.2, winSize.height / 1.1));
	settingLayer->settingSprite->addChild(settingLayer->musicOffBtn);

	settingLayer->musicOnBtn = Sprite::create();
	settingLayer->musicOnBtn->setPosition(Point(winSize.width / 1.8, winSize.height / 1.1));
	settingLayer->settingSprite->addChild(settingLayer->musicOnBtn);

	if (SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
	{
		settingLayer->musicOffBtn->setSpriteFrame("playbutton1.png");
		settingLayer->musicOnBtn->setSpriteFrame("playbutton2.png");
		settingLayer->musicOn = true;
	}
	else{
		settingLayer->musicOffBtn->setSpriteFrame("playbutton2.png");
		settingLayer->musicOnBtn->setSpriteFrame("playbutton1.png");
	}

	settingLayer->effectLabel = CCLabelTTF::create("EFFECT", "MarkerFelt-Thin", 30);
	settingLayer->effectLabel->setPosition(Point(winSize.width / 3.0, winSize.height / 1.3));
	settingLayer->effectLabel->setColor(cocos2d::Color3B::ORANGE);
	settingLayer->settingSprite->addChild(settingLayer->effectLabel);
	/*
	settingLayer->effectOffBg = Sprite::create();
	settingLayer->effectOffBg->setSpriteFrame("playbutton1.png");
	settingLayer->effectOffBg->setPosition(Point(winSize.width / 2.2, winSize.height / 1.3));
	settingLayer->settingSprite->addChild(settingLayer->effectOffBg);

	settingLayer->effectOnBg = Sprite::create();
	settingLayer->effectOnBg->setSpriteFrame("playbutton1.png");
	settingLayer->effectOnBg->setPosition(Point(winSize.width / 1.8, winSize.height / 1.3));
	settingLayer->settingSprite->addChild(settingLayer->effectOnBg);**/

	settingLayer->effectOffBtn = Sprite::create();
	settingLayer->effectOffBtn->setPosition(Point(winSize.width / 2.2, winSize.height / 1.3));
	settingLayer->settingSprite->addChild(settingLayer->effectOffBtn);

	settingLayer->effectOnBtn = Sprite::create();
	settingLayer->effectOnBtn->setPosition(Point(winSize.width / 1.8, winSize.height / 1.3));
	settingLayer->settingSprite->addChild(settingLayer->effectOnBtn);

	settingLayer->instance = GameManager::getInstance();
	if (settingLayer->instance->getEffectOn() == true)
	{
		settingLayer->effectOffBtn->setSpriteFrame("playbutton1.png");
		settingLayer->effectOnBtn->setSpriteFrame("playbutton2.png");
	}
	else{
		settingLayer->effectOffBtn->setSpriteFrame("playbutton2.png");
		settingLayer->effectOnBtn->setSpriteFrame("playbutton1.png");
	}

	settingLayer->setListener();

	return settingScene;
}

void PlaySetting::setListener()
{
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(PlaySetting::onTouchBegan,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

bool PlaySetting::onTouchBegan(Touch *touch, Event *event)
{
	auto location = touch->getLocation();

	Point reallyPoint01 = resumeBtn->getParent()->convertToNodeSpace(location);
	Rect rect01 = resumeBtn->getBoundingBox();
	Point reallyPoint02 = quitBtn->getParent()->convertToNodeSpace(location);
	Rect rect02 = quitBtn->getBoundingBox();
	Point reallyPoint03 = restartBtn->getParent()->convertToNodeSpace(location);
	Rect rect03 = restartBtn->getBoundingBox();
	Point reallyPoint04 = musicOffBtn->getParent()->convertToNodeSpace(location);
	Rect rect04 = musicOffBtn->getBoundingBox();
	Point reallyPoint05 = musicOnBtn->getParent()->convertToNodeSpace(location);
	Rect rect05 = musicOnBtn->getBoundingBox();
	Point reallyPoint06 = effectOffBtn->getParent()->convertToNodeSpace(location);
	Rect rect06 = effectOffBtn->getBoundingBox();
	Point reallyPoint07 = effectOnBtn->getParent()->convertToNodeSpace(location);
	Rect rect07 = effectOnBtn->getBoundingBox();

	if (rect01.containsPoint(reallyPoint01))//继续游戏
	{
		Director::getInstance()->popScene();
	}
	else if (rect02.containsPoint(reallyPoint02))//退出游戏
	{
		auto blockScene = BlockScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(0.1f, blockScene));
	}
	else if (rect03.containsPoint(reallyPoint03))//重新开始
	{
		//获得当前关卡对应资源文件名
		string fileName = UserDefault::getInstance()->getStringForKey("currLevelFile");
		//载入关卡资源
		LoadLevelinfo::createLoadLevelinfo(fileName.c_str())->readLevelInfo();
		Director::getInstance()->replaceScene(TransitionFadeBL::create(0.1f, PlayLayer::createScene()));
	}
	else if (rect04.containsPoint(reallyPoint04) && musicOn == true)
	{
		SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
		musicOnBtn->setSpriteFrame("playbutton1.png");
		musicOffBtn->setSpriteFrame("playbutton2.png");
		musicOn = false;
	}
	else if (rect05.containsPoint(reallyPoint05) && musicOn == false)
	{
		SimpleAudioEngine::sharedEngine()->rewindBackgroundMusic();
		musicOffBtn->setSpriteFrame("playbutton1.png");
		musicOnBtn->setSpriteFrame("playbutton2.png");
		musicOn = true;
	}
	else if (rect06.containsPoint(reallyPoint06) && instance->getEffectOn() == true)
	{
		effectOnBtn->setSpriteFrame("playbutton1.png");
		effectOffBtn->setSpriteFrame("playbutton2.png");
		instance->setEffectOn(false);
	}
	else if (rect07.containsPoint(reallyPoint07) && instance->getEffectOn() == false)
	{
		effectOnBtn->setSpriteFrame("playbutton2.png");
		effectOffBtn->setSpriteFrame("playbutton1.png");
		instance->setEffectOn(true);
	}

	return true;
}


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
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(potentiometer->getValue()/10.0f);
	}