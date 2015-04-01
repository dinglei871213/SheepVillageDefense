#ifndef __RESULT_SCENE_H__
#define __RESULT_SCENE_H__
#include "extensions/cocos-ext.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "BlockScene.h"
#include <list>
USING_NS_CC;
using namespace cocostudio;
using namespace extension;
using namespace ui;
#include "cocos2d.h"

class ResultScene : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	

	//������ս��ť�Ĵ�������
	void  retryTouchDown(Control::Ref* pSender, Widget::TouchEventType type);

	//�뿪��ť�Ĵ�������
	void  leaveTouchDown(Control::Ref* pSender, Widget::TouchEventType type);

	//��һ�ذ�ť�Ĵ�������
	void  nextTouchDown(Control::Ref* pSender, Widget::TouchEventType type);

	

	//����ͼ�㴰��
	
	
	Layer*	popFailure();
	Layer*	popSuccess();
	
	// implement the "static create()" method manually
	CREATE_FUNC(ResultScene);
	Sprite* starpic;			//�÷�����ͼƬ
private:

	//������۲���
	
	static Button* retrybtn;		//������ս��ť
	static Button* leavebtn;		//�뿪��ť
	static Button* nextbtn;			//��һ�ذ�ť


	


	
	
};

#endif // __HELLOWORLD_SCENE_H__
