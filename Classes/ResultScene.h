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

	

	//重新挑战按钮的触发函数
	void  ResultScene::retryTouchDown(Control::Ref* pSender, Widget::TouchEventType type);

	//离开按钮的触发函数
	void  ResultScene::leaveTouchDown(Control::Ref* pSender, Widget::TouchEventType type);

	//下一关按钮的触发函数
	void  ResultScene::nextTouchDown(Control::Ref* pSender, Widget::TouchEventType type);

	

	//弹出图层窗口
	
	
	Layer*	popFailure();
	Layer*	popSuccess();
	
	// implement the "static create()" method manually
	CREATE_FUNC(ResultScene);

private:

	//结果评价部分
	static Sprite* starpic;			//得分星星图片
	static Button* retrybtn;		//重新挑战按钮
	static Button* leavebtn;		//离开按钮
	static Button* nextbtn;			//下一关按钮


	


	
	
};

#endif // __HELLOWORLD_SCENE_H__
