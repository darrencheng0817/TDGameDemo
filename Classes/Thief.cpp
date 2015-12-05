//
//  Thief.cpp
//  cs526
//
//  Created by qiang on 15/2/13.
//
//

#include "Thief.h"

bool Thief::init()
{
    if (!Sprite::init())
    {
        return false;
    }
    setRunSpeed(15);
    setVaule(10);
    setEnemyType(ENEMY_GROUND);
    sprite = Sprite::createWithSpriteFrameName("myenemyRight1_1.png");
    this->addChild(sprite);
    animationRight = createAnimation("myenemyRight1", 4, 0.1f);
    AnimationCache::getInstance()->addAnimation(animationRight, "runright1");
    animationLeft = createAnimation("myenemyLeft1", 4, 0.1f);
    AnimationCache::getInstance()->addAnimation(animationLeft, "runleft1");
    animationExplode= createAnimation("myexplode1", 6, 0.15f);
    AnimationCache::getInstance()->addAnimation(animationExplode, "explode1");
    
    createAndSetHpBar();
    schedule(schedule_selector(EnemyBase::changeDirection), 0.4f);
    return true;
}

Thief* Thief::createThief(Vector<Node*> points, int hp)
{
    Thief *pRet = new Thief();
    if (pRet && pRet->init())
    {
        pRet->setPointsVector(points);
        pRet->setMaxHp(hp);
        pRet->setCurrHp(hp);
        pRet->runFllowPoint();
        
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

void Thief::changeDirection(float dt)
{
    auto curr = currPoint();
    if( curr == NULL )
    {
        return;
    }
    if(curr->getPositionX() > sprite->getPosition().x )
    {
        sprite->runAction( Animate::create(AnimationCache::getInstance()->getAnimation("runright1"))) ;
    }else{
        sprite->runAction( Animate::create(AnimationCache::getInstance()->getAnimation("runleft1"))  );
    }
}
void Thief::enemyExpload()
{
    hpBgSprite->setVisible(false);
    sprite->stopAllActions();
    unschedule(schedule_selector(Thief::changeDirection));
    sprite->setAnchorPoint(Point(0.5f, 0.25f));
    sprite->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("explode1"))
                                       ,CallFuncN::create(CC_CALLBACK_0(EnemyBase::removeFromParent, this))
                                       , NULL));
}


bool Pirate::init()
{
    if (!Sprite::init())
    {
        return false;
    }
    setRunSpeed(30);
    setVaule(20);
    setEnemyType(ENEMY_GROUND);
    sprite = Sprite::createWithSpriteFrameName("myenemyRight2_1.png");
    this->addChild(sprite);
    animationRight = createAnimation("myenemyRight2", 4, 0.1f);
    AnimationCache::getInstance()->addAnimation(animationRight, "runright2");
    animationLeft = createAnimation("myenemyLeft2", 4, 0.1f);
    AnimationCache::getInstance()->addAnimation(animationLeft, "runleft2");
    animationExplode= createAnimation("myexplode2", 6, 0.15f);
    AnimationCache::getInstance()->addAnimation(animationExplode, "explode2");
    
    createAndSetHpBar();
    schedule(schedule_selector(Pirate::changeDirection), 0.4f);
    return true;
}

Pirate* Pirate::createPirate(Vector<Node*> points, int hp)
{
    Pirate *pRet = new Pirate();
    if (pRet && pRet->init())
    {
        pRet->setPointsVector(points);
        pRet->setMaxHp(hp);
        pRet->setCurrHp(hp);
        pRet->runFllowPoint();
        
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
void Pirate::changeDirection(float dt)
{
    auto curr = currPoint();
    if( curr == NULL )
    {
        return;
    }
    if(curr->getPositionX() > sprite->getPosition().x )
    {
        sprite->runAction( Animate::create(AnimationCache::getInstance()->getAnimation("runright2"))) ;
    }else{
        sprite->runAction( Animate::create(AnimationCache::getInstance()->getAnimation("runleft2"))  );
    }
}
void Pirate::enemyExpload()
{
    hpBgSprite->setVisible(false);
    sprite->stopAllActions();
    unschedule(schedule_selector(Pirate::changeDirection));
    sprite->setAnchorPoint(Point(0.5f, 0.25f));
    sprite->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("explode2"))
                                       ,CallFuncN::create(CC_CALLBACK_0(EnemyBase::removeFromParent, this))
                                       , NULL));
}


bool Bandit::init()
{
    if (!Sprite::init())
    {
        return false;
    }
    setRunSpeed(60);
    setVaule(30);
    setEnemyType(ENEMY_SKY);
    sprite = Sprite::createWithSpriteFrameName("myenemyRight3_1.png");
    this->addChild(sprite);
    animationRight = createAnimation("myenemyRight3", 4, 0.1f);
    AnimationCache::getInstance()->addAnimation(animationRight, "runright3");
    animationLeft = createAnimation("myenemyLeft3", 4, 0.1f);
    AnimationCache::getInstance()->addAnimation(animationLeft, "runleft3");
    animationExplode= createAnimation("myexplode3", 6, 0.15f);
    AnimationCache::getInstance()->addAnimation(animationExplode, "explode3");
    
    createAndSetHpBar();
    schedule(schedule_selector(Bandit::changeDirection), 0.4f);
    return true;
}

Bandit* Bandit::createBandit(Vector<Node*> points, int hp)
{
    Bandit *pRet = new Bandit();
    if (pRet && pRet->init())
    {
        pRet->setPointsVector(points);
        pRet->setMaxHp(hp);
        pRet->setCurrHp(hp);
        pRet->runFllowPoint();
        
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
void Bandit::changeDirection(float dt)
{
    auto curr = currPoint();
    if( curr == NULL )
    {
        return;
    }
    if(curr->getPositionX() > sprite->getPosition().x )
    {
        sprite->runAction( Animate::create(AnimationCache::getInstance()->getAnimation("runright3"))) ;
    }else{
        sprite->runAction( Animate::create(AnimationCache::getInstance()->getAnimation("runleft3"))  );
    }
}
void Bandit::enemyExpload()
{
    hpBgSprite->setVisible(false);
    sprite->stopAllActions();
    unschedule(schedule_selector(Bandit::changeDirection));
    sprite->setAnchorPoint(Point(0.5f, 0.25f));
    sprite->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("explode3"))
                                       ,CallFuncN::create(CC_CALLBACK_0(EnemyBase::removeFromParent, this))
                                       , NULL));
}
