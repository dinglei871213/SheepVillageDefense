

#ifndef __SheepVillageDefense__Enemy__
#define __SheepVillageDefense__Enemy__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
//���˻���
class EnemyBase : public Sprite
{
public:
    EnemyBase();
    ~EnemyBase();
    virtual bool init() override;
    CREATE_FUNC(EnemyBase);
    
    static Animation* createAnimation(std::string prefixName, int framesNum, float delay);//�������˶���	
    virtual void changeDirection(float dt){};//�ı䷽��
    virtual void enemyExpload(){};//����������ը
    Node* currPoint();//��õ��˵�ǰ������·����
    Node* nextPoint();//������һ���ƶ���
    void runFllowPoint();//�õ���ǰ��
	bool changeRote;//�Ƿ񱻷紵��
	bool changeFinish;//�Ƿ񱻷紵���˻ص����
	void changeFinished();//����Ƿ��Ѿ��ص����
	void createAndSetHpBar();//����������Ѫ��

	void enemyReduceHp(int reduceHp);//��Ѫ
	void enemySlow(int slowSpeed, int slowSpeedTime);//����
	void enemyPoison(int poisonHpBullet, int poisonHpTimeBullet);//�ж�
	void enemyPoison(float dt);//�ж�
	void resumeSpeed(float dt);//���ٻָ�
private:
	CC_SYNTHESIZE(Vector<Node*>, pointsVector, PointsVector);//���˽�����·�ߵ㼯��
	CC_SYNTHESIZE(int, pointCounter, PointCounter);//����·������
    
protected:
    Animation *animationRight;//�Ҳ��˶�����
    Animation *animationLeft;//����˶�����
	Animation *animationFront;//ǰ���˶�����
	Animation *animationBack;//����˶�����
    Animation *animationExplode;//��������
    CC_SYNTHESIZE(float, runSpeed, RunSpeed);//�ƶ��ٶ�
    CC_SYNTHESIZE(float, maxHp, MaxHp);//���Ѫ��
    CC_SYNTHESIZE(float, vaule, Vaule);//��Ǯ
    CC_SYNTHESIZE(float, currHp, CurrHp);//��ǰѪ��
	CC_SYNTHESIZE(float, hpPercentage, HpPercentage);//Ѫ���ٷֱ�
    CC_SYNTHESIZE_READONLY(ProgressTimer*, hpBar, HpBar);//Ѫ����
    CC_SYNTHESIZE(bool, enemySuccessful, EnemySuccessful);//���˳ɹ�����
	Sprite* sprite;//���˸�����
    Sprite* hpBgSprite;//Ѫ��������


	int poisonHp;//�ж���Ѫ��
	int poisonHpTime;//�ж�ʱ��

	int preSpeed;//����ǰ�ٶ�
	//Node* node;
};



#endif /* defined(__thiefTD__Enemy__) *///;
