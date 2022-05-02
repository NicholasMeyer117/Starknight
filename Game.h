#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <list>
#include <math.h>
#include <cstring>
#include "Character.h"
#include "Entity.h"
#include "Actor.h"
#include "Enemy.h"
#include "State.h"
#include "SynergyHandler.h"
#define PI 3.14159265

class Game
{

    public:
    RenderWindow app;
    enum gameState {mainMenu, hub, game, shop, settings};
    int area = 2; //each area consists of several levels and ends with a boss
    int level = 2;
    int screenWidth;
    int screenHeight;
    int relUnitX;
    int relUnitY;
    sf::Text source;
    sf::Font gameFont;
    Character *character = new Character;
    std::vector<State*> stateList; //0=mainMenu, 1=Hub, 2=game, 3=Shop, 4=Settings)
    std::array<Texture, 2> bulletTextureList;
    SynergyHandler *synergyHandler = new SynergyHandler;
    
    bool showHitBoxes = false;
    
    void resizeWindow();
    
    void startGame(int W, int H, sf::Text Source, sf::Font font)
    {
        source = Source;
        gameFont = font;
        screenWidth = W;
        screenHeight = H;
        relUnitX = screenWidth/100;
        relUnitY = screenHeight/100;
        
        Texture b1, b2, b3, b4;
        b1.loadFromFile("images/newBullet.png");
        bulletTextureList[0] = b1;
        b2.loadFromFile("images/siphonBullet.png");
        bulletTextureList[1] = b2;
    }
    
    void nextStage()
    {
        if (level%5 != 0)
            level++;
        else
        {
            level = 1;
            area++;
        }
    }
    
    void changeState();
    
    void beginLevel();
    
    
    

};
