//
//  FailedScene.h
//  cs526
//
//  Created by Darren Cheng on 15/3/27.
//
//

#ifndef __cs526__FailedScene__
#define __cs526__FailedScene__

#include <iostream>
#include "cocos2d.h"

class FailedScene : public cocos2d::Scene
{
public:
    
    virtual bool init();
    CREATE_FUNC(FailedScene);
    void menuBackCallback(Ref* pSender);
    
};

#endif /* defined(__cs526__FailedScene__) */
