

#include "Bullet.h"


bool Bullet1::init()
{
	if (!BulletBase::init())
	{
		return false;
	}

	bulletSprite = Sprite::createWithSpriteFrameName("bullet2.png");
	addChild(bulletSprite);
	return true;
}

bool Bullet2::init()
{
	if (!BulletBase::init())
	{
		return false;
	}

	bulletSprite = Sprite::createWithSpriteFrameName("bullet3.png");
	addChild(bulletSprite);
	return true;



}


bool Bullet3::init()
{
	if (!BulletBase::init())
	{
		return false;
	}

	bulletSprite = Sprite::createWithSpriteFrameName("bullet4.png");
	addChild(bulletSprite);
	return true;
}

bool Bullet4::init()
{
	if (!BulletBase::init())
	{
		return false;
	}

	bulletSprite = Sprite::createWithSpriteFrameName("bullet5.png");
	addChild(bulletSprite);
	return true;
}