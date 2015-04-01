#ifndef __SheepVillageDefense__PlaySetting__
#define __SheepVillageDefense__PlaySetting__

#include "cocos2d.h"
#include <iostream>
#include "extensions/cocos-ext.h"
#include "SimpleAudioEngine.h"
#include "BlockScene.h"
#include "PlayLayer.h"

USING_NS_CC;

using namespace extension;
using namespace CocosDenshion;

class PlaySetting :public Layer
{
public:
	PlaySetting();
	~PlaySetting();

	void setListener();
	void setMenu();
	virtual bool onTouchBegan(Touch *touch, Event *event) override;
	static Scene* createSettingScene(RenderTexture *renderTexture);
	CREATE_FUNC(PlaySetting);
	void musicAddEffectButton();
	void onValueChange(Ref* psender, Control::EventType event);
	void resumeCallback(Ref* pSender);
	void quitCallback(Ref* pSender);
	void restartCallback(Ref* pSender);
	Sprite *settingSprite;
	Sprite *resumeBtn;
	Sprite *quitBtn;
	Sprite *restartBtn;
	CCLabelTTF *musicLabel;
	Sprite *musicBtn;
	CCLabelTTF *effectLabel;
	Sprite *effectBtn;
	bool musicOn;
	GameManager *instance;
	Sprite *musicText;
	Sprite *effectText;
};

#endif /* defined(__SheepVillageDefense__PlaySetting__) */