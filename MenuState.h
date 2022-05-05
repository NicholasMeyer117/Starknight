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
#include "ParticleSystem.h"

class MenuState: public State
{
    public:
    std::vector<Button*> buttonList;
    int screenW;
    int screenH;
    sf::Font gameFont;
    sf::Font spaceFont;
    sf::Text source;
    sf::Text titleText;
    
    void createState(Game *game)
    {
        screenW = game->screenWidth;
        screenH = game->screenHeight;
        source = game->source;
        spaceFont.loadFromFile("space_age.ttf");
        gameFont = game->gameFont;
        
    
    }
    
    int Run(sf::RenderWindow &app)
    {
        sf::Vector2i pixelPos = sf::Mouse::getPosition(app);
        sf::Vector2f worldPos = app.mapPixelToCoords(pixelPos);
        
        titleText.setFont(spaceFont);
        titleText.setString("STARKNIGHT");
        titleText.setCharacterSize(70);
        titleText.setFillColor(sf::Color::White);
        sf::FloatRect textRect = titleText.getLocalBounds();
        titleText.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
        titleText.setPosition(screenW/1.5, screenH/8);
        
        RectangleShape buttonBacker;
        buttonBacker.setSize(sf::Vector2f(400, screenH));
        buttonBacker.setOutlineColor(sf::Color::Black);
        buttonBacker.setFillColor(Color(105,105,105, 100));
        buttonBacker.setOutlineThickness(1);
        buttonBacker.setOrigin(buttonBacker.getSize().x/2, buttonBacker.getSize().y/2);
        buttonBacker.setPosition(screenW/4, screenH/2);
        
        Button *startButton = new Button;
        startButton->createButton(screenW/4, 0 + screenH/6, 300, 75, &gameFont, "START", 20, Color(0, 0, 139, 100)); 
        buttonList.push_back(startButton);
        
        Button *settingsButton = new Button;
        settingsButton->createButton(screenW/4, 0 + 2 * (screenH/6), 300, 75, &gameFont, "SETTINGS", 20, Color(0, 0, 139, 100)); 
        buttonList.push_back(settingsButton);
        
        Button *creditsButton = new Button;
        creditsButton->createButton(screenW/4, 0 + 3 * (screenH/6), 300, 75, &gameFont, "CREDITS", 20, Color(0, 0, 139, 100)); 
        buttonList.push_back(creditsButton);
        
        Button *quitButton = new Button;
        quitButton->createButton(screenW/4, 0 + 4 * (screenH/6), 300, 75, &gameFont, "QUIT", 20, Color(0, 0, 139, 100)); 
        buttonList.push_back(quitButton);
        
        ParticleSystem backParticles1(400, 20000, 10, 100, 4, Color::White, 0, screenH/8, screenH, screenW, 0);
        ParticleSystem backParticles2(800, 20000, 10, 150, 4, Color::White, 0, screenH/8, screenH, screenW, 0, 200);
        ParticleSystem backParticles3(400, 20000, 10, 200, 4, Color::White, 0, screenH/8, screenH, screenW, 0, 100);
        sf::Clock clock;
        
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
                        sf::Vector2i pixelPos = sf::Mouse::getPosition(app);
                        sf::Vector2f worldPos = app.mapPixelToCoords(pixelPos);
                        if (i -> visible == true and i->rect.contains(worldPos.x, worldPos.y) == true)
                        {
                            if (Mouse::isButtonPressed(Mouse::Left))
                                i->leftClicked = true;
                            else if (Mouse::isButtonPressed(Mouse::Right))
                                i->rightClicked = true; 
                            cout << "click!";
                        }
                    }   
                }
            }
            
            if (buttonList[0]->leftClicked == true)
            {
                buttonList[0]->leftClicked = false;
                return 1;
            
            }
            if (buttonList[3]->leftClicked == true)
            {
                buttonList[3]->leftClicked = false;
                return -1;
            
            }

            //draw
            app.clear(Color::Black);
            sf::Time elapsed = clock.restart();
            backParticles1.update(elapsed, true);
            backParticles2.update(elapsed, true);
            backParticles3.update(elapsed, true);
            app.draw(backParticles3);
            app.draw(backParticles2);
            app.draw(backParticles1);
            app.draw(buttonBacker);
            for(auto i:buttonList)
            {
                app.draw(i->rectangle);
                app.draw(i->buttonText);
            }
            
            app.draw(titleText);
            app.display();
        }
    
    
        return 0;
    }
};
