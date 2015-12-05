//
//  GameManager.h
//  cs526
//
//  Created by qiang on 15/2/13.
//
//

#ifndef cs526_GameManager_h
#define cs526_GameManager_h

#include <iostream>
#include "cocos2d.h"
#include "EnemyBase.h"
#include "TowerBase.h"
#include "GroupEnemy.h"


USING_NS_CC;

class GameManager
{
public:
    
    Vector<EnemyBase*> enemyVector;
    Vector<MyBullet*> bulletVector;
    Vector<TowerBase*> towerVector;
    Vector<GroupEnemy*> groupVector;
    
    CC_SYNTHESIZE(int, money, Money);
    CC_SYNTHESIZE(int, groupNum, GroupNum);
    CC_SYNTHESIZE(std::string, curMapName, CurMapName);
    CC_SYNTHESIZE(std::string, currLevelFile, CurrLevelFile);
    CC_SYNTHESIZE(std::string, nextLevelFile, NextLevelFile);
    CC_SYNTHESIZE(bool, isFinishedAddGroup, IsFinishedAddGroup);
    CC_SYNTHESIZE(std::string, curBgName, CurBgName);
    
    bool init();
    void clear();
    
    static GameManager* getInstance();
    
private:
    static GameManager * instance;
};

#endif
