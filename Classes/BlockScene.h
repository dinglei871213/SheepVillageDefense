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

	//声明多重图层管理器
	LayerMultiplex* multilayer;
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	//资料库按钮的触发事件函数
	void libraryTouchDown(Control::Ref* pSender, Widget::TouchEventType type);

	//升级按钮的触发事件函数
	void upgradeTouchDown(Control::Ref* pSender, Widget::TouchEventType type);

	//返回按钮的触发事件函数
	void  backTouchDown(Control::Ref* pSender, Widget::TouchEventType type);

	//开始战斗按钮的触发事件函数
	void BlockScene::fightTouchDown(Control::Ref* pSender, Widget::TouchEventType type,int i);

	//关闭窗口的触发事件函数
	void BlockScene::closeTouchDown(Control::Ref* pSender, Widget::TouchEventType type);
	
	//小狼资料信息窗口的触发事件函数
	void  BlockScene::wolfTouchDown(Control::Ref* pSender, Widget::TouchEventType type);

	//防御塔资料窗口的触发函数
	void  BlockScene::towerTouchDown(Control::Ref* pSender, Widget::TouchEventType type);
	
	//提示信息窗口的触发函数
	void  BlockScene::tipTouchDown(Control::Ref* pSender, Widget::TouchEventType type);
	
	
	//离开按钮的触发函数
	void  BlockScene::leaveTouchDown(Control::Ref* pSender, Widget::TouchEventType type);
	
	//升级按钮的触发事件函数

	void  BlockScene::uBtnTouchDown(Control::Ref* pSender, Widget::TouchEventType type, int i);
	void  BlockScene::resetTouchDown(Control::Ref* pSender, Widget::TouchEventType type);
	void BlockScene::upTouchDown(Control::Ref* pSender, Widget::TouchEventType type, int i);


	
	void certainblockTouchDown(Control::Ref* pSender, Widget::TouchEventType type,int i);

	void certaintowerTouchDown(Control::Ref* pSender, Widget::TouchEventType type, int i);
	//弹出图层窗口
	Layer*	popBlock();
	Layer*	popLibrary();
	Layer*	popFailure();
	Layer*	popSuccess();
	Layer*  popTower();
	Layer*	popCertainBlock(int i);
	Layer*  popUpgrade();

	// implement the "static create()" method manually
	CREATE_FUNC(BlockScene);

	
private:
	//关卡整体部分
	static int layernum;				//图层数量
	static int starnum;					//玩家获得的星星总数量
	static int blocknum;				//已解锁的关卡数量
	static Vector<Button*> btnlist[9];	//按钮集合
	static Vector<Sprite*> splist[9];	//关卡得分图片集合
	static Vector<Text*>textlist[9];	//关卡序号文本集合
	static Vector<Button*>towerlibbtn[6];//防御塔资料按钮集合
	//关卡部分
	static Button* block1btn;		//关卡1按钮
	static Button* block2btn;		//关卡2按钮
	static Button* block3btn;		//关卡3按钮
	static Button* block4btn;		//关卡4按钮
	static Button* block5btn;		//关卡5按钮
	static Button* block6btn;		//关卡6按钮
	static Button* block7btn;		//关卡7按钮
	static Button* block8btn;		//关卡8按钮
	static Button* block9btn;		//关卡9按钮

	static Sprite* sp1;			//关卡1得分图片
	static Sprite* sp2;			//关卡1得分图片
	static Sprite* sp3;			//关卡3得分图片
	static Sprite* sp4;			//关卡4得分图片
	static Sprite* sp5;			//关卡5得分图片
	static Sprite* sp6;			//关卡6得分图片
	static Sprite* sp7;			//关卡7得分图片
	static Sprite* sp8;			//关卡8得分图片
	static Sprite* sp9;			//关卡9得分图片

	static Text*  text1;		//关卡1说明文本
	static Text*  text2;		//关卡2说明文本
	static Text*  text3;		//关卡3说明文本
	static Text*  text4;		//关卡4说明文本
	static Text*  text5;		//关卡5说明文本
	static Text*  text6;		//关卡6说明文本
	static Text*  text7;		//关卡7说明文本
	static Text*  text8;		//关卡8说明文本
	static Text*  text9;		//关卡9说明文本
	static Text*  startext;		//星星数量显示文本

	static Button* librarybtn;		//资料库按钮
	static Button* upgradebtn;		//升级按钮
	static Button* backbtn;			//返回菜单按钮

	//具体关卡部分
	static Button* fightbtn;		//开始战斗按钮
	static Button* closebtn;		//关闭窗口按钮
	static Sprite* suolue;			//关卡缩略图
	static Text* blockinfo;			//关卡介绍
	static Text* blocktitle;		//关卡标题
	static Text* blockid;			//关卡序号

	//结果评价部分
	static Button* retrybtn;		//重新挑战按钮
	static Button* leavebtn;		//离开按钮
	static Button* nextbtn;			//下一关按钮
	

	//资料库部分
	static Button* wolfbtn;			//小狼资料按钮
	static Button* towerbtn;		//防御塔资料按钮
	static Button* tipbtn;			//提示资料按钮
	static Button* backtoblockbtn;		//返回关卡界面按钮


	static Button*	tower1btn;		//防御塔资料界面按钮1
	static Button*	tower2btn;		//防御塔资料界面按钮2
	static Button*	tower3btn;		//防御塔资料界面按钮3
	static Button*	tower4btn;		//防御塔资料界面按钮4
	static Button*	tower5btn;		//防御塔资料界面按钮5
	static Button*	tower6btn;		//防御塔资料界面按钮6
	static Sprite*  towersprite;	//防御塔图片
	static Text*	towername;		//防御塔名称
	static Text*	towerinfo;		//防御塔信息
	static Text*	damage;			//防御塔攻击力
	static Text*	speed;			//防御塔攻速
	static Text*	range;			//防御塔射程
	static Text*	specialtext;	//防御塔特性说明

	static Vector<Button*> uBtnlist[28];	//升级按钮集合
	static Button* uBtn1;           //升级技能1
	static Button* uBtn2;           //升级技能2
	static Button* uBtn3;           //升级技能3
	static Button* uBtn4;           //升级技能4
	static Button* uBtn5;           //升级技能5
	static Button* uBtn6;           //升级技能6
	static Button* uBtn7;           //升级技能7
	static Button* uBtn8;           //升级技能8
	static Button* uBtn9;           //升级技能9
	static Button* uBtn10;          //升级技能10
	static Button* uBtn11;          //升级技能11
	static Button* uBtn12;          //升级技能12
	static Button* uBtn13;          //升级技能13
	static Button* uBtn14;          //升级技能14
	static Button* uBtn15;          //升级技能15
	static Button* uBtn16;          //升级技能16
	static Button* uBtn17;          //升级技能17
	static Button* uBtn18;          //升级能18
	static Button* uBtn19;          //升级技能19
	static Button* uBtn20;          //升级技能20
	static Button* uBtn21;          //升级技能21
	static Button* uBtn22;          //升级技能22
	static Button* uBtn23;          //升级技能23
	static Button* uBtn24;          //升级技能24
	static Button* uBtn25;          //升级技能25
	static Button* uBtn26;          //升级技能26
	static Button* uBtn27;          //升级技能27
	static Button* uBtn28;          //升级技能28


	static int starNum;               //可用于升级的星星总数
	static Text* stars;				  //显示星星数量文本
	static Button* reset;			  //重置按钮	
	static Button* confirm;			  //确认按钮 
	static Text* nameText;            //技能的名称
	static Text* infoText;			  //技能的信息
	static Sprite* btnImage;          //每个按钮对应的图标
	static Text* singleStar;          //每个图标对应的星星数量
	static Button* upgrade;           //确定升级按钮
	static bool btnState[28];        //每个按钮的状态

};

#endif // __HELLOWORLD_SCENE_H__
