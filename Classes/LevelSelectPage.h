//
//  LevelSelectPage.h
//  cs526
//
//  Created by Darren Cheng on 15/3/27.
//
//

#ifndef __cs526__LevelSelectPage__
#define __cs526__LevelSelectPage__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class LevelSelectPage: public Node
{
public:
    
    bool initLevelPage(const std::string& bgName, int level);
    static LevelSelectPage* create(const std::string& bgName, int level);
    void menuStartCallback(Ref* pSender);
};
#endif /* defined(__cs526__LevelSelectPage__) */
