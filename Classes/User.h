//�û�ʵ���ඨ��
#include <string>
using namespace std;

class User{
public:
	User(){};				//User��Ĺ��캯��
	~User(){};				//User�����������

	//�����ǳ�
	void setNickName(string	nickName){
		this->nickName = nickName;
	};
	//��ȡ�ǳ�
	string getNickName(){
		return this->nickName;
	};
	//���õ÷�����
	void setStarNumber(int starNumber){
		this->starNumber = starNumber;
	};
	//��õ÷�����
	int getStarNumber(){
		return this->starNumber;
	};
	//�����û������ؿ�����
	void setBlockNumber(int num){
		this->blockNumber = num;
	}
	//����û������Ĺؿ�����
	int getBlockNumber(){
		return this->blockNumber;
	}
	//�����û������ؿ�����
	void setUpgradeNumber(int num){
		this->upgradeNumber = num;
	}
	//����û������Ĺؿ�����
	int getUpgradeNumber(){
		return this->upgradeNumber;
	}
private:
	string nickName;//�û��ǳ�
	int starNumber;//�û��÷�����
	int blockNumber;//�û������Ĺؿ�����
	int upgradeNumber;//�û������Ĺؿ�����
};