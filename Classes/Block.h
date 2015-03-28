#include <string>
using namespace std;

//关卡的实体类定义
class Block{
public:
	Block(){};		//Block的构造函数
	~Block(){};		//Block的析构函数

	//设置和获得关卡得分数量
	void setBlockStar(int number){
		this->blockStar = number;
	}
	int getBlockStar(){
		return this->blockStar;
	}

	//设置和获取关卡序号
	void setBlockId(int id){
		this->blockId = id;
	}
	int getBlockId(){
		return this->blockId;
	}
private:
	int blockStar;		//关卡的得分数量
	int blockId;		//关卡序号
	
};