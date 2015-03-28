
#ifndef __SheepVillageDefense__EvolveTowerPanleLayer__
#define __SheepVillageDefense__EvolveTowerPanleLayer__

#include <iostream>
#include "cocos2d.h"
#include "TowerBase.h"

USING_NS_CC;

//升级炮塔布景层
class EvolveTowerPanleLayer : public Layer
{
public:
	virtual bool init() override;
	CREATE_FUNC(EvolveTowerPanleLayer);

	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchEnded(Touch* touch, Event* event);
	void setMoneyText(int evolve1Money, int evolve2Money, int sellMoney);
	//void setScope();
	//void setUpScopeCircle(int upScopeCircle);
	void setScopeCircle(int scopeCircle);

private:

	Sprite* sprite1;
	Sprite* sprite2;
	Sprite* sprite3;
	Label * sellMoneyLabel;
	Label * evolve1MoneyLabel;
	Label * evolve2MoneyLabel;


	//CC_SYNTHESIZE(int, upMoney, UpMoney);//升级金钱
	//CC_SYNTHESIZE(int, sellMoney, SellMoney);//出售金钱
	CC_SYNTHESIZE(bool, evolve1Tower, Evolve1Tower);//塔技能进化1
	CC_SYNTHESIZE(bool, evolve2Tower, Evolve2Tower);//塔技能进化2
	CC_SYNTHESIZE(bool, sellTower, SellTower);//出售塔

	//CC_SYNTHESIZE(int, scope, Scope);//塔攻击范围
	//CC_SYNTHESIZE(int, upScope, UpScope);//塔升级后攻击范围
};


#endif /* defined(__SheepVillageDefense__EvolveTowerPanleLayer__) */
