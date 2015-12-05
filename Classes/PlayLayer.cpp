//
//  PlayLayer.cpp
//  cs526
//
//  Created by Darren Cheng on 15/2/11.
//
//

#define MAP_WIDTH (16)
#define MAP_HEIGHT (9)

#include "PlayLayer.h"
#include "GameManager.h"
#include "SuccessfulScene.h"
#include "FailedScene.h"
#include "LevelScene.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;
using namespace CocosDenshion;

PlayLayer::PlayLayer()
:isTouchEnable(false)
,spriteSheet(NULL)
,map(NULL)
,objects(NULL)
,pointsVector(NULL)
,chooseTowerpanel(NULL)
,DeleteOrUpgradePanle(NULL)
,towerMatrix(NULL)
,groupCounter(0)
,money(0)
,playHpBar(NULL)
,playHpPercentage(100)
,moneyLabel(NULL)
,groupLabel(NULL)
,groupTotalLabel(NULL)
,isSuccessful(false)
{
}

PlayLayer::~PlayLayer()
{
    if (towerMatrix) {
        free(towerMatrix);
    }
    pointsVector.clear();
}

Scene *PlayLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = PlayLayer::create();
    scene->addChild(layer);
    return scene;
}

bool PlayLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    Size winSize = Director::getInstance()->getWinSize();
    instance = GameManager::getInstance();
    
	auto gameBg = Sprite::create(instance->getCurBgName());
	gameBg->setPosition (Point(winSize.width / 2 ,winSize.height / 2));
	addChild(gameBg, -20);
    
    map = TMXTiledMap::create(instance->getCurMapName());
    bgLayer = map->getLayer("bg");
    bgLayer->setAnchorPoint(Point(0.5f, 0.5f));
    bgLayer->setPosition(Point(winSize.width / 2 ,winSize.height / 2));
    objects = map->getObjectGroup("obj");
    this->addChild(map, -10);
    
    initToolLayer();
    
    offX = ( map->getContentSize().width - winSize.width )/ 2;
    initPointsVector(offX);
    schedule(schedule_selector(PlayLayer::logic), 2.0f);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(PlayLayer::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    scheduleUpdate();
    
    int arraySize = sizeof(TowerBase *) * MAP_WIDTH * MAP_HEIGHT;
    towerMatrix = (TowerBase **)malloc(arraySize);
    memset((void*)towerMatrix, 0, arraySize);
    
    for (int row = 0; row < MAP_HEIGHT; row++) {
        for (int col = 0; col < MAP_WIDTH; col++) {
            towerMatrix[row * MAP_WIDTH + col] = NULL;
        }
    }
    return true;
}

void PlayLayer::initPointsVector(float offX)
{
    Node *runOfPoint = NULL;
    int count = 0;
    ValueMap point;
    point = objects->getObject(std::to_string(count));
    while (point.begin()!= point.end())
    {
        float x = point.at("x").asFloat();
        float y = point.at("y").asFloat();
        runOfPoint = Node::create();
        runOfPoint->setPosition(Point(x - offX, y ));
        this->pointsVector.pushBack(runOfPoint);
        count++;
        point = objects->getObject( std::to_string(count));
    }
    runOfPoint = NULL;
}

void PlayLayer::initToolLayer()
{
    auto size = Director::getInstance()->getWinSize();
    toolLayer = Layer::create();
    addChild(toolLayer);
    
    auto spritetool = Sprite::createWithSpriteFrameName("toolbg.png");
    spritetool->setAnchorPoint(Point(0.5f, 1));
    spritetool->setPosition (Point(size.width / 2, size.height));
    toolLayer->addChild(spritetool,0,10);
    
	//
	money = instance->getMoney();
	moneyLabel = Label::createWithBMFont("bitmapFontChinese.fnt", " ");
    moneyLabel->setPosition(Point(spritetool->getContentSize().width / 8, spritetool->getContentSize().height / 2));
    moneyLabel->setAnchorPoint(Point(0, 0.5f));
    auto moneyText = std::to_string(money);
    moneyLabel->setString(moneyText);
    spritetool->addChild(moneyLabel);
    
    //
    playHpBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("playhp.png"));
    playHpBar->setType(ProgressTimer::Type::BAR);
    playHpBar->setMidpoint(Point(0, 0.4f));
    playHpBar->setBarChangeRate(Point(1, 0));
    playHpBar->setPercentage(playHpPercentage);
    playHpBar->setPosition(Point(spritetool->getContentSize().width / 5 *4  , spritetool->getContentSize().height / 2));
    spritetool->addChild(playHpBar, 0,11); //addChild(playHpBar);
    
    auto star = Sprite::createWithSpriteFrameName("playstar.png");
    star->setPosition(Point(spritetool->getContentSize().width / 5 *4 , spritetool->getContentSize().height / 2));
	spritetool->addChild(star);
	
	//
	int groupTotal = instance->getGroupNum();
	groupLabel = Label::createWithBMFont("bitmapFontChinese.fnt", " ");
    groupLabel->setPosition(Point(spritetool->getContentSize().width / 32 * 15, spritetool->getContentSize().height / 2 ));
    groupLabel->setAnchorPoint(Point(0.5f , 0.5f));
    auto groupInfoText = std::to_string(groupCounter + 1);
    groupLabel->setString(groupInfoText);
    spritetool->addChild(groupLabel);
    
	groupTotalLabel = Label::createWithBMFont("bitmapFontChinese.fnt", " ");
    groupTotalLabel->setPosition(Point(spritetool->getContentSize().width / 32 * 17 , spritetool->getContentSize().height / 2 ));
    groupTotalLabel->setAnchorPoint(Point(0.5f , 0.5f));
    auto groupTotalText = std::to_string(groupTotal);
    groupTotalLabel->setString(groupTotalText);
    spritetool->addChild(groupTotalLabel);
    
    // back
	Sprite *backItem1 = CCSprite::createWithSpriteFrameName("playbutton1.png");
	Sprite *backItem2 = CCSprite::createWithSpriteFrameName("playbutton2.png");
	MenuItemSprite *pPauseItem = MenuItemSprite::create(backItem1, backItem2, CC_CALLBACK_1(PlayLayer::menuBackCallback, this));
	pPauseItem->setPosition(Point(spritetool->getContentSize().width - backItem1->getContentSize().width/2, spritetool->getContentSize().height / 2));
	pPauseItem->setAnchorPoint(Point(0, 0.4f));
	Menu* pMenu = Menu::create(pPauseItem, NULL);
	pMenu->setPosition(Point::ZERO);
	spritetool->addChild(pMenu);
}

void PlayLayer::menuBackCallback(Ref* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/button.wav").c_str(), false);
    instance->clear();
	Director::getInstance()->replaceScene(CCTransitionFade::create(0.5, LevelScene::create()));
}

GroupEnemy* PlayLayer::currentGroup()
{
    GroupEnemy* groupEnemy;
    if(!instance->groupVector.empty() )
    {
        groupEnemy = (GroupEnemy*)instance->groupVector.at(groupCounter);
    }
    else{
        groupEnemy =NULL;
    }
    return groupEnemy;
}

GroupEnemy* PlayLayer::nextGroup()
{
    if(instance->groupVector.empty())
    {
        return NULL;
    }
    
    if (groupCounter < instance->getGroupNum() - 1)
    {
        groupCounter++;
    }
    else{
        isSuccessful = true;
    }
    GroupEnemy* groupEnemy = (GroupEnemy*)instance->groupVector.at(groupCounter);
    return groupEnemy;
    
}

void PlayLayer::addEnemy()
{
    GameManager *instance = GameManager::getInstance();
    
    GroupEnemy* groupEnemy = this->currentGroup();
    if(groupEnemy == NULL)
    {
        return;
    }
    auto restEnemyNum = groupEnemy->getEnemyTotal();
    if( restEnemyNum <= 0){
        groupEnemy->setIsFinishedAddGroup(true);
        return;
    }
    
    restEnemyNum--;
    groupEnemy->setEnemyTotal(restEnemyNum);
    
	EnemyBase* enemy = NULL;
	
	if(groupEnemy->getType1Total() > 0){
        SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/comeout.wav").c_str(), false);
		enemy = Thief::createThief(pointsVector, groupEnemy->getType1Hp());
		groupEnemy->setType1Total(groupEnemy->getType1Total() - 1);
	}
	else if(groupEnemy->getType2Total() > 0){
        SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/comeout.wav").c_str(), false);
		enemy = Pirate::createPirate(pointsVector, groupEnemy->getType2Hp());
		groupEnemy->setType2Total(groupEnemy->getType2Total() - 1);
	}
	else if(groupEnemy->getType3Total() > 0){
		enemy = Bandit::createBandit(pointsVector, groupEnemy->getType3Hp());
        SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/comeout.wav").c_str(), false);
		groupEnemy->setType3Total(groupEnemy->getType3Total() - 1);
	}
    
    this->addChild(enemy, 10);
    instance->enemyVector.pushBack(enemy);
}

void PlayLayer::logic(float dt)
{
    GroupEnemy* groupEnemy = this->currentGroup();
    
    if(groupEnemy == NULL)
    {
        return;
    }
    if(groupEnemy->getIsFinishedAddGroup() ==true  && instance->enemyVector.size() == 0 && groupCounter < instance->getGroupNum())
    {
        groupEnemy = this->nextGroup();
        int groupTotal = instance->getGroupNum();
        auto groupInfoText =std::to_string(groupCounter + 1);
        groupLabel->setString(groupInfoText);
        auto groupTotalText = std::to_string(groupTotal);
        groupTotalLabel->setString(groupTotalText);
    }
    this->addEnemy();
}

bool PlayLayer::onTouchBegan(Touch *touch, Event *event)
{
    this->removeChild(chooseTowerpanel);
    this->removeChild(DeleteOrUpgradePanle);
    chooseTowerpanel = NULL;
    DeleteOrUpgradePanle = NULL;
    auto location = touch->getLocation();
    
    checkAndAddTowerPanle(location);
    return true;
}
void PlayLayer::addTowerChoosePanel(Point point)
{
    chooseTowerpanel = TowerPanleLayer::create();
    chooseTowerpanel->setPosition(point);
    this->addChild(chooseTowerpanel);
}

void PlayLayer::addDeleteOrUpgradePanle(Point position){
    DeleteOrUpgradePanle = DeleteOrUpgradePanleLayer::create();
    DeleteOrUpgradePanle->setPosition(position);
    this->addChild(DeleteOrUpgradePanle);
}
Point PlayLayer::convertTotileCoord(Point position)
{
    int x = (position.x + offX)/ map->getContentSize().width * map->getMapSize().width;
    int y =map->getMapSize().height- position.y / map->getContentSize().height * map->getMapSize().height;
    return Point(x, y);
}
Point PlayLayer::convertToMatrixCoord(Point position)
{
    int x = (position.x + offX)/ map->getContentSize().width * map->getMapSize().width;
    int y = position.y / map->getContentSize().height * map->getMapSize().height;
    return Point(x, y);
}

void PlayLayer::checkAndAddTowerPanle(Point position)
{
    Point towerCoord = convertTotileCoord(position);
    Point matrixCoord = convertToMatrixCoord(position);
    
    Vector<TowerBase*> TowerNeedToDelete;
    
    int gid = bgLayer->getTileGIDAt(towerCoord);
    auto tileTemp = map->getPropertiesForGID(gid).asValueMap();
    int MatrixIndex = static_cast<int>( matrixCoord.y * MAP_WIDTH + matrixCoord.x );
    
    int TouchVaule;
    if (tileTemp.empty())
    {
        TouchVaule = 0;
    }else
    {
        TouchVaule = tileTemp.at("canTouch").asInt();
    }
    auto tileWidth = map->getContentSize().width / map->getMapSize().width;
    auto tileHeight = map->getContentSize().height / map->getMapSize().height;
    towerPos = Point((towerCoord.x * tileWidth) + tileWidth/2 -offX, map->getContentSize().height - (towerCoord.y * tileHeight) - tileHeight/2);
    
    if (1 == TouchVaule && towerMatrix[MatrixIndex]==NULL)
	{
		addTowerChoosePanel(towerPos);
	}
	else if(1 == TouchVaule)
	{
       // SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/tip.wav").c_str(), false);
		//auto tips = Sprite::createWithSpriteFrameName("no.png");
		//tips->setPosition(towerPos);
		//this->addChild(tips);
		//tips->runAction(Sequence::create(DelayTime::create(0.8f),
        //                                 CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, tips)),
        //                                 NULL));
        addDeleteOrUpgradePanle(position);
        
        
    }else{
        SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/tip.wav").c_str(), false);
        auto tips = Sprite::createWithSpriteFrameName("no.png");
        tips->setPosition(towerPos);
        this->addChild(tips);
        tips->runAction(Sequence::create(DelayTime::create(0.8f),
                                         CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, tips)),
                                         NULL));
    }
}

void PlayLayer::deleteTower(int MatrixIndex){
    //Point matrixCoord = convertToMatrixCoord(position);
    
    Vector<TowerBase*> TowerNeedToDelete;
    
    //int MatrixIndex = static_cast<int>( matrixCoord.y * MAP_WIDTH + matrixCoord.x );
    
    auto towerVector = instance->towerVector;
    for (int i = 0; i < towerVector.size(); i++) {
        auto tower = towerVector.at(i);
        auto towerRect = Rect(tower->getPositionX() /*+tower->getParent()->getPositionX()*/ - tower->getContentSize().width / 2,
                              tower->getPositionY() /*+tower->getParent()->getPositionY()*/ - tower->getContentSize().height / 2,
                              tower->getContentSize().width,
                              tower->getContentSize().height );
        
        
        if (towerRect.containsPoint(towerPos)) {
            TowerNeedToDelete.pushBack(tower);
            break;
        }
    }
    for (TowerBase* TowerTemp : TowerNeedToDelete)
    {
        //TowerTemp->TowerExpload();
        TowerTemp->removeFromParent();
        instance->towerVector.eraseObject(TowerTemp);
        
        if (TowerTemp->getRole() == 1) {
            money += 100;
        }else if (TowerTemp->getRole() == 2){
            money += 75;
        }else if (TowerTemp->getRole() == 3){
            money += 200;
        }
    }
    TowerNeedToDelete.clear();
    towerMatrix[MatrixIndex]=NULL;
}

bool PlayLayer::upgradeTower(int MatrixIndex){
    //Point matrixCoord = convertToMatrixCoord(position);
    
    Vector<TowerBase*> TowerNeedToDelete;
    
    //int MatrixIndex = static_cast<int>( matrixCoord.y * MAP_WIDTH + matrixCoord.x );
    
    auto towerVector = instance->towerVector;
    for (int i = 0; i < towerVector.size(); i++) {
        auto tower = towerVector.at(i);
        CCLOG("tower->getPositionX() %f", tower->getPositionX());
        //CCLOG("tower->getParent()->getPositionX() %f", tower->getParent()->getPositionX());
        CCLOG("tower->getContentSize().width %f", tower->getContentSize().width);
        auto towerRect = Rect(tower->getPositionX() /*+tower->getParent()->getPositionX()*/ - tower->getContentSize().width / 2,
                              tower->getPositionY() /*+tower->getParent()->getPositionY()*/ - tower->getContentSize().height / 2,
                              tower->getContentSize().width,
                              tower->getContentSize().height );
        
        
        if (towerRect.containsPoint(towerPos)) {
            if (money >= tower->getTowerValue()/2) {
                if (tower->getLevel() >= 5) {
                    auto tips = Sprite::createWithSpriteFrameName("no.png");
                    tips->setPosition(towerPos);
                    this->addChild(tips);
                    tips->runAction(Sequence::create(DelayTime::create(0.8f),
                                                     CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, tips)),
                                                     NULL));
                    return false;
                }else{
                    //CCLOG("Upgrade money: %d", tower->getTowerValue()/2);
                    money -= tower->getTowerValue()/2;
                    tower->setTowerValue(tower->getTowerValue() + tower->getTowerValue()/2);
                    tower->setLethality(tower->getLethality() + 1);
                    //CCLOG("Upgrade Lethality: %d", tower->getLethality());
                    tower->setLevel(tower->getLevel() + 1);
                    //CCLOG("Upgrade Level: %d", tower->getLevel());
                    tower->setScope(tower->getScope() + 90);
                    //CCLOG("Upgrade Scope: %d", tower->getScope());
                    tower->setRate(tower->getRate() + 1);
                    //CCLOG("Upgrade Rate: %f", tower->getRate());
                    return false;
                }
            }
            break;
        }
    }
    return true;
}


void PlayLayer::deleteOrUpdateTower(){
    if(DeleteOrUpgradePanle != NULL)
    {
        int type = DeleteOrUpgradePanle->getRole();
        if(type == 0)
        {
            return;
        }
        Point matrixCoord = convertToMatrixCoord(towerPos);
        int MatrixIndex = static_cast<int>( matrixCoord.y * MAP_WIDTH + matrixCoord.x );
        bool noMoneyTips = false;
        if( type == 1 )
        {
            deleteTower(MatrixIndex);
        }
        else if( type == 2 )
        {
            noMoneyTips = upgradeTower(MatrixIndex);
        }
        type =  0;
        DeleteOrUpgradePanle->setRole(type);
        this->removeChild(DeleteOrUpgradePanle);
        DeleteOrUpgradePanle = NULL;
        
        auto moneyText = std::to_string(money);
        moneyLabel->setString(moneyText);
        
        if( noMoneyTips == true )
        {
            auto tips = Sprite::createWithSpriteFrameName("nomoney_mark.png");
            tips->setPosition(towerPos);
            this->addChild(tips);
            tips->runAction(Sequence::create(DelayTime::create(0.5f),
                                             CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, tips)),
                                             NULL));
        }
    }
}
void PlayLayer::addTower()
{
    if(chooseTowerpanel)
	{
		auto type = chooseTowerpanel->getChooseTowerType();
        if(type == TowerType::ANOTHER)
        {
            return;
        }
        Point matrixCoord = convertToMatrixCoord(towerPos);
        int MatrixIndex = static_cast<int>( matrixCoord.y * MAP_WIDTH + matrixCoord.x );
        bool noMoneyTips = false;
        TowerBase* tower = NULL;
        if( type == TowerType::ARROW_TOWER )
        {
            if( money >= 200 )
            {
                tower = ArrowTower::create();
                //tower->setRole(1);
                money -= 200;
            }
            else
                noMoneyTips = true;
        }
        else if( type == TowerType::ATTACK_TOWER )
        {
            if( money >= 150 )
            {
                tower = AttackTower::create();
                //tower->setRole(2);
                money -= 150;
            }
            else
                noMoneyTips = true;
        }
        else if( type == TowerType::MULTIDIR_TOWER )
        {
            if( money >= 500 )
            {
                tower = MultiDirTower::create();
                //tower->setRole(3);
                money -= 500;
            }else
                noMoneyTips = true;
        }
        if(tower != NULL)
        {
            tower->setPosition(towerPos);
            tower->runAction(Sequence::create(FadeIn::create(1.0f),NULL));
            this->addChild(tower);
            towerMatrix[MatrixIndex] =  tower;
            instance->towerVector.pushBack(tower);
        }
        type =  TowerType::ANOTHER;
        chooseTowerpanel->setChooseTowerType(type);
        this->removeChild(chooseTowerpanel);
        chooseTowerpanel = NULL;
        
        auto moneyText = std::to_string(money);
        moneyLabel->setString(moneyText);
        
		if( noMoneyTips == true )
		{
            SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/tip.wav").c_str(), false);
			auto tips = Sprite::createWithSpriteFrameName("nomoney_mark.png");
			tips->setPosition(towerPos);
			this->addChild(tips);
			tips->runAction(Sequence::create(DelayTime::create(0.5f),
                                             CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, tips)),
                                             NULL));
        }
    }
}

void PlayLayer::CollisionDetection()
{
    auto bulletVector = instance->bulletVector;
    auto enemyVector = instance->enemyVector;
    
    if(bulletVector.empty() || enemyVector.empty() ){
        return;
    }
    Vector<EnemyBase*> enemyNeedToDelete;
    Vector<MyBullet*> bulletNeedToDelete;
    //CCLOG("bulletVector %d",bulletVector.size());
    for (int i = 0; i < bulletVector.size(); i++)
    {
        auto bullet = bulletVector.at(i);
        if(bullet->getParent() == NULL )
        {
            //CCLOG("Here!!!!");
            continue;
        }
        auto  bulletRect = Rect(bullet->getPositionX() +bullet->getParent()->getPositionX() - bullet->getContentSize().width / 2,
                                bullet->getPositionY() +bullet->getParent()->getPositionY() - bullet->getContentSize().height / 2,
                                bullet->getContentSize().width/8,
                                bullet->getContentSize().height/8 );
        
        for (int j = 0; j < enemyVector.size(); j++)
        {
            auto enemy = enemyVector.at(j);
            if(enemy->getEnemyType()!=(bullet->getAttackType()&enemy->getEnemyType()))
                break;
                        //auto enemyRect = enemy->sprite->getBoundingBox();
                        auto enemyRect = Rect(enemy->sprite->getPositionX() - enemy->sprite->getContentSize().width / 2,
                                              enemy->sprite->getPositionY()  - enemy->sprite->getContentSize().height / 2,
                                              enemy->sprite->getContentSize().width ,
                                              enemy->sprite->getContentSize().height );
        //auto enemyRect=enemy->sprite->getBoundingBox();
            if (bulletRect.intersectsRect(enemyRect))
            {
                if(enemy->getEnemyStatus()!=ENEMY_DESPEED &&(bullet->getAttackType()&ENEMY_DESPEED)==ENEMY_DESPEED){
                    int tempspeed=enemy->getRunSpeed();
                    enemy->setRunSpeed(tempspeed/3*2);
                }
                auto currHp = enemy->getCurrHp();
                //currHp--;
                currHp = currHp - bullet->getAttackValue();
                if (currHp <= 0) {
                    currHp = 0;
                }
                enemy->setCurrHp( currHp );
                
                auto currHpPercentage = enemy->getHpPercentage();
                auto offHp = 100 / enemy->getMaxHp();
                currHpPercentage -= offHp;
                if(currHpPercentage < 0){
                    currHpPercentage = 0;
                }
                enemy->setHpPercentage(currHpPercentage);
                
                if(currHpPercentage<=70&&currHpPercentage>30){
                    enemy->hpBgSprite->removeAllChildrenWithCleanup(true);
                    ProgressTimer* hpBar = CCProgressTimer::create(Sprite::createWithSpriteFrameName("hpbary.png"));
                    hpBar->setType(ProgressTimer::Type::BAR);
                    hpBar->setMidpoint(Point(0, 0.5f));
                    hpBar->setBarChangeRate(Point(1, 0));
                    hpBar->setPercentage(currHpPercentage);
                    hpBar->setPosition(Point(enemy->hpBgSprite->getContentSize().width / 2, enemy->hpBgSprite->getContentSize().height / 3 * 2 ));
                    enemy->hpBgSprite->removeChild(hpBar, true);
                    enemy->setHpBar(hpBar);
                    enemy->hpBgSprite->addChild(hpBar);
                }
                else if(currHpPercentage<=30){
                    enemy->hpBgSprite->removeAllChildrenWithCleanup(true);
                    ProgressTimer* hpBar = CCProgressTimer::create(Sprite::createWithSpriteFrameName("hpbarr.png"));
                    hpBar->setType(ProgressTimer::Type::BAR);
                    hpBar->setMidpoint(Point(0, 0.5f));
                    hpBar->setBarChangeRate(Point(1, 0));
                    hpBar->setPercentage(currHpPercentage);
                    hpBar->setPosition(Point(enemy->hpBgSprite->getContentSize().width / 2, enemy->hpBgSprite->getContentSize().height / 3 * 2 ));
                    enemy->hpBgSprite->removeChild(hpBar, true);
                    enemy->setHpBar(hpBar);
                    enemy->hpBgSprite->addChild(hpBar);

                }
                else
                    enemy->getHpBar()->setPercentage(currHpPercentage);
                
                if(currHp <= 0)
                {
                    enemyNeedToDelete.pushBack(enemy);
                    auto valueMoney = enemy->getVaule();
                    money += valueMoney;
                    auto moneyText = std::to_string(money);
                    moneyLabel->setString(moneyText);
                }
                bulletNeedToDelete.pushBack( bullet);
                break;
            }
        }
        for (EnemyBase* enemyTemp : enemyNeedToDelete)
        {
            enemyTemp->enemyExpload();
            instance->enemyVector.eraseObject(enemyTemp);
        }
        enemyNeedToDelete.clear();
    }
    
    for (MyBullet* bulletTemp : bulletNeedToDelete)
    {
        instance->bulletVector.eraseObject(bulletTemp);
        bulletTemp->removeFromParent();
    }
    bulletNeedToDelete.clear();
}

void PlayLayer::enemyIntoHouse()
{
    auto enemyVector = instance->enemyVector;
    for (int i = 0; i < enemyVector.size(); i++)
    {
        auto enemy = enemyVector.at(i);
        if( enemy->getEnemySuccessful())
        {
            instance->enemyVector.eraseObject(enemy);
            enemy->removeFromParent();
            auto playHp = getPlayHpPercentage() - 10;
            if(playHp > 0){
                setPlayHpPercentage(playHp);
                if(playHp<=70&&playHp>30){
                    toolLayer->getChildByTag(10)->removeChildByTag(11);
                    playHpBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("tophpbary.png"));
                    playHpBar->setType(ProgressTimer::Type::BAR);
                    playHpBar->setMidpoint(Point(0, 0.4f));
                    playHpBar->setBarChangeRate(Point(1, 0));
                    playHpBar->setPercentage(playHpPercentage);
                    playHpBar->setPosition(Point(toolLayer->getChildByTag(10)->getContentSize().width / 5 *4  , toolLayer->getChildByTag(10)->getContentSize().height /40*15));
                    toolLayer->getChildByTag(10)->addChild(playHpBar,0,11);
                }
                if(playHp<=30){
                    toolLayer->getChildByTag(10)->removeChildByTag(11);
                    playHpBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("tophpbarr.png"));
                    playHpBar->setType(ProgressTimer::Type::BAR);
                    playHpBar->setMidpoint(Point(0, 0.4f));
                    playHpBar->setBarChangeRate(Point(1, 0));
                    playHpBar->setPercentage(playHpPercentage);
                    playHpBar->setPosition(Point(toolLayer->getChildByTag(10)->getContentSize().width / 5 *4  , toolLayer->getChildByTag(10)->getContentSize().height / 40*15));
                    toolLayer->getChildByTag(10)->addChild(playHpBar,0,11);
                }

                else
                    playHpBar->setPercentage(playHp);
            }
            else{
                instance->clear();
                Director::getInstance()->replaceScene(TransitionFade::create(0.1f, FailedScene::create()));
            }
        }
    }
}

void PlayLayer::update(float dt)
{
    deleteOrUpdateTower();
    addTower();
    CollisionDetection();
    enemyIntoHouse();
    if(isSuccessful)
    {
        isSuccessful = false;
        auto star = 0;
        auto playHp = this->getPlayHpPercentage();
        
        if( playHp > 0 && playHp <= 30){ star = 1;}
        else if(playHp > 30 && playHp <= 60 ){ star = 2;}
        else if(playHp > 60 && playHp <= 100 ){ star = 3;}
        
        if( star > UserDefault::getInstance()->getIntegerForKey(instance->getCurrLevelFile().c_str()))
		{
			UserDefault::getInstance()->setIntegerForKey(instance->getCurrLevelFile().c_str(), star);
			auto levelNum = UserDefault::getInstance()->getIntegerForKey("levelNum") + 1;
			UserDefault::getInstance()->setIntegerForKey("levelNum", levelNum);
		}
        
		auto nextlevel = instance->getNextLevelFile();
		UserDefault::getInstance()->setStringForKey("nextLevelFile", nextlevel);
        
		instance->clear();
        Director::getInstance()->replaceScene(TransitionFade::create(0.1f, SuccessfulScene::create()));
	}
}

