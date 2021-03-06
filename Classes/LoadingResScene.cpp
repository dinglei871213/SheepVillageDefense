
#include "LoadingResScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"  
using namespace CocosDenshion;  

LoadingResScene::LoadingResScene()
:numberOfLoadedRes(0)
,totalOfLoadedRes(25)
,progressBar(NULL)
{
}

Scene* LoadingResScene::createScene()
{
    Scene *scene = Scene::create(); 
    LoadingResScene *layer = LoadingResScene::create();
    scene->addChild(layer);

    return scene;
}

bool LoadingResScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
    progressBar = addProgress();
	loadResources();
    schedule(schedule_selector(LoadingResScene::logic));

	return true;
}

void LoadingResScene::transitionScene()
{
	unschedule(schedule_selector(LoadingResScene::logic));
	Director::getInstance()->replaceScene(TransitionFade::create(0.1f, HelloWorld::createScene()));
}

ProgressTimer * LoadingResScene::addProgress()
{
	Size size = Director::getInstance()->getWinSize();
	auto progressBarBg = Sprite::create("load.png");
	progressBarBg->setPosition(Point(size.width / 2,  size.height / 2 ));  
	addChild(progressBarBg);

	progressBar = ProgressTimer::create(Sprite::create("loadBar.png"));
	progressBar->setType(ProgressTimer::Type::BAR);
	progressBar->setMidpoint(Point(0, 0.5f));
	progressBar->setBarChangeRate(Point(1, 0));
	progressBar->setPercentage(0);
	progressBar->setAnchorPoint(Point(0.5f, 0.5f));
    progressBar->setPosition(Point(progressBarBg->getContentSize().width / 2,  progressBarBg->getContentSize().height /5.3 ));  
	progressBarBg->addChild(progressBar);
    return progressBar;
}

void LoadingResScene::loadResources()
{
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic(FileUtils::getInstance()->fullPathForFilename("sound/theme.mp3").c_str() );
    numberOfLoadedRes++;
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(FileUtils::getInstance()->fullPathForFilename("sound/block1bgm.mp3").c_str());
	numberOfLoadedRes++;
    SimpleAudioEngine::getInstance()->preloadEffect(FileUtils::getInstance()->fullPathForFilename("sound/dead.wav" ).c_str());
    numberOfLoadedRes++;
    SimpleAudioEngine::getInstance()->preloadEffect(FileUtils::getInstance()->fullPathForFilename("sound/button.wav").c_str() );
    numberOfLoadedRes++;
    SimpleAudioEngine::getInstance()->preloadEffect(FileUtils::getInstance()->fullPathForFilename("sound/comeout.wav").c_str() );
    numberOfLoadedRes++;
    SimpleAudioEngine::getInstance()->preloadEffect(FileUtils::getInstance()->fullPathForFilename("sound/shoot.wav").c_str() );
    numberOfLoadedRes++;
    SimpleAudioEngine::getInstance()->preloadEffect(FileUtils::getInstance()->fullPathForFilename("sound/tip.wav").c_str() );
    numberOfLoadedRes++;
    SimpleAudioEngine::getInstance()->preloadEffect(FileUtils::getInstance()->fullPathForFilename("sound/dead.mp3").c_str() );
    numberOfLoadedRes++;
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Play.plist");
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Wolf.plist");
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Tower.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("HP.plist");
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ToolLayer.plist");
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("bullet.plist");
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("arrow.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("bigTower.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Twister.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("fireBallExplode.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("fireBall.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("challenge.plist");
    numberOfLoadedRes++;

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Playdl.plist");
	numberOfLoadedRes++;
    Director::getInstance()->getTextureCache()->addImageAsync("playbg.png", CC_CALLBACK_1(LoadingResScene::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("anniu19.png", CC_CALLBACK_1(LoadingResScene::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("playbg1.png", CC_CALLBACK_1(LoadingResScene::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("successfulBg.png", CC_CALLBACK_1(LoadingResScene::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("btn_back.png", CC_CALLBACK_1(LoadingResScene::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("btn_back_press.png", CC_CALLBACK_1(LoadingResScene::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("card_1.png", CC_CALLBACK_1(LoadingResScene::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("card_2.png", CC_CALLBACK_1(LoadingResScene::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("card_3.png", CC_CALLBACK_1(LoadingResScene::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("LevelInfoPanel.png", CC_CALLBACK_1(LoadingResScene::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("House.png", CC_CALLBACK_1(LoadingResScene::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("selectLevelBg.png", CC_CALLBACK_1(LoadingResScene::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("selectLevelBg1.png", CC_CALLBACK_1(LoadingResScene::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("selectLevelBg2.png", CC_CALLBACK_1(LoadingResScene::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("start_1.png", CC_CALLBACK_1(LoadingResScene::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("start_2.png", CC_CALLBACK_1(LoadingResScene::loadingCallBack, this));
	//Director::getInstance()->getTextureCache()->addImageAsync("sell.png", CC_CALLBACK_1(LoadingResScene::loadingCallBack, this));
	//Director::getInstance()->getTextureCache()->addImageAsync("up.png", CC_CALLBACK_1(LoadingResScene::loadingCallBack, this));
	//Director::getInstance()->getTextureCache()->addImageAsync("yuan.png", CC_CALLBACK_1(LoadingResScene::loadingCallBack, this));
}

void LoadingResScene::loadingCallBack(cocos2d::Texture2D *texture)
{
    numberOfLoadedRes++;
}

void LoadingResScene::logic(float dt)
{
    float percent = (float)numberOfLoadedRes / (float)totalOfLoadedRes * 100;
    
    progressBar->setPercentage(percent);
    
    if (numberOfLoadedRes == totalOfLoadedRes)
    {
        transitionScene();
        SimpleAudioEngine::getInstance()->playBackgroundMusic(FileUtils::getInstance()->fullPathForFilename("sound/theme.mp3").c_str(), true);
        SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.1f);
    }
}