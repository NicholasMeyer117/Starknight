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
    float baseDamage, baseShotSpeed;
    float damage, shotSpeed;
    bool passive; //true = provides passive effect, false = provides effect on tick
    int credits; //cost
    int attachNum; //0 = cannon, etc. Used for identification
    int num = 1; //number of attachments. 2 for level 2, 3 for level 3
    int level = 1; //current level
    enum attachClass {Gun, Repair, Utility, Seeker, AOE, Support, Bleeder, Merchant, Orbital, Summoner, Chainer, Manipulator};
    string name;
    std::vector<attachClass> classList;
    sf::Sound sound;
    sf::SoundBuffer soundBuffer;
    Sprite bulletSprite;
    
    
    virtual void activate(int tick, std::vector<Entity*> *entities, std::vector<Bullet*> *bulletList, Actor *player){}
    
    virtual void upgrade(){}



}; 

class Cannon: public Attachment
{
    public:
    
    Cannon(Sprite BulletSprite)
    {
        classList.push_back(Gun);
        name = "Cannon";
        firerate = 60;
        credits = 5;
        baseDamage = 5;
        baseShotSpeed = 20;
        attachNum = 0;
        
        soundBuffer.loadFromFile("sounds/laser.wav");
        sound.setBuffer(soundBuffer);
        bulletSprite = BulletSprite;
    }
    
    
    void activate(int tick, std::vector<Entity*> *entities, std::vector<Bullet*> *bulletList, Actor *player)
    {
        damage = baseDamage * player->damageMult;
        shotSpeed = baseShotSpeed*player->bulletSpeedMult;
        if (tick%firerate == 0)
        {
            NormalBullet *b = new NormalBullet();
            b->settings(bulletSprite,player->x + 15,player->y,5, 5, 0, 5);
            b->createBullet (damage, shotSpeed);
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
            baseDamage = baseDamage*2;
            credits = credits*2;
        }
    }
};

class MachineGun: public Attachment
{
    public:
    
    MachineGun(Sprite BulletSprite)
    {
        classList.push_back(Gun);
        name = "Machine Gun";
        firerate = 15;
        credits = 5;
        baseDamage = 2;
        baseShotSpeed = 25;
        attachNum = 1;
        
        soundBuffer.loadFromFile("sounds/laser.wav");
        sound.setBuffer(soundBuffer);
        bulletSprite = BulletSprite;
        
    }
    
    void activate(int tick, std::vector<Entity*> *entities, std::vector<Bullet*> *bulletList, Actor *player)
    {
        damage = baseDamage * player->damageMult;
        shotSpeed = baseShotSpeed*player->bulletSpeedMult;
        if (tick%firerate == 0)
        {
            NormalBullet *b = new NormalBullet();
            b->settings(bulletSprite,player->x + 15,player->y,5, 5, 0, 5);
            b->createBullet (damage, shotSpeed);
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
            baseDamage = baseDamage*1.5;
            credits = credits*2;
        }
    }
};

class RepairDroid: public Attachment
{
    public:
    
    RepairDroid()
    {
        name = "Repair Droid";
        classList.push_back(Repair);
        firerate = 300;
        credits = 5;
        baseDamage = 5;
        soundBuffer.loadFromFile("sounds/heal.wav");
        sound.setBuffer(soundBuffer);
        attachNum = 2;

    }

    
    void activate(int tick, std::vector<Entity*> *entities, std::vector<Bullet*> *bulletList, Actor *player)
    {
        damage = baseDamage * player->healingMult;
        if (tick%firerate == 0)
        {
            if (player->health < player->maxHealth)
            {
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
            credits = credits*2;
        }
    }

};

class SiphonDroid: public Attachment
{
    public:
    
    SiphonDroid(Sprite BulletSprite)
    {
        name = "Siphon Droid";
        classList.push_back(Repair);
        classList.push_back(Gun);
        credits = 10;
        firerate = 75;
        baseDamage = 5;
        baseShotSpeed = 20;
        soundBuffer.loadFromFile("sounds/laser.wav");
        sound.setBuffer(soundBuffer);
        bulletSprite = BulletSprite;
        attachNum = 3;

    }

    
    void activate(int tick, std::vector<Entity*> *entities, std::vector<Bullet*> *bulletList, Actor *player)
    {
        damage = baseDamage * player->damageMult;
        shotSpeed = baseShotSpeed*player->bulletSpeedMult;
        if (tick%firerate == 0)
        {
            SiphonBullet *b = new SiphonBullet();
            b->settings(bulletSprite,player->x + 15,player->y,5, 5, 0, 5);
            b->createBullet (damage, shotSpeed);
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
            baseDamage = baseDamage*2;
            credits = credits*2;
        }
    }


};

class Shotgun: public Attachment
{
    public:
    int cone = 1;
    
    Shotgun(Sprite BulletSprite)
    {
        classList.push_back(Gun);
        name = "Shotgun";
        firerate = 120;
        credits = 5;
        baseDamage = 5;
        baseShotSpeed = 15;
        attachNum = 4;
        
        
        soundBuffer.loadFromFile("sounds/laser.wav");
        sound.setBuffer(soundBuffer);
        bulletSprite = BulletSprite;
        
    }
    
    void activate(int tick, std::vector<Entity*> *entities, std::vector<Bullet*> *bulletList, Actor *player)
    {
        float diagShotSpeed = 3.75 * player->bulletSpeedMult;
        shotSpeed = baseShotSpeed * player->bulletSpeedMult;
        damage = baseDamage * player->damageMult;
        if (tick%firerate == 0)
        {
            DiagonalBullet *b1 = new DiagonalBullet(true, true, cone);
            b1->settings(bulletSprite,player->x + 15,player->y,5, 5, 0, 5);
            b1->createBullet (damage, diagShotSpeed);
            //b1->direction (true, true, cone);
            entities->push_back(b1);
            bulletList->push_back(b1);
            
            DiagonalBullet *b2 = new DiagonalBullet(true, false, cone);
            b2->settings(bulletSprite,player->x + 15,player->y,5, 5, 0, 5);
            b2->createBullet (damage, diagShotSpeed);
            //b2->direction (true, false, cone);
            entities->push_back(b2);
            bulletList->push_back(b2);
            
            NormalBullet *b3 = new NormalBullet();
            b3->settings(bulletSprite,player->x + 15,player->y,5, 5, 0, 5);
            b3->createBullet (damage, shotSpeed);
            entities->push_back(b3);
            bulletList->push_back(b3);
            sound.play();
            
            if (level == 3)
            {
                DiagonalBullet *b3 = new DiagonalBullet(true, true, cone/2);
                b3->settings(bulletSprite,player->x + 15,player->y,5, 5, 0, 5);
                b3->createBullet (damage, diagShotSpeed);
                //b3->direction (true, true, cone/2);
                entities->push_back(b3);
                bulletList->push_back(b3);
            
                DiagonalBullet *b4 = new DiagonalBullet(true, false, cone/2);
                b4->settings(bulletSprite,player->x + 15,player->y,5, 5, 0, 5);
                b4->createBullet (damage, diagShotSpeed);
                //b4->direction (true, false, cone/2);
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
            baseDamage = baseDamage*2;
            cone = cone*2;
            credits = credits*2;
        }
    }
};


class TimeDilator: public Attachment
{
    public: 
    
    TimeDilator()
    {
        name = "Time Dilator";
        classList.push_back(Manipulator);
        credits = 5;
        firerate = 0;
        baseDamage = 0.1; //Base Damage in this case is time modifier. 0.2 damage = 20% slower
        attachNum = 5;
    }
    
    void upgrade()
    {
        num++;
        if ((level == 1 and num == 2) or (level == 2 and num == 3))
        {
            level++;
            baseDamage = baseDamage*2;
            credits = credits*2;
        }
    }

};

class HullBooster: public Attachment
{
    public: 
    
    HullBooster()
    {
        name = "Hull Booster";
        classList.push_back(Utility);
        credits = 5;
        firerate = 0;
        baseDamage = 0.25; //Base Damage in this case is added HP percentage. 0.25 damage = 25% extra HP
        attachNum = 6;
    }
    
    void upgrade()
    {
        num++;
        if ((level == 1 and num == 2) or (level == 2 and num == 3))
        {
            level++;
            baseDamage = baseDamage*2;
            credits = credits*2;
        }
    }

};

class SpeedBooster: public Attachment
{
    public: 
    
    SpeedBooster()
    {
        name = "Speed Booster";
        classList.push_back(Utility);
        credits = 5;
        firerate = 0;
        baseDamage = 0.25; //Base Damage in this case is added HP percentage. 0.25 damage = 25% extra HP
        attachNum = 7;
    }
    
    void upgrade()
    {
        num++;
        if ((level == 1 and num == 2) or (level == 2 and num == 3))
        {
            level++;
            baseDamage = baseDamage*2;
            credits = credits*2;
        }
    }

};

class SeekerDart: public Attachment
{
    public:
    
    SeekerDart(Sprite BulletSprite)
    {
        name = "Seeker Dart";
        classList.push_back(Seeker);
        credits = 5;
        firerate = 60;
        baseDamage = 2;
        baseShotSpeed = 15;
        attachNum = 8;
        
        bulletSprite = BulletSprite;
    
    
    }
    
    void activate(int tick, std::vector<Entity*> *entities, std::vector<Bullet*> *bulletList, Actor *player)
    {
        std::vector<Entity*> enemies;
        for (int i = 0; i < entities->size(); i++)
        {
            Entity *curEntity = entities->at(i);
            if (curEntity->isActor and curEntity != player)
                enemies.push_back(curEntity);
        }
        
        shotSpeed = baseShotSpeed * player->bulletSpeedMult;
        damage = baseDamage * player->damageMult;
        if (tick%firerate == 0)
        {
    
            SeekerBullet *b = new SeekerBullet(enemies);
            b->settings(bulletSprite,player->x + 15,player->y,5, 5, 0, 5);
            b->createBullet (damage, shotSpeed);
            entities->push_back(b);
            bulletList->push_back(b);
            sound.play();
        
            enemies.clear();
        }
    
    
    }
    
    void upgrade()
    {
        num++;
        if ((level == 1 and num == 2) or (level == 2 and num == 3))
        {
            level++;
            firerate = firerate/1.5;
            baseDamage = baseDamage + 2;
            credits = credits*2;
        }
    }
    

};




