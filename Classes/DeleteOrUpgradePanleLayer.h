//
//  DeleteOrUpgradePanleLayer.h
//  cs526
//
//  Created by qiang on 15/4/1.
//
//

#ifndef __cs526__DeleteOrUpgradePanleLayer__
#define __cs526__DeleteOrUpgradePanleLayer__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class DeleteOrUpgradePanleLayer: public Layer
{
public:
    virtual bool init() override;
    CREATE_FUNC(DeleteOrUpgradePanleLayer);
    
    bool onTouchBegan(Touch *touch, Event *event);
    void onTouchEnded(Touch* touch, Event* event);
    
    CC_SYNTHESIZE(int, role, Role);
    
private:
    
    Sprite* sprite1;
    Sprite* sprite2;
};

#endif /* defined(__cs526__DeleteOrUpgradePanleLayer__) */