//
//  AttackTower.h
//  cs526
//
//  Created by qiang on 15/2/13.
//
//

#ifndef __cs526__AttackTower__
#define __cs526__AttackTower__

#include "TowerBase.h"


class AttackTower:public TowerBase
{
public:
    
    virtual bool init() ;
    CREATE_FUNC(AttackTower);
    
    void shoot(float dt);
    void removeBullet(Node* pSender);
    MyBullet* AttackTowerBullet();
    
private:
    Sprite* tower;
    
};

#endif /* defined(__cs526__AttackTower__) */
