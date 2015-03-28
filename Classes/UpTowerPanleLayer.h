
#ifndef __SheepVillageDefense__UpTowerPanleLayer__
#define __SheepVillageDefense__UpTowerPanleLayer__

#include <iostream>
#include "cocos2d.h"
#include "TowerBase.h"

USING_NS_CC;

//��������������
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


	//CC_SYNTHESIZE(int, upMoney, UpMoney);//������Ǯ
	//CC_SYNTHESIZE(int, sellMoney, SellMoney);//���۽�Ǯ
	CC_SYNTHESIZE(bool, upTower, UpTower);//������
	CC_SYNTHESIZE(bool, sellTower, SellTower);//������

	//CC_SYNTHESIZE(int, scope, Scope);//��������Χ
	//CC_SYNTHESIZE(int, upScope, UpScope);//�������󹥻���Χ
};


#endif /* defined(__SheepVillageDefense__UpTowerPanleLayer__) */
