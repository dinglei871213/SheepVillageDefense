

#ifndef __SheepVillageDefense__Enemy__
#define __SheepVillageDefense__Enemy__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
//敌人基类
class EnemyBase : public Sprite
{
public:
    EnemyBase();
    ~EnemyBase();
    virtual bool init() override;
    CREATE_FUNC(EnemyBase);
    
    static Animation* createAnimation(std::string prefixName, int framesNum, float delay);//创建敌人动画	
    virtual void changeDirection(float dt){};//改变方向
    virtual void enemyExpload(){};//敌人死亡爆炸
    Node* currPoint();//获得敌人当前所处的路径点
    Node* nextPoint();//敌人下一个移动点
    void runFllowPoint();//让敌人前进
	bool changeRote;//是否被风吹到
	bool changeFinish;//是否被风吹到了回到起点
	void changeFinished();//检测是否已经回到起点
	void createAndSetHpBar();//建立并设置血条

	void enemyReduceHp(int reduceHp);//减血
	void enemySlow(int slowSpeed, int slowSpeedTime);//减速
	void enemyPoison(int poisonHpBullet, int poisonHpTimeBullet);//中毒
	void enemyPoison(float dt);//中毒
	void resumeSpeed(float dt);//减速恢复
private:
	CC_SYNTHESIZE(Vector<Node*>, pointsVector, PointsVector);//敌人进攻的路线点集合
	CC_SYNTHESIZE(int, pointCounter, PointCounter);//所处路径点编号
    
protected:
    Animation *animationRight;//右侧运动动画
    Animation *animationLeft;//左侧运动动画
	Animation *animationFront;//前侧运动动画
	Animation *animationBack;//后侧运动动画
    Animation *animationExplode;//死亡动画
    CC_SYNTHESIZE(float, runSpeed, RunSpeed);//移动速度
    CC_SYNTHESIZE(float, maxHp, MaxHp);//最大血量
    CC_SYNTHESIZE(float, vaule, Vaule);//价钱
    CC_SYNTHESIZE(float, currHp, CurrHp);//当前血量
	CC_SYNTHESIZE(float, hpPercentage, HpPercentage);//血量百分比
    CC_SYNTHESIZE_READONLY(ProgressTimer*, hpBar, HpBar);//血量条
    CC_SYNTHESIZE(bool, enemySuccessful, EnemySuccessful);//敌人成功到达
	Sprite* sprite;//敌人父精灵
    Sprite* hpBgSprite;//血量条精灵


	int poisonHp;//中毒减血量
	int poisonHpTime;//中毒时间

	int preSpeed;//减速前速度
	//Node* node;
};



#endif /* defined(__thiefTD__Enemy__) *///;
