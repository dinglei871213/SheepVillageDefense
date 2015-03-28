#include "cocos2d.h"
#include <iostream>
USING_NS_CC;

#define SHORTEST_SLIDE_LENGTH (20)

class LevelLayer : public cocos2d::Layer
{
public:
	LevelLayer();
	~LevelLayer();
	virtual bool init();
	//static cocos2d::Layer* createLayer();
	//CRAETE_FUNC(LevelLayer);

	void addNode(Node* level);
	void menuCloseCallback(Ref * pSender);
	bool onTouchBegan(Touch* pTouch, Event* pEvent);
	void onTouchMoved(Touch* pTouch, Event* pEvent);
	void onTouchEnded(Touch* pTouch, Event* pEvent);

private:
	int pageNode; //LevelLayer中的子页数
	int curPageNode;  //当前显示第几个子页
	Vec2 touchDownPoint;  //触摸屏幕的按下点
	Vec2 touchUpPoint;  //触摸屏幕的抬起点
	Vec2 touchCurPoint;   //当前触摸点
	float WINDOW_WIDTH;    //LevelLayer的固定宽
	float WINDOW_HEIGHT;
	void goToCurNode();   //在当前触摸事件完成后根据偏移量跳转到当前子页面
};
