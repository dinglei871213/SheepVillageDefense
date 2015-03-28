#include "PlayPause.h"

void PlayPause::setListener()
{
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(PlayPause::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

Scene* PlayPause::createPauseScene(RenderTexture *renderTexture)
{
	Size winSize = Director::getInstance()->getWinSize();

	Scene *pauseScene = Scene::create();
	PlayPause* pauseLayer = PlayPause::create();
	pauseScene->addChild(pauseLayer);

	Sprite* pauseSprite = Sprite::createWithTexture(renderTexture->getSprite()->getTexture());
	pauseSprite->setPosition(Point(winSize.width/2, winSize.height/2));
	pauseSprite->setFlipY(true);
	pauseSprite->setColor(cocos2d::Color3B::GRAY);
	pauseScene->addChild(pauseSprite);

	pauseLayer->setListener();


	Sprite* pauseTip = Sprite::create();
	pauseTip->setSpriteFrame("tower2_2.png");
	pauseTip->setPosition(Point(winSize.width / 2, winSize.height / 2));
	pauseScene->addChild(pauseTip);

	return pauseScene;
}

bool PlayPause::onTouchBegan(Touch *touch, Event *event)
{
	Director::getInstance()->popScene();
	return true;
}