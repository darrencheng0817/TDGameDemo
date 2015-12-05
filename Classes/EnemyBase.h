//
//  Enemy.h
//  cs526
//
//  Created by Darren Cheng on 15/2/11.
//
//

#ifndef __cs526__Enemy__
#define __cs526__Enemy__


#include <iostream>
#include "cocos2d.h"
#include "config.h"
USING_NS_CC;

class EnemyBase : public Sprite
{
public:
    EnemyBase();
    ~EnemyBase();
    virtual bool init() override;
    CREATE_FUNC(EnemyBase);
    
    Animation* createAnimation(std::string prefixName, int framesNum, float delay);
    virtual void changeDirection(float dt){};
    virtual void enemyExpload(){};
    Node* currPoint();
    Node* nextPoint();
    void runFllowPoint();
    void setPointsVector(Vector<Node*> points);
    void createAndSetHpBar();
private:
    Vector<Node*> pointsVector;
    
protected:
    int pointCounter;
    Animation *animationRight;
    Animation *animationLeft;
    Animation *animationExplode;
    CC_SYNTHESIZE(float, runSpeed, RunSpeed);
    CC_SYNTHESIZE(float, maxHp, MaxHp);
    CC_SYNTHESIZE(float, vaule, Vaule);
    CC_SYNTHESIZE(float, currHp, CurrHp);
    CC_SYNTHESIZE(int, enemytype, EnemyType);
    CC_SYNTHESIZE(int, enemystatus, EnemyStatus);
    CC_SYNTHESIZE(float, hpPercentage, HpPercentage);
    CC_SYNTHESIZE(ProgressTimer*, hpBar, HpBar);
    CC_SYNTHESIZE(bool, enemySuccessful, EnemySuccessful);
    Sprite* sprite;
    Sprite* hpBgSprite;
};


#endif /* defined(__cs526__Enemy__) */
