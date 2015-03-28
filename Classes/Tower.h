#include <string>
using namespace std;

//��������ʵ���ඨ��
class Tower{
public:
	Tower(){};				//Tower���캯��
	~Tower(){};				//Tower��������
	
	//���úͻ�÷���������
	void setTowerName(string towerName){
		this->towerName = towerName;
	}
	string getTowerName(){
		return this->towerName;
	}

	//���úͻ�÷���������
	void setTowerType(string towerType){
		this->towerType = towerType;
	}
	string getTowerType(){
		return this->towerType;
	}

	//���úͻ�÷������ȼ�
	void setTowerLevel(int level){
		this->towerLevel = level;
	}
	int getTowerLevel(){
		return this->towerLevel;
	}

	//���úͻ�÷�����������
	void setDamage(double damage){
		this->damage = damage;
	}
	double getDamage(){
		return this->damage;
	}

	//���úͻ�÷��������
	void setAttackRange(double range){
		this->attackRange = range;
	}
	double getAttackRange(){
		return this->attackRange;
	}

	//���úͻ�÷����������ٶ�
	void setAttackSpeed(double speed){
		this->attackSpeed = speed;
	}
	double getAttackSpeed(){
		return this->attackSpeed;
	}

	//���úͻ�÷���������
	void setCost(int cost){
		this->cost = cost;
	}
	int getCost(){
		return this->cost;
	}

	//���úͻ�÷�������������
	void setEvolution(string evolution){
		this->evolution = evolution;
	}
	string getEvolution(){
		return this->evolution;
	}

	//���úͻ�÷�����˵����Ϣ
	void setTowerInfo(string info){
		this->towerInfo = info;
	}
	string getTowerInfo(){
		return this->towerInfo;
	}

private:
	string towerName;		//����������
	string towerType;		//����������
	int towerLevel;			//�������ȼ�
	double damage;			//������������
	double attackRange;		//���������
	double attackSpeed;		//����������
	int cost;				//�����������ʽ�
	string evolution;		//��������������
	string towerInfo;		//������˵��
};