#pragma once
#include <string>
#include <iostream>
#include <array>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <list>
#include <math.h>
#include <cstring>
#include "Entity.h"
#include "Actor.h"
#include "Attachment.h"
#include "Enemy.h"
#include "Character.h"
//#include "ParticleSystem.h"
//#include "SynergyHandler.h"

using namespace std;

class ShopState: public State
{
    public:
    std::vector<Entity*> entities;
    std::vector<Button*> buttonList; //Vector of normal buttons
    std::vector<ShopButton*> shopButtonList; //Vector of Attachments available to buy
    std::vector<Texture> textureList; //Vector of used textures
    std::vector<Sprite> spriteList; //Vector of sprites
    std::vector<Sprite> bulletSpriteList; //Vector of bullet sprites?????
    std::vector<Attachment*> shopAttachments; //vector of ?
    std::vector<RectangleShape> slotRectangles; //Vector of black rect outlines for available attachments
    //std::vector<Sprite> attachmentSlotSprites; // ??
    std::vector<ImageButton*> attachmentSlotButtons; //Vector of buttons for equipped attachments
    Character *character = new Character;
    SynergyHandler *synergyHandler = new SynergyHandler;
    ParticleSystem *clickParticles = new ParticleSystem(500, 100, 5, 200, 2, Color::White);
    int screenW;
    int screenH;
    int relUnitX;
    int relUnitY;
    int numOfAttachments = 12; //total number of different attachments
    sf::Font gameFont;
    sf::Text source;
    
    void createState(Game *game)
    {
        screenW = game->screenWidth;
        screenH = game->screenHeight;
        relUnitX = game->relUnitX;
        relUnitY = game->relUnitY;
        source = game->source;
        gameFont = game->gameFont; 
        character = game->character;
        synergyHandler = game->synergyHandler;
        
        Texture t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12;
        t1.loadFromFile("images/cannon.png"); 
        textureList.push_back(t1);
        t2.loadFromFile("images/machineGun.png");
        textureList.push_back(t2);
        t3.loadFromFile("images/repairDroid.png");
        textureList.push_back(t3);
        t4.loadFromFile("images/siphonDroid.png");
        textureList.push_back(t4);
        t5.loadFromFile("images/shotgun.png");
        textureList.push_back(t5);
        t6.loadFromFile("images/timeDilator.png");
        textureList.push_back(t6);
        t7.loadFromFile("images/hullBooster.png");
        textureList.push_back(t7);
        t8.loadFromFile("images/speedBooster.png");
        textureList.push_back(t8);
        t9.loadFromFile("images/seekerDart.png");
        textureList.push_back(t9);
        t10.loadFromFile("images/voidBomber.png");
        textureList.push_back(t10);
        t11.loadFromFile("images/seekerMissile.png");
        textureList.push_back(t11);
        t12.loadFromFile("images/healingAura.png");
        textureList.push_back(t12);
        
        Texture i1, i2, i3, i4, i5, i6, i7, i8, i9, i10, i11, i12;
        i1.loadFromFile("images/cannon.png");
        textureList.push_back(i1);
        i2.loadFromFile("images/machineGun.png");
        textureList.push_back(i2);
        i3.loadFromFile("images/repairDroid.png");
        textureList.push_back(i3);
        i4.loadFromFile("images/siphonDroid.png");
        textureList.push_back(i4);
        i5.loadFromFile("images/shotgun.png");
        textureList.push_back(i5);
        i6.loadFromFile("images/timeDilator.png");
        textureList.push_back(i6);
        i7.loadFromFile("images/hullBooster.png");
        textureList.push_back(i7);
        i8.loadFromFile("images/speedBooster.png");
        textureList.push_back(i8);
        i9.loadFromFile("images/seekerDart.png");
        textureList.push_back(i9);
        i10.loadFromFile("images/voidBomber.png");
        textureList.push_back(i10);
        i11.loadFromFile("images/seekerMissile.png");
        textureList.push_back(i11);
        i12.loadFromFile("images/healingAura.png");
        textureList.push_back(i12);

        
        for (auto i:textureList)
        {
            Sprite sprite;
            sprite.setTexture(i);
            spriteList.push_back(sprite);
           
        }
        
        for (int i = 0; i < game->bulletTextureList.size(); i++)
        {
            Sprite sprite;
            sprite.setTexture(game->bulletTextureList[i]);
            bulletSpriteList.push_back(sprite);
            
        }

    }
    
    
    //Check is any synergys can be displayed and if so create the synergyBoxes to be displayed on screen
    void displaySynergies()
    {
        synergyHandler->synergyBoxes.clear();
        synergyHandler->checkSynergies(character->attachments);
        int synergyCounterRow = 0;
        int synergyCounterCol = 0;
        for (int i = 0; i < sizeof(synergyHandler->synergies)/sizeof(synergyHandler->synergies[0]); i++)
        {
            if (synergyHandler->synergies[i].level >= 2)
            {
                synergyHandler->addSynergyBox(relUnitX * 5 + (10 * relUnitX * synergyCounterCol), 
                relUnitY * 22 + (30 * relUnitY * synergyCounterRow), 
                synergyHandler->synergies[i].name, &gameFont, synergyHandler->synergies[i].color, synergyHandler->synergies[i].num);
                if (synergyCounterCol == 0)
                    synergyCounterCol++;
                else
                {
                    synergyCounterRow++;
                    synergyCounterCol = 0;
                }
            }
        }
        
    }
    
    //Generates Shop Button
    bool generateButton(ShopButton *button, int attachNum, int butNum, bool isReroll)
    {
        int cost = 1;
        Attachment *curAtc = new Attachment;
        switch(attachNum)
        {
            case 0:
            {
                Cannon *cannon = new Cannon(bulletSpriteList[0]);
                cost = cannon->credits;
                curAtc = cannon;
                if (ifContains(curAtc) != NULL)
                {
                     cost = ifContains(curAtc)->credits;
                     if (ifContains(curAtc)->level == 3 and isReroll)
                         return 1;
                     else if (ifContains(curAtc)->level == 3)
                         cost = cost/2;
                }
                button->createIcon(textureList[0], spriteList[0], butNum, 250, 250, &gameFont, ("Cannon: " + to_string(cost) + " Cr"), 20, cost);
                shopAttachments.push_back(cannon);
                return 0;     
            } 
            case 1:
            {
                MachineGun *machineGun = new MachineGun(bulletSpriteList[3]);
                cost = machineGun->credits;
                curAtc = machineGun;
                if (ifContains(curAtc) != NULL)
                {
                     cost = ifContains(curAtc)->credits;
                     if (ifContains(curAtc)->level == 3 and isReroll)
                         return 1;
                     else if (ifContains(curAtc)->level == 3)
                         cost = cost/2;
                }
                button->createIcon(textureList[1], spriteList[1], butNum, 250, 250, &gameFont, ("Machine Gun: " + to_string(cost) + " Cr"), 20, cost);
                shopAttachments.push_back(machineGun);
                return 0;
            }
            case 2:
            {
                RepairDroid *repairDroid = new RepairDroid();
                cost = repairDroid->credits;
                curAtc = repairDroid;
                if (ifContains(curAtc) != NULL)
                {
                     cost = ifContains(curAtc)->credits;
                     if (ifContains(curAtc)->level == 3 and isReroll)
                         return 1;
                     else if (ifContains(curAtc)->level == 3)
                         cost = cost/2;
                }
                button->createIcon(textureList[2], spriteList[2], butNum, 250, 250, &gameFont, ("Repair Droid: " + to_string(cost) + " Cr"), 20, cost);
                shopAttachments.push_back(repairDroid);
                return 0;
            }
            case 3:
            {
                SiphonDroid *siphonDroid = new SiphonDroid(bulletSpriteList[1]);
                cost = siphonDroid->credits;
                curAtc = siphonDroid;
                if (ifContains(curAtc) != NULL)
                {
                     cost = ifContains(curAtc)->credits;
                     if (ifContains(curAtc)->level == 3 and isReroll)
                         return 1;
                     else if (ifContains(curAtc)->level == 3)
                         cost = cost/2;
                }
                button->createIcon(textureList[3], spriteList[3], butNum, 250, 250, &gameFont, ("Siphon Droid: " + to_string(cost) + " Cr"), 20, cost);
                //siphonDroid->createAttachment(bulletSpriteList[1]);
                shopAttachments.push_back(siphonDroid);
                return 0;
            }
            case 4:
            {
                Shotgun *shotgun = new Shotgun(bulletSpriteList[2]);
                cost = shotgun->credits;
                curAtc = shotgun;
                if (ifContains(curAtc) != NULL)
                {
                     cost = ifContains(curAtc)->credits;
                     if (ifContains(curAtc)->level == 3 and isReroll)
                         return 1;
                     else if (ifContains(curAtc)->level == 3)
                         cost = cost/2;
                }
                button->createIcon(textureList[4], spriteList[4], butNum, 250, 250, &gameFont, ("Shotgun: " + to_string(cost) + " Cr"), 20, cost);
                //shotgun->createAttachment(bulletSpriteList[0]);
                shopAttachments.push_back(shotgun);
                return 0;
            }
            case 5:
            {
                TimeDilator *timeDilator = new TimeDilator();
                cost = timeDilator->credits;
                curAtc = timeDilator;
                if (ifContains(curAtc) != NULL)
                {
                     cost = ifContains(curAtc)->credits;
                     if (ifContains(curAtc)->level == 3 and isReroll)
                         return 1;
                     else if (ifContains(curAtc)->level == 3)
                         cost = cost/2;
                }
                button->createIcon(textureList[5], spriteList[5], butNum, 250, 250, &gameFont, ("Time Dilator: " + to_string(cost) + " Cr"), 20, cost);
                //timeDilator->createAttachment();
                shopAttachments.push_back(timeDilator);
                return 0;
            }
            case 6:
            {
                HullBooster *hullBooster = new HullBooster();
                cost = hullBooster->credits;
                curAtc = hullBooster;
                if (ifContains(curAtc) != NULL)
                {
                     cost = ifContains(curAtc)->credits;
                     if (ifContains(curAtc)->level == 3 and isReroll)
                         return 1;
                     else if (ifContains(curAtc)->level == 3)
                         cost = cost/2;
                }
                button->createIcon(textureList[6], spriteList[6], butNum, 250, 250, &gameFont, ("Hull Booster: " + to_string(cost) + " Cr"), 20, cost);
                //hullBooster->createAttachment();
                shopAttachments.push_back(hullBooster);
                return 0;
            }
            case 7:
            {
                SpeedBooster *speedBooster = new SpeedBooster();
                cost = speedBooster->credits;
                curAtc = speedBooster;
                if (ifContains(curAtc) != NULL)
                {
                     cost = ifContains(curAtc)->credits;
                     if (ifContains(curAtc)->level == 3 and isReroll)
                         return 1;
                     else if (ifContains(curAtc)->level == 3)
                         cost = cost/2;
                }
                button->createIcon(textureList[7], spriteList[7], butNum, 250, 250, &gameFont, ("Speed Booster: " + to_string(cost) + " Cr"), 20, cost);
                //hullBooster->createAttachment();
                shopAttachments.push_back(speedBooster);
                return 0;
            }
            case 8:
            {
                SeekerDart *seekerDart = new SeekerDart(bulletSpriteList[4]);
                cost = seekerDart->credits;
                curAtc = seekerDart;
                if (ifContains(curAtc) != NULL)
                {
                     cost = ifContains(curAtc)->credits;
                     if (ifContains(curAtc)->level == 3 and isReroll)
                         return 1;
                     else if (ifContains(curAtc)->level == 3)
                         cost = cost/2;
                }
                button->createIcon(textureList[8], spriteList[8], butNum, 250, 250, &gameFont, ("Seeker Dart: " + to_string(cost) + " Cr"), 20, cost);
                //hullBooster->createAttachment();
                shopAttachments.push_back(seekerDart);
                return 0;
            
            }
            case 9:
            {
                VoidBomber *voidBomber = new VoidBomber();
                cost = voidBomber->credits;
                curAtc = voidBomber;
                if (ifContains(curAtc) != NULL)
                {
                     cost = ifContains(curAtc)->credits;
                     if (ifContains(curAtc)->level == 3 and isReroll)
                         return 1;
                     else if (ifContains(curAtc)->level == 3)
                         cost = cost/2;
                }
                button->createIcon(textureList[9], spriteList[9], butNum, 250, 250, &gameFont, ("Void Bomber: " + to_string(cost) + " Cr"), 20, cost);
                shopAttachments.push_back(voidBomber);
                return 0;
            
            }
            case 10:
            {
                SeekerMissile *seekerMissile = new SeekerMissile(bulletSpriteList[5]);
                cost = seekerMissile->credits;
                curAtc = seekerMissile;
                if (ifContains(curAtc) != NULL)
                {
                     cost = ifContains(curAtc)->credits;
                     if (ifContains(curAtc)->level == 3 and isReroll)
                         return 1;
                     else if (ifContains(curAtc)->level == 3)
                         cost = cost/2;
                }
                button->createIcon(textureList[10], spriteList[10], butNum, 250, 250, &gameFont, ("Seeker Missile: " + to_string(cost) + " Cr"), 20, cost);
                shopAttachments.push_back(seekerMissile);
                return 0;
            
            }
            case 11:
            {
                HealingAura *healingAura = new HealingAura();
                cost = healingAura->credits;
                curAtc = healingAura;
                if (ifContains(curAtc) != NULL)
                {
                     cost = ifContains(curAtc)->credits;
                     if (ifContains(curAtc)->level == 3 and isReroll)
                         return 1;
                     else if (ifContains(curAtc)->level == 3)
                         cost = cost/2;
                }
                button->createIcon(textureList[11], spriteList[11], butNum, 250, 250, &gameFont, ("Healing Aura: " + to_string(cost) + " Cr"), 20, cost);
                shopAttachments.push_back(healingAura);
                return 0;
            
            }
        }
        return 0;
    }
    
    void createSlotButtons(int slotNum)
    {
        //String name = character->attachments[attachNum]->name;
        Sprite sprite;
        ImageButton *button = new ImageButton;
        int textNum = character->attachments[slotNum]->attachNum;
            
        sprite.setScale(.4, .4);
        sprite.setPosition(screenW - 400, 150 + (150 * slotNum));
        //the [textNum + i] represents the offset from double textures at the beginning. i must be iterated each time a new attachment is added
        button->createImageButton(textureList[textNum + numOfAttachments], spriteList[textNum + numOfAttachments], screenW - 400, 150 + (150 * slotNum), 100, 100);
        attachmentSlotButtons.push_back(button);
    }
    
    String getSynDesc(String name)
    {
        if (name == "Gun")
            return "Gun Synergy: Shot speed increased by 50% for all guns";
        else if (name == "Repair")
            return "Repair Synergy: Healing effectiveness increased by 50% for all repair attachments";
        else if (name == "Utility")
            return "Utility Synergy: Effectiveness increased by 50% for all utility attachments";
        else if (name == "Seeker")
            return "Seeker Synergy: Shot speed increased by 50% for all Seeker attachments";
        else if (name == "AOE")
            return "AOE Synergy: Radius increased by 50% for all AOE attachments";
            
        return "Nothing";
    }
    
    String getDesc(Attachment attachment)
    {
        String name = attachment.name;
        int levelNum = 0;
        if (ifContains(&attachment) != NULL)
        {
            levelNum = ifContains(&attachment)->level;
        }
        if (name == "Cannon")
        {
            if (levelNum == 0)
                return "Cannon: Fires a single medium damage shot (Gun)\nFirerate: 1/s\nSpeed: 20\nDamage: 5";
            else if (levelNum == 1)
                return "Cannon: Fires a single medium damage shot (Gun)\nFirerate: 1/s  ->  1.5/s\nSpeed: 20\nDamage: 5  ->  7.5";
            else if (levelNum == 2)
                return "Cannon: Fires a single medium damage shot (Gun) -> that explods on impact (AOE)\nFirerate: 1.5/s\nSpeed: 20\nDamage: 7.5  ->  10\nAOE Damage: 0 -> 2";
            else if (levelNum == 3)
                return "Cannon: Fires a single medium damage shot that exlodes on impact (Gun) (AOE)\nFirerate: 1.5/s\nSpeed: 20\nDamage: 10\nAOE Damage: 2";
        }
        else if (name == "Machine Gun")
        {
            if (levelNum == 0)
                return "Machine Gun: Fires low damage bullets at a high rate of fire (Gun)\nFirerate: 4/s\nSpeed: 25\nDamage: 2";
            else if (levelNum == 1)
                return "Machine Gun: Fires low damage bullets at a high rate of fire (Gun)\nFirerate: 4/s  ->  6/s\nSpeed: 25\nDamage: 2  ->  3";
            else if (levelNum == 2)
                return "Machine Gun: Fires low damage bullets at a high rate of fire (Gun)\nFirerate: 6/s  ->  9/s\nSpeed: 25\nDamage: 3  ->  4.5";
            else if (levelNum == 3)
                return "Machine Gun: Fires low damage bullets at a high rate of fire (Gun)\nFirerate: 9/s\nSpeed: 25\nDamage: 4.5";
        }
        else if (name == "Repair Droid")
        {
            if (levelNum == 0)
                return "Repair Droid: Repairs your ship over time (Repair)\nFirerate: 1/5s\nHealth: 5";
            else if (levelNum == 1)
                return "Repair Droid: Repairs your ship over time (Repair)\nFirerate: 1/5s\nHealth: 5  ->  10";
            else if (levelNum == 2)
                return "Repair Droid: Repairs your ship over time (Repair)\nFirerate: 1/5s\nHealth: 10  ->  20";
            else if (levelNum == 3)
                return "Repair Droid: Repairs your ship over time (Repair)\nFirerate: 1/5s\nHealth: 20";
        }
        else if (name == "Siphon Droid")
        {
            if (levelNum == 0)
                return "Siphon Droid: Fires a projectile that repairs ship equal to damage dealt (Gun) (Repair)\nFirerate: 1/1.25s\nSpeed: 20\nDamage: 5";
            else if (levelNum == 1)
                return "Siphon Droid: Fires a projectile that repairs ship equal to damage dealt (Gun) (Repair)\nFirerate: 1/1.25s\nSpeed: 20\nDamage: 5  ->  10";
            else if (levelNum == 2)
                return "Siphon Droid: Fires a projectile that repairs ship equal to damage dealt (Gun) (Repair)\nFirerate: 1/1.25s\nSpeed: 20\nDamage: 10  ->  20";
            else if (levelNum == 3)
                return "Siphon Droid: Fires a projectile that repairs ship equal to damage dealt (Gun) (Repair)\nFirerate: 1/1.25s\nSpeed: 20\nDamage: 20";
        }
        else if (name == "Shotgun")
        {
            if (levelNum == 0)
                return "Shotgun: Fires a spread of 3 medium damage projectiles (Gun)\nFirerate: 1/2s\nSpeed: 15\nDamage: 5\nShots: 3\nAngle: 45";
            else if (levelNum == 1)
                return "Shotgun: Fires a spread of 3 medium damage projectiles (Gun)\nFirerate: 1/1.5s\nSpeed: 15\nDamage: 5  ->  10\nShots: 3\nAngle: 45  ->  22.5";
            else if (levelNum == 2)
                return "Shotgun: Fires a spread of 5 medium damage projectiles (Gun)\nFirerate: 1/s\nSpeed: 15\nDamage: 10  ->  20\nShots: 3  ->  5\nAngle: 22.5  ->  11.25";
            else if (levelNum == 3)
                return "Shotgun: Fires a spread of 5 medium damage projectiles (Gun)\nFirerate: 1/s\nSpeed: 15\nDamage: 20\nShots: 5\nAngle: 11.25";
        }
        else if (name == "Time Dilator")
        {
            if (levelNum == 0)
                return "Time Dilator: Slows starting map speed (Manipulator)\nPercentage: 10%";
            else if (levelNum == 1)
                return "Time Dilator: Slows starting map speed (Manipulator)\nPercentage: 10%  ->  20%";
            else if (levelNum == 2)
                return "Time Dilator: Slows starting map speed (Manipulator)\nPercentage: 20%  ->  40%";
            else if (levelNum == 3)
                return "Time Dilator: Slows starting map speed (Manipulator)\nPercentage: 40%";
        }
        else if (name == "Hull Booster")
        {
            if (levelNum == 0)
                return "Hull Booster: Increase Max Health (Utility)\nPercentage: 25%";
            if (levelNum == 1)
                return "Hull Booster: Increase Max Health (Utility)\nPercentage: 25%  ->  50%";
            if (levelNum == 2)
                return "Hull Booster: Increase Max Health (Utility)\nPercentage: 50%  ->  100%";
            if (levelNum == 3)
                return "Hull Booster: Increase Max Health (Utility)\nPercentage: 100%";
        }
        else if (name == "Speed Booster")
        {
            if (levelNum == 0)
                return "Speed Booster: Increase Speed (Utility)\nPercentage: 25%";
            if (levelNum == 1)
                return "Speed Booster: Increase Speed (Utility)\nPercentage: 25%  ->  50%";
            if (levelNum == 2)
                return "Speed Booster: Increase Speed (Utility)\nPercentage: 50%  ->  100%";
            if (levelNum == 3)
                return "Speed Booster: Increase Speed (Utility)\nPercentage: 100%";
        }
        else if (name == "Seeker Dart")
        {
            if (levelNum == 0)
                return "Seeker Dart: Fires a low damage dart that homes in on the nearest enemy (Gun) (Seeker)\nFirerate: 1/s\nSpeed: 15\nDamage: 2\n";
            else if (levelNum == 1)
                return "Seeker Dart: Fires a low damage dart that homes in on the nearest enemy (Gun) (Seeker)\nFirerate: 1/s -> 1.5/s\nSpeed: 15\nDamage: 2 -> 4\n";
            else if (levelNum == 2)
                return "Seeker Dart: Fires a low damage dart that homes in on the nearest enemy (Gun) (Seeker)\nFirerate: 1.5/s -> 2.25/s\nSpeed: 15\nDamage: 4 -> 6\n";
            else if (levelNum == 3)
                return "Seeker Dart: Fires a low damage dart that homes in on the nearest enemy (Gun) (Seeker)\nFirerate: 2.25/s\nSpeed: 15\nDamage: 6\n";

        }
        else if (name == "Void Bomber")
        {
            if (levelNum == 0)
                return "Void Bomber: Fires an AOE blast that destroys all enemy bullets (AOE)\nFirerate: 1/3s\nSpeed: 15\nArea: 50\n";
            else if (levelNum == 1)
                return "Void Bomber: Fires an AOE blast that destroys all enemy bullets (AOE)\nFirerate: 1/3s\nSpeed: 15\nArea: 50 -> 75\n";
            else if (levelNum == 2)
                return "Void Bomber: Fires an AOE blast that destroys all enemy bullets (AOE)\nFirerate: 1/3s -> 1/2s\nSpeed: 15 -> 10\nArea: 75\n";
            else if (levelNum == 3)
                return "Void Bomber: Fires an AOE blast that destroys all enemy bullets (AOE)\nFirerate: 1/2s\nSpeed: 10\nArea: 75\n";

        }
        else if (name == "Seeker Missile")
        {
            if (levelNum == 0)
                return "Seeker Missile: Fires a seeking missile that explodes on impact (Seeker) (AOE)\nDamage: 10\nAOE Damage: 5\nFirerate: 1/3s\nSpeed: 10\nArea: 100\n";
            else if (levelNum == 1)
                return "Seeker Missile: Fires a seeking missile that explodes on impact (Seeker) (AOE)\nDamage: 10 -> 15\nAOE Damage: 5 -> 7.5\nFirerate: 1/3s\nSpeed: 10\nArea: 100\n";
            else if (levelNum == 2)
                return "Seeker Missile: Fires a seeking missile that explodes on impact (Seeker) (AOE)\nDamage: 15\nAOE Damage: 7.5\nFirerate: 1/3s -> 1/2s\nSpeed: 10\nArea: 100 -> 150\n";
            else if (levelNum == 3)
                return "Seeker Missile: Fires a seeking missile that explodes on impact (Seeker) (AOE)\nDamage: 15\nAOE Damage: 7.5\nFirerate: 1/2s\nSpeed: 10\nArea: 150\n";

        }
        else if (name == "Healing Aura")
        {
            if (levelNum == 0)
                return "Healing Aura: Creates a healing aura at a random location that heals the player (Repair) (AOE)\nHealth: 1\nHealing Rate: 1/s\nRadius: 75\n";
            else if (levelNum == 1)
                return "Healing Aura: Creates a healing aura at a random location that heals the player (Repair) (AOE)\nHealth: 1\nHealing Rate: 1/s -> 1.5/s\nRadius: 75 -> 100\n";
            else if (levelNum == 2)
                return "Healing Aura: Creates a healing aura at a random -> (the player's) location that heals the player (Repair) (AOE)\nHealth: 1\nHealing Rate: 1.5/s\nRadius: 100\n";
            else if (levelNum == 3)
                return "Healing Aura: Creates a healing aura at the player's location that heals the player (Repair) (AOE)\nHealth: 1\nHealing Rate: 1.5/s\nRadius: 100\n";

        }
        return "No Name"; 
    }
    
    void rollShop(int pos)
    {
        bool AtFullLevel = false;
        ShopButton *button = new ShopButton;
        do
        {
            int randNum = rand() % numOfAttachments;
            AtFullLevel = generateButton(button, randNum, pos, true);
        } while (AtFullLevel == true);
        shopButtonList.push_back(button);
    
    }
    
    void regenerateShop(int num1, int num2, int num3, bool visArray[3])
    {
        shopButtonList.clear();
        shopAttachments.clear();
        
            ShopButton *button1 = new ShopButton;
            generateButton(button1, num1, 1, false);
            shopButtonList.push_back(button1);

            ShopButton *button2 = new ShopButton;
            generateButton(button2, num2, 2, false);
            shopButtonList.push_back(button2);
            
            ShopButton *button3 = new ShopButton;
            generateButton(button3, num3, 3, false);
            shopButtonList.push_back(button3);
            
        for (int i = 0; i < 3; i ++)
        {
            shopButtonList[i]->visible = visArray[i];
        }
 
    }
    
    //checks if the player already has a given attachment
    Attachment* ifContains (Attachment *attachment)
    {
        String Name = attachment->name;
        for (auto i:character->attachments)
        {
            if (i->name == Name)
                return i;
        }
        return NULL;
    }
    
    void drawText( const sf::String &str, const int Size, const float xposition, const float yposition, sf::RenderWindow& window)
    {
        source.setString(str);
        source.setCharacterSize(Size);
        source.setPosition(xposition,yposition);
        source.setFillColor(Color::Black);
        window.draw(source);
    }
    
    int Run(sf::RenderWindow &app)
    {
        sf::Vector2i pixelPos = sf::Mouse::getPosition(app);
        sf::Vector2f worldPos = app.mapPixelToCoords(pixelPos);
        
        Button *continueButton = new Button;
        continueButton->createButton(screenW - screenW/4, screenH - screenH/4, 200, 50, &gameFont, "CONTINUE", 20); 
        buttonList.push_back(continueButton);
        
        Button *rerollButton = new Button;
        rerollButton->createButton(screenW/2 - 57, screenH/8, 200, 50, &gameFont, "REROLL", 20); 
        buttonList.push_back(rerollButton);
        
        Button *sellButton = new Button;
        sellButton -> createButton (0, 0, 150, 50, &gameFont, "SELL", 20);
        sellButton->visible = false;
        buttonList.push_back(sellButton);
        
        srand(time(NULL));
        sf::Clock clock;
        
        rollShop(1);
        rollShop(2);
        rollShop(3);
        
        Entity *creditImage = new Entity();
        creditImage -> noSpriteSettings(75, 75, 25, 25, Color::Yellow);
        entities.push_back(creditImage);
        
        displaySynergies();
        
       for (int i = 0; i < character->attachmentSlots; i++)
       {
           sf::RectangleShape slot;
           slot.setSize(sf::Vector2f(100, 100));
           slot.setOutlineColor(sf::Color::Black);
           slot.setOutlineThickness(5);
           slot.setPosition(screenW - 400, 150 + (150 * i));
           slotRectangles.push_back(slot);
       
       }
       
       for (int i = 0; i < character->attachments.size(); i++)
       {
           createSlotButtons(i);
       }
        
        sf::Music music;
        if (!music.openFromFile("sounds/shopMusic.wav"))
            return -1; // error
        music.play();
        //music.setPlayingOffset(sf::seconds(.2f));
        music.setLoop(true);
          
        //Check for any buttons clicked 
        while (app.isOpen())
        {
            pixelPos = sf::Mouse::getPosition(app);
            worldPos = app.mapPixelToCoords(pixelPos);
            bool buttonClicked = false;
        
            Event event;
            while (app.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    app.close();
                    
                else if (event.type == sf::Event::MouseButtonPressed) 
                {
                 
                    //Check for regular buttons clicked
                    //std::cout << "Mouse Position on Screen: " + to_string(Mouse::getPosition(app).x) + " , " + to_string(Mouse::getPosition(app).y) << std::endl;
                    //sf::Vector2i pixelPos = sf::Mouse::getPosition(app);
                    //sf::Vector2f worldPos = app.mapPixelToCoords(pixelPos);
                    for (auto i:buttonList)
                    {
                        if (i -> visible == true and i->rect.contains(worldPos.x, worldPos.y) == true)
                        {
                            if (Mouse::isButtonPressed(Mouse::Left))
                                i->leftClicked = true;
                            else if (Mouse::isButtonPressed(Mouse::Right))
                                i->rightClicked = true; 
                        }
                    }  
                    
                    //Check for Shop Buttons Clicked 
                    for (auto i:shopButtonList)
                    {
                        if (i -> visible == true and i->rect.contains(worldPos.x, worldPos.y) == true)
                        {
                            if (Mouse::isButtonPressed(Mouse::Left))
                                i->leftClicked = true;
                            else if (Mouse::isButtonPressed(Mouse::Right))
                                i->rightClicked = true; 
                                
                            clickParticles->setEmitter(sf::Vector2f(worldPos.x, worldPos.y));
                            buttonClicked = true;
                        }
                    }   
                    
                    //Check for attachment slot buttons clicked
                    for (auto i:attachmentSlotButtons)
                    {
                        if (i -> visible == true and i->rect.contains(worldPos.x, worldPos.y) == true)
                        {
                            if (Mouse::isButtonPressed(Mouse::Left))
                            {
                                for (auto j:attachmentSlotButtons)
                                    j -> leftClicked = false;
                                i->leftClicked = true;
                            }
                            else if (Mouse::isButtonPressed(Mouse::Right))
                                i->rightClicked = true; 
                        }
                    
                    }
                }
            }
            
            //Check if mouse is over shopButtonList
            for (int i = 0; i < shopButtonList.size(); i++)
            {

                if (shopButtonList[i] -> visible == true and shopButtonList[i]->rect.contains(worldPos.x, worldPos.y) == true)
                {
                    drawText(getDesc(*shopAttachments[i]), 20, screenW/6, 600, app);
                    
                }
            }
            
            //check if mouse is over attachmentSlotButtons
            for (int i = 0; i < attachmentSlotButtons.size(); i++)
            {
                if (attachmentSlotButtons[i] -> visible == true and attachmentSlotButtons[i]->rect.contains(worldPos.x, worldPos.y) == true)
                {
                    drawText(getDesc(*character->attachments[i]), 20, screenW/6, 600, app);
                    
                }
            }
            
            //check is mouse is over synergy boxes
            for (int i = 0; i < synergyHandler->synergyBoxes.size(); i++)
            {
                if (synergyHandler->synergyBoxes[i]->rect.contains(worldPos.x, worldPos.y) == true)
                {
                    drawText(getSynDesc(synergyHandler->synergyBoxes[i]->name), 20, screenW/6, 600, app);
                    
                }
            }
            
            
            //Quit Game
	     if (Keyboard::isKeyPressed(Keyboard::Q))
	         return -1;
            
            //Check if Buttons clicked
            //Continue
            if (buttonList[0]->leftClicked == true)
            {
                buttonList[0]->leftClicked = false;
                buttonList.clear();
                shopButtonList.clear();
                shopAttachments.clear();
                attachmentSlotButtons.clear();
                return 2;
            
            }
            
            //Reroll
            if (buttonList[1]->leftClicked == true)
            {
                buttonList[1]->leftClicked = false;
                shopAttachments.clear();
                shopButtonList.clear();
                
                rollShop(1);
                rollShop(2);
                rollShop(3);
            }
            
            
            //Sell
            if (buttonList[2]->leftClicked == true)
            {
                buttonList[2]->leftClicked = false;
                sellButton -> visible = false;
                for (int i = 0; i < attachmentSlotButtons.size(); i++)
                {
                    if (attachmentSlotButtons[i]->leftClicked == true)
                    {
                        //character->attachments.erase(i);
                        (character->credits) += (character->attachments[i])->credits;
                        //string test = character->attachments[i]->name;
                        character->attachments.erase(next(begin(character->attachments), + i));
                        attachmentSlotButtons.clear();
                        for (int j = 0; j < character->attachments.size(); j++)
                        {
                            createSlotButtons(j);
                        }
                    }
                }
                displaySynergies();
            }
            
            
            //check if any of the attachment buttons are clicked
            for (int i = 0; i < attachmentSlotButtons.size(); i++)
            {
                if (attachmentSlotButtons[i]->leftClicked == true)
                {
                   
                    attachmentSlotButtons[i]->leftClicked = true;
                    //shopButtonList[i]->leftClicked = false;
                    sellButton -> visible = true;
                    sellButton -> moveTo(screenW - 200, 200 + (150 * i));
                }
            }
            
            //check if any of the shop buttons are clicked
            for (int i = 0; i < 3; i++)
            {
                if (shopButtonList[i]->leftClicked == true and character->credits >= shopButtonList[i]->cost 
                && (character->attachments.size() < character->attachmentSlots or ifContains(shopAttachments[i])!=NULL))
                {
                    Attachment *alreadyHas = ifContains(shopAttachments[i]);
                    
                    if (alreadyHas == NULL)
                    {
                        character->attachments.push_back(shopAttachments[i]);
                        //attachmentSlotSprites.clear();
                        attachmentSlotButtons.clear();
                        for (int j = 0; j < character->attachments.size(); j++)
                        {
                            createSlotButtons(j);
                        }
                        shopAttachments[i]->credits = shopAttachments[i]->credits * 2;
                    }
                    else if (alreadyHas->level < 3)
                    {
                        alreadyHas->upgrade();
                    }
                    else
                    {
                        continue;
                        
                    }
                    shopButtonList[i]->leftClicked = false;
                    shopButtonList[i]->visible = false;
                    bool visArray[3] = { false };
                    for (int j = 0; j < 3; j++)
                    {
                        visArray[j] = shopButtonList[j]->visible;
                    }
                    character->credits -= shopButtonList[i]->cost;
                    regenerateShop(shopAttachments[0]->attachNum, shopAttachments[1]->attachNum, shopAttachments[2]->attachNum, visArray);
                    displaySynergies();
                }
                shopButtonList[i]->leftClicked = false;
            }
            
            sf::Time elapsed = clock.restart();
            clickParticles->update(elapsed, buttonClicked);

            //draw
            
            for(auto i:entities)
                i->draw(app);
            for(auto i:slotRectangles)
                app.draw(i);
            for(auto i:synergyHandler->synergyBoxes)
            {
                app.draw(i->synRec);
                app.draw(i->sprite);
            }
           // for(auto i:attachmentSlotSprites)
                //app.draw(i);
            for (auto i:attachmentSlotButtons)
            	app.draw(i->icon);
            for(auto i:buttonList)
            {
                   if (i->visible == true)
                   {
                       app.draw(i->rectangle);
                       app.draw(i->buttonText);
                   }
            }
            for(auto i:shopButtonList)
            {
                if (i->visible == true)
                {
                    app.draw(i->rectangle);
                    app.draw(i->buttonText);
                    app.draw(i->icon);
                }
            }
            drawText(": " + std::to_string(character->credits), 20, 95, 61, app);
            app.draw(*clickParticles);
            app.display();
            app.clear(Color(100,100,100,255));
        }
    
        return -1;
    }

};
