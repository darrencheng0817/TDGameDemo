//
//  MyBullet.cpp
//  cs526
//
//  Created by Darren Cheng on 15/4/5.
//
//

#include "MyBullet.h"

MyBullet::MyBullet()
:attacktype(0)
{
}

bool MyBullet::init()
{
    if (!Sprite::init())
    {
        return false;
    }
//    scheduleUpdate();
    return true;
}
void MyBullet::createbullet(const std::string &spriteFrameName){
    sprite=Sprite::createWithSpriteFrameName(spriteFrameName);
}


