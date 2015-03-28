#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include "extensions/cocos-ext.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameManager.h"
USING_NS_CC;
using namespace cocostudio;
using namespace extension;
using namespace ui;

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
	static HelloWorld* getInstance();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	//开始按钮的触发事件函数
	void startgameTouchDown(Control::Ref* pSender,Widget::TouchEventType type);

	//排行按钮的触发事件函数
	void rankTouchDown(Control::Ref* pSender, Widget::TouchEventType type);

	//设置按钮的触发事件函数
	void settingTouchDown(Control::Ref* pSender, Widget::TouchEventType type);

	//帮助按钮的触发事件函数
	void helpTouchDown(Control::Ref* pSender, Widget::TouchEventType type);

	//关于按钮的触发事件函数
	void aboutTouchDown(Control::Ref* pSender, Widget::TouchEventType type);

	//剧情模式按钮的触发事件函数
	void  storyTouchDown(Control::Ref* pSender, Widget::TouchEventType type);

	//返回按钮的触发事件函数
	void  backTouchDown(Control::Ref* pSender, Widget::TouchEventType type);

	//帮助界面返回按钮的触发事件函数
	void HelloWorld::exitHelpTouchDown(Control::Ref* pSender, Widget::TouchEventType type);

	//弹出游戏模式选择窗口
	void popUpMode();
	//弹出帮助窗口
	void popUpHelp();
	// implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
	
private:
	GameManager *instance;
	static HelloWorld* instance01;
	static Button* startgamebtn;	//开始游戏按钮
	static Button* rankbtn;			//排行按钮
	static Button* settingbtn;		//设置按钮
	static Button* helpbtn;			//帮助按钮
	static Button* aboutbtn;		//关于按钮
	static Button* storybtn;		//剧情模式按钮
	static Button* challengebtn;	//挑战模式按钮
	static Button* backbtn;			//返回菜单按钮
	
};

#endif // __HELLOWORLD_SCENE_H__
