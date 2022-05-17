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
#include "Swarmer.h"
#include "SwarmSpitter.h"
#include "MachineGunner.h"
#include "Bullets.h"
#include "Game.h"
#include "Boss.h"

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
    
    vector<Boss*> checkToSpawnBoss(int level, int area)
    {
        vector<Boss*> bosses;
        Sprite sprite;
        switch(area) 
        {
            case 1 :
                switch(level)
                {
                    case 5:
                        PirateLord *pirateLord = new PirateLord();
                        sprite = spriteList[4];
                        pirateLord -> settings(sprite,screenW + 100,75,485,402);
                        pirateLord -> createActor(500, 0, 50, 120, true, 0);
                        pirateLord -> enemySpawn(bulletSpriteList, screenW, screenH);
                        bosses.push_back(pirateLord);
            
                        //std::vector<Enemy*> partList
            
                        PirateTurret *turret1 = new PirateTurret();
                        Sprite turretSprite = spriteList[5];
                        turret1 -> settings(turretSprite,500,500,51,51);
                        turret1 -> createActor(100, 0, 50, 60, true, 0);
                        turret1 -> enemySpawn(bulletSpriteList, screenW, screenH);
                        turret1 -> setTop(true);
            
                        pirateLord -> Parts.push_back(turret1);
                        bosses.push_back(turret1);
            
                        PirateTurret2 *turret2 = new PirateTurret2();
                        Sprite turret2Sprite = spriteList[8];
                        turret2 -> settings(turret2Sprite,500,500,51,51);
                        turret2 -> createActor(100, 0, 50, 150, true, 0);
                        turret2 -> enemySpawn(bulletSpriteList, screenW, screenH);
            
                        pirateLord -> Parts.push_back(turret2);
                        bosses.push_back(turret2);
            
                        PirateTurret *turret3 = new PirateTurret();
                        turret3 -> settings(turretSprite,500,500,51,51);
                        turret3 -> createActor(100, 0, 50, 60, true, 0);
                        turret3 -> enemySpawn(bulletSpriteList, screenW, screenH);
                        turret3 -> setTop(false);
            
                        pirateLord -> Parts.push_back(turret3);
                        bosses.push_back(turret3);
            
                        pirateLord ->setTurretPositions();
            
                        return bosses;
                        break;
                }
                
                break;
        }
        return bosses; 
    
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
                        if (randNum <= 33)
                        {
                            return spawn(0);
                        }
                        else if (randNum > 33 and randNum <=66)
                            return spawn(1);
                        else
                            return spawn(2);
                    case 2:
                        if (randNum <= 25)
                        {
                            return spawn(0);
                        }
                        else if (randNum > 25 and randNum <=50)
                            return spawn(1);
                        else
                            return spawn(2);
                    case 3:
                        if (randNum <= 33)
                        {
                            return spawn(1);
                        }
                        else if (randNum > 33 and randNum <=66)
                            return spawn(2);
                        else
                            return spawn(6);
                    case 4: 
                        if (!contains(enemyList, Enemy::EnemyType::shielder))
                            return spawn(3);
                        else if (randNum <= 25)
                            return spawn(1);
                        else if (randNum > 25 and randNum <=65)
                            return spawn(2);
                        else
                            return spawn(6);
                
                
                } 
                break;
            case 2 :
                switch(level)
                {
                    case 1:
                        return spawn(4);
                    case 2:
                        if (randNum > 33)
                        {
                            return spawn(4);
                        }
                        else
                            return spawn(5);
                        
                
                
                } 
                break;
            case 3 :
                cout << "Well done" << endl;
                break;
            
        }
        return NULL;
    }
    
    Enemy* spawn(int enemyType) // 0 = DarkFighter; 1=TriShooter; 2=doubleShooter, 3 = Shielder, 4 = Swarmer
    {
        std::cout << "\nScreen Width1: " + std::to_string(screenW);
        Enemy *enemy;
        Sprite sprite;
        //createActor(int Health, int Shields, float Speed, float Firerate, bool IsEnemy, int IFrames)
        if (enemyType == 0)
        {
            enemy = new DarkFighter();
            sprite = spriteList[0];
            enemy -> settings(sprite,screenW + 100,75,80,80);
            enemy -> createActor(10, 0, 100, 60, true, 0);
            enemy->enemySpawn(bulletSpriteList, screenW, screenH);
            
        }
        else if (enemyType == 1)
        {
            enemy = new TriShooter();
            sprite = spriteList[1];
            enemy -> settings(sprite,screenW + 100,75,72,90);
            enemy -> createActor(15, 0, 50, 80, true, 0);
            enemy->enemySpawn(bulletSpriteList, screenW, screenH);
        }
        else if (enemyType == 2)
        {
            enemy = new DoubleShooter();
            sprite = spriteList[2];
            enemy -> settings(sprite,screenW + 100,75,68,75);
            enemy -> createActor(10, 0, 125, 70, true, 0);
            std::cout << "\nScreen Width1.5: " + std::to_string(screenW);
            enemy->enemySpawn(bulletSpriteList, screenW, screenH);
        
        }
        else if (enemyType == 3)
        {
            enemy = new Shielder();
            sprite = spriteList[3];
            enemy -> settings(sprite,screenW + 100,75,43,173);
            enemy -> createActor(25, 0, 50, 240, true, 0);
            enemy->enemySpawn(bulletSpriteList, screenW, screenH);
        
        }
        else if (enemyType == 4)
        {
            enemy = new Swarmer();
            sprite = spriteList[6];
            enemy -> settings(sprite,screenW + 100,75,80,60);
            enemy -> createActor(20, 0, 150, 300, true, 0);
            enemy->enemySpawn(bulletSpriteList, screenW, screenH);
        
        }
        else if (enemyType == 5)
        {
            enemy = new SwarmSpitter();
            sprite = spriteList[7];
            enemy -> settings(sprite,screenW + 100,75,90,90);
            enemy -> createActor(40, 0, 100, 200, true, 0);
            enemy->enemySpawn(bulletSpriteList, screenW, screenH);
        
        }
        else if (enemyType == 6)
        {
            enemy = new MachineGunner();
            sprite = spriteList[9];
            enemy -> settings(sprite,screenW + 100,75,80,84);
            enemy -> createActor(15, 0, 100, 70, true, 0);
            enemy->enemySpawn(bulletSpriteList, screenW, screenH);
        
        }
        
            
        
        return enemy;
    }
    
};
