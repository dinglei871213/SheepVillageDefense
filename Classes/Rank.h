#include<string>
#include<iostream>
#include<mysql.h>
#include<stdio.h>
#include "User.h"
#include "cocos2d.h"
#pragma  comment(lib,"libmysql.lib")
USING_NS_CC;
class Rank{
public:
	Rank(){};
	~Rank(){};
	void updateRank(User user);
	Vector<User*> getRecord();	//��ü�¼�����б�
	MYSQL* m_sqlCon;				//����Դָ��

};