//
//  DeleteOrUpgradePanleLayer.cpp
//  cs526
//
//  Created by qiang on 15/4/1.
//
//

#include "DeleteOrUpgradePanleLayer.h"

bool DeleteOrUpgradePanleLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    setRole(0);
    
    auto sprite = Sprite::createWithSpriteFrameName("towerPos.png");
    sprite->setPosition(Point(0, 0));
    this->addChild(sprite);
    
    sprite1 = Sprite::create("sell.png");
    sprite1->setAnchorPoint( Point(0.5f, 0));
    sprite1->setPosition(Point(-sprite->getContentSize().width, sprite->getContentSize().height/2));
    this->addChild(sprite1);
    
    sprite2 = Sprite::create("upload.png");
    sprite2->setAnchorPoint( Point(0.5f, 0));
    sprite2->setPosition(Point(0, sprite->getContentSize().height/2));
    this->addChild(sprite2);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(DeleteOrUpgradePanleLayer::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(DeleteOrUpgradePanleLayer::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, sprite1);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), sprite2);
    return true;
}


bool DeleteOrUpgradePanleLayer::onTouchBegan(Touch *touch, Event *event)
{
    auto target = static_cast<Sprite*>(event->getCurrentTarget());
    
    Point locationInNode = target->convertTouchToNodeSpace(touch);
    Size size = target->getContentSize();
    Rect rect = Rect(0, 0, size.width, size.height);
    
    if (rect.containsPoint(locationInNode))
    {
        target->setOpacity(180);
        return true;
    }
    return false;
}


void DeleteOrUpgradePanleLayer::onTouchEnded(Touch* touch, Event* event)
{
    auto target = static_cast<Sprite*>(event->getCurrentTarget());
    if (target == sprite1)
    {
        role = 1;
    }
    else if(target == sprite2)
    {
        role = 2;
    }
    else{
        role = 0;
    }
}