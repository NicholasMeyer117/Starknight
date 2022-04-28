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
        
        Texture t1, t2, t3, t4, t5, t6, t7;
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
        
        Texture i1, i2, i3, i4, i5, i6, i7;
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
    
    //Generates Shop Button
    bool generateButton(ShopButton *button, int attachNum, int butNum )
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
                     if (ifContains(curAtc)->level == 3)
                         return 1;
                }
                button->createIcon(textureList[0], spriteList[0], butNum, 250, 250, &gameFont, ("Cannon: " + to_string(cost) + " Cr"), 20, cost);
                //cannon->createAttachment(bulletSpriteList[0]);
                shopAttachments.push_back(cannon);
                return 0;     
            } 
            case 1:
            {
                MachineGun *machineGun = new MachineGun(bulletSpriteList[0]);
                cost = machineGun->credits;
                curAtc = machineGun;
                if (ifContains(curAtc) != NULL)
                {
                     cost = ifContains(curAtc)->credits;
                     if (ifContains(curAtc)->level == 3)
                         return 1;
                }
                button->createIcon(textureList[1], spriteList[1], butNum, 250, 250, &gameFont, "Machine Gun: 5 Cr", 20, cost);
                //machineGun->createAttachment(bulletSpriteList[0]);
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
                     if (ifContains(curAtc)->level == 3)
                         return 1;
                }
                button->createIcon(textureList[2], spriteList[2], butNum, 250, 250, &gameFont, "Repair Droid: 5 Cr", 20, cost);
                //repairDroid->createAttachment();
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
                     if (ifContains(curAtc)->level == 3)
                         return 1;
                }
                button->createIcon(textureList[3], spriteList[3], butNum, 250, 250, &gameFont, "Siphon Droid: 10 Cr", 20, cost);
                //siphonDroid->createAttachment(bulletSpriteList[1]);
                shopAttachments.push_back(siphonDroid);
                return 0;
            }
            case 4:
            {
                Shotgun *shotgun = new Shotgun(bulletSpriteList[0]);
                cost = shotgun->credits;
                curAtc = shotgun;
                if (ifContains(curAtc) != NULL)
                {
                     cost = ifContains(curAtc)->credits;
                     if (ifContains(curAtc)->level == 3)
                         return 1;
                }
                button->createIcon(textureList[4], spriteList[4], butNum, 250, 250, &gameFont, "Shotgun: 5 Cr", 20, cost);
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
                     if (ifContains(curAtc)->level == 3)
                         return 1;
                }
                button->createIcon(textureList[5], spriteList[5], butNum, 250, 250, &gameFont, "Time Dilator: 5 Cr", 20, 5);
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
                     if (ifContains(curAtc)->level == 3)
                         return 1;
                }
                button->createIcon(textureList[6], spriteList[6], butNum, 250, 250, &gameFont, "Hull Booster: 5 Cr", 20, 5);
                //hullBooster->createAttachment();
                shopAttachments.push_back(hullBooster);
                return 0;
            }
        
        
        }
        
        return 0;
        
    }
    
    void createSlotButtons(int attachNum)
    {
        String name = character->attachments[attachNum]->name;
        Sprite sprite;
        ImageButton *button = new ImageButton;
        int textNum;
        if (name == "Cannon")
        {
            textNum = 0;
        }
        else if (name == "Machine Gun")
        {
            textNum = 1;
        }
        else if (name == "Repair Droid")
        {
            textNum = 2;
        }
        else if (name == "Siphon Droid")
        {
            textNum = 3;
        }
        else if (name == "Shotgun")
        {
            textNum = 4;
        }
        else if (name == "Time Dilator")
        {
            textNum = 5;
        }
        else if (name == "Hull Booster")
        {
            textNum = 6;
        }
            
        sprite.setScale(.4, .4);
        sprite.setPosition(screenW - 400, 150 + (150 * attachNum));
        //the [textNum + i] represents the offset from double textures at the beginning. i must be iterated each time a new attachment is added
        button->createImageButton(textureList[textNum + 7], spriteList[textNum + 7], screenW - 400, 150 + (150 * attachNum), 100, 100);
        attachmentSlotButtons.push_back(button);
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
                return "Cannon: Fires a single medium damage shot (Gun)\nFirerate: 1/s  ->  2/s\nSpeed: 20\nDamage: 5  ->  10";
            else if (levelNum == 2)
                return "Cannon: Fires a single medium damage shot (Gun)\nFirerate: 2/s  ->  4/s\nSpeed: 20\nDamage: 10  ->  20";
            else if (levelNum == 3)
                return "Cannon: Fires a single medium damage shot (Gun)\nFirerate: 4/s\nSpeed: 20\nDamage: 20";
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
            if (levelNum == 1)
                return "Repair Droid: Repairs your ship over time (Repair)\nFirerate: 1/5s\nHealth: 5  ->  10";
            if (levelNum == 2)
                return "Repair Droid: Repairs your ship over time (Repair)\nFirerate: 1/5s\nHealth: 10  ->  20";
        }
        else if (name == "Siphon Droid")
        {
            if (levelNum == 0)
                return "Siphon Droid: Fires a projectile that repairs ship equal to damage dealt (Gun) (Repair)\nFirerate: 1/1.25s\nSpeed: 20\nDamage: 5";
            if (levelNum == 1)
                return "Siphon Droid: Fires a projectile that repairs ship equal to damage dealt (Gun) (Repair)\nFirerate: 1/1.25s\nSpeed: 20\nDamage: 5  ->  10";
            if (levelNum == 2)
                return "Siphon Droid: Fires a projectile that repairs ship equal to damage dealt (Gun) (Repair)\nFirerate: 1/1.25s\nSpeed: 20\nDamage: 10  ->  20";
        }
        else if (name == "Shotgun")
        {
            if (levelNum == 0)
                return "Shotgun: Fires a spread of 3 medium damage projectiles (Gun)\nFirerate: 1/2s\nSpeed: 15\nDamage: 5\nShots: 3\nAngle: 45";
            if (levelNum == 1)
                return "Shotgun: Fires a spread of 3 medium damage projectiles (Gun)\nFirerate: 1/1.5s\nSpeed: 15\nDamage: 5  ->  10\nShots: 3\nAngle: 45  ->  22.5";
            if (levelNum == 2)
                return "Shotgun: Fires a spread of 5 medium damage projectiles (Gun)\nFirerate: 1/s\nSpeed: 15\nDamage: 10  ->  20\nShots: 3  ->  5\nAngle: 22.5  ->  11.25";
        }
        else if (name == "Time Dilator")
        {
            if (levelNum == 0)
                return "Time Dilator: Slows starting map speed (Manipulator)\nPercentage: 10%";
            if (levelNum == 1)
                return "Time Dilator: Slows starting map speed (Manipulator)\nPercentage: 10%  ->  20%";
            if (levelNum == 2)
                return "Time Dilator: Slows starting map speed (Manipulator)\nPercentage: 20%  ->  40%";
        }
        else if (name == "Hull Booster")
        {
            if (levelNum == 0)
                return "Hull Booster: Increase Max Health (Utility)\nPercentage: 25%";
            if (levelNum == 1)
                return "Hull Booster: Increase Max Health (Utility)\nPercentage: 25%  ->  50%";
            if (levelNum == 2)
                return "Hull Booster: Increase Max Health (Utility)\nPercentage: 50%  ->  100%";
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
        
        Button *sellButton = new Button;
        sellButton -> createButton (0, 0, 150, 50, &gameFont, "SELL", 20);
        sellButton->visible = false;
        buttonList.push_back(sellButton);
        
        srand(time(NULL));
        
        int randNum = rand() % 7;
        ShopButton *button1 = new ShopButton;
        generateButton(button1, randNum, 1);
        //buttonList.push_back(button1);
        shopButtonList.push_back(button1);
        
        randNum = rand() % 7;
        ShopButton *button2 = new ShopButton;
        generateButton(button2, randNum, 2);
        //buttonList.push_back(button2);
        shopButtonList.push_back(button2);
        
        randNum = rand() % 7;
        ShopButton *button3 = new ShopButton;
        generateButton(button3, randNum, 3);
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
          
        //Check for any buttons clicked 
        while (app.isOpen())
        {
            Event event;
            while (app.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    app.close();
                    
                else if (event.type == sf::Event::MouseButtonPressed) 
                {
                 
                    //Check for regular buttons clicked
                    //std::cout << "Mouse Position on Screen: " + to_string(Mouse::getPosition(app).x) + " , " + to_string(Mouse::getPosition(app).y) << std::endl;
                    for (auto i:buttonList)
                    {
                        if (i -> visible == true and i->rect.contains(Mouse::getPosition(app).x, Mouse::getPosition(app).y) == true)
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
                        if (i -> visible == true and i->rect.contains(Mouse::getPosition(app).x, Mouse::getPosition(app).y) == true)
                        {
                            if (Mouse::isButtonPressed(Mouse::Left))
                                i->leftClicked = true;
                            else if (Mouse::isButtonPressed(Mouse::Right))
                                i->rightClicked = true; 
                        }
                    }   
                    
                    //Check for attachment slot buttons clicked
                    for (auto i:attachmentSlotButtons)
                    {
                        if (i -> visible == true and i->rect.contains(Mouse::getPosition(app).x, Mouse::getPosition(app).y) == true)
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
            
            for (int i = 0; i < shopButtonList.size(); i++)
            {
                if (shopButtonList[i] -> visible == true and shopButtonList[i]->rect.contains(Mouse::getPosition(app).x, Mouse::getPosition(app).y) == true)
                {
                    drawText(getDesc(*shopAttachments[i]), 20, screenW/6, 600, app);
                    
                }
            }
            
           /* FloatRect rect;
            for (int i = 0; i < attachmentSlotSprites.size(); i++)
            {
                rect = attachmentSlotSprites[i].getGlobalBounds();
                if (rect.contains(Mouse::getPosition(app).x, Mouse::getPosition(app).y) == true)
                {
                    drawText(getDesc(*character->attachments[i]), 20, screenW/6, 600, app);
                    //cout<<to_string(i);
                }
            }*/
            
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
                
                bool AtFullLevel = false;
                ShopButton *button1 = new ShopButton;
                do
                {
                    int randNum = rand() % 7;
                    AtFullLevel = generateButton(button1, randNum, 1);
                } while (AtFullLevel == true);
                shopButtonList.push_back(button1);
        
                ShopButton *button2 = new ShopButton;
                do
                {
                    int randNum = rand() % 7;
                    AtFullLevel = generateButton(button2, randNum, 2);
                } while (AtFullLevel == true);
                shopButtonList.push_back(button2);
        
                ShopButton *button3 = new ShopButton;
                do
                {
                    int randNum = rand() % 7;
                    AtFullLevel = generateButton(button3, randNum, 3);
                } while (AtFullLevel == true);
                shopButtonList.push_back(button3);
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
                        cout << "\n" + character->attachments[i]->name + ": " + to_string(character->attachments[i]->credits) + "\n";
                        character->attachments.erase(next(begin(character->attachments), + i));
                        attachmentSlotButtons.clear();
                        for (int j = 0; j < character->attachments.size(); j++)
                        {
                            createSlotButtons(j);
                        }
                    }
                }
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
                        cout << "LEVEL: " << alreadyHas -> level << "\n";
                        alreadyHas->upgrade();
                        cout << "LEVEL IS NOW: " << alreadyHas -> level << "\n";
                    }
                    else
                    {
                        cout << "LEVEL: " << alreadyHas -> level << "\n";
                        continue;
                        
                    }
                    shopButtonList[i]->leftClicked = false;
                    shopButtonList[i]->visible = false;
                    character->credits -= shopButtonList[i]->cost;
                }
            }

            //draw
            
            for(auto i:entities)
                i->draw(app);
            for(auto i:slotRectangles)
                app.draw(i);
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
            app.display();
            app.clear(Color(200,200,200,255));
        }
    
        return -1;
    }

};
