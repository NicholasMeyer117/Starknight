#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <list>
#include <math.h>
#include <cstring>
#include <unistd.h>
#include "Entity.h"
#include "Actor.h"
#include "Enemy.h"
#include "Bullets.h"
#include "EnergyShield.h"
#define PI 3.14159265

class Shielder: public Enemy
{

    public:
    bool movingUp = true;
    Sprite bulletSprite;
    int volleyNum = 0;
    std::vector<EnergyShield*> shieldList;
    
    void takeDamage(float damage)
    {
        health = health - damage;
        if (health <= 0)
            life=0;
    }
    
    void enemySpawn(std::vector<Sprite> SpriteList, int ScreenW, int ScreenH)
    {
        screenH = ScreenH;
        screenW = ScreenW;
        srand(time(NULL));
        int randNum = rand() % screenH/2 + 200;
        sprite.setPosition(screenW, randNum);
        setActorPosition(screenW, randNum);
        enemyType = shielder;
    }
    
    void enemyMove()
    {
        if (!reachedBegin)
        {
            moveActor(left);
            int spawnZone = (screenW - screenW/6) - rand() % screenW/5;
            if (x <= spawnZone)
                reachedBegin = true;
        }
        else
        {
            if (movingUp)
            {
                moveActor(up);
                if (y <= screenH/10)
                    movingUp = false;
            }
            else
            {
                moveActor(down);
                if (y >= screenH - screenH/10)
                    movingUp = true;
            }

        }
        
    }
    
    /*Bullet* checkCollisions(EnergyShield *a, std::vector<Bullet*> entities)
    {
        for(auto i:entities)
        {
            if (a->isCollide(i))
            {
                i -> life = 0;
                return i;
            }
        } 
        return NULL;
    }*/
    
    bool shieldCollision(Entity entity, EnergyShield shield)
    {
        int dx = entity.x - shield.x;
        int dy = entity.y - shield.y;
        int distance = sqrt((dx * dx) + (dy * dy));
        cout << "\nDistance: " + std::to_string(distance);
        cout << "\nmust be less than: " + std::to_string(shield.circle.getRadius() * 1 + entity.R * 1) + "\n";
        if (distance < shield.circle.getRadius() * 1 + entity.R * 1)
            return true;
        return false;
    }
    
    void updateShield(EnergyShield *shield)
    {
        if (shield->health <= shield->maxHealth/2)
            shield->circle.setOutlineColor(sf::Color::Red);
    }
    
    std::vector<EnergyShield*> removeDeadShield(std::vector<EnergyShield*> shields)
    {
        
        for(auto i=shields.begin();i!=shields.end();)
        {
            EnergyShield *e = *i;

            if (e->life==false)
            {
                i=shields.erase(i); 
                //delete e;
            }
            else i++;
        }
    return shields;

    }
    
    void ability(std::vector<Enemy*> enemyList, std::vector<Bullet*> *bulletList, RenderWindow &window)
    {
        shieldList = removeDeadShield(shieldList);
        if (ticksSinceLastFire == firerate)
        { 

            shieldList.clear();
            for (auto i:enemyList)
            {
                if (i->enemyType!=shielder)
                {
                    EnergyShield *energyShield = new EnergyShield;
                    energyShield->noSpriteSettings(i->x,i->y,i->w,i->h, Color::Black, 0,0);
                    energyShield->createActor(10, 0, 0, 0, true, 0);
                    float xCoord = i->x;// - (i->w - (i->w/1.5));
                    float yCoord = i->y;// - (i->h- (i->h/1.5));
                    energyShield->createShield(xCoord, yCoord, i->w, i);
                    shieldList.push_back(energyShield);
                }
            }
            ticksSinceLastFire = 0;
        }
        else
            ticksSinceLastFire++;
        
        for (int i = 0; i < shieldList.size(); i++)
        {
            
            shieldList[i]->x = shieldList[i]->enemy->x;
            shieldList[i]->y = shieldList[i]->enemy->y;
            shieldList[i]->circle.setPosition(shieldList[i]->enemy->x, shieldList[i]->enemy->y);
            for (int j = 0; j < bulletList->size(); j++)
            {
                if (shieldCollision(*bulletList->at(j), *shieldList.at(i)))
                {
                    cout << "\nbullet hit\n";
                    cout << "\nBullet Pos: " + std::to_string(bulletList->at(j)->x) + " , " + std::to_string(bulletList->at(j)->y);
                    cout << "\nShield Pos: " + std::to_string(shieldList.at(i)->x) + " , " + std::to_string(shieldList.at(i)->y) + "\n";
                    shieldList[i] -> takeDamage(bulletList->at(j)->damage);
                    updateShield(shieldList[i]);
                    bulletList->at(j) -> life = 0;
                }
            }

            window.draw(shieldList[i]->circle); 
        }
        
    }

};

