#include <string>
using namespace std;
//��ͼ��ʵ���ඨ��
class GameMap{
public:
	GameMap(){};		//Map�Ĺ��캯��
	~GameMap(){};		//Map����������

	//���úͻ�õ�ͼ����
	void setMapName(string name){
		this->mapName = name;
	}
	string getMapName(){
		return this->mapName;
	}

	//���úͻ�ý�������
	void setWolfTurn(int turn){
		this->wolfTurn = turn;
	}
	int getWolfTurn(){
		return this->wolfTurn;
	}

	//���úͻ�ý����
	void setGold(int gold){
		this->gold = gold;
	}
	int getGold(){
		return gold;
	}
private:
	string mapName;		//��ͼ������
	int wolfTurn;		//С�ǽ����Ĳ���
	int gold;			//��Ϸ�еĽ����
};