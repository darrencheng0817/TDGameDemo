//
//  LevelInfoScene.h
//  cs526
//
//  Created by Darren Cheng on 15/3/27.
//
//

#ifndef __cs526__LevelInfoScene__
#define __cs526__LevelInfoScene__

#include <iostream>
#include "cocos2d.h"
#include "LoadLevelInfo.h"
USING_NS_CC;

class LevelInfoScene : public Layer
{
public:
    
    LevelInfoScene();
    CREATE_FUNC(LevelInfoScene);
    static Scene * createScene();
    bool init();
    void addBackGround();
    
    void initLoadInfo(int bigLevel,int smallLevel);
    void menuBackCallback(Ref* pSender);
    void menuStartCallback(Ref* pSender);
    
private:
    LoadLevelinfo* info;
    std::string fileName;
};
#endif /* defined(__cs526__LevelInfoScene__) */
