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
