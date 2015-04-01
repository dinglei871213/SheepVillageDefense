
#ifndef __SheepVillageDefense__TowerPanleLayer__
#define __SheepVillageDefense__TowerPanleLayer__

#include <iostream>
#include "cocos2d.h"
#include "TowerBase.h"

USING_NS_CC;
// ������������
typedef enum
{
    ARROW_TOWER = 0,
	SLOW_TOWER = 1,
	POISON_TOWER,
	CANNON_TOWER,
	ANOTHER
} TowerType;

//����ѡ�񲼾���
class TowerPanleLayer: public Layer
{
public:
    virtual bool init() override;
    CREATE_FUNC(TowerPanleLayer);
    
    bool onTouchBegan(Touch *touch, Event *event);
	void onTouchEnded(Touch* touch, Event* event);
    
    CC_SYNTHESIZE(TowerType, chooseTowerType, ChooseTowerType);// ѡ�����������

	void setMoneyText(int tower1Money, int tower2Money, int tower3Money, int tower4Money);
    
private:
    
    Sprite* sprite1;
	Sprite* sprite2;
	Sprite* sprite3;
	Sprite* sprite4;

	Label * tower1MoneyLabel;
	Label * tower2MoneyLabel;
	Label * tower3MoneyLabel;
	Label * tower4MoneyLabel;
};


#endif /* defined(__thiefTD__TowerPanleLayer__) */
