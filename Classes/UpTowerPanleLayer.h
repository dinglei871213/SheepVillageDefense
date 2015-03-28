
#ifndef __SheepVillageDefense__UpTowerPanleLayer__
#define __SheepVillageDefense__UpTowerPanleLayer__

#include <iostream>
#include "cocos2d.h"
#include "TowerBase.h"

USING_NS_CC;

//Éý¼¶ÅÚËþ²¼¾°²ã
class UpTowerPanleLayer : public Layer
{
public:
	virtual bool init() override;
	CREATE_FUNC(UpTowerPanleLayer);

	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchEnded(Touch* touch, Event* event);
	void setMoneyText(int upMoney, int sellMoney);
	//void setScope();
	void setUpScopeCircle(int upScopeCircle);
	void setScopeCircle(int scopeCircle);

private:

	Sprite* sprite1;
	Sprite* sprite2;
	Label * sellMoneyLabel;
	Label * upMoneyLabel;


	//CC_SYNTHESIZE(int, upMoney, UpMoney);//Éý¼¶½ðÇ®
	//CC_SYNTHESIZE(int, sellMoney, SellMoney);//³öÊÛ½ðÇ®
	CC_SYNTHESIZE(bool, upTower, UpTower);//Éý¼¶Ëþ
	CC_SYNTHESIZE(bool, sellTower, SellTower);//³öÊÛËþ

	//CC_SYNTHESIZE(int, scope, Scope);//Ëþ¹¥»÷·¶Î§
	//CC_SYNTHESIZE(int, upScope, UpScope);//ËþÉý¼¶ºó¹¥»÷·¶Î§
};


#endif /* defined(__SheepVillageDefense__UpTowerPanleLayer__) */
