
#include "User.h"
#include "Wolf.h"
#include "Block.h"
#include "GameMap.h"
#include "Record.h"
#include "Skill.h"
#include "Tower.h"
#include "Village.h"
#include <iostream>
using namespace std;
//处理Json文件类
class InfoHandle{
public:
	User getUserInfo();
	Block getBlockInfo(int blockId);			//获取第blockId+1关关卡对象
	Record getRecordInfo();				//获取记录信息
	Tower getTowerInfo(string towerName);		//获取名称对应的防御塔对象
	Tower getTowerInfoFromBackUp(string towerName,string json);		//从备份文件中获取与名称对应的防御塔对象
	Wolf getWolfInfo(string wolfName);			//获取第wnum+1个小狼对象
	Skill getSkillInfo(string skillName);		//获取名称对应的技能对象
	Skill getSkillInfoFromBackUp(string skillName,string json);		//从备份文件中获取与名称对应的技能对象
	Village getVillageInfo();			//获取羊村信息
	GameMap getMapInfo(int gnum);		//获取地图信息
	bool InfoHandle::getUpMark(int i);//获取加点标记
	void updateUserInfo(User user);		//更新用户信息
	void updateTowerInfo(Tower tower);	//更新防御塔信息
	void updateSkillInfo(Skill skill);	//更新技能信息
	void updateBlockInfo(Block block);	//更新关卡信息
	void InfoHandle::updateSkillInfoByProperty(string skillname, string propertyname, double value);
	void InfoHandle::updateTowerInfoByProperty(string towername, string propertytype, float value);
	void InfoHandle::updateUpMark(string upmark, bool state);
	//void addUserInfo(User user);
	//void writeUserInfo(User user);
	//void writeTowerInfo(Tower tower);
	//void writeSkillInfo(Skill skill);
};
