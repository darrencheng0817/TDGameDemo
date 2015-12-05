//
//  LevelSelectPage.cpp
//  cs526
//
//  Created by Darren Cheng on 15/3/27.
//
//
#include "LevelSelectPage.h"
#include "LevelInfoScene.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

#define LEVEL_ROW (3)
#define LEVEL_COL (2)

LevelSelectPage* LevelSelectPage::create(const std::string& bgName, int level)
{
    LevelSelectPage *pRet = new LevelSelectPage();
    if (pRet && pRet->initLevelPage(bgName, level))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool LevelSelectPage::initLevelPage(const std::string& bgName, int level)
{
    if (!Node::init())
    {
        return false;
    }
    auto size = Director::getInstance()->getWinSize();
    auto sprite =Sprite::create(bgName);
    sprite->setPosition(Point(size.width / 2,size.height / 2));
    addChild(sprite,-2);
    
    Vector<MenuItem*> menuItemVector;
    auto buttonSize = Sprite::create("card_1.png")->getContentSize();
    auto gap = buttonSize.width / 4;
    auto startWidth =( size.width -  LEVEL_ROW* buttonSize.width - (LEVEL_ROW - 1)*gap ) /2 ;
    auto startHeight = ( size.height + (LEVEL_COL - 1) * gap + buttonSize.height * LEVEL_COL ) /2 - buttonSize.height;
    for ( int row = 0; row < LEVEL_COL; row++ )
    {
        auto height = startHeight - ( buttonSize.height + gap ) * row ;
        for ( int col = 0; col < LEVEL_ROW; col++)
        {
            auto width = startWidth + ( buttonSize.width + gap ) * col ;
            auto item = MenuItemImage::create(
                                              "card_1.png",
                                              "card_2.png",
                                              "card_3.png",
                                              CC_CALLBACK_1(LevelSelectPage::menuStartCallback, this));
            item->setAnchorPoint(Point(0 ,0));
            item->setPosition(Point(width, height));
            item->setTag(row * LEVEL_ROW + col + level * LEVEL_ROW * LEVEL_COL);
            menuItemVector.pushBack( item );
            auto levelNum = UserDefault::getInstance()->getIntegerForKey("levelNum");
            
            if(levelNum < row * LEVEL_ROW + col + level * LEVEL_ROW * LEVEL_COL)
            {
                item->setEnabled(false);
            }
        }
    }
    auto levelMenu = Menu::createWithArray(menuItemVector);
    levelMenu->setPosition(Point::ZERO);
    this->addChild(levelMenu, -1);
    
    return true;
}

void LevelSelectPage::menuStartCallback(Ref* pSender)
{
    auto button = (Sprite *)pSender;
    SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/button.wav").c_str(), false);
    
    char buffer[20] = { 0 };
    sprintf(buffer, "levelInfo_%d.plist", button->getTag());
    std::string strName =  buffer;
    UserDefault::getInstance()->setStringForKey("nextLevelFile", strName);
    
    Scene *scene = Scene::create();
    auto layer = LevelInfoScene::create();
    scene->addChild(layer);
    auto sence = TransitionFade::create(0.5, scene);
    
    Director::getInstance()->replaceScene(sence);
}
