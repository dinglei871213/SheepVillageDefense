
#ifndef __SheepVillageDefense__LoadLevelInfo__
#define __SheepVillageDefense__LoadLevelInfo__

#include "cocos2d.h"
using namespace cocos2d;

class LoadLevelinfo: public Ref
{
public:
    
    ~LoadLevelinfo();
    static LoadLevelinfo * createLoadLevelinfo(const std::string& plistpath);
    
    bool initPlist(const std::string& plistpath);
	void readLevelInfo();
    void clearAll();
    
private:
    ValueMap resources;
    ValueMap levelInfo;
};
#endif /* defined(__thiefTD__LoadLevelInfo__) */
