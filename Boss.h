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
    int attackPattern = 0;
    int phase = 0;
    
};

class PirateLord: public Boss
{
    public:
    bool movingUp = true;
    Sprite bulletSprite;
    int volleyNum = 0;
    std::vector<ProgressBar> bars;
    
    void takeDamage(float damage)
    {
        health = health - damage;
        if (phase == 1)
            bars[0].changePercentage(health/maxHealth);
    }
    
    void enemySpawn(std::vector<Sprite> bulletSpriteList, int ScreenW, int ScreenH)
    {
        screenH = ScreenH;
        screenW = ScreenW;
        sprite.setPosition(screenW, screenH/2);
        setActorPosition(screenW, screenH/2);
        bulletSprite = bulletSpriteList[2];
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
        Parts[0]->xPos = x - 20;
        Parts[0]->yPos = y - 150;
        Parts[1]->xPos = x;
        Parts[1]->yPos = y;
        Parts[2]->xPos = x - 20;
        Parts[2]->yPos = y + 150;
    }
    
    void enemyMove(float elapsed)
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
    
    void enemyAttack(std::vector<Bullet*> *bulletList, std::vector<Entity*> *entities, bool advanceTick)
    {
        if (ticksSinceLastFire == firerate && bulletsPassThrough == false && health > 0)
        { 
        
            DiagonalBullet *b1 = new DiagonalBullet(false, true);
            b1->settings(bulletSprite,x,y,5, 5, angle, 3);
            b1->createBullet (5, 125);
            //b1->direction (false, true);
            entities->push_back(b1);                
            bulletList->push_back(b1);   
        
            DiagonalBullet *b2 = new DiagonalBullet(false, false);
            b2->settings(bulletSprite,x,y,5, 5, angle, 3);
            b2->createBullet (5, 125);
            //b2->direction (false, false);
            entities->push_back(b2);                
            bulletList->push_back(b2);
        
            DarkBullet *b3 = new DarkBullet();
            b3->settings(bulletSprite,x,y,5, 5, angle, 3);
            b3->createBullet (5, 500);
            entities->push_back(b3);                
            bulletList->push_back(b3); 
            
            DiagonalBullet *b4 = new DiagonalBullet(false, true, 2);
            b4->settings(bulletSprite,x,y,5, 5, angle, 3);
            b4->createBullet (5, 125);
            //b4->direction (false, true, 2);
            entities->push_back(b4);                
            bulletList->push_back(b4);   
        
            DiagonalBullet *b5 = new DiagonalBullet(false, false, 2);
            b5->settings(bulletSprite,x,y,5, 5, angle, 3);
            b5->createBullet (5, 125);
            //b5->direction (false, false, 2);
            entities->push_back(b5);                
            bulletList->push_back(b5);
            
            if (volleyNum < 10)
            {
                volleyNum++;
                ticksSinceLastFire = firerate - 15;
            }
            else
            {
                ticksSinceLastFire = 0;
                volleyNum = 0;
            }
        }
        else if (bulletsPassThrough == false and advanceTick)
            ticksSinceLastFire++;                   
    }

};

class PirateTurret: public Boss
{
    public:
    bool movingUp = true;
    Sprite bulletSprite;
    int volleyNum = 0;
    bool top;
    
    void takeDamage(float damage)
    {
        changeBar = true;
        health = health - damage;
        if (health <= 0)
            life=0;
        
    }

    void enemySpawn(std::vector<Sprite> bulletSpriteList, int ScreenW, int ScreenH)
    {
        screenH = ScreenH;
        screenW = ScreenW;
        bulletSprite = bulletSpriteList[2];
        enemyType = pirateTurret;
        bulletsPassThrough = false;
    }
    
    void setTop (bool Top)
    {
        top = Top;
    }
    
    Bullet* enemyFire(int type, int X, int Y, bool right = false, bool up = true, float cone = 1)
    {
        if (type == 1)
        {
            DarkBullet *b1 = new DarkBullet();
            b1->settings(bulletSprite,X,Y,15, 15, angle, 3);
            b1->createBullet (10, 1000); 
            return b1;
        }
        else if (type == 2)
        {
            DiagonalBullet *b1 = new DiagonalBullet(right, up, cone);
            b1->settings(bulletSprite,X, Y,5, 5, angle, 3);
            b1->createBullet (10, 250);
            return b1;  
                           
        }
        return NULL;
        
    }
    
    void enemyAttack(std::vector<Bullet*> *bulletList, std::vector<Entity*> *entities, bool advanceTick)
    {
        
        if (ticksSinceLastFire == firerate)
        { 
            Bullet *b1;
            Bullet *b2;
            if (attackPattern <= 1)
            {
                b1 = enemyFire(1, x, y - 10);
                b2 = enemyFire(1, x, y + 15);
                entities->push_back(b1);                
                bulletList->push_back(b1); 
                entities->push_back(b2);                
                bulletList->push_back(b2); 
                ticksSinceLastFire = 0; 

                if (volleyNum < 4)
                {
                    volleyNum++;
                    ticksSinceLastFire = firerate - 10;
                }
                else
                {
                    ticksSinceLastFire = 0;
                    attackPattern++;
                    volleyNum = 0;
                }
            }
            else
            { 
                if (volleyNum == 0){
                    b1 = enemyFire(2, x, y - 10, false, top, 0.5);
                    b2 = enemyFire(2, x, y + 15, false, top, 0.5);}
                else if (volleyNum == 1){
                    b1 = enemyFire(2, x, y - 10, false, top);
                    b2 = enemyFire(2, x, y + 15, false, top);}
                else if (volleyNum == 2){
                    b1 = enemyFire(2, x, y - 10, false, top, 2);
                    b2 = enemyFire(2, x, y + 15, false, top, 2);}
                else if (volleyNum == 2){
                    b1 = enemyFire(1, x, y - 10);
                    b2 = enemyFire(1, x, y + 15);}
                else if (volleyNum == 3){
                    b1 = enemyFire(2, x, y - 10, false, !top);
                    b2 = enemyFire(2, x, y + 15, false, !top);}
                else if (volleyNum == 4){
                    b1 = enemyFire(2, x, y - 10, false, !top, 0.5);
                    b2 = enemyFire(2, x, y + 15, false, !top, 0.5);}
                else if (volleyNum == 5){
                    b1 = enemyFire(2, x, y - 10, false, !top, 0.25);
                    b2 = enemyFire(2, x, y + 15, false, !top, 0.25);}
                    
                entities->push_back(b1);                
                bulletList->push_back(b1); 
                entities->push_back(b2);                
                bulletList->push_back(b2); 
                    
                ticksSinceLastFire = 0; 
                if (volleyNum < 5)
                {
                    volleyNum++;
                    ticksSinceLastFire = firerate - 10;
                }
                else
                {
                    ticksSinceLastFire = 0;
                    attackPattern = 0;
                    volleyNum = 0;
                }
        
     
            
            }
        }
        else if (advanceTick)
            ticksSinceLastFire++;                   
    }
    

};

class PirateTurret2: public Boss
{
    public:
    bool movingUp = true;
    Sprite bulletSprite;
    int volleyNum = 0;
    
    void takeDamage(float damage)
    {
        changeBar = true;
        health = health - damage;
        if (health <= 0)
            life=0;
        
    }

    void enemySpawn(std::vector<Sprite> bulletSpriteList, int ScreenW, int ScreenH)
    {
        screenH = ScreenH;
        screenW = ScreenW;
        bulletSprite = bulletSpriteList[5];
        enemyType = pirateTurret2;
        bulletsPassThrough = false;
    }
    
    Bullet* enemyFire(int type, int X, int Y, bool right = false, bool up = true, int cone = 1)
    {
        if (type == 1)
        {
            DarkBullet *b1 = new DarkBullet();
            b1->settings(bulletSprite,X,Y,45, 135, angle, 3);
            b1->createBullet (20, 500); 
            return b1;
        }
        return NULL;
        
    }
    
    void enemyAttack(std::vector<Bullet*> *bulletList, std::vector<Entity*> *entities, bool advanceTick)
    {
        
        if (ticksSinceLastFire == firerate)
        { 
            Bullet *b1;
            if (attackPattern <= 1)
            {
                b1 = enemyFire(1, x, y);
                entities->push_back(b1);                
                bulletList->push_back(b1); 
                ticksSinceLastFire = 0; 

                    ticksSinceLastFire = 0;
            }
            
        }
        else if (advanceTick)
            ticksSinceLastFire++;                   
    }
    

};
