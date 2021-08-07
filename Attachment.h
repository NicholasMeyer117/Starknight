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
    float damage;
    bool passive; //true = provides passive effect, false = provides effect on tick
    int credits; //cost
    int num = 1; //number of attachments. 2 for level 2, 3 for level 3
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
        damage = 5;
        
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
            b->createBullet (damage, 20);
            entities->push_back(b);
            bulletList->push_back(b);
            sound.play();
            
        }
    }
    
    void upgrade()
    {
        num++;
        if ((level == 1 and num == 2) or (level == 2 and num == 3))
        {
            level++;
            firerate = firerate/2;
            damage = damage*2;
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
        damage = 2;
        
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
            b->createBullet (damage, 25);
            entities->push_back(b);
            bulletList->push_back(b);
            sound.play();
            
        }
    }
    
    void upgrade()
    {
        num++;
        if ((level == 1 and num == 2) or (level == 2 and num == 3))
        {
            level++;
            firerate = firerate/1.5;
            damage = damage*1.5;
        }
    }
};

class Shotgun: public Attachment
{
    public:
    int cone = 1;
    
    void createAttachment(Sprite BulletSprite)
    {
        classList.push_back(Gun);
        name = "Shotgun";
        firerate = 120;
        credits = 5;
        damage = 5;
        
        
        soundBuffer.loadFromFile("sounds/laser.wav");
        sound.setBuffer(soundBuffer);
        bulletSprite = BulletSprite;
        
    }
    
    void activate(int tick, std::vector<Entity*> *entities, std::vector<Bullet*> *bulletList, Actor *player)
    {
        if (tick%firerate == 0)
        {
            DiagonalBullet *b1 = new DiagonalBullet();
            b1->settings(bulletSprite,player->x + 5,player->y,5, 5, 0, 5);
            b1->createBullet (damage, 3.75);
            b1->direction (true, true, cone);
            entities->push_back(b1);
            bulletList->push_back(b1);
            
            DiagonalBullet *b2 = new DiagonalBullet();
            b2->settings(bulletSprite,player->x + 5,player->y,5, 5, 0, 5);
            b2->createBullet (damage, 3.75);
            b2->direction (true, false, cone);
            entities->push_back(b2);
            bulletList->push_back(b2);
            
            NormalBullet *b3 = new NormalBullet();
            b3->settings(bulletSprite,player->x + 5,player->y,5, 5, 0, 5);
            b3->createBullet (damage, 15);
            entities->push_back(b3);
            bulletList->push_back(b3);
            sound.play();
            
            if (level == 3)
            {
                DiagonalBullet *b3 = new DiagonalBullet();
                b3->settings(bulletSprite,player->x + 5,player->y,5, 5, 0, 5);
                b3->createBullet (damage, 3.75);
                b3->direction (true, true, cone/2);
                entities->push_back(b3);
                bulletList->push_back(b3);
            
                DiagonalBullet *b4 = new DiagonalBullet();
                b4->settings(bulletSprite,player->x + 5,player->y,5, 5, 0, 5);
                b4->createBullet (damage, 3.75);
                b4->direction (true, false, cone/2);
                entities->push_back(b4);
                bulletList->push_back(b4);
            
            
            }
            
        }
    }
    
    void upgrade()
    {
        num++;
        if ((level == 1 and num == 2) or (level == 2 and num == 3))
        {
            level++;
            firerate = firerate/1.5;
            damage = damage*2;
            cone = cone*2;
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
        damage = 5;
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
                player->health+=damage;
                sound.play();
            }
            
        }
    }
    
    void upgrade()
    {
        num++;
        if ((level == 1 and num == 2) or (level == 2 and num == 3))
        {
            level++;
            damage = damage*2;
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
        damage = 5;
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
            b->createBullet (damage, 20);
            entities->push_back(b);
            bulletList->push_back(b);
            sound.play();
            
        }
    }
    
    void upgrade()
    {
        num++;
        if ((level == 1 and num == 2) or (level == 2 and num == 3))
        {
            level++;
            damage = damage*2;
        }
    }


};
