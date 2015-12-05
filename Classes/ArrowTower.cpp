//
//  ArrowTower.cpp
//  cs526
//
//  Created by qiang on 15/2/13.
//
//

#include "ArrowTower.h"
#include "GameManager.h"

bool ArrowTower::init()
{
    if (!TowerBase::init())
    {
        return false;
    }
    
    setScope(90);
    setLethality(1);
    setTowerValue(200);
    setRate(1);
    setLevel(1);
    setRole(1);
    setAttackType(ENEMY_SKY | ENEMY_GROUND);
    auto baseplate = Sprite::createWithSpriteFrameName("baseplate.png");
    addChild(baseplate);
    
    rotateArrow = Sprite::createWithSpriteFrameName("arrow.png");
    rotateArrow->setPosition(0, baseplate->getContentSize().height /4  );
    addChild(rotateArrow);
    
    schedule(schedule_selector(ArrowTower::rotateAndShoot), 0.8f);
    return true;
}


MyBullet* ArrowTower::ArrowTowerBullet()
{
    auto bullet = MyBullet::create();
    bullet->sprite= Sprite::createWithSpriteFrameName("arrowBullet.png");
    bullet->setPosition(rotateArrow->getPosition());
    bullet->setRotation(rotateArrow->getRotation());
    bullet->setAttackType(this->getAttackType());
    bullet->setAttackValue(this->getLethality());
    bullet->addChild(bullet->sprite);
    addChild(bullet);
    return bullet;
}

void ArrowTower::rotateAndShoot(float dt)
{
    checkNearestEnemy();
    if (nearestEnemy != NULL)
    {
        auto rotateVector = nearestEnemy->sprite->getPosition() - this->getPosition();
        auto rotateRadians = rotateVector.getAngle();
        auto rotateDegrees = CC_RADIANS_TO_DEGREES(-1 * rotateRadians);
        
        auto speed = 0.5 / M_PI;
        auto rotateDuration = fabs(rotateRadians * speed);
        rotateArrow->runAction( Sequence::create(RotateTo::create(rotateDuration, rotateDegrees),
                                                 CallFunc::create(CC_CALLBACK_0(ArrowTower::shoot, this)),
                                                 NULL));
    }
}

void ArrowTower::shoot()
{
    GameManager *instance = GameManager::getInstance();
    auto bulletVector = instance->bulletVector;
    
    if(nearestEnemy!=NULL && nearestEnemy->getCurrHp() > 0 )
    {
        auto currBullet = ArrowTowerBullet();
        instance->bulletVector.pushBack(currBullet);
        
        auto moveDuration = getRate();
        Point shootVector = nearestEnemy->sprite->getPosition() - this->getPosition();
        Point normalizedShootVector = -shootVector;
        normalizedShootVector.normalize();
        
        auto farthestDistance = Director::getInstance()->getWinSize().width;
        Point overshotVector = normalizedShootVector * farthestDistance;
        Point offscreenPoint = (rotateArrow->getPosition() - overshotVector);
        
        currBullet->runAction(Sequence::create(MoveTo::create(moveDuration, offscreenPoint),
                                               CallFuncN::create(CC_CALLBACK_1(ArrowTower::removeBullet, this)),
                                               NULL));
        currBullet = NULL;
    }
}

void ArrowTower::removeBullet(Node* pSender)
{
    GameManager *instance = GameManager::getInstance();
    
    auto bulletVector = instance->bulletVector;
    
    MyBullet *sprite = (MyBullet *)pSender;
    instance->bulletVector.eraseObject(sprite);
    sprite->removeFromParent();
}

