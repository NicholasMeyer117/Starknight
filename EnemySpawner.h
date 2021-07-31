#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <list>
#include <stdlib.h> 
#include <math.h>
#include <cstring>
#include "Entity.h"
#include "Button.h"
#include "Actor.h"
#include "Character.h"
#include "Enemy.h"
#include "DarkFighter.h"
#include "TriShooter.h"
#include "DoubleShooter.h"
#include "Shielder.h"
#include "Bullets.h"
#include "Game.h"

class EnemySpawner
{
    public:
    int level;
    std::vector<Sprite> spriteList;
    std::vector<Sprite> bulletSpriteList;
    int screenW;
    int screenH;
    
    void createSpawner(std::vector<Sprite> SpriteList, std::vector<Sprite> BulletSpriteList, int ScreenW, int ScreenH)
    {
        spriteList = SpriteList;
        bulletSpriteList = BulletSpriteList;
        screenW = ScreenW;
        screenH = ScreenH;
        
    }
    
    bool contains(std::vector<Enemy*> enemyList, Enemy::EnemyType type)
    {
        for (auto i:enemyList)
        {
            if (i->enemyType == type)
                return true;
        
        }
        return false;
    }
    
    Enemy* checkToSpawn(int level, int area, int tick, std::vector<Enemy*> enemyList)
    {
        srand(time(NULL));
        int randNum = rand() % 100 + 1;
        switch(area) 
        {
            case 1 :
                switch(level)
                {
                    case 1:
                        return spawn(0);
                        break;
                    case 2:
                        if (randNum > 66)
                        {
                            return spawn(1);
                        }
                        else
                            return spawn(0);
                    case 3:
                        if (randNum <= 33)
                        {
                            return spawn(2);
                        }
                        else if (randNum > 33 and randNum <=66)
                            return spawn(1);
                        else
                            return spawn(0);
                    case 4: 
                        if (randNum <= 25)
                        {
                            return spawn(0);
                        }
                        else if (randNum > 26 and randNum <=50)
                            return spawn(1);
                        else if (randNum > 51 and randNum <=75)
                            return spawn(2);
                        else if (!contains(enemyList, Enemy::EnemyType::shielder))
                            return spawn(3);
                        else
                            return spawn(0);
                    case 5:
                        break;
                
                
                } 
                break;
            case 2 :
            case 3 :
                cout << "Well done" << endl;
                break;
            
        }
        return NULL;
    }
    
    Enemy* spawn(int enemyType) // 0 = DarkFighter; 1=TriShooter; 2=doubleShooter
    {
        std::cout << "\nScreen Width1: " + std::to_string(screenW);
        Enemy *enemy;
        Sprite sprite;
        if (enemyType == 0)
        {
            enemy = new DarkFighter();
            sprite = spriteList[0];
            enemy -> settings(sprite,screenW + 100,75,53,53);
            enemy -> createActor(10, 0, 2, 60, true, 0);
            enemy->enemySpawn(bulletSpriteList[1], screenW, screenH);
            
        }
        else if (enemyType == 1)
        {
            enemy = new TriShooter();
            sprite = spriteList[1];
            enemy -> settings(sprite,screenW + 100,75,50,50);
            enemy -> createActor(10, 0, 1, 80, true, 0);
            enemy->enemySpawn(bulletSpriteList[1], screenW, screenH);
        }
        else if (enemyType == 2)
        {
            enemy = new DoubleShooter();
            sprite = spriteList[2];
            enemy -> settings(sprite,screenW + 100,75,50,50);
            enemy -> createActor(10, 0, 2.5, 70, true, 0);
            std::cout << "\nScreen Width1.5: " + std::to_string(screenW);
            enemy->enemySpawn(bulletSpriteList[1], screenW, screenH);
        
        }
        else if (enemyType == 3)
        {
            enemy = new Shielder();
            sprite = spriteList[3];
            enemy -> settings(sprite,screenW + 100,75,17,71);
            enemy -> createActor(25, 0, 1, 240, true, 0);
            enemy->enemySpawn(bulletSpriteList[1], screenW, screenH);
        
        }
            
        
        return enemy;
    }
    
};
