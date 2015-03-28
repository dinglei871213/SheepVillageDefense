#ifndef __SheepVillageDefense__PlaySetting__
#define __SheepVillageDefense__PlaySetting__

#include "cocos2d.h"
#include <iostream>
#include "extensions/cocos-ext.h"
#include "SimpleAudioEngine.h"
#include "BlockScene.h"
#include "PlayLayer.h"
#include "GameManager.h"

USING_NS_CC;

using namespace extension;
using namespace CocosDenshion;

class PlaySetting :public Layer
{
public:
	PlaySetting();
	~PlaySetting();

	void setListener();
	virtual bool onTouchBegan(Touch *touch, Event *event) override;
	static Scene* createSettingScene(RenderTexture *renderTexture);
	CREATE_FUNC(PlaySetting);
	void musicAddEffectButton();
	void onValueChange(Ref* psender, Control::EventType event);
	Sprite *settingSprite;
	Sprite *resumeBtn;
	Sprite *quitBtn;
	Sprite *restartBtn;
	CCLabelTTF *musicLabel;
	Sprite *musicOnBg;
	Sprite *musicOnBtn;
	Sprite *musicOffBg;
	Sprite *musicOffBtn;
	CCLabelTTF *effectLabel;
	Sprite *effectOnBg;
	Sprite *effectOnBtn;
	Sprite *effectOffBg;
	Sprite *effectOffBtn;
	bool musicOn;
	bool effectOn;
	GameManager *instance;
};

#endif /* defined(__SheepVillageDefense__PlaySetting__) */