#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <list>
#include <math.h>
#include <cstring>
#include "Entity.h"
#include "Actor.h"
#include "Enemy.h"
#define PI 3.14159265

class AOE: public Actor
{
    public:
    bool isMoving;
    sf::Color color;
    sf::CircleShape AOEcircle;
    float baseDamage;
    
    AOE(int r, bool IsMoving, sf::Color Color, float BaseDamage)
    {
        isMoving = IsMoving;
        color = Color;
        AOEcircle.setRadius(r);
        AOEcircle.setOrigin(r, r);
        AOEcircle.setPointCount(100);
        //circle.setOutlineThickness(5);
        //circle.setOutlineColor(sf::Color(0, 255, 255, 200));
        AOEcircle.setFillColor(color);
        
        baseDamage = BaseDamage;
    }
    
    virtual void checkDamage(std::vector<Enemy*> *enemyList){};
    virtual void checkBullets(std::vector<Bullet*> *bulletList){};
    virtual void AoeUpdate(float elapsed){};
    
    

};

class SolidCircle: public AOE
{
    public:
    SolidCircle(int r, bool IsMoving, sf::Color color, float BaseDamage) : AOE(r, IsMoving, color, BaseDamage) 
    {
        visible = true;
    }
    
    void AoeUpdate(float elapsed)
    {
    
        moveActor(right);
        AOEcircle.setPosition(xPos,yPos);
        if (x>2000 || x<-1000) life=0;

    }
    
    void checkBullets(std::vector<Bullet*> *bulletList)
    {
        for (int i = 0; i < bulletList->size(); i++)
        {
            if (bulletList->at(i)->isSpriteCollideWithCircle(AOEcircle))
            {
                bulletList->at(i) -> life = 0;
            }
            
        }
    
    }
    

};

class Explosion: public AOE
{
    public:
    int ticksSinceLastFlick = 0;
    int numOfFlicks = 0;
    bool damageDealt = false;
    
    Explosion(int r, bool IsMoving, sf::Color color, float BaseDamage) : AOE(r, IsMoving, color, BaseDamage) {}   // Call the superclass constructor in the subclass' initialization list.
    
    void AoeUpdate(float elapsed)
    {
    
        //AOEcircle.setPosition(xPos,yPos);
        if (ticksSinceLastFlick < 2)
            ticksSinceLastFlick++;
        else
        {
            visible = not visible;
            ticksSinceLastFlick = 0;
            numOfFlicks++;
        }
        
        if (numOfFlicks == 6)
            life = 0;

    }
    
    void checkDamage(std::vector<Enemy*> *enemyList)
    {
        float damage = baseDamage * damageMult;
        if (damageDealt == false)
        {
            damageDealt = true;
            for (int i = 0; i < enemyList->size(); i++)
            {
                if (enemyList->at(i)->isSpriteCollideWithCircle(AOEcircle))
                {
                    enemyList->at(i) -> takeDamage(damage);
                    enemyList->at(i) -> isHit = true;
                }
            }
        }
    
    }
    
};
