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

class Bullet: public Entity
{
   public:
   float damage; 
   float bulletSpeed;

   void createBullet(float Damage, float BulletSpeed)
   {
       damage = Damage;
       bulletSpeed = BulletSpeed;
   }


};

class NormalBullet: public Bullet
{
    public:
    
    void update()
    {
        x += bulletSpeed;
        if (x>2000 || x<-1000) life=0;
    
    }

};


class DarkBullet: public Bullet
{

    public:
    
    void update()
    {
        x -= bulletSpeed;
    
    }

};

class DiagonalBullet: public Bullet
{
    public: 
    bool right; //1: right, 0: left
    bool up; //1: up, 0: down
    //1, 1 = diaginol up and right
    
    void direction(bool Right, bool Up)
    {
        right = Right;
        up = Up;
    }
    
    void update()
    {
        if (right)
            x+=bulletSpeed*4;
        else
            x-=bulletSpeed*4;
        if (up)
            y-=bulletSpeed;
        else
            y+=bulletSpeed;
        
    
    }
    
    
    

};
