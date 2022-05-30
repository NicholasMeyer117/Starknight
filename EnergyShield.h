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

class EnergyShield: public Actor
{
    public:
    sf::CircleShape shieldShape;
    Enemy *enemy;
    
    void takeDamage(float damage)
    {
        health = health - damage;
        if (health <= 0)
            life=0;
    }

    void createShield(int x, int y, int r, Enemy *newEnemy)
    {
        enemy = newEnemy;
        shieldShape.setPosition(x, y);
        shieldShape.setRadius(r);
        shieldShape.setOrigin(r, r);
        shieldShape.setPointCount(100);
        shieldShape.setOutlineThickness(5);
        shieldShape.setOutlineColor(sf::Color(0, 255, 255, 200));
        shieldShape.setFillColor(sf::Color(0, 255, 255, 100));
        
    }
    
    


};
