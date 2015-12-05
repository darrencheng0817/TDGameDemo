//
//  AttackTower.cpp
//  cs526
//
//  Created by qiang on 15/2/13.
//
//

#include "AttackTower.h"
#include "GameManager.h"

bool AttackTower::init()
{
    if (!TowerBase::init())
    {
        return false;
    }
    
    setScope(90);
    setTowerValue(150);
    setLethality(1.5);
    setRate(1);
    setLevel(1);
    setRole(2);
    setAttackType(ENEMY_GROUND);
    tower= Sprite::createWithSpriteFrameName("attackTower.png");
    this->addChild(tower);
    
    schedule(schedule_selector(AttackTower::shoot), 0.8f);
    return true;
}


MyBullet* AttackTower::AttackTowerBullet()
{
    auto bullet = MyBullet::create();
    bullet->sprite= Sprite::createWithSpriteFrameName("bullet1.png");
    bullet->setPosition(0, tower->getContentSize().height /4 );
    //bullet->setTag(DECELERATE_BULLET);
    bullet->setAttackType(this->getAttackType());
    bullet->setAttackValue(this->getLethality());
    bullet->addChild(bullet->sprite);
    this->addChild(bullet);
    
    return bullet;
}

void AttackTower::shoot(float dt)
{
    GameManager *instance = GameManager::getInstance();
    auto bulletVector = instance->bulletVector;
    
    checkNearestEnemy();
    if(nearestEnemy!=NULL && nearestEnemy->getCurrHp() > 0 )
    {
        auto currBullet = AttackTowerBullet();
        instance->bulletVector.pushBack(currBullet);
        
        auto moveDuration = getRate();
        Point shootVector = nearestEnemy->sprite->getPosition() - this->getPosition();
        Point normalizedShootVector = -shootVector;
        normalizedShootVector.normalize();
        
        auto farthestDistance = Director::getInstance()->getWinSize().width;
        Point overshotVector = normalizedShootVector * farthestDistance;
        Point offscreenPoint = (currBullet->getPosition() - overshotVector);
        
        currBullet->runAction(Sequence::create(MoveTo::create(moveDuration, offscreenPoint),
                                               CallFuncN::create(CC_CALLBACK_1(AttackTower::removeBullet, this)),
                                               NULL));
        currBullet = NULL;
    }
}

void AttackTower::removeBullet(Node* pSender)
{
    GameManager *instance = GameManager::getInstance();
    
    auto bulletVector = instance->bulletVector;
    
    MyBullet *sprite = (MyBullet *)pSender;
    instance->bulletVector.eraseObject(sprite);
    sprite->removeFromParent();
}

