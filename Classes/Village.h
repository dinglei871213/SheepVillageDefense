#include <string>
using namespace std;
//����ʵ���ඨ��
class Village{
public:
	Village(){};	//Village�Ĺ��캯��
	~Village(){};	//Village����������

	//���úͻ������������
	void setTotalNumber(int number){
		this->totalNumber = number;
	}
	int getTotalNumber(){
		return totalNumber;
	}

	//���úͻ�����ʣ����������
	void setLeftNumber(int number){
		this->leftNumber = number;
	}
	int getLeftNumber(){
		return this->getLeftNumber();
	}

private:
	int totalNumber;	//����������
	int leftNumber;		//���ʣ���������
};