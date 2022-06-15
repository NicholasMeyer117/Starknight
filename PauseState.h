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
#include "Actor.h"

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
    Actor *player;
    Texture pauseTex;
    
    PauseState(Game *game, Texture PauseTex, Actor *Player)
    {
        source = game->source;
        gameFont = game->gameFont;
        curGame = game;
        relUnitX = game->relUnitX;
        relUnitY = game->relUnitY;
        
        player = Player;
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
    
    void displayLevelInfo(Actor *player, sf::RenderWindow& app)
    {
        drawText("Level Info:", 20, (relUnitX * 5), (relUnitY * 14), app);
        drawText("Area: " + to_string(curGame->area), 16, (relUnitX * 5), (relUnitY * 18), app);
        drawText("Level: " + to_string(curGame->level), 16, (relUnitX * 5), (relUnitY * 22), app);
    
    
    }
    
    void displayPlayerMults(Actor *player, sf::RenderWindow& app)
    {
        drawText("Player Multipliers:", 20, (relUnitX * 75), (relUnitY * 60), app);
        drawText("Speed Mult: " + to_string(player->speedMult), 16, (relUnitX * 75), (relUnitY * 64), app);
        drawText("Health Mult: " + to_string(player->healthMult), 16, (relUnitX * 75), (relUnitY * 68), app);
        drawText("Damage Mult: " + to_string(player->damageMult), 16, (relUnitX * 75), (relUnitY * 72), app);
        drawText("Firerate Mult: " + to_string(player->fireRateMult), 16, (relUnitX * 75), (relUnitY * 76), app);
        drawText("Bullet Speed Mult: " + to_string(player->bulletSpeedMult), 16, (relUnitX * 75), (relUnitY * 80), app);
        drawText("Healing Mult: " + to_string(player->healingMult), 16, (relUnitX * 75), (relUnitY * 84), app);
    }
    
    void displayPlayerStats(Actor *player, sf::RenderWindow& app)
    {
        drawText("Player Stats:", 20, (relUnitX * 75), (relUnitY * 14), app);
        drawText("Current Health: " + to_string(player->health), 16, (relUnitX * 75), (relUnitY * 18), app);
        drawText("Max Health: " + to_string(player->maxHealth), 16, (relUnitX * 75), (relUnitY * 22), app);
        drawText("Shields: " + to_string(player->shields), 16, (relUnitX * 75), (relUnitY * 26), app);
        drawText("Speed: " + to_string(player->speed), 16, (relUnitX * 75), (relUnitY * 30), app);
        drawText("iFrames: " + to_string(player->iFrames), 16, (relUnitX * 75), (relUnitY * 34), app);
    
    
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
            displayPlayerStats(player, app);
            displayPlayerMults(player, app);
            displayLevelInfo(player, app);
            drawText("PAUSED", 60, relUnitX * 45, relUnitY * 40, app);
            app.display();

        }
    
    
        return 0;
    }


};
