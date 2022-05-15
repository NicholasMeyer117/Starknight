#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <list>
#include <stdlib.h> 
#include <math.h>
#include <cstring>
#include "Game.h"
#include "State.h"
#include "Button.h"
#include "Crew.h"

class HubState: public State
{
    public:
    std::vector<Button*> buttonList;
    std::vector<Sprite> shipSprites;
    std::vector<RectangleShape> slotDiamonds;
    int screenW;
    int screenH;
    int relUnitX;
    int relUnitY;
    int curShipNum = 0;
    sf::Font gameFont;
    sf::Text source;
    Character *curChar;
    
    void createState(Game *game)
    {
        screenW = game->screenWidth;
        screenH = game->screenHeight;
        relUnitX = game->relUnitX;
        relUnitY = game->relUnitY;
        source = game->source;
        gameFont = game->gameFont;
        curChar = game->character;

    }
    
    float crossProduct(Vector2f a, Vector2f b)
    {
        float ax = a.x;
        float ay = a.y;
        
        float bx = b.x;
        float by = b.y;
        
        float cx = ax * by - ay * bx;
        
        return cx;
    }
    
    float dotProduct(Vector2f a, Vector2f b)
    {
       return a.x * b.x + a.y * b.y;
    }
    
    bool sameSide(Vector2f p1, Vector2f p2, Vector2f a, Vector2f b)
    {
        Vector2f temp1;
        temp1.x = b.x - a.x;
        temp1.y = b.y - a.y;
        
        Vector2f temp2;
        temp2.x = p1.x - a.x;
        temp2.y = p1.y - a.y;
        
        float cp1 = crossProduct(temp1, temp2);

        temp2.x = p2.x - a.x;
        temp2.y = p2.y - a.y;
        
        float cp2 = crossProduct(temp1, temp2);
        
        if (cp1 * cp2 >= 0)
        {
            //cout << "\nDot Product: " + to_string(dotProduct(cp1, cp2));
            return true;
        }
        return false;
        
    
    }
    
    bool triangleClicked(CircleShape triangle, int angle, Vector2f pointM)
    {
        Vector2f point1;
        Vector2f point2;
        Vector2f point3;
        
        if (angle == 0)
        {
            point1 = Vector2f(triangle.getPosition().x - triangle.getRadius(), triangle.getPosition().y + triangle.getRadius()/2);
            point2 = Vector2f(triangle.getPosition().x, triangle.getPosition().y - triangle.getRadius());
            point3 = Vector2f(triangle.getPosition().x + triangle.getRadius(), triangle.getPosition().y + triangle.getRadius()/2);
        }
        else if (angle == 180)
        {
            point1 = Vector2f(triangle.getPosition().x - triangle.getRadius(), triangle.getPosition().y - triangle.getRadius()/2);
            point2 = Vector2f(triangle.getPosition().x, triangle.getPosition().y + triangle.getRadius());
            point3 = Vector2f(triangle.getPosition().x + triangle.getRadius(), triangle.getPosition().y - triangle.getRadius()/2);
        }
        
        cout << "\n" + to_string(point1.x) + "," + to_string(point1.y);
        cout << "\n" + to_string(point2.x) + "," + to_string(point2.y);
        cout << "\n" + to_string(point3.x) + "," + to_string(point3.y)+ "\n";
        
        if (sameSide(pointM, point1, point2, point3) && sameSide(pointM, point2, point1, point3) && sameSide(pointM, point3, point1, point2))
            return true;
        return false;
    }
    
    void drawText( const sf::String &str, const int Size, const float xposition, const float yposition, sf::RenderWindow& window)
    {
        source.setString(str);
        source.setCharacterSize(Size); //only the lower cased word size is reserved. A capital S fixes that.
        source.setPosition(xposition,yposition);
        source.setFillColor(Color::Black);
        window.draw(source);
    }
    
    void createCrewSlots()
    {
       slotDiamonds.clear();
       cout <<"\nCrew Slots: "<< curChar -> crewSlots << "\n";
       for (int i = 0; i < curChar -> crewSlots; i++)
       {
           cout <<"\nSLOT CREATED\n";
           sf::RectangleShape slot;
           slot.setSize(sf::Vector2f(100, 100));
           slot.setOutlineColor(sf::Color::Black);
           slot.setFillColor(Color(150,150,150,255));
           slot.setOutlineThickness(5);
           //slot.setPosition();
           slot.setPosition(relUnitX * 90, relUnitY * 5 + ((relUnitY * 20) * i));
           slot.setRotation(45);
           slotDiamonds.push_back(slot);
          
       
       }
    }
    
    String getName(int num)
    {
        switch(num)
        {
            case 0:
            {
                return "Warhorse MKIII: Starfighter";
            }
            case 1:
            {
                return "Battering Ram: Heavy Fighter";
            }
            case 2:
            {
                return "Serpent: Interceptor";            
            }
        }
        
        return "Bruh";
    } 
    
    String getDesc(int num)
    {
        switch(num)
        {
            case 0:
            {
                curChar->attachmentSlots = 3;
                curChar->crewSlots = 1;
                return "Health: 100\nSpeed: 5\nShields: 0\nDamage: (x1.0)\nAttachments: 3";
            }
            case 1:
            {
                curChar->attachmentSlots = 4;
                curChar->crewSlots = 2;
                return "Health: 150\nSpeed: (x0.75)\nShields: 0\nDamage: (x1.25)\nAttachments: 4";
            }
            case 2:
            {
                curChar->attachmentSlots = 2;
                curChar->crewSlots = 0;
                return "Health: 75\nSpeed: (x1.25)\nShields: 0\nDamage: (x1.25)\nAttachments: 2";
            }
        }
        return "Bruh";
    } 
    
    int Run(sf::RenderWindow &app)
    {
        sf::Vector2i pixelPos = sf::Mouse::getPosition(app);
        sf::Vector2f worldPos = app.mapPixelToCoords(pixelPos);
        
        Texture t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12;
        t1.loadFromFile("images/warhorse.png");
        t2.loadFromFile("images/batteringRam.png");
        t3.loadFromFile("images/serpent.png");
        
        t1.setSmooth(true);
        t2.setSmooth(true);
        t3.setSmooth(true);
        
        sf::CircleShape upArrow(80.f, 3);
        upArrow.setFillColor(Color::Black);
        upArrow.setOrigin(sf::Vector2f(upArrow.getRadius(), upArrow.getRadius()));
        upArrow.setPosition(relUnitX * 10, relUnitY * 10);
        
        sf::CircleShape downArrow(80.f, 3);
        downArrow.setFillColor(Color::Black);
        downArrow.setOrigin(sf::Vector2f(downArrow.getRadius(), downArrow.getRadius()));
        downArrow.setPosition(relUnitX * 10, relUnitY * 50);
        downArrow.rotate(180);
        
        sf::CircleShape upArrow2(80.f, 3);
        upArrow2.setFillColor(Color::Black);
        upArrow2.setOrigin(sf::Vector2f(upArrow2.getRadius(), upArrow2.getRadius()));
        upArrow2.setPosition(relUnitX * 75, relUnitY * 10);
        
        sf::CircleShape downArrow2(80.f, 3);
        downArrow2.setFillColor(Color::Black);
        downArrow2.setOrigin(sf::Vector2f(downArrow2.getRadius(), downArrow2.getRadius()));
        downArrow2.setPosition(relUnitX * 75, relUnitY * 50);
        downArrow2.rotate(180);
    
        Button *playButton = new Button;
        playButton->createButton(relUnitX * 90, relUnitY * 90, 200, 50, &gameFont, "PLAY", 20); 
        buttonList.push_back(playButton);
        
        Sprite triSprite(t1);
        triSprite.setOrigin(sf::Vector2f(26, 38));
        shipSprites.push_back(triSprite);
        
        Sprite battSprite(t2);
        battSprite.setOrigin(sf::Vector2f(38, 45));
        shipSprites.push_back(battSprite);
        
        Sprite serpSprite(t3);
        serpSprite.setOrigin(sf::Vector2f(25, 25));
        shipSprites.push_back(serpSprite);
        
        for (int i = 0; i < shipSprites.size(); i++)
        {
            shipSprites[i].setPosition(relUnitX * 10, relUnitY * 30);
            shipSprites[i].setScale(2, 2);
        }
        
        
        while (app.isOpen())
        {
        
            pixelPos = sf::Mouse::getPosition(app);
            worldPos = app.mapPixelToCoords(pixelPos);
        
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
                        cout << "\nButton: (" << i->rect.left << "," << i->rect.top << ") and " << i->rect.width << " x " << i->rect.height << "\n"; 
                        if (i -> visible == true and i->rect.contains(worldPos.x, worldPos.y) == true)
                        {
                            cout << "BUTTON CLICKED";
                            if (Mouse::isButtonPressed(Mouse::Left))
                                i->leftClicked = true;
                            else if (Mouse::isButtonPressed(Mouse::Right))
                                i->rightClicked = true; 
                        }
                    }   
                    
                    if (triangleClicked(upArrow, 0, Vector2f(worldPos)) == true)
                    {
                        //cout << "Up arrow pressed!";
                        curShipNum--;
                        if (curShipNum == -1)
                            curShipNum = shipSprites.size() - 1;
                    }
                    else if (triangleClicked(downArrow, 180, Vector2f(worldPos)) == true)
                    {
                        curShipNum++;
                        if (curShipNum == shipSprites.size())
                            curShipNum = 0;
                    }
                }
            }
            
            
            
            if (buttonList[0]->leftClicked == true)
            {
                buttonList[0]->leftClicked = false;
                curChar->shipType = curShipNum;
                return 3;
            
            }
            

            //draw
            app.clear(Color(100,100,100,255));
            drawText(getName(curShipNum), 30, screenW/5, screenH/8, app);
            drawText(getDesc(curShipNum), 20, screenW/5, screenH/6, app);
            createCrewSlots();
            app.draw(upArrow);
            app.draw(downArrow);
            app.draw(upArrow2);
            app.draw(downArrow2);
            app.draw(shipSprites[curShipNum]);
            for(auto i:slotDiamonds)
                app.draw(i);
            for(auto i:buttonList)
            {
                app.draw(i->rectangle);
                app.draw(i->buttonText);
            }
            app.display();
        }
    
    
    return -1;
    }
    
    
};
