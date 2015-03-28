#include <string>
using namespace std;

//防御塔的实体类定义
class Tower{
public:
	Tower(){};				//Tower构造函数
	~Tower(){};				//Tower析构函数
	
	//设置和获得防御塔名称
	void setTowerName(string towerName){
		this->towerName = towerName;
	}
	string getTowerName(){
		return this->towerName;
	}

	//设置和获得防御塔类型
	void setTowerType(string towerType){
		this->towerType = towerType;
	}
	string getTowerType(){
		return this->towerType;
	}

	//设置和获得防御塔等级
	void setTowerLevel(int level){
		this->towerLevel = level;
	}
	int getTowerLevel(){
		return this->towerLevel;
	}

	//设置和获得防御塔攻击力
	void setDamage(double damage){
		this->damage = damage;
	}
	double getDamage(){
		return this->damage;
	}

	//设置和获得防御塔射程
	void setAttackRange(double range){
		this->attackRange = range;
	}
	double getAttackRange(){
		return this->attackRange;
	}

	//设置和获得防御塔攻击速度
	void setAttackSpeed(double speed){
		this->attackSpeed = speed;
	}
	double getAttackSpeed(){
		return this->attackSpeed;
	}

	//设置和获得防御塔费用
	void setCost(int cost){
		this->cost = cost;
	}
	int getCost(){
		return this->cost;
	}

	//设置和获得防御塔进化方向
	void setEvolution(string evolution){
		this->evolution = evolution;
	}
	string getEvolution(){
		return this->evolution;
	}

	//设置和获得防御塔说明信息
	void setTowerInfo(string info){
		this->towerInfo = info;
	}
	string getTowerInfo(){
		return this->towerInfo;
	}

private:
	string towerName;		//防御塔名称
	string towerType;		//防御塔类型
	int towerLevel;			//防御塔等级
	double damage;			//防御塔攻击力
	double attackRange;		//防御塔射程
	double attackSpeed;		//防御塔攻速
	int cost;				//防御塔建造资金
	string evolution;		//防御塔进化方向
	string towerInfo;		//防御塔说明
};