#include <string>
using namespace std;
//��¼��ʵ���ඨ��
class Record{
public:
	Record(){};		//Record���캯��
	~Record(){};	//Record��������

	//���úͻ���û��ǳ�
	void setNickName(string name){
		this->nickName = name;
	}
	string getNickName(){
		return this->nickName;
	}

	//���úͻ����������
	void setStarNumber(int number){
		this->starNumber = number;
	}
	int getStarNumber(){
		return this->starNumber;
	}

	//���úͻ�ý����ؿ�����
	void setBlockNumber(int number){
		this->blockNumber = number;
	}
	int getBlockNumber(){
		return this->blockNumber;
	}
private:
	string nickName;	//��ҵ��ǳ�
	int starNumber;		//��һ�õ���������
	int blockNumber;	//��ҽ����Ĺؿ�����
};