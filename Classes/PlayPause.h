#ifndef __SheepVillageDefense__PlayPause__
#define __SheepVillageDefense__PlayPause__

#include "cocos2d.h"
#include <iostream>

USING_NS_CC;

class PlayPause :public Layer
{
public:
	void setListener();
	virtual bool onTouchBegan(Touch *touch, Event *event) override;
	static Scene* createPauseScene(RenderTexture *renderTexture);
	CREATE_FUNC(PlayPause);
};

#endif /* defined(__SheepVillageDefense__PlayPause__) */