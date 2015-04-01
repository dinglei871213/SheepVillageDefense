#ifndef __SheepVillageDefense__InfoHandle__
#define __SheepVillageDefense__InfoHandle__

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
//����Json�ļ���
class InfoHandle{
public:
	string intostr(int i);//intתstring
	User getUserInfo();
	Block getBlockInfo(int blockId);			//��ȡ��blockId+1�عؿ�����
	Record getRecordInfo();				//��ȡ��¼��Ϣ
	Tower getTowerInfo(string towerName);		//��ȡ���ƶ�Ӧ�ķ���������
	Tower getTowerInfoFromBackUp(string towerName,string json);		//�ӱ����ļ��л�ȡ�����ƶ�Ӧ�ķ���������
	Wolf getWolfInfo(string wolfName);			//��ȡ��wnum+1��С�Ƕ���
	Skill getSkillInfo(string skillName);		//��ȡ���ƶ�Ӧ�ļ��ܶ���
	Skill getSkillInfoFromBackUp(string skillName,string json);		//�ӱ����ļ��л�ȡ�����ƶ�Ӧ�ļ��ܶ���
	Village getVillageInfo();			//��ȡ�����Ϣ
	GameMap getMapInfo(int gnum);		//��ȡ��ͼ��Ϣ
	bool getUpMark(int i);//��ȡ�ӵ���
	void updateUserInfo(User user);		//�����û���Ϣ
	void updateTowerInfo(Tower tower);	//���·�������Ϣ
	void updateSkillInfo(Skill skill);	//���¼�����Ϣ
	void updateBlockInfo(Block block);	//���¹ؿ���Ϣ
	void updateSkillInfoByProperty(string skillname, string propertyname, double value);
	void updateTowerInfoByProperty(string towername, string propertytype, double value);
	void updateUpMark(string upmark, bool state);
	//void addUserInfo(User user);
	//void writeUserInfo(User user);
	//void writeTowerInfo(Tower tower);
	//void writeSkillInfo(Skill skill);
};
#endif
