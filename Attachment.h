#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <list>
#include <math.h>
#include <cstring>
#include "Entity.h"
#include "Actor.h"
#include "Bullets.h"
#define PI 3.14159265

class Attachment
{
    public:
    int firerate; //ticks per activation
    bool passive; //true = provides passive effect, false = provides effect on tick
    int credits; //cost
    int level = 1; //current level
    enum attachClass {Gun, Repair, Utility, Seeker, AOE, Support, Bleeder, Merchant, Orbital, Summoner, Chainer, Manipulator};
    String name;
    std::vector<attachClass> classList;
    sf::Sound sound;
    sf::SoundBuffer soundBuffer;
    Sprite bulletSprite;
    
    virtual void createAttachment(){}
    
    virtual void activate(int tick, std::vector<Entity*> *entities, std::vector<Bullet*> *bulletList, Actor *player){}
    
    virtual void upgrade(){}



}; 

class Cannon: public Attachment
{
    public:
    
    void createAttachment(Sprite BulletSprite)
    {
        classList.push_back(Gun);
        name = "Cannon";
        firerate = 60;
        credits = 5;
        
        soundBuffer.loadFromFile("sounds/laser.wav");
        sound.setBuffer(soundBuffer);
        bulletSprite = BulletSprite;
        
    }
    
    void activate(int tick, std::vector<Entity*> *entities, std::vector<Bullet*> *bulletList, Actor *player)
    {
        if (tick%firerate == 0)
        {
            NormalBullet *b = new NormalBullet();
            b->settings(bulletSprite,player->x + 5,player->y,5, 5, 0, 5);
            b->createBullet (5, 20);
            entities->push_back(b);
            bulletList->push_back(b);
            sound.play();
            
        }
    }
};

class MachineGun: public Attachment
{
    public:
    
    void createAttachment(Sprite BulletSprite)
    {
        classList.push_back(Gun);
        name = "Machine Gun";
        firerate = 15;
        credits = 5;
        
        soundBuffer.loadFromFile("sounds/laser.wav");
        sound.setBuffer(soundBuffer);
        bulletSprite = BulletSprite;
        
    }
    
    void activate(int tick, std::vector<Entity*> *entities, std::vector<Bullet*> *bulletList, Actor *player)
    {
        if (tick%firerate == 0)
        {
            NormalBullet *b = new NormalBullet();
            b->settings(bulletSprite,player->x + 5,player->y,5, 5, 0, 5);
            b->createBullet (2, 25);
            entities->push_back(b);
            bulletList->push_back(b);
            sound.play();
            
        }
    }
};

class RepairDroid: public Attachment
{
    public:
    
    void createAttachment()
    {
        name = "Repair Droid";
        classList.push_back(Repair);
        firerate = 300;
        soundBuffer.loadFromFile("sounds/heal.wav");
        sound.setBuffer(soundBuffer);

    }

    
    void activate(int tick, std::vector<Entity*> *entities, std::vector<Bullet*> *bulletList, Actor *player)
    {
        if (tick%firerate == 0)
        {
            cout << "check heal";
            if (player->health < player->maxHealth)
            {
                cout << "Heal!";
                player->health+=5;
                sound.play();
            }
            
        }
    }


};

class SiphonDroid: public Attachment
{
    public:
    
    void createAttachment(Sprite BulletSprite)
    {
        name = "Siphon Droid";
        classList.push_back(Repair);
        classList.push_back(Gun);
        firerate = 75;
        soundBuffer.loadFromFile("sounds/laser.wav");
        sound.setBuffer(soundBuffer);
        bulletSprite = BulletSprite;

    }

    
    void activate(int tick, std::vector<Entity*> *entities, std::vector<Bullet*> *bulletList, Actor *player)
    {
        if (tick%firerate == 0)
        {
            SiphonBullet *b = new SiphonBullet();
            b->settings(bulletSprite,player->x + 5,player->y,5, 5, 0, 5);
            b->createBullet (5, 20);
            entities->push_back(b);
            bulletList->push_back(b);
            sound.play();
            
        }
    }


};
