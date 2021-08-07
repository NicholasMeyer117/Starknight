#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "ProgressBar.h"

class Boss: public Enemy
{
    public:
    std::vector<Boss*> Parts;
    bool changeBar = false;
    int phase = 0;
    
};

class PirateLord: public Boss
{
    public:
    bool movingUp = true;
    Sprite bulletSprite;
    std::vector<ProgressBar> bars;
    
    void takeDamage(int damage)
    {
        health = health - damage;
        if (phase == 1)
            bars[0].changePercentage(health/maxHealth);
        if (health <= 0)
            life=0;
    }
    
    void enemySpawn(Sprite BulletSprite, int ScreenW, int ScreenH)
    {
        screenH = ScreenH;
        screenW = ScreenW;
        sprite.setPosition(screenW, screenH/2);
        setActorPosition(screenW, screenH/2);
        bulletSprite = BulletSprite;
        enemyType = pirateLord;
        bulletsPassThrough = true;
        ProgressBar healthBar1(250, 800, 30, ScreenW/2 - 400, 0 + ScreenH/8);
        bars.push_back(healthBar1);
        ProgressBar healthBar2(250, 800, 30, ScreenW/2 - 400, 0 + (ScreenH/8) + (ScreenH/32));
        bars.push_back(healthBar2);
        ProgressBar healthBar3(250, 800, 30, ScreenW/2 - 400, 0 + (ScreenH/8) + ((ScreenH/32)* 2));
        bars.push_back(healthBar3);
    }
    
    void setTurretPositions()
    {
        Parts[0]->xPos = x;
        Parts[0]->yPos = y;
        Parts[1]->xPos = x;
        Parts[1]->yPos = y + 140;
        Parts[2]->xPos = x;
        Parts[2]->yPos = y - 135;
    }
    
    void enemyMove()
    {
        if (!reachedBegin)
        {
            moveActor(left);
            for (auto i:Parts)
            {
                i->moveActor(left);
            }
            if (x <= screenW - screenW/8)
                reachedBegin = true;
                
        }
        else
        {
            if (movingUp)
            {
                moveActor(up);
                for (auto i:Parts)
                {
                    i->moveActor(up);
                }
                if (y <= screenH/10)
                    movingUp = false;
            }
            else
            {
                moveActor(down);
                for (auto i:Parts)
                {
                    i->moveActor(down);
                }
                if (y >= screenH - screenH/10)
                    movingUp = true;
            }

        }
    }
    
    void checkIfTurretsDead()
    {
        for (auto i:Parts)
        {
            if (i->health>0)
                return;
        
        }
        Parts.clear();
        bars.clear();
        ProgressBar healthBar(250, 800, 30, screenW/2 - 400, 0 + screenH/8);
        bars.push_back(healthBar);
        bulletsPassThrough = false;
        phase++;
        return;
    
    }
    
    void ability(std::vector<Enemy*> enemyList, std::vector<Bullet*> *bulletList, RenderWindow &window)
    {
        float tempPer = 0;
        if (phase == 0)
        {
            setTurretPositions();
            checkIfTurretsDead();
        }
        for (int i = 0; i < bars.size(); i++)
        {
            window.draw(bars[i].rectangle);
            if (Parts[i]->changeBar == true && phase == 0)
            {
                Parts[i]->changeBar = false;
                bars[i].changePercentage(Parts[i]->health/Parts[i]->maxHealth);
            }
            for (int j = 0; j < bars[i].bars.size(); j++)
            {
                window.draw(bars[i].bars[j]);
            } 
        }
    }

};

class PirateTurret: public Boss
{
    public:
    bool movingUp = true;
    Sprite bulletSprite;
    
    void takeDamage(int damage)
    {
        changeBar = true;
        health = health - damage;
        if (health <= 0)
            life=0;
        
    }

    void enemySpawn(Sprite BulletSprite, int ScreenW, int ScreenH)
    {
        screenH = ScreenH;
        screenW = ScreenW;
        bulletSprite = BulletSprite;
        enemyType = pirateTurret;
        bulletsPassThrough = false;
    }
    
    

};