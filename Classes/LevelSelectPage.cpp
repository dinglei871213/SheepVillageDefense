#include <LevelSelectPage.h>
#include "cocos2d.h"
#define LEVEL_ROW (3)
#define LEVEL_COL (2)
using namespace cocos2d;

LevelSelectPage* LevelSelectPage::create(const std::string& bgName, int level)
{
	LevelSelectPage *pRet = new LevelSelectPage();
	if (pRet && pRet->initLevelPage(bgName, level))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool LevelSelectPage::initLevelPage(const std::string& bgName, int level){
	if (!Node::init()){
		return false;
	}
	auto size = Director::getInstance()->getWinSize();
	auto sprite = Sprite::create(bgName);
	sprite->setPosition(Vec2(size.width / 2, size.height / 2));
	addChild(sprite, -2);

	return true;
}
