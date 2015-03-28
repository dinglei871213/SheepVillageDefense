//用户实体类定义
#include <string>
using namespace std;

class User{
public:
	User(){};				//User类的构造函数
	~User(){};				//User类的析构函数

	//设置昵称
	void setNickName(string	nickName){
		this->nickName = nickName;
	};
	//获取昵称
	string getNickName(){
		return this->nickName;
	};
	//设置得分数量
	void setStarNumber(int starNumber){
		this->starNumber = starNumber;
	};
	//获得得分数量
	int getStarNumber(){
		return this->starNumber;
	};
	//设置用户解锁关卡数量
	void setBlockNumber(int num){
		this->blockNumber = num;
	}
	//获得用户解锁的关卡数量
	int getBlockNumber(){
		return this->blockNumber;
	}
	//设置用户解锁关卡数量
	void setUpgradeNumber(int num){
		this->upgradeNumber = num;
	}
	//获得用户解锁的关卡数量
	int getUpgradeNumber(){
		return this->upgradeNumber;
	}
private:
	string nickName;//用户昵称
	int starNumber;//用户得分数量
	int blockNumber;//用户解锁的关卡数量
	int upgradeNumber;//用户解锁的关卡数量
};