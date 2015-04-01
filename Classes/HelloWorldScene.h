#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include "cocos-ext.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameManager.h"
#include "MainSceneSetting.h"
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

	//��ʼ��ť�Ĵ����¼�����
	void startgameTouchDown(Control::Ref* pSender,Widget::TouchEventType type);

	//���ð�ť�Ĵ����¼�����
	void settingTouchDown(Control::Ref* pSender, Widget::TouchEventType type);

	//������ť�Ĵ����¼�����
	void helpTouchDown(Control::Ref* pSender, Widget::TouchEventType type);

	//���ڰ�ť�Ĵ����¼�����
	void aboutTouchDown(Control::Ref* pSender, Widget::TouchEventType type);
	void challengeTouchDown(Control::Ref* pSender, Widget::TouchEventType type);

	//����ģʽ��ť�Ĵ����¼�����
	void  storyTouchDown(Control::Ref* pSender, Widget::TouchEventType type);

	//���ذ�ť�Ĵ����¼�����
	void  backTouchDown(Control::Ref* pSender, Widget::TouchEventType type);
	void  musiconTouchDown(Control::Ref* pSender, Widget::TouchEventType type);
	void  musicoffTouchDown(Control::Ref* pSender, Widget::TouchEventType type);
	void  soundonTouchDown(Control::Ref* pSender, Widget::TouchEventType type);
	void  soundoffTouchDown(Control::Ref* pSender, Widget::TouchEventType type);
	void  restartTouchDown(Control::Ref* pSender, Widget::TouchEventType type);

	//�������淵�ذ�ť�Ĵ����¼�����
	void  exitHelpTouchDown(Control::Ref* pSender, Widget::TouchEventType type);

	//������Ϸģʽѡ�񴰿�
	Scene *popUpMode(RenderTexture *renderTexture);
	Scene *popUpSetting(RenderTexture *renderTexture);
	//������������
	void popUpHelp();
	// implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
	
private:
	GameManager *instance;
	static HelloWorld* instance01;
	static Button* startgamebtn;	//��ʼ��Ϸ��ť
	static Button* settingbtn;		//���ð�ť
	static Button* helpbtn;			//������ť
	static Button* aboutbtn;		//���ڰ�ť
	static Button* storybtn;		//����ģʽ��ť
	static Button* challengebtn;	//��սģʽ��ť
	static Button* backbtn;			//���ز˵���ť

	static Button* soundonbtn;
	static Button* soundoffbtn;
	static Button* musiconbtn;
	static Button* musicoffbtn;
	static Button* restartbtn;
	
};

#endif // __HELLOWORLD_SCENE_H__
