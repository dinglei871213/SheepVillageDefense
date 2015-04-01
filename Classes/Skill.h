#include <string>
using namespace std;
//技能实体类定义

class Skill{
public:
	Skill(){};	//Skill类的构造函数
	~Skill(){};	//Skill类的析构函数

	//设置和获得技能的名称
	void setSkillName(string name){
		this->skillName = name;
	}
	string getSkillName(){
		return this->skillName;
	}

	//设置和获得技能的类型
	void setSkillType(string type){
		this->skillType = type;
	}
	string getSkillType(){
		return this->skillType;
	}

	//设置和获得技能的伤害
	void setSkillDamage(double damage){
		this->skillDamage = damage;
	}
	double getSkillDamage(){
		return this->skillDamage;
	}

	//设置和获得技能的等级
	void setSkillLevel(int level){
		this->skillLevel = level;
	}
	int getSkillLevel(){
		return this->skillLevel;
	}

	//设置和获得技能的说明信息
	void setSkillInfo(string info){
		this->skillInfo = info;
	}
	string getSkillInfo(){
		return this->skillInfo;
	}
	void setSkillTime(double time){
		this->skillTime = time;
	}
	double getSkillTime(){
		return this->skillTime;
	}

	void setSkillRange(double range){
		this->skillRange = range;
	}
	double getSkillRange(){
		return this->skillRange;
	}
	void setSkillStrong(int strong){
		this->skillStrong = strong;
	}
	int getSkillStrong(){
		return this->getSkillStrong();
	}
private:
	string skillName;		//技能的名称
	string skillType;		//技能的类型
	double skillDamage;		//技能的伤害
	double skillTime;
	double skillRange;
	int skillStrong;
	int skillLevel;			//技能的等级
	string skillInfo;		//技能的说明信息
};
