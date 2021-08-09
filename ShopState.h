#pragma once
#include <iostream>
#include <array>
#include <string>
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

class ShopState: public State
{
    public:
    std::vector<Entity*> entities;
    std::vector<Button*> buttonList;
    std::vector<ShopButton*> shopButtonList;
    std::vector<Texture> textureList;
    std::vector<Sprite> spriteList;
    std::vector<Sprite> bulletSpriteList;
    std::vector<Attachment*> shopAttachments;
    std::vector<RectangleShape> slotRectangles;
    std::vector<Sprite> attachmentSlotSprites;
    Character *character = new Character;
    int screenW;
    int screenH;
    sf::Font gameFont;
    sf::Text source;
    
    void createState(Game *game)
    {
        screenW = game->screenWidth;
        screenH = game->screenHeight;
        source = game->source;
        gameFont = game->gameFont; 
        character = game->character;
        
        Texture t1, t2, t3, t4, t5;
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
    
    void createButton(ShopButton *button, int attachNum, int butNum )
    {
        switch(attachNum)
        {
            case 0:
            {
                button->createIcon(textureList[0], spriteList[0], butNum, 250, 250, &gameFont, "Cannon: 3 Cr", 20, 3);
                Cannon *cannon = new Cannon;
                cannon->createAttachment(bulletSpriteList[0]);
                shopAttachments.push_back(cannon);
                return;     
            } 
            case 1:
            {
                button->createIcon(textureList[1], spriteList[1], butNum, 250, 250, &gameFont, "Machine Gun: 3 Cr", 20, 3);
                MachineGun *machineGun = new MachineGun;
                machineGun->createAttachment(bulletSpriteList[0]);
                shopAttachments.push_back(machineGun);
                return;
            }
            case 2:
            {
                button->createIcon(textureList[2], spriteList[2], butNum, 250, 250, &gameFont, "Repair Droid: 3 Cr", 20, 3);
                RepairDroid *repairDroid = new RepairDroid;
                repairDroid->createAttachment();
                shopAttachments.push_back(repairDroid);
                return;
            }
            case 3:
            {
                button->createIcon(textureList[3], spriteList[3], butNum, 250, 250, &gameFont, "Siphon Droid: 6 Cr", 20, 6);
                SiphonDroid *siphonDroid = new SiphonDroid;
                siphonDroid->createAttachment(bulletSpriteList[1]);
                shopAttachments.push_back(siphonDroid);
                return;
            }
            case 4:
            {
                button->createIcon(textureList[4], spriteList[4], butNum, 250, 250, &gameFont, "Shotgun: 3 Cr", 20, 3);
                Shotgun *shotgun = new Shotgun;
                shotgun->createAttachment(bulletSpriteList[0]);
                shopAttachments.push_back(shotgun);
                return;
            }
        
        }
        
    }
    
    void createSlotButtons(int attachNum)
    {
        String name = character->attachments[attachNum]->name;
        Sprite sprite;
        if (name == "Cannon")
            sprite.setTexture(textureList[0]);
        else if (name == "Machine Gun")
            sprite.setTexture(textureList[1]);
        else if (name == "Repair Droid")
            sprite.setTexture(textureList[2]);
        else if (name == "Siphon Droid")
            sprite.setTexture(textureList[3]);
        else if (name == "Shotgun")
            sprite.setTexture(textureList[4]);
            
        sprite.setScale(.4, .4);
        sprite.setPosition(screenW - 400, 150 + (150 * attachNum));
        attachmentSlotSprites.push_back(sprite);
    }
    
    String getDesc(Attachment attachment)
    {
        String name = attachment.name;
        int levelNum = 1;
        if (ifContains(&attachment) != NULL)
        {
            levelNum = ifContains(&attachment)->level;
        }
        if (name == "Cannon")
        {
            if (levelNum == 1)
                return "Cannon: Fires a single medium damage shot (Gun)\nFirerate: 1/s  ->  2/s\nSpeed: 20\nDamage: 5    ->  10";
            if (levelNum == 2)
                return "Cannon: Fires a single medium damage shot (Gun)\nFirerate: 2/s  ->  4/s\nSpeed: 20\nDamage: 10   ->  20";
            if (levelNum == 3)
                return "Cannon: Fires a single medium damage shot (Gun)\nFirerate: 4/s\nSpeed: 20\nDamage: 20";
        }
        else if (name == "Machine Gun")
        {
            if (levelNum == 1)
                return "Machine Gun: Fires low damage bullets at a high rate of fire (Gun)\nFirerate: 4/s\nSpeed: 25\nDamage: 2";
            if (levelNum == 2)
                return "Machine Gun: Fires low damage bullets at a high rate of fire (Gun)\nFirerate: 6/s\nSpeed: 25\nDamage: 3";
            if (levelNum == 3)
                return "Machine Gun: Fires low damage bullets at a high rate of fire (Gun)\nFirerate: 9/s\nSpeed: 25\nDamage: 4.5";
        }
        else if (name == "Repair Droid")
        {
            if (levelNum == 1)
                return "Repair Droid: Repairs your ship over time (Repair)\nFirerate: 1/5s\nHealth: 5";
            if (levelNum == 2)
                return "Repair Droid: Repairs your ship over time (Repair)\nFirerate: 1/5s\nHealth: 10";
            if (levelNum == 3)
                return "Repair Droid: Repairs your ship over time (Repair)\nFirerate: 1/5s\nHealth: 20";
        }
        else if (name == "Siphon Droid")
        {
            if (levelNum == 1)
                return "Siphon Droid: Fires a projectile that repairs ship equal to damage dealt (Gun) (Repair)\nFirerate: 1/1.25s\nSpeed: 20\nDamage: 5";
            if (levelNum == 2)
                return "Siphon Droid: Fires a projectile that repairs ship equal to damage dealt (Gun) (Repair)\nFirerate: 1/1.25s\nSpeed: 20\nDamage: 10";
            if (levelNum == 3)
                return "Siphon Droid: Fires a projectile that repairs ship equal to damage dealt (Gun) (Repair)\nFirerate: 1/1.25s\nSpeed: 20\nDamage: 20";
        }
        else if (name == "Shotgun")
        {
            if (levelNum == 1)
                return "Shotgun: Fires a spread of 3 medium damage projectiles (Gun)\nFirerate: 1/2s\nSpeed: 15\nDamage: 5\nShots: 3\nAngle: 45";
            if (levelNum == 2)
                return "Shotgun: Fires a spread of 3 medium damage projectiles (Gun)\nFirerate: 1/1.5s\nSpeed: 15\nDamage: 10\nShots: 3\nAngle: 22.5";
            if (levelNum == 3)
                return "Shotgun: Fires a spread of 3 medium damage projectiles (Gun)\nFirerate: 1/s\nSpeed: 15\nDamage: 20\nShots: 3\nAngle: 11.25";
        }
        return "No Name"; 
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
        Button *continueButton = new Button;
        continueButton->createButton(screenW - screenW/4, screenH - screenH/4, 200, 50, &gameFont, "CONTINUE", 20); 
        buttonList.push_back(continueButton);
        
        Button *rerollButton = new Button;
        rerollButton->createButton(screenW/2 - 57, screenH/8, 200, 50, &gameFont, "REROLL", 20); 
        buttonList.push_back(rerollButton);
        
        srand(time(NULL));
        
        int randNum = rand() % 5;
        ShopButton *button1 = new ShopButton;
        createButton(button1, randNum, 1);
        //buttonList.push_back(button1);
        shopButtonList.push_back(button1);
        
        randNum = rand() % 5;
        ShopButton *button2 = new ShopButton;
        createButton(button2, randNum, 2);
        //buttonList.push_back(button2);
        shopButtonList.push_back(button2);
        
        randNum = rand() % 5;
        ShopButton *button3 = new ShopButton;
        createButton(button3, randNum, 3);
        //buttonList.push_back(button3);
        shopButtonList.push_back(button3);
        
        Entity *creditImage = new Entity();
        creditImage -> noSpriteSettings(75, 75, 25, 25, Color::Yellow);
        entities.push_back(creditImage);
        
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
           
        while (app.isOpen())
        {
            Event event;
            while (app.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    app.close();
                    
                else if (event.type == sf::Event::MouseButtonPressed) 
                {
                 
                    std::cout << "Mouse Position on Screen: " + to_string(Mouse::getPosition(app).x) + " , " + to_string(Mouse::getPosition(app).y) << std::endl;
                    for (auto i:buttonList)
                    {
                        if (i -> visible == true and i->rect.contains(Mouse::getPosition(app).x, Mouse::getPosition(app).y) == true)
                        {
                            i->clicked = true;
                        }
                    }   
                    for (auto i:shopButtonList)
                    {
                        if (i -> visible == true and i->rect.contains(Mouse::getPosition(app).x, Mouse::getPosition(app).y) == true)
                        {
                            i->clicked = true;
                        }
                    }   
                }
            }
            
            for (int i = 0; i < shopButtonList.size(); i++)
            {
                if (shopButtonList[i] -> visible == true and shopButtonList[i]->rect.contains(Mouse::getPosition(app).x, Mouse::getPosition(app).y) == true)
                {
                    drawText(getDesc(*shopAttachments[i]), 20, screenW/6, 600, app);
                    
                }
            }
            
            FloatRect rect;
            for (int i = 0; i < attachmentSlotSprites.size(); i++)
            {
                rect = attachmentSlotSprites[i].getGlobalBounds();
                if (rect.contains(Mouse::getPosition(app).x, Mouse::getPosition(app).y) == true)
                {
                    drawText(getDesc(*character->attachments[i]), 20, screenW/6, 600, app);
                    //cout<<to_string(i);
                }
            }
            
            //Quit Game
	     if (Keyboard::isKeyPressed(Keyboard::Q))
	         return -1;
            
            if (buttonList[0]->clicked == true)
            {
                buttonList[0]->clicked = false;
                buttonList.clear();
                shopButtonList.clear();
                shopAttachments.clear();
                attachmentSlotSprites.clear();
                return 2;
            
            }
            
            if (buttonList[1]->clicked == true)
            {
                buttonList[1]->clicked = false;
                shopAttachments.clear();
                shopButtonList.clear();
                int randNum = rand() % 5;
                ShopButton *button1 = new ShopButton;
                createButton(button1, randNum, 1);
                shopButtonList.push_back(button1);
        
                randNum = rand() % 5;
                ShopButton *button2 = new ShopButton;
                createButton(button2, randNum, 2);
                shopButtonList.push_back(button2);
        
                randNum = rand() % 5;
                ShopButton *button3 = new ShopButton;
                createButton(button3, randNum, 3);
                shopButtonList.push_back(button3);
            }
            
            //check if any of the shop buttons are clicked
            for (int i = 0; i < 3; i++)
            {
                if (shopButtonList[i]->clicked == true and character->credits >= shopButtonList[i]->cost 
                && (character->attachments.size() < character->attachmentSlots or ifContains(shopAttachments[i])!=NULL))
                {
                    Attachment *alreadyHas = ifContains(shopAttachments[i]);
                    shopButtonList[i]->clicked = false;
                    shopButtonList[i]->visible = false;
                    character->credits -= shopButtonList[i]->cost;
                    
                    if (alreadyHas == NULL)
                    {
                        character->attachments.push_back(shopAttachments[i]);
                        attachmentSlotSprites.clear();
                        for (int j = 0; j < character->attachments.size(); j++)
                        {
                            createSlotButtons(j);
                        }
                    }
                    else
                    {
                        alreadyHas->upgrade();
                    }
                }
            }

            //draw
            
            for(auto i:entities)
                i->draw(app);
            for(auto i:slotRectangles)
                app.draw(i);
            for(auto i:attachmentSlotSprites)
                app.draw(i);
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
            app.display();
            app.clear(Color(255,255,255,255));
        }
    
        return -1;
    }

};
