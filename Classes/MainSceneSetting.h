#ifndef __SheepVillageDefense__MainSceneSetting__
#define __SheepVillageDefense__MainSceneSetting__

#include "cocos2d.h"
#include <iostream>
#include "extensions/cocos-ext.h"
#include "SimpleAudioEngine.h"
#include "GameManager.h"
#include "InfoHandle.h"
#include "HelloWorldScene.h"
#include "CheckScene.h"

USING_NS_CC;

using namespace extension;
using namespace CocosDenshion;

class MainSceneSetting :public Layer
{
public:
	MainSceneSetting();
	~MainSceneSetting();

	void setListener();
	void setMenu();
	virtual bool onTouchBegan(Touch *touch, Event *event) override;
	static Scene* createSettingScene(RenderTexture *renderTexture);
	CREATE_FUNC(MainSceneSetting);
	void resumeCallback(Ref* pSender);
	void resetCallback(Ref* pSender);
	Scene *checkScene(RenderTexture *renderTexture);
	Sprite *settingSprite;
	Sprite *resetBtn;
	Sprite *musicBtn;
	Sprite *effectBtn;
	bool musicOn;
	GameManager *instance;
	Sprite *musicText;
	Sprite *effectText;
	Sprite *setBg;
};

#endif /* defined(__SheepVillageDefense__MainSceneSetting__) */