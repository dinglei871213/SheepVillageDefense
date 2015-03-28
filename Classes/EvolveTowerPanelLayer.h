
#ifndef __SheepVillageDefense__EvolveTowerPanleLayer__
#define __SheepVillageDefense__EvolveTowerPanleLayer__

#include <iostream>
#include "cocos2d.h"
#include "TowerBase.h"

USING_NS_CC;

//��������������
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


	//CC_SYNTHESIZE(int, upMoney, UpMoney);//������Ǯ
	//CC_SYNTHESIZE(int, sellMoney, SellMoney);//���۽�Ǯ
	CC_SYNTHESIZE(bool, evolve1Tower, Evolve1Tower);//�����ܽ���1
	CC_SYNTHESIZE(bool, evolve2Tower, Evolve2Tower);//�����ܽ���2
	CC_SYNTHESIZE(bool, sellTower, SellTower);//������

	//CC_SYNTHESIZE(int, scope, Scope);//��������Χ
	//CC_SYNTHESIZE(int, upScope, UpScope);//�������󹥻���Χ
};


#endif /* defined(__SheepVillageDefense__EvolveTowerPanleLayer__) */
