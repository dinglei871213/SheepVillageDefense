#include <string>
using namespace std;
//地图的实体类定义
class GameMap{
public:
	GameMap(){};		//Map的构造函数
	~GameMap(){};		//Map的析构函数

	//设置和获得地图名称
	void setMapName(string name){
		this->mapName = name;
	}
	string getMapName(){
		return this->mapName;
	}

	//设置和获得进攻波数
	void setWolfTurn(int turn){
		this->wolfTurn = turn;
	}
	int getWolfTurn(){
		return this->wolfTurn;
	}

	//设置和获得金币数
	void setGold(int gold){
		this->gold = gold;
	}
	int getGold(){
		return gold;
	}
private:
	string mapName;		//地图的名称
	int wolfTurn;		//小狼进攻的波数
	int gold;			//游戏中的金币数
};