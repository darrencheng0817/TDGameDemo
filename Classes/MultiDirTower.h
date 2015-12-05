//
//  MultiDirTower.h
//  cs526
//
//  Created by qiang on 15/2/13.
//
//

#ifndef __cs526__MultiDirTower__
#define __cs526__MultiDirTower__

#include "TowerBase.h"


class MultiDirTower:public TowerBase
{
public:
    
    virtual bool init();
    CREATE_FUNC(MultiDirTower);
    
    //void rotateAndShoot(float dt);
    void shoot(float dt);
    void removeBullet(Node* pSender);
    MyBullet* MultiDirTowerBullet();
    void createBullet6(float dt);
private:
    Sprite* tower;
    
};

#endif /* defined(__cs526__MultiDirTower__) */
