#include "CheckScene.h"

CheckScene::CheckScene()
{};

CheckScene::~CheckScene()
{}

Scene *CheckScene::createCheckScene(RenderTexture *renderTexture)
{
	Size winSize = Director::getInstance()->getWinSize();
	CheckScene *checkLayer = CheckScene::create();

	Scene *resetScene = Scene::create();

	resetScene->addChild(checkLayer);

	Sprite* resetSprite = Sprite::createWithTexture(renderTexture->getSprite()->getTexture());
	resetSprite->setPosition(Point(winSize.width / 2, winSize.height / 2));
	resetSprite->setFlippedY(true);
	resetSprite->setColor(cocos2d::Color3B::GRAY);
	resetScene->addChild(resetSprite);

	checkLayer->checkBg = Sprite::create();
	checkLayer->checkBg->setTexture("check.png");
	checkLayer->checkBg->setPosition(Point(winSize.width / 2 - 5, winSize.height / 2));
	resetSprite->addChild(checkLayer->checkBg);

	Size checkBgSize = checkLayer->checkBg->getContentSize();

	Sprite *checkText = Sprite::create();
	checkText->setTexture("checkText.png");
	checkText->setPosition(Point(checkBgSize.width/2,checkBgSize.height*2/3));
	checkLayer->checkBg->addChild(checkText);

	checkLayer->setMenu();

	return resetScene;
}

void CheckScene::setMenu()
{
	Size checkBgSize = checkBg->getContentSize();

	Sprite *okBtn01 = Sprite::create();
	okBtn01->setTexture("okOn.png");
	Sprite *okBtn02 = Sprite::create();
	okBtn02->setTexture("okDown.png");
	MenuItemSprite *okItem = MenuItemSprite::create(okBtn01, okBtn02, CC_CALLBACK_1(CheckScene::okCallBack, this));

	Sprite *cancel01 = Sprite::create();
	cancel01->setTexture("cancelOn.png");
	Sprite *cancel02 = Sprite::create();
	cancel02->setTexture("cancelDown.png");
	MenuItemSprite *cancelItem = MenuItemSprite::create(cancel01, cancel02, CC_CALLBACK_1(CheckScene::CancelCallback, this));

	auto menu = Menu::create(okItem, cancelItem, NULL);

	menu->alignItemsHorizontally();

	menu->setPosition(Point(checkBgSize.width / 2, checkBgSize.height/3));

	checkBg->addChild(menu);
}

void CheckScene::okCallBack(Ref *pSender)
{
	//重置用户文件信息
	InfoHandle handle;
	User user = handle.getUserInfo();
	user.setUpgradeNumber(0);
	user.setBlockNumber(0);
	user.setNickName("litdon");
	user.setStarNumber(0);
	handle.updateUserInfo(user);

	//重置关卡文件信息
	for (int i = 0; i < 9; i++)
	{
		Block block = handle.getBlockInfo(i);
		block.setBlockId(i);
		block.setBlockStar(0);
		handle.updateBlockInfo(block);
	}

	//重置升级图标标识状态
	for (int i = 0; i < 28; i++){
		char sp[10];
		sprintf(sp, "%d", i + 1);
		string t = sp;
		string btn = "btn" + t;
		string picname = "uu" + t + ".png";
		handle.updateUpMark(btn, false);

	}

	//重置防御塔和技能基础属性
	string tstype[7] = { "arrowtower", "slowtower", "poisontower", "turrettower", "ice", "wind", "fire" };
	for (int i = 0; i < 4; i++)
	{
		handle.updateTowerInfo(handle.getTowerInfoFromBackUp(tstype[i], "towerInfo2.json"));
	}
	for (int i = 4; i < 7; i++)
	{
		handle.updateSkillInfo(handle.getSkillInfoFromBackUp(tstype[i], "skillInfo2.json"));
	}

	
	Director::getInstance()->popScene();
}

void CheckScene::CancelCallback(Ref *pSender)
{
	Director::getInstance()->popScene();
}