#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <list>
#include <stdlib.h> 
#include <math.h>
#include <cstring>

using namespace sf;
using namespace std;

extern RenderWindow app;
extern int screenW;
extern int screenH;

class PauseState
{
    public: 
    Game *curGame;
    int relUnitX;
    int relUnitY;
    sf::Font gameFont;
    sf::Text source;
    sf::View *pauseView;//(sf::Vector2f(screenW/2, screenH/2), sf::Vector2f(screenW/2, screenH/2));
    Texture pauseTex;
    
    PauseState(Game *game, Texture PauseTex)
    {
        source = game->source;
        gameFont = game->gameFont;
        curGame = game;
        relUnitX = game->relUnitX;
        relUnitY = game->relUnitY;
        
        pauseTex = PauseTex;
        pauseView = new View(sf::Vector2f(screenW/2, screenH/2), sf::Vector2f(screenW, screenH));
        pauseView->setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
        app.setView(*pauseView);

    }
    
    void drawText( const sf::String &str, const int Size, const float xposition, const float yposition, sf::RenderWindow& window)
    {
        source.setString(str);
        source.setCharacterSize(Size); //only the lower cased word size is reserved. A capital S fixes that.
        source.setPosition(xposition,yposition);
        source.setFillColor(Color::White);
        window.draw(source);
    }
    
    int Run()
    {
        //Texture pauseTex;
        //pauseTex.loadFromFile("images/screenshot.png");
        Sprite pauseImage(pauseTex);
        while (app.isOpen())
        {
            Event event;
            while (app.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    app.close();
                
                if (event.type == Event::KeyPressed)
                {
                     if (event.key.code == Keyboard::Escape)
                     {
                         return 0;
                     }
             
                 }
            }
            app.clear(Color::White);
            app.draw(pauseImage);
            drawText("PAUSED", 60, relUnitX * 45, relUnitY * 40, app);
            app.display();

        }
    
    
        return 0;
    }


};
