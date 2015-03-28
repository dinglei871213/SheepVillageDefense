#include <string>
using namespace std;
//羊村的实体类定义
class Village{
public:
	Village(){};	//Village的构造函数
	~Village(){};	//Village的析构函数

	//设置和获得羊村的羊总量
	void setTotalNumber(int number){
		this->totalNumber = number;
	}
	int getTotalNumber(){
		return totalNumber;
	}

	//设置和获得羊村剩余的羊的数量
	void setLeftNumber(int number){
		this->leftNumber = number;
	}
	int getLeftNumber(){
		return this->getLeftNumber();
	}

private:
	int totalNumber;	//羊村的羊总量
	int leftNumber;		//羊村剩余的羊数量
};