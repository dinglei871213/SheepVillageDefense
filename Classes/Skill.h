#include <string>
using namespace std;
//����ʵ���ඨ��

class Skill{
public:
	Skill(){};	//Skill��Ĺ��캯��
	~Skill(){};	//Skill�����������

	//���úͻ�ü��ܵ�����
	void setSkillName(string name){
		this->skillName = name;
	}
	string getSkillName(){
		return this->skillName;
	}

	//���úͻ�ü��ܵ�����
	void setSkillType(string type){
		this->skillType = type;
	}
	string getSkillType(){
		return this->skillType;
	}

	//���úͻ�ü��ܵ��˺�
	void setSkillDamage(double damage){
		this->skillDamage = damage;
	}
	double getSkillDamage(){
		return this->skillDamage;
	}

	//���úͻ�ü��ܵĵȼ�
	void setSkillLevel(int level){
		this->skillLevel = level;
	}
	int getSkillLevel(){
		return this->skillLevel;
	}

	//���úͻ�ü��ܵ�˵����Ϣ
	void setSkillInfo(string info){
		this->skillInfo = info;
	}
	string getSkillInfo(){
		return this->skillInfo;
	}

private:
	string skillName;		//���ܵ�����
	string skillType;		//���ܵ�����
	double skillDamage;		//���ܵ��˺�
	int skillLevel;			//���ܵĵȼ�
	string skillInfo;		//���ܵ�˵����Ϣ
};
