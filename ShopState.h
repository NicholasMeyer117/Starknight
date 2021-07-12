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
#include "Attachment.h"
#include "Enemy.h"
#include "Character.h"

class ShopState: public State
{
    public:
    std::vector<Button*> buttonList;
    std::vector<ShopButton*> shopButtonList;
    std::vector<Texture> textureList;
    std::vector<Sprite> spriteList;
    std::vector<Texture*> bulletTextureList;
    std::vector<Sprite> bulletSpriteList;
    std::vector<Attachment*> shopAttachments;
    Character *character = new Character;
    int screenW;
    int screenH;
    sf::Font gameFont;
    sf::Text source;
    
    void createState(Game *game)
    {
        screenW = game->screenW;
        screenH = game->screenH;
        source = game->source;
        gameFont = game->gameFont; 
        character = game->character;
        
        Texture t1, t2, t3, t4;
        t1.loadFromFile("images/cannon.png");
        textureList.push_back(t1);
        t2.loadFromFile("images/machineGun.png");
        textureList.push_back(t2);
        
        for (auto i:textureList)
        {
            Sprite sprite;
            sprite.setTexture(i);
            spriteList.push_back(sprite);
           
        }
        
        Texture *b1, *b2, *b3, *b4;
        b1->loadFromFile("images/cannonBullet.png");
        bulletTextureList.push_back(b1);
        
        for (auto i:bulletTextureList)
        {
            Sprite sprite;
            sprite.setTexture(*i);
            bulletSpriteList.push_back(sprite);
           
        }
        
    
    }
    
    int Run(sf::RenderWindow &app)
    {
        Button *continueButton = new Button;
        continueButton->createButton(1000, 700, 200, 50, &gameFont, "CONTINUE", 20); 
        buttonList.push_back(continueButton);
        
        ShopButton *button1 = new ShopButton;
        button1->createIcon(textureList[0], spriteList[0], 1, 250, 250, &gameFont, "Cannon: 3 Cr", 20);
        buttonList.push_back(button1);
        shopButtonList.push_back(button1);
        
        ShopButton *button2 = new ShopButton;
        button2->createIcon(textureList[1], spriteList[1], 2, 250, 250, &gameFont, "Machine Gun: 3 Cr", 20);
        buttonList.push_back(button2);
        shopButtonList.push_back(button2);
        
        ShopButton *button3 = new ShopButton;
        button3->createIcon(textureList[0], spriteList[0], 3, 250, 250, &gameFont, "Cannon: 3 Cr", 20);
        buttonList.push_back(button3);
        shopButtonList.push_back(button3);
        
        Cannon *cannon = new Cannon;
        cannon->createAttachment(bulletSpriteList[0]);
        shopAttachments.push_back(cannon);
        
        MachineGun *machineGun = new MachineGun;
        machineGun->createAttachment(bulletSpriteList[0]);
        shopAttachments.push_back(machineGun);
           
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
                            cout << "click!";
                        }
                    }   
                }
            }
            
            if (buttonList[0]->clicked == true)
            {
                buttonList[0]->clicked = false;
                buttonList.clear();
                shopButtonList.clear();
                shopAttachments.clear();
                return 2;
            
            }
            
            if (buttonList[1]->clicked == true)
            {
                buttonList[1]->clicked = false;
                character->attachments.push_back(shopAttachments[0]);
                buttonList[1]->visible = false;
            
            }
            
            if (buttonList[2]->clicked == true)
            {
                buttonList[2]->clicked = false;
                character->attachments.push_back(shopAttachments[1]);
                buttonList[2]->visible = false;
            }


            //draw
            app.clear(Color(255,255,255,255));
            for(auto i:buttonList)
            {
                   app.draw(i->rectangle);
                   app.draw(i->buttonText);
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
            app.display();
        }
    
        return -1;
    }

};
