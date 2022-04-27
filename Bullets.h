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
#define PI 3.14159265

//Bullets for player, allies, and enemies
class Bullet: public Entity
{
   public:
   float damage; 
   float bulletSpeed;

   //sets bullet stats
   void createBullet(float Damage, float BulletSpeed)
   {
       damage = Damage;
       bulletSpeed = BulletSpeed;
   }
   
   void checkIfDead()
   {
       if (x>2000 || x<-1000) life=0;
   }
   
   //special function in case bullet impact affects player
   virtual void onContact(Actor *player){}


};

//Bullet used by cannon and machine gun
class NormalBullet: public Bullet
{
    public:
    
    void update()
    {
        x += bulletSpeed;
        checkIfDead();
    
    }

};

class SiphonBullet: public Bullet
{
    
    public:
    
    void update()
    {
        x += bulletSpeed;
        checkIfDead();
    
    }

    void onContact(Actor *player)
    {
        if(player->health < player->maxHealth)
        {
            player->health+=damage;
        }
    }
};

//Bullet used by dark fighter and tri shooter
class DarkBullet: public Bullet
{

    public:
    
    void update()
    {
        
        x -= bulletSpeed;
        checkIfDead();
    }

};

class OrdinalBullet: public Bullet
{
    public:
    String dir;
    OrdinalBullet(String direction)
    {
        dir = direction;
    }
    
    void update()
    {
        if (dir=="right")
            x+=bulletSpeed;
        else if (dir=="left")
            x-=bulletSpeed;
        else if (dir=="up")
            y-=bulletSpeed;
        else if (dir=="down")
            y+=bulletSpeed;
            
        checkIfDead();

    }
    
};

//used by tri-shooter
class DiagonalBullet: public Bullet
{
    public: 
    bool right; //1: right, 0: left
    bool up; //1: up, 0: down
    float cone;
    //1, 1 = diaginol up and right
    
    DiagonalBullet(bool Right, bool Up, float Cone = 1)
    {
        right = Right;
        up = Up;
        cone = Cone;
    }
    
    void update()
    {
        if (right)
            x+=(bulletSpeed*4);
        else
            x-=(bulletSpeed*4);
        if (up)
            y-=(bulletSpeed/cone);
        else
            y+=(bulletSpeed/cone);
            
        checkIfDead();

    }
    
};

class BombBullet: public Bullet
{
    public:
    std::vector<Bullet*> subBulletList;
    int progressCounter;
    
    BombBullet()
    {
        progressCounter = rand() % 100 + 50;
    }
    void update()
    {
        if (progressCounter > 0)
        {
            x -= bulletSpeed;
            progressCounter--;
        }
        checkIfDead();
    }
    
};
