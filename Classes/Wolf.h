#include <string>
using namespace std;

//小狼的实体类定义
class Wolf{
public:
	Wolf(){};	//小狼的构造函数
	~Wolf(){};	//小狼的析构函数

	//设置和获得小狼的名称
	void setWolfName(string name){
		this->wolfName = name;
	}
	string getWolfName(){
		return this->wolfName;
	}

	//设置和获得小狼的类型
	void setWolfType(string type){
		this->wolfType = type;
	}
	string getWolfType(){
		return this->wolfType;
	}

	//设置和获得小狼的血量
	void setWolfHealth(int health){
		this->wolfHealth = health;
	}
	int getWolfHealth(){
		return this->wolfHealth;
	}

	//设置和获得小狼的移动速度
	void setMovingSpeed(double speed){
		this->movingSpeed = speed;
	}
	double getMovingSpeed(){
		return this->movingSpeed;
	}

	//设置和获得小狼的防御力
	void setWolfDefense(int defense){
		this->wolfDefense = defense;
	}
	int getWolfDefense(){
		return this->wolfDefense;
	}

	//设置和获得小狼的说明信息
	void setWolfInfo(string info){
		this->wolfInfo = info;
	}
	string getWolfInfo(){
		return this->wolfInfo;
	}

	//设置和获得小狼的击杀赏金
	void setGold(int gold){
		this->gold = gold;
	}
	int getGold(){
		return this->gold;
	}

private:
	string wolfName;		//小狼的名称
	string wolfType;		//小狼的类型
	int wolfHealth;			//小狼的血量
	double movingSpeed;		//小狼的移动速度
	int wolfDefense;		//小狼的防御力
	string wolfInfo;		//小狼的说明信息
	int gold;				//小狼的击杀赏金
};