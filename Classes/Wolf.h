#include <string>
using namespace std;

//С�ǵ�ʵ���ඨ��
class Wolf{
public:
	Wolf(){};	//С�ǵĹ��캯��
	~Wolf(){};	//С�ǵ���������

	//���úͻ��С�ǵ�����
	void setWolfName(string name){
		this->wolfName = name;
	}
	string getWolfName(){
		return this->wolfName;
	}

	//���úͻ��С�ǵ�����
	void setWolfType(string type){
		this->wolfType = type;
	}
	string getWolfType(){
		return this->wolfType;
	}

	//���úͻ��С�ǵ�Ѫ��
	void setWolfHealth(int health){
		this->wolfHealth = health;
	}
	int getWolfHealth(){
		return this->wolfHealth;
	}

	//���úͻ��С�ǵ��ƶ��ٶ�
	void setMovingSpeed(double speed){
		this->movingSpeed = speed;
	}
	double getMovingSpeed(){
		return this->movingSpeed;
	}

	//���úͻ��С�ǵķ�����
	void setWolfDefense(int defense){
		this->wolfDefense = defense;
	}
	int getWolfDefense(){
		return this->wolfDefense;
	}

	//���úͻ��С�ǵ�˵����Ϣ
	void setWolfInfo(string info){
		this->wolfInfo = info;
	}
	string getWolfInfo(){
		return this->wolfInfo;
	}

	//���úͻ��С�ǵĻ�ɱ�ͽ�
	void setGold(int gold){
		this->gold = gold;
	}
	int getGold(){
		return this->gold;
	}

private:
	string wolfName;		//С�ǵ�����
	string wolfType;		//С�ǵ�����
	int wolfHealth;			//С�ǵ�Ѫ��
	double movingSpeed;		//С�ǵ��ƶ��ٶ�
	int wolfDefense;		//С�ǵķ�����
	string wolfInfo;		//С�ǵ�˵����Ϣ
	int gold;				//С�ǵĻ�ɱ�ͽ�
};