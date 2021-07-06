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
#include "Enemy.h"
#define PI 3.14159265

class Game
{

    public:
    RenderWindow app;
    enum gameState {mainMenu, hub, game, shop, settings};
    int area = 0; //each area consists of several levels and ends with a boss
    int level = 0;
    int screenW;
    int screenH;
    sf::Text source;
    sf::Font gameFont;
    
    void resizeWindow();
    
    void startGame(int W, int H, sf::Text Source, sf::Font font)
    {
        source = Source;
        gameFont = font;
        screenW = W;
        screenH = H;
    }
    
    void changeState();
    
    void beginLevel();
    
    
    

};
