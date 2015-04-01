#include "BlockScene.h"
#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "extensions/cocos-ext.h"
#include "PlayLayer.h"
#include "LoadLevelInfo.h"
#include "SimpleAudioEngine.h" 
#include "InfoHandle.h"
#include <iostream>
//cocos2dx 3.x�汾 CCControl����ΪControl ��CCObject����ΪRef ������������


USING_NS_CC;
using namespace std;
using namespace CocosDenshion;
using namespace extension;//Control������Ҫ�����������ռ�
using namespace cocostudio;
using namespace cocostudio::timeline;

//��ʼ����̬��Դ���Ϊȫ�ֱ�������
int BlockScene::layernum = 0;
int BlockScene::blocknum = 0;
int BlockScene::starnum = 0;

Vector<Button*> BlockScene::btnlist[9] = {};
Vector<Sprite*> BlockScene::splist[9] = {};
Vector<Text*>	BlockScene::textlist[9] = {};
Vector<Button*> BlockScene::towerlibbtn[8] = {};
Vector<Button*> BlockScene::wolflibbtn[6] = {};

Button* BlockScene::block1btn	= new Button();
Button* BlockScene::block2btn	= new Button();
Button* BlockScene::block3btn	= new Button();
Button* BlockScene::block4btn	= new Button();
Button* BlockScene::block5btn	= new Button();
Button* BlockScene::block6btn	= new Button();
Button* BlockScene::block7btn	= new Button();
Button* BlockScene::block8btn	= new Button();
Button* BlockScene::block9btn	= new Button();

Text* BlockScene::text1 = new Text();
Text* BlockScene::text2 = new Text();
Text* BlockScene::text3 = new Text();
Text* BlockScene::text4 = new Text();
Text* BlockScene::text5 = new Text();
Text* BlockScene::text6 = new Text();
Text* BlockScene::text7 = new Text();
Text* BlockScene::text8 = new Text();
Text* BlockScene::text9 = new Text();
Text* BlockScene::startext = new Text();

Button* BlockScene::librarybtn	= new Button();
Button* BlockScene::upgradebtn	= new Button();
Button* BlockScene::backbtn		= new Button();

Button* BlockScene::fightbtn	= new Button();
Button* BlockScene::closebtn	= new Button();
Text* BlockScene::blocktitle	= new Text();
Text* BlockScene::blockinfo		= new Text();
Text* BlockScene::blockid		= new Text();

Button* BlockScene::retrybtn = new Button();
Button* BlockScene::leavebtn = new Button();
Button* BlockScene::nextbtn = new Button();

Button* BlockScene::wolfbtn		= new Button();
Button* BlockScene::towerbtn	= new Button();
Button* BlockScene::tipbtn		= new Button();
Button* BlockScene::backtoblockbtn = new Button();

Button* BlockScene::tower1btn = new Button();
Button* BlockScene::tower2btn = new Button();
Button* BlockScene::tower3btn = new Button();
Button* BlockScene::tower4btn = new Button();
Button* BlockScene::tower5btn = new Button();
Button* BlockScene::tower6btn = new Button();
Button* BlockScene::tower7btn = new Button();
Button* BlockScene::tower8btn = new Button();
Text*	BlockScene::towername = new Text();
Text*	BlockScene::towerinfo = new Text();
Text*	BlockScene::damage = new Text();
Text*	BlockScene::speed = new Text();
Text*	BlockScene::range = new Text();
Text*	BlockScene::specialtext = new Text();

Button* BlockScene::wolf1btn = new Button();
Button* BlockScene::wolf2btn = new Button();
Button* BlockScene::wolf3btn = new Button();
Button* BlockScene::wolf4btn = new Button();
Button* BlockScene::wolf5btn = new Button();
Button* BlockScene::wolf6btn = new Button();
Text*	BlockScene::wolfname = new Text();
Text*	BlockScene::wolfinfo = new Text();
Text*	BlockScene::health = new Text();
Text*	BlockScene::movingspeed = new Text();


Vector<Button*> BlockScene::uBtnlist[28] = {};
Button* BlockScene::uBtn1 = new Button();
Button* BlockScene::uBtn2 = new Button();
Button* BlockScene::uBtn3 = new Button();
Button* BlockScene::uBtn4 = new Button();
Button* BlockScene::uBtn5 = new Button();
Button* BlockScene::uBtn6 = new Button();
Button* BlockScene::uBtn7 = new Button();
Button* BlockScene::uBtn8 = new Button();
Button* BlockScene::uBtn9 = new Button();
Button* BlockScene::uBtn10 = new Button();
Button* BlockScene::uBtn11 = new Button();
Button* BlockScene::uBtn12 = new Button();
Button* BlockScene::uBtn13 = new Button();
Button* BlockScene::uBtn14 = new Button();
Button* BlockScene::uBtn15 = new Button();
Button* BlockScene::uBtn16 = new Button();
Button* BlockScene::uBtn17 = new Button();
Button* BlockScene::uBtn18 = new Button();
Button* BlockScene::uBtn19 = new Button();
Button* BlockScene::uBtn20 = new Button();
Button* BlockScene::uBtn21 = new Button();
Button* BlockScene::uBtn22 = new Button();
Button* BlockScene::uBtn23 = new Button();
Button* BlockScene::uBtn24 = new Button();
Button* BlockScene::uBtn25 = new Button();
Button* BlockScene::uBtn26 = new Button();
Button* BlockScene::uBtn27 = new Button();
Button* BlockScene::uBtn28 = new Button();

int  BlockScene::starNum = 0;
Text* BlockScene::stars = new Text();
Button* BlockScene::reset = new Button();
Button* BlockScene::confirm = new Button();
Button* BlockScene::upgrade = new Button();
Text*	BlockScene::singleStar = new Text();
Text* BlockScene::nameText = new Text();
Text* BlockScene::infoText = new Text();
bool BlockScene::btnState[28] = { false };

Scene* BlockScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = BlockScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool BlockScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	//������Դ�ļ����ɸ��ڵ㣬��Ӧ����ͼ�еĸ��ڵ�
	auto rootNode = CSLoader::createNode("BlockScene.csb");
	this->addChild(rootNode);

	//ͨ�����ڵ�õ���Ӧ��ʶ���ƵĿؼ���ת��Ϊ��Ӧ���͵Ķ���
	//�˴�ע��ڵ�Ĳ㼶��ϵ��������Ϊ��㣬��������
	librarybtn = (Button*)rootNode->getChildByName("library");
	upgradebtn = (Button*)rootNode->getChildByName("upgrade");
	backbtn = (Button*)rootNode->getChildByName("backtomenu");
	auto blocknode = rootNode->getChildByName("blocknode");//blocknodeΪ��С�ؿ����ڵĸ��ڵ�
	block1btn = (Button*)blocknode->getChildByName("b1");
	block2btn = (Button*)blocknode->getChildByName("b2");
	block3btn = (Button*)blocknode->getChildByName("b3");
	block4btn = (Button*)blocknode->getChildByName("b4");
	block5btn = (Button*)blocknode->getChildByName("b5");
	block6btn = (Button*)blocknode->getChildByName("b6");
	block7btn = (Button*)blocknode->getChildByName("b7");
	block8btn = (Button*)blocknode->getChildByName("b8");
	block9btn = (Button*)blocknode->getChildByName("b9");

	sp1 = (Sprite*)blocknode->getChildByName("s1");
	sp2 = (Sprite*)blocknode->getChildByName("s2");
	sp3 = (Sprite*)blocknode->getChildByName("s3");
	sp4 = (Sprite*)blocknode->getChildByName("s4");
	sp5 = (Sprite*)blocknode->getChildByName("s5");
	sp6 = (Sprite*)blocknode->getChildByName("s6");
	sp7 = (Sprite*)blocknode->getChildByName("s7");
	sp8 = (Sprite*)blocknode->getChildByName("s8");
	sp9 = (Sprite*)blocknode->getChildByName("s9");

	text1 = (Text*)blocknode->getChildByName("t1");
	text2 = (Text*)blocknode->getChildByName("t2");
	text3 = (Text*)blocknode->getChildByName("t3");
	text4 = (Text*)blocknode->getChildByName("t4");
	text5 = (Text*)blocknode->getChildByName("t5");
	text6 = (Text*)blocknode->getChildByName("t6");
	text7 = (Text*)blocknode->getChildByName("t7");
	text8 = (Text*)blocknode->getChildByName("t8");
	text9 = (Text*)blocknode->getChildByName("t9");
	startext = (Text*)rootNode->getChildByName("tstar");

	//��Button����ͳһ����btnlist
	//���btnlist��Ϊ�գ��������մ���
	if (!btnlist->empty())
	{
		btnlist->clear();
	}
	btnlist->insert(0, block1btn);
	btnlist->insert(1, block2btn);
	btnlist->insert(2, block3btn);
	btnlist->insert(3, block4btn);
	btnlist->insert(4, block5btn);
	btnlist->insert(5, block6btn);
	btnlist->insert(6, block7btn);
	btnlist->insert(7, block8btn);
	btnlist->insert(8, block9btn);

	//��Sprite����ͳһ����splist
	//���splist��Ϊ�գ��������մ���
	if (!splist->empty())
	{
		splist->clear();
	}
	splist->insert(0, sp1);
	splist->insert(1, sp2);
	splist->insert(2, sp3);
	splist->insert(3, sp4);
	splist->insert(4, sp5);
	splist->insert(5, sp6);
	splist->insert(6, sp7);
	splist->insert(7, sp8);
	splist->insert(8, sp9);
	

	//��Text����ͳһ����textlist
	//���textlist��Ϊ�գ��������մ���
	if (!textlist->empty())
	{
		textlist->clear();
	}
	textlist->insert(0, text1);
	textlist->insert(1, text2);
	textlist->insert(2, text3);
	textlist->insert(3, text4);
	textlist->insert(4, text5);
	textlist->insert(5, text6);
	textlist->insert(6, text7);
	textlist->insert(7, text8);
	textlist->insert(8, text9);

	
	//ͨ��json�ļ���ȡ�����Ĺؿ���������������
	InfoHandle handle;
	blocknum = handle.getUserInfo().getBlockNumber();
	starnum	 = handle.getUserInfo().getStarNumber();

	//������ʾ�Ĺؿ�ͼƬ������ı����÷�����
	for (int i = 0; i < blocknum;i++)
	{
		btnlist->at(i)->setVisible(true);
		btnlist->at(i)->setEnabled(true);
		btnlist->at(i)->loadTextures("qizi.png", "qizi.png", "qizi.png");

		//intתstring
		char sp[10];
		sprintf(sp, "%d", handle.getBlockInfo(i).getBlockStar());
		string b = sp;
		string starpic = b + "star.png";
		splist->at(i)->setVisible(true);
		splist->at(i)->setTexture(starpic);

		char tx[10];
		sprintf(tx, "%d", i+1);
		string t = tx;
		string textnum = "1-"+ t;
		textlist->at(i)->setVisible(true);
		textlist->at(i)->setText(textnum);
	}
	//���ô���������һ�ص�ͼƬ������ı�
	if (blocknum<9)
	{
		btnlist->at(blocknum)->setVisible(true);
		btnlist->at(blocknum)->loadTextures("unlock.png", "unlock.png", "unlock.png");
		textlist->at(blocknum)->setVisible(true);
		char tx[10];
		sprintf(tx, "%d", blocknum + 1);
		string b = tx;
		string textnum = "1-" + b;
		textlist->at(blocknum)->setText(textnum);
	}

	//����������ʾ����
	char stext[10];
	sprintf(stext, "%d", starnum);
	string b = stext;
	startext->setText("/"+b);

	//ʵ��������ͼ�����
	multilayer =LayerMultiplex::create();
	this->addChild(multilayer);

	
	//Ϊ��ť����Ӧ�Ĵ����¼�
	librarybtn->addTouchEventListener(CC_CALLBACK_2(BlockScene::libraryTouchDown, this));
	upgradebtn->addTouchEventListener(CC_CALLBACK_2(BlockScene::upgradeTouchDown, this));
	backbtn->addTouchEventListener(CC_CALLBACK_2(BlockScene::backTouchDown, this));
	for (int i = 0; i <9;i++)
	{
		btnlist->at(i)->addTouchEventListener(CC_CALLBACK_2(BlockScene::certainblockTouchDown, this, i));
	}
	
	return true;
}



Layer* BlockScene::popCertainBlock(int i){

	//������Դ�ļ�����ͼ��
	Layer* blocklayer = (Layer*)CSLoader::createNode("SelectedBlock.csb");

	//����ͼ������λ��
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint pointCenter = ccp(winSize.width / 2 - 320, winSize.height / 2 - 240);
	blocklayer->setPosition(pointCenter);
	//this->addChild(blocklayer);

	//��ȡͼ���а�ť����
	fightbtn = (Button*)blocklayer->getChildByName("fight");
	closebtn = (Button*)blocklayer->getChildByName("close");
	suolue = (Sprite*)blocklayer->getChildByName("suolue");
	blocktitle = (Text*)blocklayer->getChildByName("selectedblocktitletext");
	blockinfo = (Text*)blocklayer->getChildByName("blockinfo");
	blockid = (Text*)blocklayer->getChildByName("blocknumber");

	//��plist�ļ��ж�ȡ������ص������ַ�									 
	CCDictionary* plistDic = CCDictionary::createWithContentsOfFile("blockinfo.plist");
	//intתstring
	char na[10];
	sprintf(na, "%d", i+1);
	string bid = na;
	CCString* blockname = (CCString *)plistDic->objectForKey("block"+bid+"name");
	CCString* blockdescribtion = (CCString *)plistDic->objectForKey("block"+bid+"info");
	CCString* blocknumber = (CCString *)plistDic->objectForKey("block"+bid+"id");
	
	//���ùؿ����⡢����ͼ�����ܡ����
	suolue->setTexture("suolue"+bid+".jpg");
	blocktitle->setText(blockname->getCString());
	blockinfo->setText(blockdescribtion->getCString());
	blockid->setText(blocknumber->getCString());

	//Ϊ��ť��ӵ�������¼�
	fightbtn->addTouchEventListener(CC_CALLBACK_2(BlockScene::fightTouchDown, this,i));
	closebtn->addTouchEventListener(CC_CALLBACK_2(BlockScene::closeTouchDown, this));

	return blocklayer;
}

Layer *BlockScene::popLibrary(){

	//������Դ�ļ�����ͼ��
	Layer* librarylayer = (Layer*)CSLoader::createNode("LibraryLayer.csb");

	//����ͼ������λ��
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint pointCenter = ccp(winSize.width / 2 - 320, winSize.height / 2 - 240);
	librarylayer->setPosition(pointCenter);
	//this->addChild(librarylayer);

	//��ȡͼ���а�ť����
	wolfbtn = (Button*)librarylayer->getChildByName("wolfinfo");
	towerbtn = (Button*)librarylayer->getChildByName("towerinfo");
	tipbtn = (Button*)librarylayer->getChildByName("tipinfo");
	backtoblockbtn = (Button*)librarylayer->getChildByName("backtoblock");

	//Ϊ��ť��ӵ�������¼�
	wolfbtn->addTouchEventListener(CC_CALLBACK_2(BlockScene::wolfTouchDown, this));
	towerbtn->addTouchEventListener(CC_CALLBACK_2(BlockScene::towerTouchDown, this));
	tipbtn->addTouchEventListener(CC_CALLBACK_2(BlockScene::tipTouchDown, this));
	backtoblockbtn->addTouchEventListener(CC_CALLBACK_2(BlockScene::closeTouchDown, this));
	return librarylayer;

}

Layer* BlockScene::popTower(){

	//������Դ�ļ�����ͼ��
	Layer* towerlayer = (Layer*)CSLoader::createNode("TowerLibraryLayer.csb");

	//����ͼ������λ��
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint pointCenter = ccp(winSize.width / 2 - 320, winSize.height / 2 - 240);
	towerlayer->setPosition(pointCenter);

	//��ȡͼ���а�ť����
	tower1btn = (Button*)towerlayer->getChildByName("tower1");
	tower2btn = (Button*)towerlayer->getChildByName("tower2");
	tower3btn = (Button*)towerlayer->getChildByName("tower3");
	tower4btn = (Button*)towerlayer->getChildByName("tower4");
	tower5btn = (Button*)towerlayer->getChildByName("tower5");
	tower6btn = (Button*)towerlayer->getChildByName("tower6");
	tower7btn = (Button*)towerlayer->getChildByName("tower7");
	tower8btn = (Button*)towerlayer->getChildByName("tower8");

	backbtn	= (Button*)towerlayer->getChildByName("back");
	closebtn = (Button*)towerlayer->getChildByName("close");
	towername = (Text*)towerlayer->getChildByName("towernametext");
	towerinfo = (Text*)towerlayer->getChildByName("towerinfotext");
	damage = (Text*)towerlayer->getChildByName("damagetext");
	speed = (Text*)towerlayer->getChildByName("speedtext");
	range = (Text*)towerlayer->getChildByName("rangetext");
	specialtext = (Text*)towerlayer->getChildByName("specialtext");

	//�����������ϰ�ť�ӵ�Vector��
	//���Vector��Ϊ�գ�������մ���
	if (!towerlibbtn->empty())
	{
		towerlibbtn->clear();
	}

	towerlibbtn->insert(0, tower1btn);
	towerlibbtn->insert(1, tower2btn);
	towerlibbtn->insert(2, tower3btn);
	towerlibbtn->insert(3, tower4btn);
	towerlibbtn->insert(4, tower5btn);
	towerlibbtn->insert(5, tower6btn);
	towerlibbtn->insert(6, tower7btn);
	towerlibbtn->insert(7, tower8btn);
	//Ϊ��ť��ӵ�������¼�
	for (int i = 0; i < 8;i++)
	{
		towerlibbtn->at(i)->addTouchEventListener(CC_CALLBACK_2(BlockScene::certaintowerTouchDown,this,i));
	}
	closebtn->addTouchEventListener(CC_CALLBACK_2(BlockScene::closeTouchDown, this));
	backbtn->addTouchEventListener(CC_CALLBACK_2(BlockScene::leaveTouchDown, this));

	return towerlayer;

}

Layer* BlockScene::popWolf(){

	//������Դ�ļ�����ͼ��
	Layer* wolflayer = (Layer*)CSLoader::createNode("WolfLibraryLayer.csb");

	//����ͼ������λ��
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint pointCenter = ccp(winSize.width / 2 - 320, winSize.height / 2 - 240);
	wolflayer->setPosition(pointCenter);

	//��ȡͼ���а�ť����
	wolf1btn = (Button*)wolflayer->getChildByName("wolf1");
	wolf2btn = (Button*)wolflayer->getChildByName("wolf2");
	wolf3btn = (Button*)wolflayer->getChildByName("wolf3");
	wolf4btn = (Button*)wolflayer->getChildByName("wolf4");
	wolf5btn = (Button*)wolflayer->getChildByName("wolf5");
	wolf6btn = (Button*)wolflayer->getChildByName("wolf6");

	backbtn = (Button*)wolflayer->getChildByName("back");
	closebtn = (Button*)wolflayer->getChildByName("close");
	wolfname = (Text*)wolflayer->getChildByName("wolfnametext");
	wolfinfo = (Text*)wolflayer->getChildByName("wolfinfotext");
	health = (Text*)wolflayer->getChildByName("healthtext");
	movingspeed = (Text*)wolflayer->getChildByName("movingspeedtext");
	

	//�����������ϰ�ť�ӵ�Vector��
	//���Vector��Ϊ�գ�������մ���
	if (!wolflibbtn->empty())
	{
		wolflibbtn->clear();
	}

	wolflibbtn->insert(0, wolf1btn);
	wolflibbtn->insert(1, wolf2btn);
	wolflibbtn->insert(2, wolf3btn);
	wolflibbtn->insert(3, wolf4btn);
	wolflibbtn->insert(4, wolf5btn);
	wolflibbtn->insert(5, wolf6btn);
	//Ϊ��ť��ӵ�������¼�
	for (int i = 0; i < 6; i++)
	{
		wolflibbtn->at(i)->addTouchEventListener(CC_CALLBACK_2(BlockScene::certainwolfTouchDown, this, i));
	}
	closebtn->addTouchEventListener(CC_CALLBACK_2(BlockScene::closeTouchDown, this));
	backbtn->addTouchEventListener(CC_CALLBACK_2(BlockScene::leaveTouchDown, this));

	return wolflayer;

}

//������ť����Ӧ�����¼���������
//����
Layer *BlockScene::popUpgrade(){

	//������Դ�ļ�����ͼ��
	Layer* upgradelayer = (Layer*)CSLoader::createNode("UpgradeLayer.csb");

	//����ͼ������λ��
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint pointCenter = ccp(winSize.width / 2 - 320, winSize.height / 2 - 240);
	upgradelayer->setPosition(pointCenter);




	//��ȡͼ���а�ť����
	uBtn1 = (Button*)upgradelayer->getChildByName("uBtn1");
	uBtn2 = (Button*)upgradelayer->getChildByName("uBtn2");
	uBtn3 = (Button*)upgradelayer->getChildByName("uBtn3");
	uBtn4 = (Button*)upgradelayer->getChildByName("uBtn4");
	uBtn5 = (Button*)upgradelayer->getChildByName("uBtn5");
	uBtn6 = (Button*)upgradelayer->getChildByName("uBtn6");
	uBtn7 = (Button*)upgradelayer->getChildByName("uBtn7");
	uBtn8 = (Button*)upgradelayer->getChildByName("uBtn8");
	uBtn9 = (Button*)upgradelayer->getChildByName("uBtn9");
	uBtn10 = (Button*)upgradelayer->getChildByName("uBtn10");
	uBtn11 = (Button*)upgradelayer->getChildByName("uBtn11");
	uBtn12 = (Button*)upgradelayer->getChildByName("uBtn12");
	uBtn13 = (Button*)upgradelayer->getChildByName("uBtn13");
	uBtn14 = (Button*)upgradelayer->getChildByName("uBtn14");
	uBtn15 = (Button*)upgradelayer->getChildByName("uBtn15");
	uBtn16 = (Button*)upgradelayer->getChildByName("uBtn16");
	uBtn17 = (Button*)upgradelayer->getChildByName("uBtn17");
	uBtn18 = (Button*)upgradelayer->getChildByName("uBtn18");
	uBtn19 = (Button*)upgradelayer->getChildByName("uBtn19");
	uBtn20 = (Button*)upgradelayer->getChildByName("uBtn20");
	uBtn21 = (Button*)upgradelayer->getChildByName("uBtn21");
	uBtn22 = (Button*)upgradelayer->getChildByName("uBtn22");
	uBtn23 = (Button*)upgradelayer->getChildByName("uBtn23");
	uBtn24 = (Button*)upgradelayer->getChildByName("uBtn24");
	uBtn25 = (Button*)upgradelayer->getChildByName("uBtn25");
	uBtn26 = (Button*)upgradelayer->getChildByName("uBtn26");
	uBtn27 = (Button*)upgradelayer->getChildByName("uBtn27");
	uBtn28 = (Button*)upgradelayer->getChildByName("uBtn28");


	//��Button����ͳһ����uBtnlist
	if (!uBtnlist->empty())
	{
		uBtnlist->clear();
	}
	uBtnlist->insert(0, uBtn1);
	uBtnlist->insert(1, uBtn2);
	uBtnlist->insert(2, uBtn3);
	uBtnlist->insert(3, uBtn4);
	uBtnlist->insert(4, uBtn5);
	uBtnlist->insert(5, uBtn6);
	uBtnlist->insert(6, uBtn7);
	uBtnlist->insert(7, uBtn8);
	uBtnlist->insert(8, uBtn9);
	uBtnlist->insert(9, uBtn10);
	uBtnlist->insert(10, uBtn11);
	uBtnlist->insert(11, uBtn12);
	uBtnlist->insert(12, uBtn13);
	uBtnlist->insert(13, uBtn14);
	uBtnlist->insert(14, uBtn15);
	uBtnlist->insert(15, uBtn16);
	uBtnlist->insert(16, uBtn17);
	uBtnlist->insert(17, uBtn18);
	uBtnlist->insert(18, uBtn19);
	uBtnlist->insert(19, uBtn20);
	uBtnlist->insert(20, uBtn21);
	uBtnlist->insert(21, uBtn22);
	uBtnlist->insert(22, uBtn23);
	uBtnlist->insert(23, uBtn24);
	uBtnlist->insert(24, uBtn25);
	uBtnlist->insert(25, uBtn26);
	uBtnlist->insert(26, uBtn27);
	uBtnlist->insert(27, uBtn28);


	stars = (Text*)upgradelayer->getChildByName("star");
	reset = (Button*)upgradelayer->getChildByName("reset");
	confirm = (Button*)upgradelayer->getChildByName("confirm");
	nameText = (Text*)upgradelayer->getChildByName("name");
	infoText = (Text*)upgradelayer->getChildByName("info");
	singleStar = (Text*)upgradelayer->getChildByName("singlestar");
	btnImage = (Sprite*)upgradelayer->getChildByName("buttonimage");
	upgrade = (Button*)upgradelayer->getChildByName("upgrade");

	//��Json�ļ��ж�ȡ���üӵ����������									 
	InfoHandle handle;
	starNum = handle.getUserInfo().getUpgradeNumber();
	//intתΪstring
	char dd[5];
	sprintf(dd, "%d", starNum);
	std::string bb = dd;
	stars->setText(bb);
	

	
	for (int i = 0; i < 28; i++)
	{
		if (handle.getUpMark(i)==false)
		{	
			char b[10];
			sprintf(b, "%d", i + 1);
			string pic = b;
			
			string picname = "uu" + pic+".png";
			uBtnlist->at(i)->loadTextures(picname,picname,picname);
		}
		else
		{
			char b[10];
			sprintf(b, "%d", i + 1);
			string pic = b;
			string picname = "u" + pic + ".png";
			uBtnlist->at(i)->loadTextures(picname, picname, picname);
		}
		
		uBtnlist->at(i)->addTouchEventListener(CC_CALLBACK_2(BlockScene::uBtnTouchDown, this, i));

	}
	//Ϊ��ť��ӵ�������¼�
	reset->addTouchEventListener(CC_CALLBACK_2(BlockScene::resetTouchDown, this));
	confirm->addTouchEventListener(CC_CALLBACK_2(BlockScene::closeTouchDown, this));
	return upgradelayer;
}

//ͼ�갴�µ���Ӧ�����¼�
void  BlockScene::uBtnTouchDown(Control::Ref* pSender, Widget::TouchEventType type, int i){
	char sp[10];
	sprintf(sp, "%d", i + 1);
	string t = sp;
	
	switch (type)
		{
		case Widget::TouchEventType::BEGAN:
		case Widget::TouchEventType::MOVED:

			break;
		case Widget::TouchEventType::ENDED:
		{
											 

												  //��plist�ļ��ж�ȡ������ص��ַ�									 
												  CCDictionary* plistDic = CCDictionary::createWithContentsOfFile("upgrade.plist");
												  CCString* starr = (CCString *)plistDic->objectForKey("star" + t);
												  CCString* name1 = (CCString *)plistDic->objectForKey("name" + t);
												  CCString* info1 = (CCString *)plistDic->objectForKey("info" + t);

												  nameText->setText(name1->getCString());
												  infoText->setText(info1->getCString());
												  singleStar->setText(starr->getCString());
												  btnImage->setTexture("u"+t+".png");

												  upgrade->addTouchEventListener(CC_CALLBACK_2(BlockScene::upTouchDown, this, i));
											 
											 
		}
		case Widget::TouchEventType::CANCELED:
			break;
		default:
			break;

		}
	
}

//ͼ���Ӧȷ����ť����Ӧ�����¼�
void BlockScene::upTouchDown(Control::Ref* pSender, Widget::TouchEventType type, int i){
	char sp[10];
	sprintf(sp, "%d", i + 1);
	string t = sp;
	string tstype[7] = { "arrowtower", "slowtower", "poisontower", "turrettower", "ice", "wind", "fire" };
	string towerproperty[4] = { "damage", "attackspeed", "attackrange", "cost" };//��������һЩ��������
	string skillproperty[4] = { "damage", "time", "range", "strong" };//���ܵ���������

	string towername;
	string valuetype;


	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
	case Widget::TouchEventType::MOVED:
		break;

	case Widget::TouchEventType::ENDED:
	{
		towername = tstype[i / 4];//��ȡһ�������������ܵ�����
		if (i < 16){
			valuetype = towerproperty[i % 4];//��ȡһ����������������
		}
		else{
			valuetype = skillproperty[i % 4];
		}

		//��ȡplist�ļ��д洢����������ʼֵ��������������
		CCDictionary* plistDic = CCDictionary::createWithContentsOfFile("upgrade.plist");
		CCString* value = (CCString *)plistDic->objectForKey("uBtn" + t);
		CCString* starr = (CCString *)plistDic->objectForKey("star" + t);
		CCString* ori = (CCString *)plistDic->objectForKey("origin" + t);

		int snum = starr->intValue();
		double valueup = value->doubleValue();
		double originvalue = ori->doubleValue();

		if (starNum>0&&starNum - snum >= 0 && btnState[i] == false)
		{
			originvalue += originvalue*valueup;//���¼�������ֵ
			starNum -= snum;//������������
			char sn[5];
			sprintf(sn, "%d", starNum);
			std::string stext = sn;
			stars->setText(stext);//������������
			btnState[i] = true;

			InfoHandle handle;
			if (i<16)
			{
				handle.updateTowerInfoByProperty(towername, valuetype, originvalue);
			}
			else{
				handle.updateSkillInfoByProperty(towername, valuetype, originvalue);
			}
			//�����û����üӵ���������
			User user = handle.getUserInfo();
			user.setUpgradeNumber(starNum);
			handle.updateUserInfo(user);
			uBtnlist->at(i)->loadTextures("u" + t + ".png", "u" + t + ".png", "u" + t + ".png");
			string btn = "btn" + t;
			handle.updateUpMark(btn, true);
		}
	}
	case Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}

}
//���ð�ť����Ӧ�����¼�
void  BlockScene::resetTouchDown(Control::Ref* pSender, Widget::TouchEventType type){
	Layer* uglayer = popUpgrade();
	InfoHandle handle;
	
	
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:

	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:{
										   for (int i = 0; i < 28; i++){
											   char sp[10];
											   sprintf(sp, "%d", i + 1);
											   string t = sp;
											   string btn = "btn" + t;
											   btnState[i] = false;
											   string picname = "uu" + t + ".png";
											   uBtnlist->at(i)->loadTextures(picname,picname,picname);
											   handle.updateUpMark(btn, false);

										   }
	string tstype[7] = { "arrowtower", "slowtower", "poisontower", "turrettower", "ice", "wind", "fire" };
	for (int i = 0; i < 4;i++)
	{
		handle.updateTowerInfo(handle.getTowerInfoFromBackUp(tstype[i], "towerInfo2.json"));
	}
	for (int i = 4; i < 7;i++)
	{
		handle.updateSkillInfo(handle.getSkillInfoFromBackUp(tstype[i], "skillInfo2.json"));
	}

	User user = handle.getUserInfo();
	user.setUpgradeNumber(starnum);
	handle.updateUserInfo(user);
	starNum = starnum;
	char s[10];
	sprintf(s, "%d", starnum);
	string st = s;
	stars->setText(st);
	multilayer->addLayer(uglayer);		//�����Ͽ��������������ͼ�������
	layernum++;		//ͼ��������һ
	multilayer->switchTo(layernum - 1);	//��ת����ͼ��
	

	}
	case Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}

}

//ȷ���ӵ�İ�ť�����¼�
void  BlockScene::upgradeTouchDown(Control::Ref* pSender, Widget::TouchEventType type){

	Layer* uglayer = popUpgrade();
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		break;
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:
		multilayer->addLayer(uglayer);		//�����Ͽ��������������ͼ�������
		layernum++;							//ͼ��������һ
		multilayer->switchTo(layernum - 1);	//��ת����ͼ��

	case Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}

}

//�ؿ���ť����Ӧ�����¼���������
void BlockScene::certainblockTouchDown(Control::Ref* pSender, Widget::TouchEventType type, int i){
	Layer* certainblocklayer = popCertainBlock(i);
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		multilayer->addLayer(certainblocklayer);		//�����Ͽ��������������ͼ�������
		layernum++;							//ͼ��������һ
		multilayer->switchTo(layernum - 1);	//��ת����ͼ��
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}
//С�ǰ�ť�İ�����������Ӧ�¼�
void BlockScene::certainwolfTouchDown(Control::Ref* pSender, Widget::TouchEventType type, int i){
	//��ת����Ӧͼ��
	//������Ͽ�ͼ�����
	Layer* wolflayer = popWolf();
	//���ݰ������ͽ�����Ӧ
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		break;
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:
	{
										  //��plist�ļ��ж�ȡ������ص������ַ�									 
										  CCDictionary* plistDic = CCDictionary::createWithContentsOfFile("wolflib.plist");
										  InfoHandle handle;
										  string wstr = handle.intostr(i + 1);
										  CCString* wname = (CCString *)plistDic->objectForKey("wolf" + wstr + "name");
										  CCString* winfo = (CCString *)plistDic->objectForKey("wolf" + wstr + "info");
										  CCString* whealth = (CCString *)plistDic->objectForKey("health"+wstr);
										  CCString* wmovingspeed = (CCString *)plistDic->objectForKey("movingspeed"+wstr);
										 
										  wolfname->setText(wname->getCString());
										  wolfinfo->setText(winfo->getCString());
										  health->setText(whealth->getCString());
										  movingspeed->setText(wmovingspeed->getCString());
										  
										  multilayer->addLayer(wolflayer);		//�����Ͽ��������������ͼ�������
										  layernum++;							//ͼ��������һ
										  multilayer->switchTo(layernum - 1);	//��ת����ͼ��
	}
	case Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

//��������ť�İ�����������Ӧ�¼�
void BlockScene::certaintowerTouchDown(Control::Ref* pSender, Widget::TouchEventType type, int i){
	//��ת����Ӧͼ��
	//������Ͽ�ͼ�����
	Layer* towerlayer = popTower();
	//���ݰ������ͽ�����Ӧ
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		break;
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:
	{
	//��plist�ļ��ж�ȡ������ص������ַ�									 
	CCDictionary* plistDic = CCDictionary::createWithContentsOfFile("towerlib.plist");
	char tn[10];
	sprintf(tn,"%d",i+1);
	string tstr = tn;
	CCString* tname		= (CCString *)plistDic->objectForKey("tower" + tstr + "name");
	CCString* tinfo		= (CCString *)plistDic->objectForKey("tower" + tstr + "info");
	CCString* tdamage	= (CCString *)plistDic->objectForKey("tower" + tstr + "damage");
	CCString* tspeed	= (CCString *)plistDic->objectForKey("tower" + tstr + "speed");
	CCString* trange	= (CCString *)plistDic->objectForKey("tower" + tstr + "range");
	CCString* tspecial	= (CCString *)plistDic->objectForKey("tower" + tstr + "special");


	towername->setText(tname->getCString());
	towerinfo->setText(tinfo->getCString());
	damage->setText(tdamage->getCString());
	speed->setText(tspeed->getCString());
	range->setText(trange->getCString());
	specialtext->setText(tspecial->getCString());
	multilayer->addLayer(towerlayer);		//�����Ͽ��������������ͼ�������
	layernum++;							//ͼ��������һ
	multilayer->switchTo(layernum - 1);	//��ת����ͼ��
	}
	case Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

//���Ͽⰴť�İ�����Ӧ�¼�
void  BlockScene::libraryTouchDown(Control::Ref* pSender, Widget::TouchEventType type){
	//��ת����Ӧͼ��
	//������Ͽ�ͼ�����
	Layer* liblayer = popLibrary();
	//���ݰ������ͽ�����Ӧ
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		break;
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:
		multilayer->addLayer(liblayer);		//�����Ͽ��������������ͼ�������
		layernum++;							//ͼ��������һ
		multilayer->switchTo(layernum - 1);	//��ת����ͼ��

	case Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
	
	
}


void  BlockScene::backTouchDown(Control::Ref* pSender, Widget::TouchEventType type){
	auto initscene = HelloWorld::createScene();
	//����ͼ������
	layernum = 0;
	Director::sharedDirector()->replaceScene(initscene);
}

void BlockScene::fightTouchDown(Control::Ref* pSender, Widget::TouchEventType type,int i){
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
	{
	multilayer->removeAllComponents();
	layernum = 0;
	SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/button.wav").c_str(), false);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Play.plist");

	//��ȡ��Ӧ�����صĹؿ�plist��Դ�ļ�
	InfoHandle handle;
	string fileName = "levelInfo_"+handle.intostr(i)+".plist";
	string bgmMusic = "block1bgm.mp3";
	//��ӵ�ǰ�ؿ����
	UserDefault::getInstance()->setIntegerForKey("currBlock", i);
	GameManager::getInstance()->clear();
	//����ؿ���Դ
	LoadLevelinfo::createLoadLevelinfo(fileName.c_str())->readLevelInfo();
	Director::getInstance()->replaceScene(TransitionFadeBL::create(0.1f, PlayLayer::createScene()));
	SimpleAudioEngine::getInstance()->playBackgroundMusic(FileUtils::getInstance()->fullPathForFilename("sound/"+bgmMusic).c_str(), true);
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.1f);
	}
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
	
}

void BlockScene::closeTouchDown(Control::Ref* pSender, Widget::TouchEventType type){
	auto blockscene = BlockScene::createScene();
	//����ͼ������
	multilayer->removeAllComponents();
	layernum = 0;
	Director::sharedDirector()->replaceScene(blockscene);
}

void  BlockScene::wolfTouchDown(Control::Ref* pSender, Widget::TouchEventType type){
	//��ת����Ӧͼ��
	//��ת����Ӧͼ��
	Layer* wolflayer;
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		break;
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:
		wolflayer= popWolf();
		multilayer->addLayer(wolflayer);
		layernum++;
		multilayer->switchTo(layernum - 1);
	case Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
	
}
void  BlockScene::towerTouchDown(Control::Ref* pSender, Widget::TouchEventType type){
	//��ת����Ӧͼ��
	Layer* towerlayer = popTower();
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		break;
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:
		multilayer->addLayer(towerlayer);
		layernum++;
		multilayer->switchTo(layernum - 1);
	case Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}

}
void  BlockScene::tipTouchDown(Control::Ref* pSender, Widget::TouchEventType type){
	//popBlock();
}


//������һ����Ӧ����
void  BlockScene::leaveTouchDown(Control::Ref* pSender, Widget::TouchEventType type){
	//��ת����Ӧͼ��
	Layer* liblayer = popLibrary();
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:
		multilayer->addLayer(liblayer);
		layernum++;
		multilayer->switchTo(layernum - 1);
	case Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
	
}

