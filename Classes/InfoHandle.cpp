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
string InfoHandle::intostr(int i){
	char str[20];
	sprintf(str,"%d",i);
	string strin = str;
	return strin;
}

User InfoHandle::getUserInfo(){
	bool result = false;
	User user;

	//读取文件内容
	std::string str = FileUtils::getInstance()->getStringFromFile("userInfo.json");
	CCLOG("%s", str.c_str());
	//创建用于处理json代码的类
	//创建rapidjson::Document类，用于操作json代码
	rapidjson::Document d;
	//解析json文件的内容
	//其中rapidjson::kParseDefaultFlags = 0,默认方式
	d.Parse<rapidjson::kParseDefaultFlags>(str.c_str());
	//判断解析是否出错
	if (d.HasParseError()){
		CCLOG("GetParseError%s\n", d.GetParseError());
		return user;
	}
	//获取json中的数据
	//判断json数据是否为数组格式
	if (d.IsArray()){
		rapidjson::Value& array = d;                 //读取文档
		result = true;
		
				rapidjson::Value& object = array[array.Size()-1];
				//user.setNickName(object["nickName"].GetString()) ;
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

	//读取文件内容
	std::string str = FileUtils::getInstance()->getStringFromFile("upmark.json");
	CCLOG("%s", str.c_str());
	//创建用于处理json代码的类
	//创建rapidjson::Document类，用于操作json代码
	rapidjson::Document d;
	//解析json文件的内容
	//其中rapidjson::kParseDefaultFlags = 0,默认方式
	d.Parse<rapidjson::kParseDefaultFlags>(str.c_str());
	//判断解析是否出错
	if (d.HasParseError()){
		CCLOG("GetParseError%s\n", d.GetParseError());
		return result;
	}
	//获取json中的数据
	//判断json数据是否为数组格式
	if (d.IsObject())
	{
		result = d["btn"][btnname.c_str()].GetBool();
		
	}
	return result;
}
Block InfoHandle::getBlockInfo(int blockid){
	Block block;
	bool result = false;
	//将下标转成键值
	char bn[10];
	sprintf(bn,"%d",blockid);
	string blocktag = bn;
	blocktag = "block"+blocktag;

	//读取文件内容
	std::string str = FileUtils::getInstance()->getStringFromFile("blockInfo.json");
	CCLOG("%s", str.c_str());
	rapidjson::Document d;
	//解析文件
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
	//读取文件内容
	std::string str = FileUtils::getInstance()->getStringFromFile("recordInfo.json");
	CCLOG("%s", str.c_str());
	rapidjson::Document d;
	//解析文件
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
	//读取文件内容
	std::string str = FileUtils::getInstance()->getStringFromFile("towerInfo.json");
	CCLOG("%s", str.c_str());
	rapidjson::Document d;
	//解析文件
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
		//tower.setTowerInfo(object["towerInfo"].GetString());
		//tower.setTowerType(object["towerType"].GetString());
		//tower.setTowerLevel(object["towerLevel"].GetInt());
		tower.setDamage(object["damage"].GetDouble());
		tower.setAttackSpeed(object["attackSpeed"].GetDouble());
		tower.setAttackRange(object["attackRange"].GetDouble());
		tower.setCost(object["cost"].GetInt());
		//tower.setEvolution(object["evolution"].GetString());
		
	}
	return tower;
}


Tower InfoHandle::getTowerInfoFromBackUp(string towerName,string json){
	Tower tower;
	bool result = false;
	//读取文件内容
	std::string str = FileUtils::getInstance()->getStringFromFile(json);
	CCLOG("%s", str.c_str());
	rapidjson::Document d;
	//解析文件
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
		tower.setTowerName(towerName);
		//tower.setTowerInfo(object["towerInfo"].GetString());
		//tower.setTowerType(object["towerType"].GetString());
		//tower.setTowerLevel(object["towerLevel"].GetInt());
		tower.setDamage(object["damage"].GetDouble());
		tower.setAttackSpeed(object["attackSpeed"].GetDouble());
		tower.setAttackRange(object["attackRange"].GetDouble());
		//tower.setEvolution(object["evolution"].GetString());
		tower.setCost(object["cost"].GetInt());
	}
	return tower;
}
Wolf InfoHandle::getWolfInfo(string wolfName){
	Wolf wolf;
	bool result = false;
	//读取文件内容
	std::string str = FileUtils::getInstance()->getStringFromFile("wolfInfo.json");
	CCLOG("%s", str.c_str());
	rapidjson::Document d;
	//解析文件
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
			//wolf.setWolfInfo(object["wolfInfo"].GetString());
			//wolf.setWolfType(object["wolfType"].GetString());
			wolf.setMovingSpeed(object["movingSpeed"].GetDouble());
			wolf.setWolfHealth(object["wolfHealth"].GetInt());
			//wolf.setWolfDefense(object["wolfDefense"].GetInt());
			wolf.setGold(object["gold"].GetInt());
		
	}
	return wolf;
}

Skill InfoHandle::getSkillInfo(string skillInfo){
	Skill skill;
	bool result = false;
	//读取文件内容
	std::string str = FileUtils::getInstance()->getStringFromFile("skillInfo.json");
	CCLOG("%s", str.c_str());
	rapidjson::Document d;
	//解析文件
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
			skill.setSkillDamage(object["skillDamage"].GetDouble());
			skill.setSkillTime(object["time"].GetDouble());
			skill.setSkillRange(object["range"].GetDouble());
			skill.setSkillStrong(object["strong"].GetInt());
		
	}
	return skill;
}

Skill InfoHandle::getSkillInfoFromBackUp(string skillInfo,string json){
	Skill skill;
	bool result = false;
	//读取文件内容
	std::string str = FileUtils::getInstance()->getStringFromFile(json);
	CCLOG("%s", str.c_str());
	rapidjson::Document d;
	//解析文件
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
		//skill.setSkillInfo(object["skillInfo"].GetString());
		//skill.setSkillType(object["skillType"].GetString());
		skill.setSkillDamage(object["skillDamage"].GetDouble());
		//skill.setSkillLevel(object["skillLevel"].GetInt());
		skill.setSkillTime(object["time"].GetDouble());
		skill.setSkillRange(object["range"].GetDouble());
		skill.setSkillStrong(object["strong"].GetInt());
	}
	return skill;
}
Village InfoHandle::getVillageInfo(){
	Village village;
	bool result = false;
	//读取文件内容
	std::string str = FileUtils::getInstance()->getStringFromFile("villageInfo.json");
	CCLOG("%s", str.c_str());
	//创建用于处理json代码的类
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
	//读取文件内容
	std::string str = FileUtils::getInstance()->getStringFromFile("mapInfo.json");
	CCLOG("%s", str.c_str());
	//创建用于处理json代码的类
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
//	rapidjson::Document::AllocatorType&allocator = d.GetAllocator();//获取最初的适配器
//	rapidjson::Value object(rapidjson::kObjectType);
//	//json object添加键/值对
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
	//读取json文件内容
	std::string str = FileUtils::getInstance()->getStringFromFile("userInfo.json");

	rapidjson::Document d;

	rapidjson::Document::AllocatorType&allocator = d.GetAllocator();    //获取最初的分配器

	d.Parse<0>(str.c_str());    //解析json文件内容

	//判断是否出错
	if (d.HasParseError())
	{
		CCLOG("GetParseError%s\n", d.GetParseError());
		return;
	}

	//修改用户对象的属性
	d[d.Size()-1]["blockNumber"].SetInt(user.getBlockNumber());
	d[d.Size()-1]["starNumber"].SetInt(user.getStarNumber());
	d[d.Size() - 1]["upgradeNumber"].SetInt(user.getUpgradeNumber());
	//数据重新写入文件
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
	//将关卡序号转成标签键值
	char bn[10];
	sprintf(bn,"%d",block.getBlockId());
	string blocktag = bn;
	blocktag ="block"+blocktag;

	//读取json文件内容
	std::string str = FileUtils::getInstance()->getStringFromFile("blockInfo.json");

	rapidjson::Document d;

	rapidjson::Document::AllocatorType&allocator = d.GetAllocator();    //获取最初的分配器

	d.Parse<0>(str.c_str());    //解析json文件内容

	//判断是否出错
	if (d.HasParseError())
	{
		CCLOG("GetParseError%s\n", d.GetParseError());
		return;
	}
	
	//修改关卡对象的属性
	d[blocktag.c_str()].SetInt(block.getBlockStar());

	//数据重新写入文件
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

	//读取json文件内容
	std::string str = FileUtils::getInstance()->getStringFromFile("upmark.json");

	rapidjson::Document d;

	rapidjson::Document::AllocatorType&allocator = d.GetAllocator();    //获取最初的分配器

	d.Parse<0>(str.c_str());    //解析json文件内容

	//判断是否出错
	if (d.HasParseError())
	{
		CCLOG("GetParseError%s\n", d.GetParseError());
		return;
	}

	//修改加点标记对象的属性
	d["btn"][upmark.c_str()].SetBool(state);

	//数据重新写入文件
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

//更新技能对象信息到Json文件中
void InfoHandle::updateSkillInfo(Skill skill){
	//读取json文件内容
	std::string str = FileUtils::getInstance()->getStringFromFile("skillInfo.json");

	rapidjson::Document d;

	rapidjson::Document::AllocatorType&allocator = d.GetAllocator();    //获取最初的分配器

	d.Parse<0>(str.c_str());    //解析json文件内容

	//判断是否出错
	if (d.HasParseError())
	{
		CCLOG("GetParseError%s\n", d.GetParseError());
		return;
	}

	string skillName = skill.getSkillName();
	//修改相应技能对象的属性
	d[skillName.c_str()]["skillDamage"].SetDouble(skill.getSkillDamage());
	d[skillName.c_str()]["time"].SetDouble(skill.getSkillTime());
	d[skillName.c_str()]["range"].SetDouble(skill.getSkillRange());
	d[skillName.c_str()]["strong"].SetInt(skill.getSkillStrong());

	//数据重新写入文件
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	d.Accept(writer);

	FILE * file = fopen("skillInfo.json", "wb");
	if (file) {
		fputs(buffer.GetString(), file);
		fclose(file);
	}
	CCLOG("%s", buffer.GetString());
}

void InfoHandle::updateTowerInfo(Tower tower){
	//读取json文件内容
	std::string str = FileUtils::getInstance()->getStringFromFile("towerInfo.json");

	rapidjson::Document d;

	rapidjson::Document::AllocatorType&allocator = d.GetAllocator();    //获取最初的分配器

	d.Parse<0>(str.c_str());    //解析json文件内容

	//判断是否出错
	if (d.HasParseError())
	{
		CCLOG("GetParseError%s\n", d.GetParseError());
		return;
	}

	string towerName = tower.getTowerName();
	//修改相应防御塔对象的属性
	d[towerName.c_str()]["damage"].SetDouble(tower.getDamage());
	d[towerName.c_str()]["attackSpeed"].SetDouble(tower.getAttackSpeed());
	d[towerName.c_str()]["attackRange"].SetDouble(tower.getAttackRange());
	d[towerName.c_str()]["cost"].SetInt(tower.getCost());
	
	//数据重新写入文件
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	d.Accept(writer);

	FILE * file = fopen("towerInfo.json", "wb");
	if (file) {
		fputs(buffer.GetString(), file);
		fclose(file);
	}
	CCLOG("%s", buffer.GetString());
}

void InfoHandle::updateTowerInfoByProperty(string towername,string propertytype ,double value){
	//读取json文件内容
	std::string str = FileUtils::getInstance()->getStringFromFile("towerInfo.json");

	rapidjson::Document d;

	rapidjson::Document::AllocatorType&allocator = d.GetAllocator();    //获取最初的分配器

	d.Parse<0>(str.c_str());    //解析json文件内容

	//判断是否出错
	if (d.HasParseError())
	{
		CCLOG("GetParseError%s\n", d.GetParseError());
		return;
	}

	
	//修改相应防御塔对象的属性
	d[towername.c_str()][propertytype.c_str()].SetDouble(value);

	//数据重新写入文件
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	d.Accept(writer);

	FILE * file = fopen("towerInfo.json", "wb");
	if (file) {
		fputs(buffer.GetString(), file);
		fclose(file);
	}
	CCLOG("%s", buffer.GetString());
}

void InfoHandle::updateSkillInfoByProperty(string skillname,string propertyname,double value){
	//读取json文件内容
	std::string str = FileUtils::getInstance()->getStringFromFile("skillInfo.json");

	rapidjson::Document d;

	rapidjson::Document::AllocatorType&allocator = d.GetAllocator();    //获取最初的分配器

	d.Parse<0>(str.c_str());    //解析json文件内容

	//判断是否出错
	if (d.HasParseError())
	{
		CCLOG("GetParseError%s\n", d.GetParseError());
		return;
	}

	
	//修改相应技能对象的属性
	d[skillname.c_str()][propertyname.c_str()].SetDouble(value);

	//数据重新写入文件
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	d.Accept(writer);

	FILE * file = fopen("skillInfo.json", "wb");
	if (file) {
		fputs(buffer.GetString(), file);
		fclose(file);
	}
	CCLOG("%s", buffer.GetString());
}
////添加一个User对象到Json文件
//void InfoHandle::addUserInfo(User user){
//
//	//读取json文件内容
//	std::string str = FileUtils::getInstance()->getStringFromFile("userInfo.json");
//
//	rapidjson::Document d;
//
//	rapidjson::Document::AllocatorType&allocator = d.GetAllocator();    //获取最初的分配器
//
//	d.Parse<0>(str.c_str());    //解析json文件内容
//
//	//判断是否出错
//	if (d.HasParseError())
//	{
//		CCLOG("GetParseError%s\n", d.GetParseError());
//		return;
//	}
//	//d.SetObject();将json文件设置为对象类型？
//	rapidjson::Value object(rapidjson::kObjectType);
//
//	//增加对象
//	object.AddMember("nickName", user.getNickName(), allocator);
//	object.AddMember("starNumber", user.getStarNumber(), allocator);
//	d.AddMember("addUserInfo", object, allocator);
//
//	//数据重新写入文件
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


//创建Skill类的Json文件
//void InfoHandle::writeSkillInfo(Skill skill){
//	rapidjson::Document d;
//	d.SetObject();
//	rapidjson::Document::AllocatorType&allocator = d.GetAllocator();//获取最初的分配器
//	rapidjson::Value object(rapidjson::kObjectType);
//	//json object添加键/值对
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