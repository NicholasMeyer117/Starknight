#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "State.h"
#include "Button.h"

class MenuState: public State
{
    public:
    std::vector<Button*> buttonList;
    int screenW;
    int screenH;
    sf::Font mainGameFont;
    sf::Text source;
    
    void createState(Game *game)
    {
        screenW = game->screenW;
        screenH = game->screenH;
        source = game->source;
    
    }
    
    int Run(sf::RenderWindow &app)
    {
        Button *startGame = new Button;
        startGame->createButton(500, 200, 200, 50, &mainGameFont, "START", 40); 
        buttonList.push_back(startGame);
        
        while (app.isOpen())
        {
            Event event;
            while (app.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    app.close();
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
