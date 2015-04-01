
#ifndef __SheepVillageDefense__PlayLayer__
#define __SheepVillageDefense__PlayLayer__

#include <iostream>
#include "cocos2d.h"
#include "Thief.h"
#include "ArrowTower.h"
#include "PoisonTower.h"
#include "CannonTower.h"
#include "SlowTower.h"
//#include "AttackTower.h"
//#include "MultiDirTower.h"
#include "TowerPanleLayer.h"
#include "GameManager.h"
#include "EvolveTowerPanelLayer.h"
#include "Tower.h"

USING_NS_CC;
class PlayLayer : public Layer
{
public:
    PlayLayer();
    ~PlayLayer();
    
    virtual bool init() override;
    static Scene* createScene();
    CREATE_FUNC(PlayLayer);
    
    virtual void update(float dt) override;
    virtual bool onTouchBegan(Touch *touch, Event *event) override;
    
    GroupEnemy* currentGroup();
	GroupEnemy* nextGroup();
	void addGroupEnemy();
	void logic(float dt);
	void twisterlogic(float dt);
	void fireBallExplode(Node* pSender,Point point);
	void fireBallExplodeLogic(float dt);
	void skillsCool(float dt);
	void skill01Logic(float dt);
	void initLabelText();
	void doPause();
	void clickSetting();	
	void addUpTowerChoosePanel(Point point, TowerBase* tower);
	void upOrSellTower();
	void evolveOrSellTower();
	void removeEnemy();
	void checkBullet();
	void addEvolveTowerChoosePanel(Point point, TowerBase* tower);

	void startGame();
	int MatrixIndex;
	//Vector<TMXObjectGroup*> mapobject[5];
	//Vector<ValueMap> valobject[5];
	//Vector<Vector<Node*>> pointvec[5];
private:
    SpriteBatchNode *spriteSheet;
    TMXTiledMap* map;
	TMXLayer* bgLayer;
	TMXObjectGroup* objects;
	TMXObjectGroup* objects01;
	TMXObjectGroup* objects02;
	Vector<Node*> pointsVector;
	Vector<Node*> pointsVector01;
	Vector<Node*> pointsVector02;
	int roteNum;
	GameManager* instance;
    float offX;
	static int mapobjnum;//地图对象层数量
	int groupCounter;
	int money;
    
    Label* moneyLabel;
	Label* groupLabel;
	Label* groupTotalLabel;
	Layer* toolLayer;
	Layer* skillsLayer;
	void initToolLayer();
	void initSkillsLayer();
	void addSkill01Timmer();
	void addSkill02Timmer();
	void addSkill03Timmer();
	CC_SYNTHESIZE(float, playHpPercentage, PlayHpPercentage);
	CC_SYNTHESIZE(float, skill01CoolPercentage, Skill01CoolPercentage);
	CC_SYNTHESIZE(float, skill02CoolPercentage, Skill02CoolPercentage);
	CC_SYNTHESIZE(float, skill03CoolPercentage, Skill03CoolPercentage);
	CC_SYNTHESIZE_READONLY(ProgressTimer*, playHpBar, PlayHpBar);
	CC_SYNTHESIZE_READONLY(ProgressTimer*, skill01CoolBar, Skill01CoolBar);
	CC_SYNTHESIZE_READONLY(ProgressTimer*, skill02CoolBar, Skill02CoolBar);
	CC_SYNTHESIZE_READONLY(ProgressTimer*, skill03CoolBar, Skill03CoolBar);
	bool isSuccessful;
    
    bool isTouchEnable;
    TowerPanleLayer* chooseTowerpanel;

	UpTowerPanleLayer * upTowerPanleLayer;
	EvolveTowerPanleLayer * evolveTowerPanleLayer;

    void addTowerChoosePanel(Point position);
    Point convertTotileCoord(Point position);
	Point convertToMatrixCoord(Point position);
	void checkAndAddTowerPanle(Point position);
	void CollisionDetection();
    void enemyIntoHouse();
    void menuBackCallback(Ref* pSender);
    
	Point towerPos;
    void initPointsVector(float offX);
    void addEnemy();
    void addTower();
    TowerBase **towerMatrix;
	Sprite* skill01;
	Sprite* skillsSprite;
	bool skill01Ready;
	bool skill01Chose;
	void skill01Release();
	Sprite* skill02;
	bool skill02Ready;
	bool skill02Chose;
	void skill02Release(Point point);
	Sprite* twisterSprite;
	Rect twisterRect;
	Sprite* skill03;
	bool skill03Ready;
	bool skill03Chose;
	void skill03Release(Point point);
	void createFireBall(Point point,float relativeHeight);
	Sprite* fireBallSprite;
	Sprite* fireBallExplodeSprite;
	Rect fireBallExplodeRect;
	void moveToOriginPoint(float dt);
	Sprite* pauseBtn;
	Sprite* speedBtn;
	bool isSpeeding;
	Sprite *settingBtn;
	Sprite * startBtn;
	bool isStart;
};

#endif /* defined(__thiefTD__PlayLayer__) */
