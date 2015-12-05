//
//  SuccessfulScene.h
//  cs526
//
//  Created by Darren Cheng on 15/3/27.
//
//

#ifndef __cs526__SuccessfulScene__
#define __cs526__SuccessfulScene__

#include <iostream>
#include "cocos2d.h"

class SuccessfulScene : public cocos2d::Scene
{
public:
    
    virtual bool init();
    
    void menuNextCallback(Ref* pSender);
    void menuCloseCallback(Ref* pSender);
    CREATE_FUNC(SuccessfulScene);
private:
    
};
#endif /* defined(__cs526__SuccessfulScene__) */
