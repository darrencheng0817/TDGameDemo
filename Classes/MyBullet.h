//
//  MyBullet.h
//  cs526
//
//  Created by Darren Cheng on 15/4/5.
//
//

#ifndef __cs526__MyBullet__
#define __cs526__MyBullet__
#include <iostream>
#include "cocos2d.h"
#include "config.h"
#include "TowerBase.h"


USING_NS_CC;

class MyBullet: public Sprite
{
public:
    MyBullet();
    
    virtual bool init();
    CREATE_FUNC(MyBullet);
    void createbullet(const std::string &spriteFrameName);
    CC_SYNTHESIZE(int, attacktype, AttackType);
    CC_SYNTHESIZE(int, attackValue, AttackValue);
    Sprite* sprite;
};
#endif /* defined(__cs526__MyBullet__) */
