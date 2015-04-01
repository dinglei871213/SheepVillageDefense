#ifndef __BLOCK_SCENE_H__
#define __BLOCK_SCENE_H__
#include "extensions/cocos-ext.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <list>
USING_NS_CC;
using namespace cocostudio;
using namespace extension;
using namespace ui;
#include "cocos2d.h"

class BlockScene : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	//��������ͼ�������
	LayerMultiplex* multilayer;
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	//���Ͽⰴť�Ĵ����¼�����
	void libraryTouchDown(Control::Ref* pSender, Widget::TouchEventType type);

	//������ť�Ĵ����¼�����
	void upgradeTouchDown(Control::Ref* pSender, Widget::TouchEventType type);

	//���ذ�ť�Ĵ����¼�����
	void  backTouchDown(Control::Ref* pSender, Widget::TouchEventType type);

	//��ʼս����ť�Ĵ����¼�����
	void fightTouchDown(Control::Ref* pSender, Widget::TouchEventType type,int i);

	//�رմ��ڵĴ����¼�����
	void closeTouchDown(Control::Ref* pSender, Widget::TouchEventType type);
	
	//С��������Ϣ���ڵĴ����¼�����
	void  wolfTouchDown(Control::Ref* pSender, Widget::TouchEventType type);

	//���������ϴ��ڵĴ�������
	void  towerTouchDown(Control::Ref* pSender, Widget::TouchEventType type);
	
	//��ʾ��Ϣ���ڵĴ�������
	void  tipTouchDown(Control::Ref* pSender, Widget::TouchEventType type);
	
	
	//�뿪��ť�Ĵ�������
	void  leaveTouchDown(Control::Ref* pSender, Widget::TouchEventType type);
	
	//������ť�Ĵ����¼�����

	void  uBtnTouchDown(Control::Ref* pSender, Widget::TouchEventType type, int i);
	void  resetTouchDown(Control::Ref* pSender, Widget::TouchEventType type);
	void  upTouchDown(Control::Ref* pSender, Widget::TouchEventType type, int i);


	
	void certainblockTouchDown(Control::Ref* pSender, Widget::TouchEventType type,int i);

	void certaintowerTouchDown(Control::Ref* pSender, Widget::TouchEventType type, int i);
	void certainwolfTouchDown(Control::Ref* pSender, Widget::TouchEventType type, int i);
	//����ͼ�㴰��
	Layer*	popBlock();
	Layer*	popLibrary();
	Layer*	popFailure();
	Layer*	popSuccess();
	Layer*  popTower();
	Layer*	popCertainBlock(int i);
	Layer*  popUpgrade();
	Layer*	popWolf();

	// implement the "static create()" method manually
	CREATE_FUNC(BlockScene);

	Sprite* sp1;			//�ؿ�1�÷�ͼƬ
	Sprite* sp2;			//�ؿ�1�÷�ͼƬ
	Sprite* sp3;			//�ؿ�3�÷�ͼƬ
	Sprite* sp4;			//�ؿ�4�÷�ͼƬ
	Sprite* sp5;			//�ؿ�5�÷�ͼƬ
	Sprite* sp6;			//�ؿ�6�÷�ͼƬ
	Sprite* sp7;			//�ؿ�7�÷�ͼƬ
	Sprite* sp8;			//�ؿ�8�÷�ͼƬ
	Sprite* sp9;			//�ؿ�9�÷�ͼƬ
	Sprite* suolue;			//�ؿ�����ͼ
	Sprite* btnImage;          //ÿ����ť��Ӧ��ͼ��
private:
	//�ؿ����岿��
	static int layernum;				//ͼ������
	static int starnum;					//��һ�õ�����������
	static int blocknum;				//�ѽ����Ĺؿ�����
	static Vector<Button*> btnlist[9];	//��ť����
	static Vector<Sprite*> splist[9];	//�ؿ��÷�ͼƬ����
	static Vector<Text*> textlist[9];	//�ؿ�����ı�����
	static Vector<Button*> towerlibbtn[8];//���������ϰ�ť����
	static Vector<Button*> wolflibbtn[6];//С�����ϰ�ť����
	//�ؿ�����
	static Button* block1btn;		//�ؿ�1��ť
	static Button* block2btn;		//�ؿ�2��ť
	static Button* block3btn;		//�ؿ�3��ť
	static Button* block4btn;		//�ؿ�4��ť
	static Button* block5btn;		//�ؿ�5��ť
	static Button* block6btn;		//�ؿ�6��ť
	static Button* block7btn;		//�ؿ�7��ť
	static Button* block8btn;		//�ؿ�8��ť
	static Button* block9btn;		//�ؿ�9��ť

	 

	static Text*  text1;		//�ؿ�1˵���ı�
	static Text*  text2;		//�ؿ�2˵���ı�
	static Text*  text3;		//�ؿ�3˵���ı�
	static Text*  text4;		//�ؿ�4˵���ı�
	static Text*  text5;		//�ؿ�5˵���ı�
	static Text*  text6;		//�ؿ�6˵���ı�
	static Text*  text7;		//�ؿ�7˵���ı�
	static Text*  text8;		//�ؿ�8˵���ı�
	static Text*  text9;		//�ؿ�9˵���ı�
	static Text*  startext;		//����������ʾ�ı�

	static Button* librarybtn;		//���Ͽⰴť
	static Button* upgradebtn;		//������ť
	static Button* backbtn;			//���ز˵���ť

	//����ؿ�����
	static Button* fightbtn;		//��ʼս����ť
	static Button* closebtn;		//�رմ��ڰ�ť
	 
	static Text* blockinfo;			//�ؿ�����
	static Text* blocktitle;		//�ؿ�����
	static Text* blockid;			//�ؿ����

	//������۲���
	static Button* retrybtn;		//������ս��ť
	static Button* leavebtn;		//�뿪��ť
	static Button* nextbtn;			//��һ�ذ�ť
	

	//���Ͽⲿ��
	static Button* wolfbtn;			//С�����ϰ�ť
	static Button* towerbtn;		//���������ϰ�ť
	static Button* tipbtn;			//��ʾ���ϰ�ť
	static Button* backtoblockbtn;		//���عؿ����水ť


	static Button*	tower1btn;		//���������Ͻ��水ť1
	static Button*	tower2btn;		//���������Ͻ��水ť2
	static Button*	tower3btn;		//���������Ͻ��水ť3
	static Button*	tower4btn;		//���������Ͻ��水ť4
	static Button*	tower5btn;		//���������Ͻ��水ť5
	static Button*	tower6btn;		//���������Ͻ��水ť6
	static Button*	tower7btn;		//���������Ͻ��水ť6
	static Button*	tower8btn;		//���������Ͻ��水ť6
	
	static Text*	towername;		//����������
	static Text*	towerinfo;		//��������Ϣ
	static Text*	damage;			//������������
	static Text*	speed;			//����������
	static Text*	range;			//���������
	static Text*	specialtext;	//����������˵��

	static Button*	wolf1btn;		//С�����Ͻ��水ť1
	static Button*	wolf2btn;		//С�����Ͻ��水ť2
	static Button*	wolf3btn;		//С�����Ͻ��水ť3
	static Button*	wolf4btn;		//С�����Ͻ��水ť4
	static Button*	wolf5btn;		//С�����Ͻ��水ť5
	static Button*	wolf6btn;		//С�����Ͻ��水ť6

	static Text*	wolfname;		//С������
	static Text*	wolfinfo;		//С����Ϣ
	static Text*	health;			//С������ֵ
	static Text*	movingspeed;	//С���ƶ��ٶ�
	

	static Vector<Button*> uBtnlist[28];	//������ť����
	static Button* uBtn1;           //��������1
	static Button* uBtn2;           //��������2
	static Button* uBtn3;           //��������3
	static Button* uBtn4;           //��������4
	static Button* uBtn5;           //��������5
	static Button* uBtn6;           //��������6
	static Button* uBtn7;           //��������7
	static Button* uBtn8;           //��������8
	static Button* uBtn9;           //��������9
	static Button* uBtn10;          //��������10
	static Button* uBtn11;          //��������11
	static Button* uBtn12;          //��������12
	static Button* uBtn13;          //��������13
	static Button* uBtn14;          //��������14
	static Button* uBtn15;          //��������15
	static Button* uBtn16;          //��������16
	static Button* uBtn17;          //��������17
	static Button* uBtn18;          //������18
	static Button* uBtn19;          //��������19
	static Button* uBtn20;          //��������20
	static Button* uBtn21;          //��������21
	static Button* uBtn22;          //��������22
	static Button* uBtn23;          //��������23
	static Button* uBtn24;          //��������24
	static Button* uBtn25;          //��������25
	static Button* uBtn26;          //��������26
	static Button* uBtn27;          //��������27
	static Button* uBtn28;          //��������28


	static int starNum;               //��������������������
	static Text* stars;				  //��ʾ���������ı�
	static Button* reset;			  //���ð�ť	
	static Button* confirm;			  //ȷ�ϰ�ť 
	static Text* nameText;            //���ܵ�����
	static Text* infoText;			  //���ܵ���Ϣ
	static Text* singleStar;          //ÿ��ͼ���Ӧ����������
	static Button* upgrade;           //ȷ��������ť
	static bool btnState[28];        //ÿ����ť��״̬

};

#endif // __HELLOWORLD_SCENE_H__
