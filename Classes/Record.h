#include <string>
using namespace std;
//记录的实体类定义
class Record{
public:
	Record(){};		//Record构造函数
	~Record(){};	//Record析构函数

	//设置和获得用户昵称
	void setNickName(string name){
		this->nickName = name;
	}
	string getNickName(){
		return this->nickName;
	}

	//设置和获得星星数量
	void setStarNumber(int number){
		this->starNumber = number;
	}
	int getStarNumber(){
		return this->starNumber;
	}

	//设置和获得解锁关卡数量
	void setBlockNumber(int number){
		this->blockNumber = number;
	}
	int getBlockNumber(){
		return this->blockNumber;
	}
private:
	string nickName;	//玩家的昵称
	int starNumber;		//玩家获得的星星数量
	int blockNumber;	//玩家解锁的关卡数量
};