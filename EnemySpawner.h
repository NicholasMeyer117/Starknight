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
#include "Bullets.h"

class EnemySpawner
{
    public:
    int level;
    std::vector<Sprite> spriteList;
    
    void createSpawner(std::vector<Sprite> SpriteList)
    {
        spriteList = SpriteList;
    
    
    
    }
    
    Enemy* checkToSpawn(int level, int area, int tick)
    {
        cout<<"\ncheck to spawn";
        switch(area) 
        {
            case 1 :
                switch(level)
                {
                    case 1:
                        cout<<"\nless go";
                        int randNum = rand() % 100 + 1;
                        if (randNum > 0)
                        {
                            cout<<"\nspawn";
                            return spawn(0);
                        }
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
    
    Enemy* spawn(int enemyType) // 0 = DarkFighter;
    {
        Enemy *enemy;
        Sprite sprite;
        if (enemyType == 0)
        {
            enemy = new DarkFighter();
            sprite = spriteList[0];
            
        }
            
        enemy -> settings(sprite,1300,75,50,50);
        enemy -> createActor(10, 0, 2, 60, true, 0);
        enemy->enemySpawn();
        return enemy;
    }
    
};
