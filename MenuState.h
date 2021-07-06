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

class MenuState: public State
{
    public:
    std::vector<Button*> buttonList;
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
        
    
    }
    
    int Run(sf::RenderWindow &app)
    {
        Button *startButton = new Button;
        startButton->createButton(600, 200, 200, 50, &gameFont, "START", 20); 
        buttonList.push_back(startButton);
        
        Button *settingsButton = new Button;
        settingsButton->createButton(600, 300, 200, 50, &gameFont, "SETTINGS", 20); 
        buttonList.push_back(settingsButton);
        
        Button *creditsButton = new Button;
        creditsButton->createButton(600, 400, 200, 50, &gameFont, "CREDITS", 20); 
        buttonList.push_back(creditsButton);
        
        Button *quitButton = new Button;
        quitButton->createButton(600, 500, 200, 50, &gameFont, "QUIT", 20); 
        buttonList.push_back(quitButton);
        
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
                return -1;
            
            }

            //draw
            app.clear(Color(255,255,255,255));
            for(auto i:buttonList)
            {
                app.draw(i->rectangle);
                app.draw(i->buttonText);
            }
            app.display();
        }
    
    
        return 0;
    }
};
