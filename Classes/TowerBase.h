//
//  TowerBase.h
//  cs526
//
//  Created by Darren Cheng on 15/2/11.
//
//

#ifndef __cs526__TowerBase__
#define __cs526__TowerBase__

#include <iostream>
#include "cocos2d.h"
#include "config.h"
#include "EnemyBase.h"
#include "MyBullet.h"

USING_NS_CC;

class TowerBase: public Sprite
{
public:
    TowerBase();
    
    virtual bool init();
    CREATE_FUNC(TowerBase);
    
    void checkNearestEnemy();
    CC_SYNTHESIZE(int, attacktype, AttackType);
    CC_SYNTHESIZE(int, scope, Scope);  // 塔的视线范围
    CC_SYNTHESIZE(int, lethality, Lethality);   // 杀伤力
    CC_SYNTHESIZE(int, towerValue, TowerValue);  //
    CC_SYNTHESIZE(float, rate, Rate);  //
    
    
    CC_SYNTHESIZE(float, level, Level);  //
    CC_SYNTHESIZE(float, role, Role);  //
protected:
    EnemyBase* nearestEnemy;    // 塔子视野内最近的敌人
};
#endif /* defined(__cs526__TowerBase__) */
