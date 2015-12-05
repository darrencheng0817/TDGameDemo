//
//  GameManager.cpp
//  cs526
//
//  Created by qiang on 15/2/13.
//
//

#include "GameManager.h"



GameManager* GameManager::instance;

GameManager* GameManager::getInstance()
{
    if (instance == NULL)
        instance = new GameManager();
    return instance;
}

void GameManager::clear()
{
    enemyVector.clear();
    bulletVector.clear();
    //towerVector.clear();
    groupVector.clear();
}
