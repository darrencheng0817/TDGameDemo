//
//  LevelScene.h
//  cs526
//
//  Created by Darren Cheng on 15/3/27.
//
//

#ifndef __cs526__LevelScene__
#define __cs526__LevelScene__

#include <iostream>
#include "cocos2d.h"

class LevelScene : public cocos2d::Scene
{
public:
    
    virtual bool init();
    CREATE_FUNC(LevelScene);
    void menuCloseCallback(Ref* pSender);
    static LevelScene *getInstance();
    
private:
    static LevelScene *instance;
};
#endif /* defined(__cs526__LevelScene__) */
