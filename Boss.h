#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "Enemy.h"

class Boss: public Enemy
{
    public:
    std::vector<Enemy*> Parts;
    
};

class PirateLord: public Boss
{
    public:
    bool movingUp = true;
    Sprite bulletSprite;
    
    void takeDamage(int damage)
    {
        health = health - damage;
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
    }
    
    void setTurretPositions()
    {

        Parts[0]->sprite.setPosition(x, y);
        Parts[1]->sprite.setPosition(x, y + 135);
        Parts[2]->sprite.setPosition(x, y - 135);

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
    
    void ability(std::vector<Enemy*> enemyList, std::vector<Bullet*> *bulletList, RenderWindow &window)
    {
        setTurretPositions();
        for (int i = 0; i < Parts.size(); i++)
        {
            //cout << "turret: " + std::to_string(i);
            //cout << "spriteX: " + std::to_string(Parts[i]->sprite.getPosition().x);
            window.draw(Parts[i]->sprite); 
        }  
    }

};

class PirateTurret: public Boss
{
    bool movingUp = true;
    Sprite bulletSprite;
    
    void takeDamage(int damage)
    {
        health = health - damage;
        if (health <= 0)
            life=0;
    }

    void enemySpawn(Sprite BulletSprite, int ScreenW, int ScreenH)
    {
        screenH = ScreenH;
        screenW = ScreenW;
        //sprite.setPosition(screenW, screenH/2);
        //setActorPosition(screenW, screenH/2);
        bulletSprite = BulletSprite;
        enemyType = pirateTurret;
        bulletsPassThrough = false;
    }
    
    



};
