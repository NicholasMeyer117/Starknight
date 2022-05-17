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
#include "Bullets.h"
#include "Actor.h"
#define PI 3.14159265

class Enemy: public Actor
{
    public:
    bool reachedBegin = false;
    int ticksSinceLastFire = 0;
    enum EnemyType {darkFighter, triShooter, doubleShooter, shielder, pirateLord, pirateTurret, pirateTurret2, swarmer, swarmSpitter, machineGunner};
    EnemyType enemyType;
    int bulletsPassThrough = false;
    int screenH;
    int screenW;
    int relUnitX;
    int relUnitY;
    
    virtual void takeDamage(float damage){}
    
    virtual void enemySpawn(std::vector<Sprite> BulletSpriteList, int ScreenW, int ScreenH){}
    
    virtual void enemyMove(float elapsed){}
    
    virtual void enemyAttack(std::vector<Bullet*> *bulletList, std::vector<Entity*> *entities){}
    
    virtual void ability(std::vector<Enemy*> enemyList, std::vector<Bullet*> *bulletList, RenderWindow &window){}
    

};
