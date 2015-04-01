#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "cocostudio/CocoStudio.h"
#include "cocos2d.h"
#include "InfoHandle.h"
#include "ui/CocosGUI.h"
#include <stdio.h>
#include "fstream" 
#include<iostream>

using namespace rapidjson;
USING_NS_CC;
User InfoHandle::getUserInfo(){
	bool result = false;
	User user;

	//��ȡ�ļ�����
	std::string str = FileUtils::getInstance()->getStringFromFile("userInfo.json");
	CCLOG("%s", str.c_str());
	//�������ڴ���json�������
	//����rapidjson::Document�࣬���ڲ���json����
	rapidjson::Document d;
	//����json�ļ�������
	//����rapidjson::kParseDefaultFlags = 0,Ĭ�Ϸ�ʽ
	d.Parse<rapidjson::kParseDefaultFlags>(str.c_str());
	//�жϽ����Ƿ����
	if (d.HasParseError()){
		CCLOG("GetParseError%s\n", d.GetParseError());
		return user;
	}
	//��ȡjson�е�����
	//�ж�json�����Ƿ�Ϊ�����ʽ
	if (d.IsArray()){
		rapidjson::Value& array = d;                 //��ȡ�ĵ�
		result = true;
		
				rapidjson::Value& object = array[array.Size()-1];
				user.setNickName(object["nickName"].GetString()) ;
				user.setStarNumber(object["starNumber"].GetInt());
				user.setBlockNumber(object["blockNumber"].GetInt());
				user.setUpgradeNumber(object["upgradeNumber"].GetInt());
		
	}
	return user;
}


bool InfoHandle::getUpMark(int i){
	bool result = false;
	char p[10];
	sprintf(p, "%d", i + 1);
	string btn = p;
	string btnname ="btn" + btn;

	//��ȡ�ļ�����
	std::string str = FileUtils::getInstance()->getStringFromFile("upmark.json");
	CCLOG("%s", str.c_str());
	//�������ڴ���json�������
	//����rapidjson::Document�࣬���ڲ���json����
	rapidjson::Document d;
	//����json�ļ�������
	//����rapidjson::kParseDefaultFlags = 0,Ĭ�Ϸ�ʽ
	d.Parse<rapidjson::kParseDefaultFlags>(str.c_str());
	//�жϽ����Ƿ����
	if (d.HasParseError()){
		CCLOG("GetParseError%s\n", d.GetParseError());
		return result;
	}
	//��ȡjson�е�����
	//�ж�json�����Ƿ�Ϊ�����ʽ
	if (d.IsObject())
	{
		result = d["btn"][btnname.c_str()].GetBool();
		
	}
	return result;
}
Block InfoHandle::getBlockInfo(int blockid){
	Block block;
	bool result = false;
	//���±�ת�ɼ�ֵ
	char bn[10];
	sprintf(bn,"%d",blockid);
	string blocktag = bn;
	blocktag = "block"+blocktag;

	//��ȡ�ļ�����
	std::string str = FileUtils::getInstance()->getStringFromFile("blockInfo.json");
	CCLOG("%s", str.c_str());
	rapidjson::Document d;
	//�����ļ�
	d.Parse<0>(str.c_str());
	if (d.HasParseError())
	{
		CCLOG("GetPatseError%s\n", d.GetParseError());
		return block;
	}

	if (d.IsObject())
	{
		result = true;
		
		block.setBlockStar(d[blocktag.c_str()].GetInt());
		
	}
	return block;
}

Record InfoHandle::getRecordInfo(){
	Record record;
	bool result = false;
	//��ȡ�ļ�����
	std::string str = FileUtils::getInstance()->getStringFromFile("recordInfo.json");
	CCLOG("%s", str.c_str());
	rapidjson::Document d;
	//�����ļ�
	d.Parse<0>(str.c_str());
	if (d.HasParseError())
	{
		CCLOG("GetPatseError%s\n", d.GetParseError());
		return record;
	}

	if (d.IsArray())
	{
		result = true;
		rapidjson::Value&array = d;   //array=d
		
			rapidjson::Value&object = array[array.Size()-1];
			record.setNickName(object["nickName"].GetString());
			record.setBlockNumber(object["blockNumber"].GetInt());
			record.setStarNumber(object["starNumber"].GetInt());
	}
	
	return record;
}

Tower InfoHandle::getTowerInfo(string towerName){
	Tower tower;
	bool result = false;
	//��ȡ�ļ�����
	std::string str = FileUtils::getInstance()->getStringFromFile("towerInfo.json");
	CCLOG("%s", str.c_str());
	rapidjson::Document d;
	//�����ļ�
	d.Parse<0>(str.c_str());
	if (d.HasParseError())
	{
		CCLOG("GetPatseError%s\n", d.GetParseError());
		return tower;
	}

	if (d.IsObject())
	{
		result = true;
		rapidjson::Value&object = d[towerName.c_str()];
		//tower.setTowerName(object["towerName"].GetString());
		tower.setTowerInfo(object["towerInfo"].GetString());
		tower.setTowerType(object["towerType"].GetString());
		tower.setTowerLevel(object["towerLevel"].GetInt());
		tower.setDamage(object["damage"].GetDouble());
		tower.setAttackSpeed(object["attackSpeed"].GetDouble());
		tower.setAttackRange(object["attackRange"].GetDouble());
		tower.setCost(object["cost"].GetInt());
		tower.setEvolution(object["evolution"].GetString());
		
	}
	return tower;
}


Tower InfoHandle::getTowerInfoFromBackUp(string towerName,string json){
	Tower tower;
	bool result = false;
	//��ȡ�ļ�����
	std::string str = FileUtils::getInstance()->getStringFromFile(json);
	CCLOG("%s", str.c_str());
	rapidjson::Document d;
	//�����ļ�
	d.Parse<0>(str.c_str());
	if (d.HasParseError())
	{
		CCLOG("GetPatseError%s\n", d.GetParseError());
		return tower;
	}

	if (d.IsObject())
	{
		result = true;
		rapidjson::Value&object = d[towerName.c_str()];
		tower.setTowerName(object["towerName"].GetString());
		tower.setTowerInfo(object["towerInfo"].GetString());
		tower.setTowerType(object["towerType"].GetString());
		tower.setTowerLevel(object["towerLevel"].GetInt());
		tower.setDamage(object["damage"].GetDouble());
		tower.setAttackSpeed(object["attackSpeed"].GetDouble());
		tower.setAttackRange(object["attackRange"].GetDouble());
		tower.setEvolution(object["evolution"].GetString());

	}
	return tower;
}
Wolf InfoHandle::getWolfInfo(string wolfName){
	Wolf wolf;
	bool result = false;
	//��ȡ�ļ�����
	std::string str = FileUtils::getInstance()->getStringFromFile("wolfInfo.json");
	CCLOG("%s", str.c_str());
	rapidjson::Document d;
	//�����ļ�
	d.Parse<0>(str.c_str());
	if (d.HasParseError())
	{
		CCLOG("GetPatseError%s\n", d.GetParseError());
		return wolf;
	}

	if (d.IsObject())
	{
		result = true;
	//	rapidjson::Value&array = d;   //array=d
		
			rapidjson::Value&object = d[wolfName.c_str()];
			wolf.setWolfInfo(object["wolfInfo"].GetString());
			wolf.setWolfType(object["wolfType"].GetString());
			wolf.setMovingSpeed(object["movingSpeed"].GetDouble());
			wolf.setWolfHealth(object["wolfHealth"].GetInt());
			wolf.setWolfDefense(object["wolfDefense"].GetInt());
			wolf.setGold(object["gold"].GetInt());
		
	}
	return wolf;
}

Skill InfoHandle::getSkillInfo(string skillInfo){
	Skill skill;
	bool result = false;
	//��ȡ�ļ�����
	std::string str = FileUtils::getInstance()->getStringFromFile("skillInfo.json");
	CCLOG("%s", str.c_str());
	rapidjson::Document d;
	//�����ļ�
	d.Parse<0>(str.c_str());
	if (d.HasParseError())
	{
		CCLOG("GetPatseError%s\n", d.GetParseError());
		return skill;
	}

	if (d.IsObject())
	{
		result = true;
		//rapidjson::Value&array = d;   //array=d
		
			rapidjson::Value&object = d[skillInfo.c_str()];
			skill.setSkillInfo(object["skillInfo"].GetString());
			skill.setSkillType(object["skillType"].GetString());
			skill.setSkillDamage(object["skillDamage"].GetDouble());
			skill.setSkillLevel(object["skillLevel"].GetInt());
		
	}
	return skill;
}

Skill InfoHandle::getSkillInfoFromBackUp(string skillInfo,string json){
	Skill skill;
	bool result = false;
	//��ȡ�ļ�����
	std::string str = FileUtils::getInstance()->getStringFromFile(json);
	CCLOG("%s", str.c_str());
	rapidjson::Document d;
	//�����ļ�
	d.Parse<0>(str.c_str());
	if (d.HasParseError())
	{
		CCLOG("GetPatseError%s\n", d.GetParseError());
		return skill;
	}

	if (d.IsObject())
	{
		result = true;
		//rapidjson::Value&array = d;   //array=d

		rapidjson::Value&object = d[skillInfo.c_str()];
		skill.setSkillInfo(object["skillInfo"].GetString());
		skill.setSkillType(object["skillType"].GetString());
		skill.setSkillDamage(object["skillDamage"].GetDouble());
		skill.setSkillLevel(object["skillLevel"].GetInt());

	}
	return skill;
}
Village InfoHandle::getVillageInfo(){
	Village village;
	bool result = false;
	//��ȡ�ļ�����
	std::string str = FileUtils::getInstance()->getStringFromFile("villageInfo.json");
	CCLOG("%s", str.c_str());
	//�������ڴ���json�������
	rapidjson::Document d;
	d.Parse<rapidjson::kParseDefaultFlags>(str.c_str());

	if (d.HasParseError()){
		CCLOG("GetParseError%s\n", d.GetParseError());
		return village;
	}

	if (d.IsArray()){
		rapidjson::Value& array = d;                 
		result = true;
		
			rapidjson::Value& object = array[array.Size()-1];
			village.setTotalNumber(object["totalNumber"].GetInt());
			village.setLeftNumber(object["leftNumber"].GetInt());
		
	}
	return village;
}

GameMap InfoHandle::getMapInfo(int gnum){
	GameMap gmap;
	bool result = false;
	//��ȡ�ļ�����
	std::string str = FileUtils::getInstance()->getStringFromFile("mapInfo.json");
	CCLOG("%s", str.c_str());
	//�������ڴ���json�������
	rapidjson::Document d;
	d.Parse<rapidjson::kParseDefaultFlags>(str.c_str());

	if (d.HasParseError()){
		CCLOG("GetParseError%s\n", d.GetParseError());
		return gmap;
	}

	if (d.IsArray()){
		rapidjson::Value& array = d;
		result = true;
		
			rapidjson::Value& object = array[gnum];
			gmap.setMapName(object["mapName"].GetString());
			gmap.setWolfTurn(object["wolfTurn"].GetInt());
			gmap.setGold(object["gold"].GetInt());
		
	}
	return gmap;
}

//void InfoHandle::writeUserInfo(){
//	rapidjson::Document d;
//	d.SetObject();
//	rapidjson::Document::AllocatorType&allocator = d.GetAllocator();//��ȡ�����������
//	rapidjson::Value object(rapidjson::kObjectType);
//	//json object��Ӽ�/ֵ��
//	object.AddMember("nickName", "sandy", allocator);
//	object.AddMember("starNumber", 100, allocator);
//	d.AddMember("writeUserInfo", object, allocator);
//
//	rapidjson::StringBuffer buffer;
//	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
//	d.Accept(writer);
//	
//	//FILE* file = fopen("D:\Cocosworkspace\Cocos\CocosProjects\SheepVilligeDefense\Resources\res\testWriteUser.json", "w");
//	auto path = FileUtils::getInstance()->getWritablePath();
//	path.append("testWriteUser.json");
//	FILE * file = fopen(path.c_str(), "wb");
//	if (file)
//	{
//		fputs(buffer.GetString(), file);
//		fclose(file);
//	}
//
//	auto out = buffer.GetString();
//	log("out: %s", out);
//}

void InfoHandle::updateUserInfo(User user){
	//��ȡjson�ļ�����
	std::string str = FileUtils::getInstance()->getStringFromFile("userInfo.json");

	rapidjson::Document d;

	rapidjson::Document::AllocatorType&allocator = d.GetAllocator();    //��ȡ����ķ�����

	d.Parse<0>(str.c_str());    //����json�ļ�����

	//�ж��Ƿ����
	if (d.HasParseError())
	{
		CCLOG("GetParseError%s\n", d.GetParseError());
		return;
	}

	//�޸��û����������
	d[d.Size()-1]["nickName"].SetString(user.getNickName().c_str());
	d[d.Size()-1]["blockNumber"].SetInt(user.getBlockNumber());
	d[d.Size()-1]["starNumber"].SetInt(user.getStarNumber());
	d[d.Size() - 1]["upgradeNumber"].SetInt(user.getUpgradeNumber());
	//��������д���ļ�
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	d.Accept(writer);

	FILE * file = fopen("userInfo.json", "wb");
	if (file) {
		fputs(buffer.GetString(), file);
		fclose(file);
	}
	CCLOG("%s", buffer.GetString());
}

void InfoHandle::updateBlockInfo(Block block){
	//���ؿ����ת�ɱ�ǩ��ֵ
	char bn[10];
	sprintf(bn,"%d",block.getBlockId());
	string blocktag = bn;
	blocktag ="block"+blocktag;

	//��ȡjson�ļ�����
	std::string str = FileUtils::getInstance()->getStringFromFile("blockInfo.json");

	rapidjson::Document d;

	rapidjson::Document::AllocatorType&allocator = d.GetAllocator();    //��ȡ����ķ�����

	d.Parse<0>(str.c_str());    //����json�ļ�����

	//�ж��Ƿ����
	if (d.HasParseError())
	{
		CCLOG("GetParseError%s\n", d.GetParseError());
		return;
	}
	
	//�޸Ĺؿ����������
	d[blocktag.c_str()].SetInt(block.getBlockStar());

	//��������д���ļ�
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	d.Accept(writer);

	FILE * file = fopen("blockInfo.json", "wb");
	if (file) {
		fputs(buffer.GetString(), file);
		fclose(file);
	}
	CCLOG("%s", buffer.GetString());
}
void InfoHandle::updateUpMark(string upmark,bool state){

	//��ȡjson�ļ�����
	std::string str = FileUtils::getInstance()->getStringFromFile("upmark.json");

	rapidjson::Document d;

	rapidjson::Document::AllocatorType&allocator = d.GetAllocator();    //��ȡ����ķ�����

	d.Parse<0>(str.c_str());    //����json�ļ�����

	//�ж��Ƿ����
	if (d.HasParseError())
	{
		CCLOG("GetParseError%s\n", d.GetParseError());
		return;
	}

	//�޸ļӵ��Ƕ��������
	d["btn"][upmark.c_str()].SetBool(state);

	//��������д���ļ�
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	d.Accept(writer);

	FILE * file = fopen("upmark.json", "wb");
	if (file) {
		fputs(buffer.GetString(), file);
		fclose(file);
	}
	CCLOG("%s", buffer.GetString());
}

//���¼��ܶ�����Ϣ��Json�ļ���
void InfoHandle::updateSkillInfo(Skill skill){
	//��ȡjson�ļ�����
	std::string str = FileUtils::getInstance()->getStringFromFile("skillInfo.json");

	rapidjson::Document d;

	rapidjson::Document::AllocatorType&allocator = d.GetAllocator();    //��ȡ����ķ�����

	d.Parse<0>(str.c_str());    //����json�ļ�����

	//�ж��Ƿ����
	if (d.HasParseError())
	{
		CCLOG("GetParseError%s\n", d.GetParseError());
		return;
	}

	string skillName = skill.getSkillName();
	//�޸���Ӧ���ܶ��������
	d[skillName.c_str()]["skillType"].SetString(skill.getSkillType().c_str());
	d[skillName.c_str()]["skillDamage"].SetDouble(skill.getSkillDamage());
	d[skillName.c_str()]["skillInfo"].SetString(skill.getSkillInfo().c_str());
	d[skillName.c_str()]["skillLevel"].SetInt(skill.getSkillLevel());

	//��������д���ļ�
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	d.Accept(writer);

	FILE * file = fopen("skillInfo", "wb");
	if (file) {
		fputs(buffer.GetString(), file);
		fclose(file);
	}
	CCLOG("%s", buffer.GetString());
}

void InfoHandle::updateTowerInfo(Tower tower){
	//��ȡjson�ļ�����
	std::string str = FileUtils::getInstance()->getStringFromFile("towerInfo.json");

	rapidjson::Document d;

	rapidjson::Document::AllocatorType&allocator = d.GetAllocator();    //��ȡ����ķ�����

	d.Parse<0>(str.c_str());    //����json�ļ�����

	//�ж��Ƿ����
	if (d.HasParseError())
	{
		CCLOG("GetParseError%s\n", d.GetParseError());
		return;
	}

	string towerName = tower.getTowerName();
	//�޸���Ӧ���������������
	d[towerName.c_str()]["towerType"].SetString(tower.getTowerType().c_str());
	d[towerName.c_str()]["damage"].SetDouble(tower.getDamage());
	d[towerName.c_str()]["towerInfo"].SetString(tower.getTowerInfo().c_str());
	d[towerName.c_str()]["towerLevel"].SetInt(tower.getTowerLevel());
	d[towerName.c_str()]["attackSpeed"].SetDouble(tower.getAttackSpeed());
	d[towerName.c_str()]["attackRange"].SetDouble(tower.getAttackRange());
	d[towerName.c_str()]["cost"].SetInt(tower.getCost());
	d[towerName.c_str()]["evolution"].SetString(tower.getEvolution().c_str());

	//��������д���ļ�
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	d.Accept(writer);

	FILE * file = fopen("towerInfo", "wb");
	if (file) {
		fputs(buffer.GetString(), file);
		fclose(file);
	}
	CCLOG("%s", buffer.GetString());
}

void InfoHandle::updateTowerInfoByProperty(string towername,string propertytype ,float value){
	//��ȡjson�ļ�����
	std::string str = FileUtils::getInstance()->getStringFromFile("towerInfo.json");

	rapidjson::Document d;

	rapidjson::Document::AllocatorType&allocator = d.GetAllocator();    //��ȡ����ķ�����

	d.Parse<0>(str.c_str());    //����json�ļ�����

	//�ж��Ƿ����
	if (d.HasParseError())
	{
		CCLOG("GetParseError%s\n", d.GetParseError());
		return;
	}

	
	//�޸���Ӧ���������������
	d[towername.c_str()][propertytype.c_str()].SetDouble(value);

	//��������д���ļ�
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	d.Accept(writer);

	FILE * file = fopen("towerInfo", "wb");
	if (file) {
		fputs(buffer.GetString(), file);
		fclose(file);
	}
	CCLOG("%s", buffer.GetString());
}

void InfoHandle::updateSkillInfoByProperty(string skillname,string propertyname,double value){
	//��ȡjson�ļ�����
	std::string str = FileUtils::getInstance()->getStringFromFile("skillInfo.json");

	rapidjson::Document d;

	rapidjson::Document::AllocatorType&allocator = d.GetAllocator();    //��ȡ����ķ�����

	d.Parse<0>(str.c_str());    //����json�ļ�����

	//�ж��Ƿ����
	if (d.HasParseError())
	{
		CCLOG("GetParseError%s\n", d.GetParseError());
		return;
	}

	
	//�޸���Ӧ���ܶ��������
	d[skillname.c_str()][propertyname.c_str()].SetDouble(value);

	//��������д���ļ�
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	d.Accept(writer);

	FILE * file = fopen("skillInfo", "wb");
	if (file) {
		fputs(buffer.GetString(), file);
		fclose(file);
	}
	CCLOG("%s", buffer.GetString());
}
////���һ��User����Json�ļ�
//void InfoHandle::addUserInfo(User user){
//
//	//��ȡjson�ļ�����
//	std::string str = FileUtils::getInstance()->getStringFromFile("userInfo.json");
//
//	rapidjson::Document d;
//
//	rapidjson::Document::AllocatorType&allocator = d.GetAllocator();    //��ȡ����ķ�����
//
//	d.Parse<0>(str.c_str());    //����json�ļ�����
//
//	//�ж��Ƿ����
//	if (d.HasParseError())
//	{
//		CCLOG("GetParseError%s\n", d.GetParseError());
//		return;
//	}
//	//d.SetObject();��json�ļ�����Ϊ�������ͣ�
//	rapidjson::Value object(rapidjson::kObjectType);
//
//	//���Ӷ���
//	object.AddMember("nickName", user.getNickName(), allocator);
//	object.AddMember("starNumber", user.getStarNumber(), allocator);
//	d.AddMember("addUserInfo", object, allocator);
//
//	//��������д���ļ�
//	rapidjson::StringBuffer buffer;
//	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
//	d.Accept(writer);
//
//	FILE * file = fopen("userInfo.json", "wb");
//	if (file) {
//		fputs(buffer.GetString(), file);
//		fclose(file);
//	}
//	CCLOG("%s", buffer.GetString());
//}


//����Skill���Json�ļ�
//void InfoHandle::writeSkillInfo(Skill skill){
//	rapidjson::Document d;
//	d.SetObject();
//	rapidjson::Document::AllocatorType&allocator = d.GetAllocator();//��ȡ����ķ�����
//	rapidjson::Value object(rapidjson::kObjectType);
//	//json object��Ӽ�/ֵ��
//	object.AddMember("skillName", "sandy", allocator);
//	object.AddMember("skillInfo", "good guy", allocator);
//	object.AddMember("skillType", "defense", allocator);
//	object.AddMember("skillDamage", 5.5, allocator);
//	object.AddMember("skillLevel", 20, allocator);
//
//	d.AddMember("writeSkillInfo", object, allocator);
//
//	rapidjson::StringBuffer buffer;
//	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
//	d.Accept(writer);
//
//	//FILE* file = fopen("D:\Cocosworkspace\Cocos\CocosProjects\SheepVilligeDefense\Resources\res\testWriteSkill.json", "w");
//	auto path = FileUtils::getInstance()->getWritablePath();
//	path.append("testWriteSkill.json");
//	FILE * file = fopen(path.c_str(), "wb");
//	if (file)
//	{
//		fputs(buffer.GetString(), file);
//		fclose(file);
//	}
//
//	auto out = buffer.GetString();
//	log("out: %s", out);
//}