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
	int pageNode; //LevelLayer�е���ҳ��
	int curPageNode;  //��ǰ��ʾ�ڼ�����ҳ
	Vec2 touchDownPoint;  //������Ļ�İ��µ�
	Vec2 touchUpPoint;  //������Ļ��̧���
	Vec2 touchCurPoint;   //��ǰ������
	float WINDOW_WIDTH;    //LevelLayer�Ĺ̶���
	float WINDOW_HEIGHT;
	void goToCurNode();   //�ڵ�ǰ�����¼���ɺ����ƫ������ת����ǰ��ҳ��
};
