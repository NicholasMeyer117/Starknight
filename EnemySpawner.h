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
#include "Bullets.h"

class EnemySpawner
{
    public:
    int level;
    std::vector<Sprite> spriteList;
    std::vector<Sprite> bulletSpriteList;
    
    void createSpawner(std::vector<Sprite> SpriteList, std::vector<Sprite> BulletSpriteList)
    {
        spriteList = SpriteList;
        bulletSpriteList = BulletSpriteList;
        
    }
    
    Enemy* checkToSpawn(int level, int area, int tick)
    {
        srand(time(NULL));
        cout<<"\ncheck to spawn";
        int randNum = rand() % 100 + 1;
        switch(area) 
        {
            case 1 :
                switch(level)
                {
                    case 1:
                        cout<<"\nless go";
                        if (randNum > 0)
                        {
                            cout<<"\nspawn";
                            return spawn(0);
                        }
                        break;
                    case 2:
                        if (randNum > 50)
                        {
                            cout<<"\nspawn";
                            return spawn(1);
                        }
                        else
                            return spawn(0);
                    case 3:
                        if (randNum > 30)
                        {
                            cout<<"\nspawn";
                            return spawn(1);
                        }
                        else
                            return spawn(0);
                    case 4: 
                        break;
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
    
    Enemy* spawn(int enemyType) // 0 = DarkFighter; 1=TriShooter;
    {
        Enemy *enemy;
        Sprite sprite;
        if (enemyType == 0)
        {
            enemy = new DarkFighter();
            sprite = spriteList[0];
            enemy -> settings(sprite,1300,75,53,53);
            enemy -> createActor(10, 0, 2, 60, true, 0);
            enemy->enemySpawn(bulletSpriteList[1]);
            
        }
        else if (enemyType == 1)
        {
            enemy = new TriShooter();
            sprite = spriteList[1];
            enemy -> settings(sprite,1300,75,50,50);
            enemy -> createActor(10, 0, 1, 80, true, 0);
            enemy->enemySpawn(bulletSpriteList[1]);
        }
            
        
        return enemy;
    }
    
};
