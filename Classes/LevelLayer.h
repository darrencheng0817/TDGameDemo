//
//  LevelLayer.h
//  cs526
//
//  Created by Darren Cheng on 15/3/27.
//
//

#ifndef __cs526__LevelLayer__
#define __cs526__LevelLayer__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

#define SHORTEST_SLIDE_LENGTH (20)

class LevelLayer: public Layer
{
private:
    
    int pageNode;
    int curPageNode;
    Point touchDownPoint;
    Point touchUpPoint;
    Point touchCurPoint;
    float WINDOW_WIDTH;
    float WINDOW_HEIGHT;
    void goToCurrNode();
    
public:
    LevelLayer();
    ~LevelLayer();
    
    virtual bool init();
    static cocos2d::Scene* createScene();
    CREATE_FUNC(LevelLayer);
    
    void menuCloseCallback(Ref* pSender);
    bool onTouchBegan(Touch *touch, Event  *event);
    void onTouchMoved(Touch *touch, Event  *event);
    void onTouchEnded(Touch *touch, Event  *event);
    void addNode(Node *level);
};
#endif /* defined(__cs526__LevelLayer__) */
