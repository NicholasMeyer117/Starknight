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
#include "AOE.h"
#define PI 3.14159265

class Attachment
{
    public:
    int firerate; //ticks per activation
    float baseDamage, baseShotSpeed, baseFirerate, baseRadius, baseAoeDamage;
    float damage, shotSpeed, radius, aoeDamage;
    bool passive; //true = provides passive effect, false = provides effect on tick
    int credits; //cost
    int attachNum; //0 = cannon, etc. Used for identification
    int num = 1; //number of attachments. 2 for level 2, 3 for level 3
    int level = 1; //current level
    int ticksSinceLastFire = 0;
    enum attachClass {Gun, Repair, Utility, Seeker, Aoe, Support, Bleeder, Merchant, Orbital, Summoner, Chainer, Manipulator};
    string name;
    std::vector<attachClass> classList;
    sf::Sound sound;
    sf::SoundBuffer soundBuffer;
    Sprite bulletSprite;
    
    
    virtual void activate(std::vector<Entity*> *entities, std::vector<Bullet*> *bulletList, Actor *player){}
    
    virtual void activate(std::vector<AOE*> *AOElist, Actor *player){}
    
    virtual void upgrade(){}



}; 

class Cannon: public Attachment
{
    public:
    std::vector<Bullet*> personalBulletList;
    
    Cannon(Sprite BulletSprite)
    {
        classList.push_back(Gun);
        name = "Cannon";
        baseFirerate = 60;
        credits = 5;
        baseDamage = 5;
        baseAoeDamage = 2;
        baseRadius = 100;
        baseShotSpeed = 1000;
        attachNum = 0;
        
        soundBuffer.loadFromFile("sounds/laser.wav");
        sound.setBuffer(soundBuffer);
        bulletSprite = BulletSprite;
    }
    
    
    void activate(std::vector<Entity*> *entities, std::vector<Bullet*> *bulletList, Actor *player)
    {
        damage = baseDamage * player->damageMult;
        shotSpeed = baseShotSpeed*player->bulletSpeedMult;
        firerate = baseFirerate / player->fireRateMult;
        if (ticksSinceLastFire == firerate)
        {
            ticksSinceLastFire = 0;
            NormalBullet *b = new NormalBullet();
            b->settings(bulletSprite,player->x + 15,player->y,5, 5, 0, 5);
            b->createBullet (damage, shotSpeed);
            entities->push_back(b);
            bulletList->push_back(b);
            personalBulletList.push_back(b);
            sound.play();
            
        }
        else
        {
            ticksSinceLastFire++;
        }
        
    }
    
    void activate(std::vector<AOE*> *AOElist, Actor *player)
    {
        radius = baseRadius * player->aoeRadiusMult;
        aoeDamage = baseAoeDamage;
        for (int i = 0; i < personalBulletList.size(); i++)
        {
            if (personalBulletList.at(i)->life == 0 and level == 3)
            {
                cout << "bullet dead\n";
                cout << "explosion at: " << personalBulletList.at(i)->x << "," << personalBulletList.at(i)->y;
                Explosion *explosion = new Explosion(radius, false, sf::Color(255, 0, 0, 100), aoeDamage);
                explosion -> createActor(0, 0, 0, 0, false, 0);
                explosion -> noSpriteSettings(personalBulletList.at(i)->x,personalBulletList.at(i)->y,0,0, sf::Color(0, 0, 0, 100));
                //explosion->circleSpriteSettings(personalBulletList.at(i)->x,personalBulletList.at(i)->y,sf::Color(0, 255, 255, 100), 100);
                //explosion->setPosition(personalBulletList.at(i)->x,personalBulletList.at(i)->y);
                explosion->AOEcircle.setPosition(personalBulletList.at(i)->x,personalBulletList.at(i)->y);
                AOElist->push_back(explosion);
                personalBulletList.erase(personalBulletList.begin()+i);
                //entities->push_back(explosion);
            }
        
        }
    }
    
    void upgrade()
    {
        if (level < 3)
        {
            level++;
            if (level == 2)
                baseFirerate = baseFirerate/1.5;
            else if (level == 3)
                classList.push_back(Aoe);
            baseDamage = baseDamage*1.5;
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
        baseFirerate = 15;
        credits = 5;
        baseDamage = 2;
        baseShotSpeed = 1250;
        attachNum = 1;
        
        soundBuffer.loadFromFile("sounds/laser.wav");
        sound.setBuffer(soundBuffer);
        bulletSprite = BulletSprite;
        
    }
    
    void activate(std::vector<Entity*> *entities, std::vector<Bullet*> *bulletList, Actor *player)
    {
        damage = baseDamage * player->damageMult;
        shotSpeed = baseShotSpeed*player->bulletSpeedMult;
        firerate = baseFirerate / player->fireRateMult;
        if (ticksSinceLastFire == firerate)
        {
            ticksSinceLastFire = 0;
            NormalBullet *b = new NormalBullet();
            b->settings(bulletSprite,player->x + 15,player->y,5, 5, 0, 5);
            b->createBullet (damage, shotSpeed);
            entities->push_back(b);
            bulletList->push_back(b);
            sound.play();
            
        }
        else
        {
            ticksSinceLastFire++;
        }
    }
    
    void upgrade()
    {
        num++;
        if ((level == 1 and num == 2) or (level == 2 and num == 3))
        {
            level++;
            baseFirerate = baseFirerate/1.5;
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
        baseFirerate = 300;
        credits = 5;
        baseDamage = 5;
        soundBuffer.loadFromFile("sounds/heal.wav");
        sound.setBuffer(soundBuffer);
        attachNum = 2;

    }

    
    void activate(std::vector<Entity*> *entities, std::vector<Bullet*> *bulletList, Actor *player)
    {
        damage = baseDamage * player->healingMult;
        firerate = baseFirerate / player->fireRateMult;
        if (ticksSinceLastFire == firerate)
        {
            ticksSinceLastFire = 0;
            if (player->health < player->maxHealth)
            {
                player->health+=damage;
                sound.play();
            }
            
        }
        else
        {
            ticksSinceLastFire++;
        
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
        baseFirerate = 75;
        baseDamage = 5;
        baseShotSpeed = 1000;
        soundBuffer.loadFromFile("sounds/laser.wav");
        sound.setBuffer(soundBuffer);
        bulletSprite = BulletSprite;
        attachNum = 3;

    }

    
    void activate(std::vector<Entity*> *entities, std::vector<Bullet*> *bulletList, Actor *player)
    {
        damage = baseDamage * player->damageMult;
        shotSpeed = baseShotSpeed*player->bulletSpeedMult;
        firerate = baseFirerate / player->fireRateMult;
        if (ticksSinceLastFire == firerate)
        {
            ticksSinceLastFire = 0;
            SiphonBullet *b = new SiphonBullet();
            b->settings(bulletSprite,player->x + 15,player->y,5, 5, 0, 5);
            b->createBullet (damage, shotSpeed);
            entities->push_back(b);
            bulletList->push_back(b);
            sound.play();
            
        }
        else
           ticksSinceLastFire++;
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
        baseFirerate = 120;
        credits = 5;
        baseDamage = 5;
        baseShotSpeed = 750;
        attachNum = 4;
        
        
        soundBuffer.loadFromFile("sounds/laser.wav");
        sound.setBuffer(soundBuffer);
        bulletSprite = BulletSprite;
        
    }
    
    void activate(std::vector<Entity*> *entities, std::vector<Bullet*> *bulletList, Actor *player)
    {
        float diagShotSpeed = 187.5 * player->bulletSpeedMult;
        shotSpeed = baseShotSpeed * player->bulletSpeedMult;
        damage = baseDamage * player->damageMult;
        firerate = baseFirerate / player->fireRateMult;
        if (ticksSinceLastFire == firerate)
        {
            ticksSinceLastFire = 0;
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
        else
            ticksSinceLastFire++;
            
    }
    
    void upgrade()
    {
        num++;
        if ((level == 1 and num == 2) or (level == 2 and num == 3))
        {
            level++;
            baseFirerate = baseFirerate/1.5;
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
        baseFirerate = 60;
        baseDamage = 2;
        baseShotSpeed = 750;
        attachNum = 8;
        
        bulletSprite = BulletSprite;
    
    }
    
    void activate(std::vector<Entity*> *entities, std::vector<Bullet*> *bulletList, Actor *player)
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
        firerate = baseFirerate / player->fireRateMult;
        if (ticksSinceLastFire == firerate)
        {
            ticksSinceLastFire = 0;
            SeekerBullet *b = new SeekerBullet(enemies);
            b->settings(bulletSprite,player->x + 15,player->y,5, 5, 0, 5);
            b->createBullet (damage, shotSpeed);
            entities->push_back(b);
            bulletList->push_back(b);
            sound.play();
        
            enemies.clear();
        }
        else
            ticksSinceLastFire++;
    
    
    }
    
    void upgrade()
    {
        num++;
        if ((level == 1 and num == 2) or (level == 2 and num == 3))
        {
            level++;
            baseFirerate = baseFirerate/1.5;
            baseDamage = baseDamage + 2;
            credits = credits*2;
        }
    }
    

};

class VoidBomber: public Attachment
{
    public:
    VoidBomber()
    {
        classList.push_back(Aoe);
        name = "Void Bomber";
        baseFirerate = 180;
        credits = 5;
        baseDamage = 0;
        baseShotSpeed = 750;
        baseRadius = 50;
        attachNum = 9;
        
        soundBuffer.loadFromFile("sounds/laser.wav");
        sound.setBuffer(soundBuffer);
    }
    
    void activate(std::vector<AOE*> *AOElist, Actor *player)
    {
        shotSpeed = baseShotSpeed*player->bulletSpeedMult;
        firerate = baseFirerate / player->fireRateMult;
        radius = baseRadius * player->aoeRadiusMult;
        if (ticksSinceLastFire == firerate)
        {
            ticksSinceLastFire = 0;
            SolidCircle *solidCircle = new SolidCircle(radius, true, sf::Color(0, 0, 0, 100), 0);
            solidCircle -> noSpriteSettings(player->x,player->y,0,0, sf::Color(0, 0, 0, 100));
            solidCircle -> createActor(0, 0, shotSpeed, 0, false, 0);
            solidCircle->AOEcircle.setPosition(player->x,player->y);
            AOElist->push_back(solidCircle);
            
        }
        else
        {
            ticksSinceLastFire++;
        }

    }
    
    void upgrade()
    {
        if (level < 3)
        {
            level++;
            if (level == 2)
                baseRadius = baseRadius * 1.5;
            else if (level == 3)
            {
                baseFirerate = baseFirerate/1.5;
                baseShotSpeed = baseShotSpeed/1.5;
            }
            credits = credits*2;
        }
    }
};

class SeekerMissile: public Attachment
{
    public:
    std::vector<Bullet*> personalBulletList;
    
    SeekerMissile(Sprite BulletSprite)
    {
        name = "Seeker Missile";
        classList.push_back(Seeker);
        classList.push_back(Aoe);
        credits = 10;
        baseFirerate = 180;
        baseDamage = 10;
        baseAoeDamage = 5;
        baseShotSpeed = 500;
        baseRadius = 100;
        attachNum = 10;
        
        bulletSprite = BulletSprite;
    
    }
    
    void activate(std::vector<Entity*> *entities, std::vector<Bullet*> *bulletList, Actor *player)
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
        firerate = baseFirerate / player->fireRateMult;
        //radius = baseRadius;
        //aoeDamage = baseAoeDamage;
        if (ticksSinceLastFire == firerate)
        {
            ticksSinceLastFire = 0;
            SeekerBullet *b = new SeekerBullet(enemies);
            b->settings(bulletSprite,player->x + 15,player->y,5, 5, 0, 5);
            b->createBullet (damage, shotSpeed);
            entities->push_back(b);
            bulletList->push_back(b);
            personalBulletList.push_back(b);
            sound.play();
        
            enemies.clear();
        }
        else
            ticksSinceLastFire++;
    
    
    }
    
    void activate(std::vector<AOE*> *AOElist, Actor *player)
    {
        radius = baseRadius * player->aoeRadiusMult;
        aoeDamage = baseAoeDamage;
        for (int i = 0; i < personalBulletList.size(); i++)
        {
            if (personalBulletList.at(i)->life == 0)
            {
                cout << "bullet dead\n";
                cout << "explosion at: " << personalBulletList.at(i)->x << "," << personalBulletList.at(i)->y;
                Explosion *explosion = new Explosion(radius, false, sf::Color(255, 0, 0, 100), aoeDamage);
                explosion -> noSpriteSettings(personalBulletList.at(i)->x,personalBulletList.at(i)->y,0,0, sf::Color(0, 0, 0, 100));
                explosion -> createActor(0, 0, 0, 0, false, 0);
                explosion->AOEcircle.setPosition(personalBulletList.at(i)->x,personalBulletList.at(i)->y);
                AOElist->push_back(explosion);
                personalBulletList.erase(personalBulletList.begin()+i);
            }
        
        }
    }
    
    void upgrade()
    {
        if (level < 3)
        {
            level++;
            if (level == 2)
            {
                baseDamage = baseDamage * 1.5;
                baseAoeDamage = baseAoeDamage * 1.5;
            }
            else if (level == 3)
            {
                baseFirerate = baseFirerate/1.5;
                baseRadius = baseRadius*1.5;
            }
            credits = credits*2;
        }
    }



};


