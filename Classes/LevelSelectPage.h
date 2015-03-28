#include "cocos2d.h"
#include <iostream>
USING_NS_CC;
class LevelSelectPage: public Node
{
public:
	bool initLevelPage(const std::string& bgname, int level);
	static LevelSelectPage* create(const std::string& bgname, int level);
};
