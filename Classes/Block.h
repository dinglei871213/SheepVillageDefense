#include <string>
using namespace std;

//�ؿ���ʵ���ඨ��
class Block{
public:
	Block(){};		//Block�Ĺ��캯��
	~Block(){};		//Block����������

	//���úͻ�ùؿ��÷�����
	void setBlockStar(int number){
		this->blockStar = number;
	}
	int getBlockStar(){
		return this->blockStar;
	}

	//���úͻ�ȡ�ؿ����
	void setBlockId(int id){
		this->blockId = id;
	}
	int getBlockId(){
		return this->blockId;
	}
private:
	int blockStar;		//�ؿ��ĵ÷�����
	int blockId;		//�ؿ����
	
};