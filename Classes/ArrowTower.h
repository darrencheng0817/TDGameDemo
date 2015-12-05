//
//  ArrowTower.h
//  cs526
//
//  Created by qiang on 15/2/13.
//
//

#ifndef __cs526__ArrowTower__
#define __cs526__ArrowTower__

#include "TowerBase.h"


class ArrowTower:public TowerBase
{
public:
    
    virtual bool init() ;
    CREATE_FUNC(ArrowTower);
    
    void rotateAndShoot(float dt);
    void shoot();
    void removeBullet(Node* pSender);
    MyBullet* ArrowTowerBullet();
    
private:
    Sprite* rotateArrow;
    
};

#endif /* defined(__cs526__ArrowTower__) */
