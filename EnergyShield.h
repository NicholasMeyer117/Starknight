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
    sf::CircleShape circle;
    Enemy *enemy;
    
    void takeDamage(float damage)
    {
        health = health - damage;
        if (health <= 0)
            life=0;
    }

    void createShield(int x, int y, int r, Enemy *newEnemy)
    {
        cout << "Shield Created";
        enemy = newEnemy;
        circle.setPosition(x, y);
        circle.setRadius(r);
        circle.setOrigin(r, r);
        circle.setPointCount(100);
        circle.setOutlineThickness(10);
        circle.setOutlineColor(sf::Color::Cyan);
        circle.setFillColor(sf::Color::Transparent);
    }
    
    


};
