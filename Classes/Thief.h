//
//  Thief.h
//  cs526
//
//  Created by qiang on 15/2/13.
//
//

#ifndef __cs526__Thief__
#define __cs526__Thief__

#include <iostream>
#include "EnemyBase.h"
#include "cocos2d.h"

USING_NS_CC;

class Thief : public EnemyBase
{
public:
    virtual bool init() override;
    
    static Thief* createThief(Vector<Node*> points, int hp);
    
    void changeDirection(float dt);
    void enemyExpload();
    
};

class Pirate : public EnemyBase
{
public:
    virtual bool init() override;
    
    static Pirate* createPirate(Vector<Node*> points, int hp);
    void changeDirection(float dt);
    void enemyExpload();
};

class Bandit : public EnemyBase
{
public:
    virtual bool init() override;
    
    static Bandit* createBandit(Vector<Node*> points, int hp);
    void changeDirection(float dt);
    void enemyExpload();
};



#endif /* defined(__cs526__Thief__) */
