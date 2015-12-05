//
//  MultiDirTower.cpp
//  cs526
//
//  Created by qiang on 15/2/13.
//
//

#include "MultiDirTower.h"
#include "GameManager.h"
#include <algorithm>

bool MultiDirTower::init()
{
    if (!TowerBase::init())
    {
        return false;
    }
    
    setScope(60);
    setTowerValue(500);
    setLethality(1);
    setRate(1);
    setLevel(1);
    setRole(3);
    setAttackType(ENEMY_GROUND|ENEMY_DESPEED);
    tower= Sprite::createWithSpriteFrameName("multiDirTower.png");
    this->addChild(tower);
    
    this->schedule(schedule_selector(MultiDirTower::createBullet6), 0.8f);
    return true;
}


MyBullet* MultiDirTower::MultiDirTowerBullet()
{
    auto bullet = MyBullet::create();
    bullet->sprite= Sprite::createWithSpriteFrameName("icebullet.png");
    bullet->setPosition(0, tower->getContentSize().height /4 );
    bullet->setAttackType(this->getAttackType());
    bullet->setAttackValue(this->getLethality());
    this->addChild(bullet);
    bullet->addChild(bullet->sprite);
    return bullet;
}

void MultiDirTower::createBullet6(float dt)
{
    GameManager *instance = GameManager::getInstance();
    auto bulletVector = instance->bulletVector;
    int dirTotal = 10;
    this->checkNearestEnemy();
    if(nearestEnemy != NULL && nearestEnemy->getCurrHp() > 0 )
    {
        for(int i = 0; i < dirTotal; i++)
        {
            auto currBullet = MultiDirTowerBullet();
            instance->bulletVector.pushBack(currBullet);
            
            auto moveDuration = getRate();
            
            Point shootVector;
            shootVector.x = 1;
            shootVector.y = tan( i * 2 * M_PI / dirTotal );
            Point normalizedShootVector;
            if( i >= dirTotal / 2 )
            {
                normalizedShootVector = shootVector;
                normalizedShootVector.normalize();
            }else{
                normalizedShootVector = -shootVector;
                normalizedShootVector.normalize();
            }
            auto farthestDistance = Director::getInstance()->getWinSize().width;
            Point overshotVector = normalizedShootVector * farthestDistance;
            Point offscreenPoint = (currBullet->getPosition() - overshotVector);
            
            currBullet->runAction(Sequence::create(MoveTo::create(moveDuration, offscreenPoint),
                                                   CallFuncN::create(CC_CALLBACK_1(MultiDirTower::removeBullet, this)),
                                                   NULL));
            currBullet = NULL;
        }
    }
}


void MultiDirTower::removeBullet(Node* pSender)
{
    GameManager *instance = GameManager::getInstance();
    auto bulletVector = instance->bulletVector;
    
    MyBullet *sprite = (MyBullet *)pSender;
    instance->bulletVector.eraseObject(sprite);
    sprite->removeFromParent();
}