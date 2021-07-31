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
        
        Texture t1, t2, t3, t4;
        t1.loadFromFile("images/cannon.png");
        textureList.push_back(t1);
        t2.loadFromFile("images/machineGun.png");
        textureList.push_back(t2);
        t3.loadFromFile("images/repairDroid.png");
        textureList.push_back(t3);
        t4.loadFromFile("images/siphonDroid.png");
        textureList.push_back(t4);
        
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
        
        }
        
    }
    
    String getDesc(Attachment attachment)
    {
        String name = attachment.name;
        if (name == "Cannon")
            return "Cannon: Fires a single medium damage shot (Gun)\nFirerate: 1/s\nSpeed: 20\nDamage: 5";
        else if (name == "Machine Gun")
            return "Machine Gun: Fires low damage bullets at a high rate of fire (Gun)\nFirerate: 4/s\nSpeed: 25\nDamage: 2";
        else if (name == "Repair Droid")
            return "Repair Droid: Repairs your ship over time (Repair)\nFirerate: 1/5s\nHealth: 5";
        else if (name == "Siphon Droid")
            return "Siphon Droid: Fires a projectile that repairs ship equal to damage dealt (Gun) (Repair)\nFirerate: 1/1.25s\nSpeed: 20\nDamage: 5";
        return "No Name"; 
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
        
        srand(time(NULL));
        
        int randNum = rand() % 4;
        ShopButton *button1 = new ShopButton;
        createButton(button1, randNum, 1);
        buttonList.push_back(button1);
        shopButtonList.push_back(button1);
        
        randNum = rand() % 4;
        ShopButton *button2 = new ShopButton;
        createButton(button2, randNum, 2);
        buttonList.push_back(button2);
        shopButtonList.push_back(button2);
        
        randNum = rand() % 4;
        ShopButton *button3 = new ShopButton;
        createButton(button3, randNum, 3);
        buttonList.push_back(button3);
        shopButtonList.push_back(button3);
        
        Entity *creditImage = new Entity();
        creditImage -> noSpriteSettings(75, 75, 25, 25, Color::Yellow);
        entities.push_back(creditImage);
        
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
                }
            }
            
            for (int i = 0; i < shopButtonList.size(); i++)
            {
                cout << "Test";
                if (shopButtonList[i] -> visible == true and shopButtonList[i]->rect.contains(Mouse::getPosition(app).x, Mouse::getPosition(app).y) == true)
                {
                    cout << "Yes";
                    drawText(getDesc(*shopAttachments[i]), 20, screenW/6, 600, app);
                    
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
                return 2;
            
            }
            
            if (buttonList[1]->clicked == true and character->credits >= button1->cost && character->attachments.size() < character->attachmentSlots)
            {
                buttonList[1]->clicked = false;
                character->attachments.push_back(shopAttachments[0]);
                buttonList[1]->visible = false;
                character->credits -= button1->cost;
            
            }
            
            if (buttonList[2]->clicked == true and character->credits >= button2->cost && character->attachments.size() < character->attachmentSlots)
            {
                buttonList[2]->clicked = false;
                character->attachments.push_back(shopAttachments[1]);
                buttonList[2]->visible = false;
                character->credits -= button2->cost;
            }
            
            if (buttonList[3]->clicked == true and character->credits >= button3->cost && character->attachments.size() < character->attachmentSlots)
            {
                buttonList[3]->clicked = false;
                character->attachments.push_back(shopAttachments[2]);
                buttonList[3]->visible = false;
                character->credits -= button3->cost;
            }


            //draw
            
            for(auto i:entities)
                i->draw(app);
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
