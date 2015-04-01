#ifndef __SheepVillageDefense__CheckScene__
#define __SheepVillageDefense__CheckScene__

#include "cocos2d.h"
#include "InfoHandle.h"

USING_NS_CC;

class CheckScene :public Layer
{
public:
	CheckScene();
	~CheckScene();

	static Scene *createCheckScene(RenderTexture *renderTexture);
	void okCallBack(Ref *pSender);
	void CancelCallback(Ref *pSender);
	void setMenu();
	Sprite *checkBg;

	CREATE_FUNC(CheckScene);
};
#endif /* defined(__SheepVillageDefense__CheckScene__) */