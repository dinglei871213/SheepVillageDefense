
#define MAP_WIDTH (15)
#define MAP_HEIGHT (10)

#include "PlayLayer.h"
#include "GameManager.h"
#include "SimpleAudioEngine.h"
#include "extensions/cocos-ext.h"
#include "EnemyBase.h"
#include "ResultScene.h"
#include "PlayPause.h"
#include "InfoHandle.h"
#include "PlaySetting.h"
USING_NS_CC_EXT;
using namespace CocosDenshion;

PlayLayer::PlayLayer()
	:isTouchEnable(false)
	,spriteSheet(NULL)
	,map(NULL)
	, roteNum(0)
	, pointsVector(NULL)
	,pointsVector01(NULL)
	,pointsVector02(NULL)
	, objects(NULL)
	, objects01(NULL)
	, objects02(NULL)
	,chooseTowerpanel(NULL)
	,towerMatrix(NULL)
	,groupCounter(0)
	,money(0)
	,playHpBar(NULL)
	,skill01CoolBar(NULL)
	,playHpPercentage(100)
	,skill01CoolPercentage(100)
	,skill01Ready(false)
	,skill01Chose(false)
	,skill02CoolPercentage(100)
	,skill02Ready(false)
	,skill02Chose(false)
	,skill03CoolPercentage(100)
	,skill03Ready(false)
	,skill03Chose(false)
	,moneyLabel(NULL)
	,groupLabel(NULL)
	,groupTotalLabel(NULL)
	, isSuccessful(false)
	, upTowerPanleLayer(NULL)
	, isSpeeding(false)
	, evolveTowerPanleLayer(NULL)
{
}
int PlayLayer::mapobjnum = 0;

PlayLayer::~PlayLayer()
{
	if (towerMatrix) {
		free(towerMatrix);
	}
	pointsVector01.clear();
	pointsVector02.clear();
}

Scene *PlayLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = PlayLayer::create();
	scene->addChild(layer);
	return scene;
}

bool PlayLayer::init()
{
	if (!Layer::init()) {
		return false;
	}

	Size winSize = Director::getInstance()->getWinSize();
	instance = GameManager::getInstance();
	instance->setTowerInfo();

	auto gameBg = Sprite::create(instance->getCurBgName());
	gameBg->setPosition (Point(winSize.width / 2 ,winSize.height / 2));
	addChild(gameBg, -20);

	map = TMXTiledMap::create(instance->getCurMapName());
	bgLayer = map->getLayer("bg");
	bgLayer->setAnchorPoint(Point(0.5f, 0.5f));
	bgLayer->setPosition(Point(winSize.width / 2 ,winSize.height / 2));
	roteNum = map->getObjectGroups().size();
	if (roteNum ==1)
	{
		objects = map->getObjectGroup("obj01");
	}else
	{
		objects01 = map->getObjectGroup("obj01");
		objects02 = map->getObjectGroup("obj02");
	}



	/*pointvec->insert(0,pointsVector01);
	pointvec->insert(1, pointsVector02);
	pointvec->insert(2, pointsVector03);
	pointvec->insert(3, pointsVector04);
	pointvec->insert(4, pointsVector05);*/
	this->addChild(map, -10);

	pauseBtn = Sprite::create();
	pauseBtn->setTexture("anniu20.png");
	pauseBtn->setPosition(Point(winSize.width * 8 / 9 - 20, winSize.height * 24 / 25));
	this->addChild(pauseBtn);

	speedBtn = Sprite::create();
	speedBtn->setTexture("anniu23.png");
	speedBtn->setPosition(Point(winSize.width * 8 / 9 + 30, winSize.height * 24 / 25));
	this->addChild(speedBtn);

	settingBtn = Sprite::create();
	settingBtn->setTexture("anniu22.png");
	settingBtn->setPosition(Point(winSize.width * 8 / 9 + 80, winSize.height * 24 / 25));
	this->addChild(settingBtn);


	initToolLayer();
	initSkillsLayer();

	offX = ( map->getContentSize().width - winSize.width )/ 2;
	initPointsVector(offX);
	
	startBtn = Sprite::create();
	startBtn->setScale(0.4);
	startBtn->setTexture("anniu19.png");
	startBtn->setPosition(Point(winSize.width * 1 / 20, winSize.height * 24 / 25));
	this->addChild(startBtn);
	isStart = false;


	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(PlayLayer::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	scheduleUpdate();

	int arraySize = sizeof(TowerBase *) * MAP_WIDTH * MAP_HEIGHT;
	towerMatrix = (TowerBase **)malloc(arraySize);
	memset((void*)towerMatrix, 0, arraySize);

	for (int row = 0; row < MAP_HEIGHT; row++) {
		for (int col = 0; col < MAP_WIDTH; col++) {
			towerMatrix[row * MAP_WIDTH + col] = NULL;
		}
	}
	setTouchEnabled(true);
	return true;
}

void PlayLayer::clickSetting()
{
	Size winSize = Director::getInstance()->getWinSize();
	RenderTexture *renderTexture = RenderTexture::create(winSize.width, winSize.height);
	renderTexture->begin();
	this->getParent()->visit();
	renderTexture->end();
	Director::getInstance()->pushScene(PlaySetting::createSettingScene(renderTexture));
}



void PlayLayer::doPause()
{
	RenderTexture *renderTexture = RenderTexture::create(960, 640);
	renderTexture->begin();
	this->getParent()->visit();
	renderTexture->end();
	Director::getInstance()->pushScene(PlayPause::createPauseScene(renderTexture));
}

void PlayLayer::skill01Logic(float dt)
{
	InfoHandle handle;
	Vector<EnemyBase*> enemyNeedToDelete;
	int currentEnemyNum=instance->enemyVector.size();
	for(int i=0;i<currentEnemyNum;i++){
		auto currentEnemy=instance->enemyVector.at(i);
		int hp=currentEnemy->getCurrHp();
		hp--;
		currentEnemy->setCurrHp(hp);

		auto currHpPercentage = currentEnemy->getHpPercentage();
		auto offHp = 100 / currentEnemy->getMaxHp();
		currHpPercentage -= offHp;
		if(currHpPercentage < 0){
			currHpPercentage = 0;
		}
		currentEnemy->setHpPercentage(currHpPercentage);
		currentEnemy->getHpBar()->setPercentage(currHpPercentage);

		if(hp <= 0)
		{
			enemyNeedToDelete.pushBack(currentEnemy);
			auto valueMoney = currentEnemy->getVaule();
			money += valueMoney;
			auto moneyText = handle.intostr(money);
			moneyLabel->setString(moneyText);
		}
	}
	for (EnemyBase* enemyTemp : enemyNeedToDelete)
	{
		enemyTemp->enemyExpload();
		instance->enemyVector.eraseObject(enemyTemp);
	}
	enemyNeedToDelete.clear();
}

void PlayLayer::skill01Release()
{
	//粒子效果
	Size winSize = Director::getInstance()->getWinSize();
	ParticleSystem* snow = ParticleSystemQuad::create("snow01.plist");
	snow->retain();
	ParticleBatchNode *batch = ParticleBatchNode::createWithTexture(snow->getTexture());
	batch->addChild(snow);
	snow->setPosition(Point(winSize.width/2, winSize.height));
	addChild(batch, 20);
	snow->release();
	scheduleOnce(schedule_selector(PlayLayer::skill01Logic),2);
}

void PlayLayer::moveToOriginPoint(float dt)
{	
	twisterRect = Rect(twisterSprite->getPositionX() +twisterSprite->getParent()->getPositionX() - twisterSprite->getContentSize().width / 2,
		twisterSprite->getPositionY() +twisterSprite->getParent()->getPositionY() - twisterSprite->getContentSize().height / 2,
		twisterSprite->getContentSize().width,
		twisterSprite->getContentSize().height );
	auto enemyVector = instance->enemyVector;
	for (int j = 0; j < enemyVector.size(); j++)
	{
		auto enemy = enemyVector.at(j);
		auto enemyRect = Rect(enemy->sprite->getPositionX() - enemy->sprite->getContentSize().width / 4,
			enemy->sprite->getPositionY()  - enemy->sprite->getContentSize().height / 4,
			enemy->sprite->getContentSize().width / 2,
			enemy->sprite->getContentSize().height / 2 );
		if (twisterRect.intersectsRect(enemyRect))
		{
			enemy->changeRote=1;
		}
	}
}

void PlayLayer::fireBallExplodeLogic(float dt)
{
	InfoHandle handle;
	fireBallExplodeRect = Rect(fireBallExplodeSprite->getPositionX() +fireBallExplodeSprite->getParent()->getPositionX() - fireBallExplodeSprite->getContentSize().width / 2-20,
		fireBallExplodeSprite->getPositionY() +fireBallExplodeSprite->getParent()->getPositionY() - fireBallExplodeSprite->getContentSize().height / 2-20,
		fireBallExplodeSprite->getContentSize().width+20,
		fireBallExplodeSprite->getContentSize().height+20 );
	Vector<EnemyBase*> enemyNeedToDelete;
	auto enemyVector = instance->enemyVector;
	for (int j = 0; j < enemyVector.size(); j++)
	{
		auto enemy = enemyVector.at(j);
		//auto enemyRect = enemy->sprite->getBoundingBox();
		auto enemyRect = Rect(enemy->sprite->getPositionX() - enemy->sprite->getContentSize().width / 4,
			enemy->sprite->getPositionY()  - enemy->sprite->getContentSize().height / 4,
			enemy->sprite->getContentSize().width / 2,
			enemy->sprite->getContentSize().height / 2 );
		if (fireBallExplodeRect.intersectsRect(enemyRect))
		{
			auto currHp = enemy->getCurrHp();
			currHp-=4;
			enemy->setCurrHp( currHp );

			auto currHpPercentage = enemy->getHpPercentage();
			auto offHp = 100 / enemy->getMaxHp();
			currHpPercentage -= offHp*4;
			if(currHpPercentage < 0){
				currHpPercentage = 0;
			}
			enemy->setHpPercentage(currHpPercentage);
			enemy->getHpBar()->setPercentage(currHpPercentage);

			if(currHp <= 0)
			{
				enemyNeedToDelete.pushBack(enemy);
				auto valueMoney = enemy->getVaule();
				money += valueMoney;
				auto moneyText = handle.intostr(money);
				moneyLabel->setString(moneyText);
			}
		}
	}
	for (EnemyBase* enemyTemp : enemyNeedToDelete)
	{
		enemyTemp->enemyExpload();
		instance->enemyVector.eraseObject(enemyTemp);
	}
}

void PlayLayer::fireBallExplode(Node* pSender,Point point)
{
	Sprite *sprite = (Sprite *)pSender;
	sprite->removeFromParent();
	fireBallExplodeSprite=Sprite::create();
	Animation* fireBallExplodeAnimation=EnemyBase::createAnimation("fireBallExplode",9,0.08f);
	//fireBallExplodeAnimation->setLoops(2);
	AnimationCache::getInstance()->addAnimation(fireBallExplodeAnimation, "fireBallExplode");
	fireBallExplodeSprite->setPosition(point);
	this->addChild(fireBallExplodeSprite,20);
	fireBallExplodeSprite->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("fireBallExplode"))
		,CallFuncN::create(CC_CALLBACK_0(PlayLayer::removeFromParent,fireBallExplodeSprite ))
		, NULL));
	scheduleOnce(schedule_selector(PlayLayer::fireBallExplodeLogic), 0.3);
}

void PlayLayer::skill02Release(Point point)
{
	twisterSprite=Sprite::create();
	Animation* twisterAnimation=EnemyBase::createAnimation("Twister",12,0.1f);
	//twisterAnimation->setLoops(2);
	AnimationCache::getInstance()->addAnimation(twisterAnimation, "twister");
	twisterSprite->setPosition(point);
	this->addChild(twisterSprite,20);
	twisterSprite->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("twister"))
		,CallFuncN::create(CC_CALLBACK_0(PlayLayer::removeFromParent,twisterSprite ))
		, NULL));
	schedule(schedule_selector(PlayLayer::moveToOriginPoint), 0.2f,4,0);
}

void PlayLayer::createFireBall(Point point,float relativeHeight)
{
	float shadowFrameTime=relativeHeight/400/12;
	Sprite* fireBallShadow=Sprite::create();
	fireBallShadow->setPosition(point);
	Animation* fireBallShadowAnim=EnemyBase::createAnimation("fireBall_shadow",12,shadowFrameTime);
	AnimationCache::getInstance()->addAnimation(fireBallShadowAnim,"fireBallShadow");
	fireBallShadow->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("fireBallShadow"))
		,CallFuncN::create(CC_CALLBACK_0(PlayLayer::removeFromParent,fireBallShadow)),NULL));
	this->addChild(fireBallShadow);

	Size winSize = Director::getInstance()->getWinSize();
	Point initPoint=Point(point.x,point.y+relativeHeight);
	Sprite* fireBall=Sprite::create();
	fireBall->setAnchorPoint(Point(0.5f,0));
	Animation* fireBallAnimation=EnemyBase::createAnimation("fireBall",3,0.03f);
	fireBallAnimation->setLoops(-1);
	AnimationCache::getInstance()->addAnimation(fireBallAnimation, "fireBall");
	fireBall->runAction( Animate::create(AnimationCache::getInstance()->getAnimation("fireBall"))) ;
	fireBall->setPosition(initPoint);
	this->addChild(fireBall,20);
	auto duration=initPoint.getDistance(point)/400;
	fireBall->runAction(Sequence::create(MoveTo::create(duration, point)
		, CallFuncN::create(CC_CALLBACK_1(PlayLayer::fireBallExplode, this, point))
		, NULL));
}

void PlayLayer::skill03Release(Point point)
{
	Size winSize = Director::getInstance()->getWinSize();
	float relativeHeight=winSize.height-point.y;

	Point initPoint01=point;
	Point initPoint02=Point(point.x+(60.0*rand()/RAND_MAX-30.0),point.y+(60.0*rand()/RAND_MAX-30.0));
	Point initPoint03=Point(point.x+(60.0*rand()/RAND_MAX-30.0),point.y+(60.0*rand()/RAND_MAX-30.0));
	Point initPoint04=Point(point.x+(60.0*rand()/RAND_MAX-30.0),point.y+(60.0*rand()/RAND_MAX-30.0));
	Point initPoint05=Point(point.x+(60.0*rand()/RAND_MAX-30.0),point.y+(60.0*rand()/RAND_MAX-30.0));
	createFireBall(initPoint01,relativeHeight);
	createFireBall(initPoint02,relativeHeight);
	createFireBall(initPoint03,relativeHeight);
	createFireBall(initPoint04,relativeHeight);
	createFireBall(initPoint05,relativeHeight);
}

void PlayLayer::initPointsVector(float offX)
{
	InfoHandle handle;
	if (roteNum ==1)
	{
		Node *runOfPoint = NULL;
		int count = 0;
		ValueMap point;
		point = objects->getObject(handle.intostr(count));
		while (point.begin() != point.end())
		{
			float x = point.at("x").asFloat();
			float y = point.at("y").asFloat();
			runOfPoint = Node::create();
			runOfPoint->setPosition(Point(x - offX, y));
			this->pointsVector.pushBack(runOfPoint);
			count++;
			point = objects->getObject(handle.intostr(count));
		}
		runOfPoint = NULL;
	}
	else
	{
		Node *runOfPoint01 = NULL;
		int count01 = 0;
		ValueMap point01;
		point01 = objects01->getObject(handle.intostr(count01));
		while (point01.begin() != point01.end())
		{
			float x = point01.at("x").asFloat();
			float y = point01.at("y").asFloat();
			runOfPoint01 = Node::create();
			runOfPoint01->setPosition(Point(x - offX, y));
			this->pointsVector01.pushBack(runOfPoint01);
			count01++;
			point01 = objects01->getObject(handle.intostr(count01));
		}
		runOfPoint01 = NULL;

		Node *runOfPoint02 = NULL;
		int count02 = 0;
		ValueMap point02;
		point02 = objects02->getObject(handle.intostr(count02));
		while (point02.begin() != point02.end())
		{
			float x = point02.at("x").asFloat();
			float y = point02.at("y").asFloat();
			runOfPoint02 = Node::create();
			runOfPoint02->setPosition(Point(x - offX, y));
			this->pointsVector02.pushBack(runOfPoint02);
			count02++;
			point02 = objects02->getObject(handle.intostr(count02));
		}
		runOfPoint02 = NULL;
	}



}

void PlayLayer::initToolLayer()
{
	auto size = Director::getInstance()->getWinSize();
	toolLayer = Layer::create();
	//toolLayer->setScale(1.0f/2.0f);
	//Size winSize = Director::getInstance()->getWinSize();
	//toolLayer->setContentSize(winSize/2);
	addChild(toolLayer, 40);

	//auto spritetool = Sprite::createWithSpriteFrameName("toolbg.png");
	auto spritetool = Sprite::create();
	spritetool->setTexture("toolBg.png");
	//spritetool->setScale(0.4);
	spritetool->setAnchorPoint(Point(0.5f, 1));
	spritetool->setPosition(Point(size.width / 2, size.height));
	toolLayer->addChild(spritetool);

	//
	money = instance->getMoney();
	moneyLabel = Label::createWithBMFont("fonts/bitmapFontChinese.fnt", " ");
	moneyLabel->setScale(0.5);
	moneyLabel->setPosition(Point(spritetool->getContentSize().width / 8, spritetool->getContentSize().height / 2 - 2));
	moneyLabel->setAnchorPoint(Point(0, 0.5f));
	auto moneyText = std::to_string(money);
	moneyLabel->setString(moneyText);
	spritetool->addChild(moneyLabel);

	//
	auto hpSprite = Sprite::create();
	hpSprite->setTexture("playHp.png");
	//playHpBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("playhp.png"));
	playHpBar = ProgressTimer::create(hpSprite);
	playHpBar->setType(ProgressTimer::Type::BAR);
	playHpBar->setMidpoint(Point(0, 0.4f));
	playHpBar->setBarChangeRate(Point(1, 0));
	playHpBar->setPercentage(playHpPercentage);
	playHpBar->setPosition(Point(spritetool->getContentSize().width / 5 * 4 - 14, spritetool->getContentSize().height / 2 - 7.5));
	spritetool->addChild(playHpBar);

	//auto star = Sprite::createWithSpriteFrameName("playstar.png");
	auto star = Sprite::create();
	star->setTexture("playStar.png");
	star->setPosition(Point(spritetool->getContentSize().width / 5 * 4, spritetool->getContentSize().height / 2));
	spritetool->addChild(star);

	//
	int groupTotal = instance->getGroupNum();
	groupLabel = Label::createWithBMFont("fonts/bitmapFontChinese.fnt", " ");
	groupLabel->setScale(0.5);
	groupLabel->setPosition(Point(spritetool->getContentSize().width / 8 * 3 + 6, spritetool->getContentSize().height / 2 - 2));
	groupLabel->setAnchorPoint(Point(0.5f, 0.5f));
	auto groupInfoText = std::to_string(groupCounter + 1);
	groupLabel->setString(groupInfoText);
	spritetool->addChild(groupLabel);

	groupTotalLabel = Label::createWithBMFont("fonts/bitmapFontChinese.fnt", " ");
	groupTotalLabel->setScale(0.5);
	groupTotalLabel->setPosition(Point(spritetool->getContentSize().width / 2 + 6, spritetool->getContentSize().height / 2 - 2));
	groupTotalLabel->setAnchorPoint(Point(0.5f, 0.5f));
	auto groupTotalText = std::to_string(groupTotal);
	groupTotalLabel->setString(groupTotalText);
	spritetool->addChild(groupTotalLabel);
}

void PlayLayer::initSkillsLayer()
{
	skillsLayer = Layer::create();
	addChild(skillsLayer, 40);

	//skillsSprite = Sprite::createWithSpriteFrameName("toolbg.png");
	skillsSprite = Sprite::create();
	skillsSprite->setTexture("skillBar.png");
	//skillsSprite->setScale(0.4);
	skillsSprite->setAnchorPoint(Point(0, 0));
	skillsSprite->setPosition(Point(0, 0));
	skillsLayer->addChild(skillsSprite);

	//skill01 = Sprite::createWithSpriteFrameName("tower2_1.png");
	skill01 = Sprite::create();
	skill01->setTexture("skill_snow.png");
	skill01->setAnchorPoint(Point(0.5, 0));
	skill01->setPosition(Point(skillsSprite->getContentSize().width - 900, skillsSprite->getContentSize().height / 5));
	skillsSprite->addChild(skill01);

	//skill02 = Sprite::createWithSpriteFrameName("tower2_1.png");
	skill02 = Sprite::create();
	skill02->setTexture("skill_typhon.png");
	skill02->setAnchorPoint(Point(0.5, 0));
	skill02->setPosition(Point(skillsSprite->getContentSize().width - 660, skillsSprite->getContentSize().height / 5));
	skillsSprite->addChild(skill02);

	//skill03 = Sprite::createWithSpriteFrameName("tower2_1.png");
	skill03 = Sprite::create();
	skill03->setTexture("skill_meteor.png");
	skill03->setAnchorPoint(Point(0.5, 0));
	skill03->setPosition(Point(skillsSprite->getContentSize().width - 780, skillsSprite->getContentSize().height / 5));
	skillsSprite->addChild(skill03);

	addSkill01Timmer();
	addSkill02Timmer();
	addSkill03Timmer();
}

void PlayLayer::addSkill01Timmer()
{
	Sprite *snowGray = Sprite::create();
	snowGray->setTexture("skill_snow_gray.png");
	//skill01CoolBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("tower2_2.png"));
	skill01CoolBar = ProgressTimer::create(snowGray);
	skill01CoolBar->setType(ProgressTimer::Type::BAR);
	skill01CoolBar->setMidpoint(Point(0.5, 0));
	skill01CoolBar->setBarChangeRate(Point(0, 1));
	skill01CoolBar->setPercentage(skill01CoolPercentage);
	skill01CoolBar->setAnchorPoint(Point(0.5, 0));
	skill01CoolBar->setPosition(Point(skillsSprite->getContentSize().width - 900, skillsSprite->getContentSize().height - 28));
	skillsSprite->addChild(skill01CoolBar);
}

void PlayLayer::addSkill02Timmer()
{
	Sprite *typhonGray = Sprite::create();
	typhonGray->setTexture("skill_typhon_gray.png");
	//skill02CoolBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("tower2_2.png"));
	skill02CoolBar = ProgressTimer::create(typhonGray);
	skill02CoolBar->setType(ProgressTimer::Type::BAR);
	skill02CoolBar->setMidpoint(Point(0.5, 0));
	skill02CoolBar->setBarChangeRate(Point(0, 1));
	skill02CoolBar->setPercentage(skill02CoolPercentage);
	skill02CoolBar->setAnchorPoint(Point(0.5, 0));
	skill02CoolBar->setPosition(Point(skillsSprite->getContentSize().width - 660, skillsSprite->getContentSize().height - 30));
	skillsSprite->addChild(skill02CoolBar);
}

void PlayLayer::addSkill03Timmer()
{
	Sprite *meteorGray = Sprite::create();
	meteorGray->setTexture("skill_meteor_gray.png");
	//skill03CoolBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("tower2_2.png"));
	skill03CoolBar = ProgressTimer::create(meteorGray);
	skill03CoolBar->setType(ProgressTimer::Type::BAR);
	skill03CoolBar->setMidpoint(Point(0.5, 0));
	skill03CoolBar->setBarChangeRate(Point(0, 1));
	skill03CoolBar->setPercentage(skill03CoolPercentage);
	skill03CoolBar->setAnchorPoint(Point(0.5, 0));
	skill03CoolBar->setPosition(Point(skillsSprite->getContentSize().width - 780, skillsSprite->getContentSize().height - 30));
	skillsSprite->addChild(skill03CoolBar);
}

void PlayLayer::menuBackCallback(Ref* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/button.wav").c_str(), false);
	GameManager::getInstance()->clear();
	//回到关卡界面
	auto scene = BlockScene::createScene();
	Director::getInstance()->replaceScene(CCTransitionFade::create(0.5, scene));
	SimpleAudioEngine::getInstance()->playBackgroundMusic(FileUtils::getInstance()->fullPathForFilename("sound/theme.mp3").c_str(), true);
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.1f);
}

GroupEnemy* PlayLayer::currentGroup()
{
	GroupEnemy* groupEnemy;
	if(!instance->groupVector.empty() )
	{
		groupEnemy = (GroupEnemy*)instance->groupVector.at(groupCounter);
	}
	else{
		groupEnemy =NULL;
	}
	return groupEnemy;
}

GroupEnemy* PlayLayer::nextGroup()
{
	if(instance->groupVector.empty())
	{
		return NULL;
	}

	if (groupCounter < instance->getGroupNum() - 1)
	{
		groupCounter++;
	}
	else{
		isSuccessful = true;
	}
	GroupEnemy* groupEnemy = (GroupEnemy*)instance->groupVector.at(groupCounter);
	return groupEnemy;

}

void PlayLayer::addEnemy()
{
	GameManager *instance = GameManager::getInstance();

	GroupEnemy* groupEnemy = this->currentGroup();
	if (groupEnemy == NULL)
	{
		return;
	}
	auto restEnemyNum = groupEnemy->getEnemyTotal();
	if (restEnemyNum <= 0){
		groupEnemy->setIsFinishedAddGroup(true);
		return;
	}

	if (roteNum == 2)
	{
		if (groupEnemy->getType1Total() > 0){
			restEnemyNum--;
			EnemyBase* enemy = NULL;
			SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/comeout.wav").c_str(), false);
			enemy = Thief::createThief(pointsVector01, groupEnemy->getType1Hp());
			groupEnemy->setType1Total(groupEnemy->getType1Total() - 1);
			this->addChild(enemy, 10);
			instance->enemyVector.pushBack(enemy);
		}
		if (groupEnemy->getType2Total() > 0){
			restEnemyNum--;
			EnemyBase* enemy = NULL;
			SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/comeout.wav").c_str(), false);
			enemy = Pirate::createPirate(pointsVector01, groupEnemy->getType2Hp());
			groupEnemy->setType2Total(groupEnemy->getType2Total() - 1);
			this->addChild(enemy, 10);
			instance->enemyVector.pushBack(enemy);
		}
		if (groupEnemy->getType3Total() > 0){
			restEnemyNum--;
			EnemyBase* enemy = NULL;
			enemy = Bandit::createBandit(pointsVector02, groupEnemy->getType3Hp());
			SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/comeout.wav").c_str(), false);
			groupEnemy->setType3Total(groupEnemy->getType3Total() - 1);
			this->addChild(enemy, 10);
			instance->enemyVector.pushBack(enemy);
		}
		groupEnemy->setEnemyTotal(restEnemyNum);
	}
	else
	{
		if (groupEnemy->getType1Total() > 0){
			restEnemyNum--;
			EnemyBase* enemy = NULL;
			SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/comeout.wav").c_str(), false);
			enemy = Thief::createThief(pointsVector, groupEnemy->getType1Hp());
			groupEnemy->setType1Total(groupEnemy->getType1Total() - 1);
			this->addChild(enemy, 10);
			instance->enemyVector.pushBack(enemy);
		}
		if (groupEnemy->getType2Total() > 0){
			restEnemyNum--;
			EnemyBase* enemy = NULL;
			SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/comeout.wav").c_str(), false);
			enemy = Pirate::createPirate(pointsVector, groupEnemy->getType2Hp());
			groupEnemy->setType2Total(groupEnemy->getType2Total() - 1);
			this->addChild(enemy, 10);
			instance->enemyVector.pushBack(enemy);
		}
		if (groupEnemy->getType3Total() > 0){
			restEnemyNum--;
			EnemyBase* enemy = NULL;
			enemy = Bandit::createBandit(pointsVector, groupEnemy->getType3Hp());
			SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/comeout.wav").c_str(), false);
			groupEnemy->setType3Total(groupEnemy->getType3Total() - 1);
			this->addChild(enemy, 10);
			instance->enemyVector.pushBack(enemy);
		}
		groupEnemy->setEnemyTotal(restEnemyNum);
	}

}
void PlayLayer::logic(float dt)
{
	GroupEnemy* groupEnemy = this->currentGroup();

	if(groupEnemy == NULL)
	{
		return;
	}
	if(groupEnemy->getIsFinishedAddGroup() ==true  && instance->enemyVector.size() == 0 && groupCounter < instance->getGroupNum())
	{
		InfoHandle handle;
		groupEnemy = this->nextGroup();
		int groupTotal = instance->getGroupNum();
		auto groupInfoText = handle.intostr(groupCounter + 1);
		groupLabel->setString(groupInfoText);
		auto groupTotalText = handle.intostr(groupTotal);
		groupTotalLabel->setString(groupTotalText);
	}
	this->addEnemy();
}

void PlayLayer::skillsCool(float dt)
{
	auto skill01Cool = getSkill01CoolPercentage()-10;
	auto skill02Cool = getSkill02CoolPercentage()-10;
	auto skill03Cool = getSkill03CoolPercentage()-10;
	if(skill01Cool > 0){
		setSkill01CoolPercentage(skill01Cool);
		skill01CoolBar->setPercentage(skill01Cool);
	}
	else if(skill01Ready==false)
	{
		skill01CoolBar->removeFromParent();
		skill01Ready=true;
	}

	if(skill02Cool > 0){
		setSkill02CoolPercentage(skill02Cool);
		skill02CoolBar->setPercentage(skill02Cool);
	}
	else if(skill02Ready==false)
	{
		skill02CoolBar->removeFromParent();
		skill02Ready=true;
	}

	if(skill03Cool > 0){
		setSkill03CoolPercentage(skill03Cool);
		skill03CoolBar->setPercentage(skill03Cool);
	}
	else if(skill03Ready==false)
	{
		skill03CoolBar->removeFromParent();
		skill03Ready=true;
	}
}

bool PlayLayer::onTouchBegan(Touch *touch, Event *event)
{
	this->removeChild(evolveTowerPanleLayer);
	evolveTowerPanleLayer = NULL;
	this->removeChild(upTowerPanleLayer);
	upTowerPanleLayer = NULL;
	this->removeChild(chooseTowerpanel);
	chooseTowerpanel = NULL;
	auto location = touch->getLocation();

	Point reallyPoint01=skill01->getParent()->convertToNodeSpace(location);
	Rect rect01=skill01->getBoundingBox();
	Point reallyPoint02=skill02->getParent()->convertToNodeSpace(location);
	Rect rect02=skill02->getBoundingBox();
	Point reallyPoint03=skill03->getParent()->convertToNodeSpace(location);
	Rect rect03=skill03->getBoundingBox();
	Point reallyPoint04 = pauseBtn->getParent()->convertToNodeSpace(location);
	Rect rect04 = pauseBtn->getBoundingBox();
	Point reallyPoint05 = speedBtn->getParent()->convertToNodeSpace(location);
	Rect rect05 = speedBtn->getBoundingBox();
	Point reallyPoint06 = settingBtn->getParent()->convertToNodeSpace(location);
	Rect rect06 = settingBtn->getBoundingBox();

	if (!isStart)
	{
		Point reallyPoint07 = startBtn->getParent()->convertToNodeSpace(location);
		Rect rect07 = startBtn->getBoundingBox();

		if (rect07.containsPoint(reallyPoint07))
		{
			startGame();
			return true;
		}
	}


	if (rect06.containsPoint(reallyPoint06))
	{
		clickSetting();
		return true;
	}

	if (rect05.containsPoint(reallyPoint05))
	{
		if (isSpeeding == false)
		{
			isSpeeding = true;
			Director::getInstance()->getScheduler()->setTimeScale(2);
		}
		else{
			isSpeeding = false;
			Director::getInstance()->getScheduler()->setTimeScale(1);
		}
		return true;
	}

	if (rect04.containsPoint(reallyPoint04))
	{
		doPause();
		return true;
	}

	if (skill01Chose == true && (!rect01.containsPoint(reallyPoint01)))
	{
		skill01Ready = false;
		skill01Chose = false;
		//skill01->setSpriteFrame("tower2_1.png");
		skill01->setPosition(Point(skillsSprite->getContentSize().width - 900, skillsSprite->getContentSize().height / 5));
		setSkill01CoolPercentage(100);
		addSkill01Timmer();
		skill01Release();
		return true;
	}

	if(skill01Chose==true&&(!rect01.containsPoint(reallyPoint01)))
	{
		skill01Ready=false;
		skill01Chose=false;
		skill01->setSpriteFrame("tower2_1.png");
		skill01->setPosition(Point(skillsSprite->getContentSize().width/5,skillsSprite->getContentSize().height/2));
		setSkill01CoolPercentage(100);
		addSkill01Timmer();
		skill01Release();
		return true;
	}

	if(skill02Chose==true&&(!rect02.containsPoint(reallyPoint02)))
	{
		skill02Ready = false;
		skill02Chose = false;
		//skill02->setSpriteFrame("tower2_1.png");
		skill02->setPosition(Point(skillsSprite->getContentSize().width - 660, skillsSprite->getContentSize().height / 5));
		setSkill02CoolPercentage(100);
		addSkill02Timmer();
		skill02Release(location);
		return true;
	}

	if(skill03Chose==true&&(!rect03.containsPoint(reallyPoint03)))
	{
		skill03Ready = false;
		skill03Chose = false;
		//skill03->setSpriteFrame("tower2_1.png");
		skill03->setPosition(Point(skillsSprite->getContentSize().width - 780, skillsSprite->getContentSize().height / 5));
		setSkill03CoolPercentage(100);
		addSkill03Timmer();
		skill03Release(location);
		return true;
	}

	if (rect01.containsPoint(reallyPoint01)&&skill01Ready)//判断触摸点是否在目标的范围内
	{
		Point p = skill01->getPosition();
		if (p.y == skillsSprite->getContentSize().height)
		{
			//skill01->setSpriteFrame("tower2_1.png");
			//skill01->setTexture("skill_snow.png");
			skill01->setPosition(Point(skillsSprite->getContentSize().width - 900, skillsSprite->getContentSize().height / 5));
			skill01Chose = false;
		}
		else
		{
			//skill01->setSpriteFrame("tower2_1_big.png");
			skill01->setPosition(Point(skillsSprite->getContentSize().width - 900, skillsSprite->getContentSize().height / 2));
			skill01Chose = true;
		}
		return true;
	}

	if (rect02.containsPoint(reallyPoint02)&&skill02Ready)//判断触摸点是否在目标的范围内
	{
		Point p = skill02->getPosition();
		if (p.y == skillsSprite->getContentSize().height / 2)
		{
			//skill02->setSpriteFrame("tower2_1.png");
			skill02->setPosition(Point(skillsSprite->getContentSize().width - 660, skillsSprite->getContentSize().height / 5));
			skill02Chose = false;
		}
		else
		{
			//skill02->setSpriteFrame("tower2_1_big.png");
			skill02->setPosition(Point(skillsSprite->getContentSize().width - 660, skillsSprite->getContentSize().height / 2));
			skill02Chose = true;
		}
		return true;
	}

	if (rect03.containsPoint(reallyPoint03)&&skill03Ready)//判断触摸点是否在目标的范围内
	{
		Point p = skill03->getPosition();
		if (p.y == skillsSprite->getContentSize().height / 2)
		{
			//skill03->setSpriteFrame("tower2_1.png");
			skill03->setPosition(Point(skillsSprite->getContentSize().width - 780, skillsSprite->getContentSize().height / 5));
			skill03Chose = false;
		}
		else
		{
			//skill03->setSpriteFrame("tower2_1_big.png");
			skill03->setPosition(Point(skillsSprite->getContentSize().width - 780, skillsSprite->getContentSize().height / 2));
			skill03Chose = true;
		}
		return true;
	}

	if(skill01Chose==false&&skill02Chose==false&&(!rect01.containsPoint(reallyPoint01))&&(!rect02.containsPoint(reallyPoint02)))
	{
		checkAndAddTowerPanle(location);
	}
	return true;
}

void PlayLayer::addTowerChoosePanel(Point point)
{
	chooseTowerpanel = TowerPanleLayer::create();
	auto towerValue1 = instance->towerInfo[0].getCost();
	auto towerValue2 = instance->towerInfo[2].getCost();
	auto towerValue3 = instance->towerInfo[1].getCost();
	auto towerValue4 = instance->towerInfo[3].getCost();
	chooseTowerpanel->setMoneyText(towerValue1, towerValue2, towerValue3, towerValue4);
	chooseTowerpanel->setPosition(point);
	this->addChild(chooseTowerpanel, 60);
}

Point PlayLayer::convertTotileCoord(Point position)
{
	int x = (position.x + offX)/ map->getContentSize().width * map->getMapSize().width;
	int y =map->getMapSize().height- position.y / map->getContentSize().height * map->getMapSize().height;
	return Point(x, y);
}
Point PlayLayer::convertToMatrixCoord(Point position)
{
	int x = (position.x + offX)/ map->getContentSize().width * map->getMapSize().width;
	int y = position.y / map->getContentSize().height * map->getMapSize().height;
	return Point(x, y);
}

void PlayLayer::checkAndAddTowerPanle(Point position)
{

	//把传入的Cocos2d坐标系分别转换为tiledMap坐标和数组坐标。
	//tiledMap坐标的(0, 0) 坐标在左上角，而数组坐标的(0 , 0)在左下角角。
	//convertTotileCoord把本地坐标（OpenGL坐标）转换为地图坐标
	Point towerCoord = convertTotileCoord(position);

	// 把本地坐标（OpenGL坐标）转换为数组坐标
	Point matrixCoord = convertToMatrixCoord(position);

	//分别求瓦片的全局标和数组下标。
	//对于tiledMap的每一个瓦片来说，它都有一个全局标识量，瓦片的GID范围从正整数1开始到瓦片地图中tile的总量。
	//得到了瓦片的GID就可以获取该块瓦片的全值在左。   
	int gid = bgLayer->getTileGIDAt(towerCoord);
	auto test = map->getPropertiesForGID(gid);
	auto tileTemp = map->getPropertiesForGID(gid).asValueMap();
	MatrixIndex = static_cast<int>(matrixCoord.y * MAP_WIDTH + matrixCoord.x);

	int TouchVaule;
	if (tileTemp.empty())
	{
		TouchVaule = 0;
	}
	else
	{
		TouchVaule = tileTemp.at("canTouch").asInt();
	}
	auto tileWidth = map->getContentSize().width / map->getMapSize().width;
	auto tileHeight = map->getContentSize().height / map->getMapSize().height;
	towerPos = Point((towerCoord.x * tileWidth) + tileWidth / 2 - offX, map->getContentSize().height - (towerCoord.y * tileHeight) - tileHeight / 2);
	TowerBase* tower = towerMatrix[MatrixIndex];
	if (1 == TouchVaule && tower == NULL)
	{
		addTowerChoosePanel(towerPos);
	}
	else if (tower != NULL &&tower->getTowerLevel() < tower->getTowerMaxLevel())
	{
		addUpTowerChoosePanel(towerPos, tower);//升级和出售
	}
	else if (tower != NULL &&tower->getTowerLevel() == tower->getTowerMaxLevel())
	{
		addEvolveTowerChoosePanel(towerPos, tower);//进化和出售
	}
	else
	{
		/*SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/tip.wav").c_str(), false);
		auto tips = Sprite::createWithSpriteFrameName("nono.png");
		tips->setPosition(towerPos);
		this->addChild(tips);
		tips->runAction(Sequence::create(DelayTime::create(0.8f),
		CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, tips)),
		NULL));*/
	}
}

void PlayLayer::addTower()
{
	if (chooseTowerpanel)
	{
		auto type = chooseTowerpanel->getChooseTowerType();
		if (type == TowerType::ANOTHER)
		{
			return;
		}
		Point matrixCoord = convertToMatrixCoord(towerPos);
		int MatrixIndex = static_cast<int>(matrixCoord.y * MAP_WIDTH + matrixCoord.x);
		bool noMoneyTips = false;
		TowerBase* tower = NULL;
		int towerValue = 0;
		if (type == TowerType::ARROW_TOWER)
		{
			towerValue = instance->towerInfo[0].getCost();
			if (money >= towerValue)
			{
				SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/build.wav").c_str(), false);
				tower = ArrowTower::create();
				tower->setTowerInfo(instance->towerInfo[0]);
				tower->updateShootTime();
				money -= towerValue;
			}
			else
				noMoneyTips = true;
		}
		else if (type == TowerType::SLOW_TOWER)
		{
			towerValue = instance->towerInfo[1].getCost();
			if (money >= towerValue)
			{
				SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/build.wav").c_str(), false);
				tower = SlowTower::create();
				tower->setTowerInfo(instance->towerInfo[1]);
				tower->updateShootTime();
				money -= towerValue;
			}
			else
				noMoneyTips = true;
		}
		else if (type == TowerType::POISON_TOWER)
		{
			towerValue = instance->towerInfo[2].getCost();
			if (money >= towerValue)
			{
				SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/build.wav").c_str(), false);
				tower = PoisonTower::create();
				tower->setTowerInfo(instance->towerInfo[2]);
				tower->updateShootTime();
				money -= towerValue;
			}
			else
				noMoneyTips = true;
		}
		else if (type == TowerType::CANNON_TOWER)
		{
			towerValue = instance->towerInfo[3].getCost();
			if (money >= towerValue)
			{
				SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/build.wav").c_str(), false);
				tower = CannonTower::create();
				tower->setTowerInfo(instance->towerInfo[3]);
				tower->updateShootTime();
				money -= towerValue;
			}
			else
				noMoneyTips = true;
		}
		if (tower != NULL)
		{
			tower->setPosition(towerPos);
			tower->runAction(Sequence::create(FadeIn::create(1.0f), NULL));
			this->addChild(tower, 0);
			towerMatrix[MatrixIndex] = tower;
		}
		type = TowerType::ANOTHER;
		chooseTowerpanel->setChooseTowerType(type);
		this->removeChild(chooseTowerpanel);
		chooseTowerpanel = NULL;

		auto moneyText = std::to_string(money);
		moneyLabel->setString(moneyText);

		if (noMoneyTips == true)
		{
			SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/tip.wav").c_str(), false);
			auto tips = Sprite::createWithSpriteFrameName("nomoney_mark.png");
			tips->setPosition(towerPos);
			this->addChild(tips);
			tips->runAction(Sequence::create(DelayTime::create(0.5f),
				CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, tips)),
				NULL));
		}
	}
}

void PlayLayer::CollisionDetection()
{
	auto bulletVector = instance->bulletVector;
	auto enemyVector = instance->enemyVector;

	if (bulletVector.empty() || enemyVector.empty()){
		return;
	}
	Vector<BulletBase*> bulletNeedToDelete;
	for (int i = 0; i < bulletVector.size(); i++)
	{
		auto bullet = bulletVector.at(i);
		if (bullet->getParent() == NULL)
		{
			return;
		}
		auto  bulletRect = Rect(bullet->getPositionX() + bullet->getParent()->getPositionX() - bullet->getContentSize().width / 2,
			bullet->getPositionY() + bullet->getParent()->getPositionY() - bullet->getContentSize().height / 2,
			bullet->getBulletSprite()->getContentSize().width,
			bullet->getBulletSprite()->getContentSize().height);

		for (int j = 0; j < enemyVector.size(); j++)
		{
			auto enemy = enemyVector.at(j);
			//auto enemyRect = enemy->sprite->getBoundingBox();
			auto enemyRect = Rect(enemy->sprite->getPositionX() - enemy->sprite->getContentSize().width / 2,
				enemy->sprite->getPositionY() - enemy->sprite->getContentSize().height / 2,
				enemy->sprite->getContentSize().width,
				enemy->sprite->getContentSize().height);
			if (bulletRect.intersectsRect(enemyRect))
			{
				bullet->reduceProperty(enemy);
				bulletNeedToDelete.pushBack(bullet);
				if (bullet->getBombRange() > 0)
				{
					for (int m = 0; m < enemyVector.size(); m++)
					{
						auto enemyToBomb = instance->enemyVector.at(m);
						auto pointBomb = bullet->getPosition() + bullet->getParent()->getPosition();
						auto distanceFromBomb = pointBomb.getDistance(enemyToBomb->sprite->getPosition());
						if (distanceFromBomb <= bullet->getBombRange())
						{
							enemyToBomb->enemyReduceHp(bullet->getBombHp());

						}

					}

				}
				break;
			}
		}
	}

	for (BulletBase* bulletTemp : bulletNeedToDelete)
	{
		instance->bulletVector.eraseObject(bulletTemp);
		bulletTemp->removeFromParent();
	}
	bulletNeedToDelete.clear();
}

void PlayLayer::enemyIntoHouse()
{
	auto enemyVector = instance->enemyVector;
	for (int i = 0; i < enemyVector.size(); i++)
	{
		auto enemy = enemyVector.at(i);
		if( enemy->getEnemySuccessful())
		{
			instance->enemyVector.eraseObject(enemy);
			enemy->removeFromParent();
			auto playHp = getPlayHpPercentage() - 10;
			if(playHp > 0){
				setPlayHpPercentage(playHp);
				playHpBar->setPercentage(playHp);
			}
			else{
				instance->clear();

				auto failurescene = ResultScene::createScene();
				ResultScene *result = new ResultScene();
				auto failurelayer = result->popFailure();
				failurescene->addChild(failurelayer);
				Director::getInstance()->getScheduler()->setTimeScale(1);
				Director::getInstance()->replaceScene(TransitionFade::create(0.1f, failurescene));
			}
		}
	}
}

void PlayLayer::update(float dt)
{
	addTower();
	CollisionDetection();
	enemyIntoHouse();
	upOrSellTower();
	evolveOrSellTower();
	checkBullet();
	removeEnemy();

	if(isSuccessful)
	{
		Director::getInstance()->getScheduler()->setTimeScale(1);
		isSuccessful = false;
		auto star = 0;
		auto playHp = this->getPlayHpPercentage();

		if( playHp > 0 && playHp <= 30){ star = 1;}
		else if(playHp > 30 && playHp <= 60 ){ star = 2;}
		else if(playHp > 60 && playHp <= 100 ){ star = 3;}

		//当前关卡原始得分
		InfoHandle handle;
		Block upblock = handle.getBlockInfo(UserDefault::getInstance()->getIntegerForKey("currBlock"));//当前关卡
		User user = handle.getUserInfo();//当前用户
		int curBlockStar = upblock.getBlockStar();//当前关卡原始得分
		//如果原始得分为0并且本关得分大于0，则解锁关卡
		//并修改得分数量
		if (curBlockStar==0&&star>0)
		{
			//增加解锁关卡数量
			user.setBlockNumber(user.getBlockNumber() + 1);
			handle.updateUserInfo(user);
		}
		if( star > curBlockStar)//如果当前得分大于原始得分，则修改本关原始得分数量
		{
			user.setStarNumber(user.getStarNumber() + star - curBlockStar);
			user.setUpgradeNumber(user.getUpgradeNumber() + star - curBlockStar);
			handle.updateUserInfo(user);//更新用户总得分
			upblock.setBlockId(UserDefault::getInstance()->getIntegerForKey("currBlock"));
			upblock.setBlockStar(star);
			handle.updateBlockInfo(upblock);//更新关卡得分
			
		}
		//设置当前关卡通关显示星星数量
		UserDefault::getInstance()->setIntegerForKey("currStar", star);
		//设置下一关加载资源信息
		auto nextlevel = instance->getNextLevelFile();
		UserDefault::getInstance()->setStringForKey("nextLevelFile", nextlevel);

		instance->clear();

		//加载成功通关界面
		auto successscene = ResultScene::createScene();
		ResultScene *result = new ResultScene();
		auto successlayer = result->popSuccess();
		successscene->addChild(successlayer);

		Director::getInstance()->replaceScene(TransitionFade::create(0.1f, successscene));
	}
}

void PlayLayer::addUpTowerChoosePanel(Point point, TowerBase* tower)
{
	upTowerPanleLayer = UpTowerPanleLayer::create();
	upTowerPanleLayer->setMoneyText(tower->getTowerUpValue(), tower->getTowerSellValue());
	upTowerPanleLayer->setPosition(point);
	auto scope = tower->getScope();
	auto upScopeCircle = scope + 30;
	this->addChild(upTowerPanleLayer,60);
	upTowerPanleLayer->setScopeCircle(scope);
	upTowerPanleLayer->setUpScopeCircle(upScopeCircle);
}

void PlayLayer::upOrSellTower()
{
	InfoHandle handle;

	if (upTowerPanleLayer != NULL)
	{


		auto up = upTowerPanleLayer->getUpTower();
		auto sell = upTowerPanleLayer->getSellTower();
		if (!up && !sell)
		{
			return;
		}
		int upValue = towerMatrix[MatrixIndex]->getTowerUpValue();
		if (up)
		{
			if (money >= upValue && towerMatrix[MatrixIndex]->getTowerLevel() < towerMatrix[MatrixIndex]->getTowerMaxLevel())
			{
				SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/up.wav").c_str(), false);
				towerMatrix[MatrixIndex]->upTower();
				money -= upValue;
				auto moneyText = handle.intostr(money);
				moneyLabel->setString(moneyText);
			}
			else
			{
				SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/tip.wav").c_str(), false);
				auto tips = Sprite::createWithSpriteFrameName("no_money.png");
				tips->setPosition(towerPos);
				this->addChild(tips);
				tips->runAction(Sequence::create(DelayTime::create(0.8f),
					CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, tips)),
					NULL));
			}
		}

		if (sell)
		{
			money += towerMatrix[MatrixIndex]->getTowerSellValue();
			auto moneyText = handle.intostr(money);
			moneyLabel->setString(moneyText);
			towerMatrix[MatrixIndex]->sellTower();
			towerMatrix[MatrixIndex] = NULL;
		}
		this->removeChild(upTowerPanleLayer);
		upTowerPanleLayer = NULL;
	}
}

void PlayLayer::removeEnemy(){
	InfoHandle hanlde;
	auto enemyVector = instance->enemyVector;
	Vector<EnemyBase*> enemyNeedToDelete;
	for (int j = 0; j < enemyVector.size(); j++)
	{
		auto enemy = enemyVector.at(j);
		auto currHp = enemy->getCurrHp();
		if (currHp <= 0)
		{
			enemyNeedToDelete.pushBack(enemy);
			auto valueMoney = enemy->getVaule();
			money += valueMoney;
			auto moneyText =hanlde.intostr(money);
			moneyLabel->setString(moneyText);
		}
	}
	for (EnemyBase* enemyTemp : enemyNeedToDelete)
	{
		instance->enemyVector.eraseObject(enemyTemp);
		enemyTemp->enemyExpload();
	}
	enemyNeedToDelete.clear();

}

//防御塔进化
void PlayLayer::addEvolveTowerChoosePanel(Point point, TowerBase* tower)
{
	evolveTowerPanleLayer = EvolveTowerPanleLayer::create();
	evolveTowerPanleLayer->setMoneyText(tower->getTowerEvolve1Value(), tower->getTowerEvolve2Value(), tower->getTowerSellValue());
	evolveTowerPanleLayer->setPosition(point);
	auto scope = tower->getScope();
	this->addChild(evolveTowerPanleLayer,60);
	evolveTowerPanleLayer->setScopeCircle(scope);
}


void PlayLayer::evolveOrSellTower()
{
	InfoHandle handle;

	if (evolveTowerPanleLayer != NULL)
	{
		auto evolve1 = evolveTowerPanleLayer->getEvolve1Tower();
		auto evolve2 = evolveTowerPanleLayer->getEvolve2Tower();
		auto sell = evolveTowerPanleLayer->getSellTower();
		if (!evolve1 && !evolve2 && !sell)
		{
			return;
		}
		if (evolve1)
		{

			int evolve1Value = towerMatrix[MatrixIndex]->getTowerEvolve1Value();
			if (money >= evolve1Value && towerMatrix[MatrixIndex]->getTowerEvolve1Level() < towerMatrix[MatrixIndex]->getTowerMaxEvolveLevel())
			{
				SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/up.wav").c_str(), false);
				towerMatrix[MatrixIndex]->evolve1Tower();
				money -= evolve1Value;
				auto moneyText = handle.intostr(money);
				moneyLabel->setString(moneyText);
			}
			else
			{
				SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/tip.wav").c_str(), false);
				auto tips = Sprite::createWithSpriteFrameName("no_money.png");
				tips->setPosition(towerPos);
				this->addChild(tips);
				tips->runAction(Sequence::create(DelayTime::create(0.8f),
					CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, tips)),
					NULL));
			}
		}
		if (evolve2)
		{

			int evolve2Value = towerMatrix[MatrixIndex]->getTowerEvolve2Value();
			if (money >= evolve2Value && towerMatrix[MatrixIndex]->getTowerEvolve2Level() < towerMatrix[MatrixIndex]->getTowerMaxEvolveLevel())
			{
				SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/up.wav").c_str(), false);
				towerMatrix[MatrixIndex]->evolve2Tower();
				money -= evolve2Value;
				auto moneyText = handle.intostr(money);
				moneyLabel->setString(moneyText);
			}
			else
			{
				SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/tip.wav").c_str(), false);
				auto tips = Sprite::createWithSpriteFrameName("no_money.png");
				tips->setPosition(towerPos);
				this->addChild(tips);
				tips->runAction(Sequence::create(DelayTime::create(0.8f),
					CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, tips)),
					NULL));
			}
		}

		if (sell)
		{
			money += towerMatrix[MatrixIndex]->getTowerSellValue();
			auto moneyText = handle.intostr(money);
			moneyLabel->setString(moneyText);
			towerMatrix[MatrixIndex]->sellTower();
			towerMatrix[MatrixIndex] = NULL;
		}
		this->removeChild(evolveTowerPanleLayer);
		evolveTowerPanleLayer = NULL;
	}
}


void PlayLayer::checkBullet(){
	auto bulletVector = instance->bulletVector;
	Vector<BulletBase*> bulletNeedToDelete;
	for (int j = 0; j < bulletVector.size(); j++)
	{
		auto bullet = bulletVector.at(j);
		/*if (bullet->getIsFollow())
		{
		if (bullet->getTargetEnemy()->getCurrHp()>0)
		{
		bullet->followEnemy();
		}
		else
		{
		bullet->setIsFollow(false);
		}
		}*/
		if (bullet->getToDelete() == true)
		{
			bulletNeedToDelete.pushBack(bullet);
		}
	}
	for (BulletBase* bulletTemp : bulletNeedToDelete)
	{
		instance->bulletVector.eraseObject(bulletTemp);
		bulletTemp->removeFromParent();
	}
	bulletNeedToDelete.clear();
}


void PlayLayer::startGame()
{

	schedule(schedule_selector(PlayLayer::logic), 2.0f);
	schedule(schedule_selector(PlayLayer::skillsCool), 0.2f);
	isStart = true;
	startBtn->removeFromParent();
}
