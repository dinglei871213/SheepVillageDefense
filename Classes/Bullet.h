#ifndef __SheepVillageDefense__Bullet1__
#define __SheepVillageDefense__Bullet1__

#include <iostream>
#include "BulletBase.h"
#include "cocos2d.h"

USING_NS_CC;
//�ӵ�1��
class Bullet1 : public BulletBase
{
public:
	bool init();

	CREATE_FUNC(Bullet1);

};


//�ӵ�2��
class Bullet2 : public BulletBase
{
public:
	 bool init() ;

	 CREATE_FUNC(Bullet2);

};

//�ӵ�3��
class Bullet3 : public BulletBase
{
public:
	 bool init() ;

	 CREATE_FUNC(Bullet3);

};

//�ӵ�4��
class Bullet4 : public BulletBase
{
public:
	bool init();

	CREATE_FUNC(Bullet4);

};


#endif /* defined(__SheepVillageDefense__Bullet1__) */
