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
#include "CrewHandler.h"
#define PI 3.14159265

extern int screenW;
extern int screenH;
extern RenderWindow app;
extern View view;

class Game
{

    public:
    enum gameState {mainMenu, hub, game, shop, settings};
    int area = 1; //each area consists of several levels and ends with a boss
    int level = 1;
    int screenWidth;
    int screenHeight;
    int relUnitX;
    int relUnitY;
    
    int nextStageType = 0; //0 = regular level, 1 = Don't get hit challenge level
    sf::Text source;
    sf::Font gameFont;
    Character *character = new Character;
    std::vector<State*> stateList; //0=mainMenu, 1=Hub, 2=game, 3=Shop, 4=Settings)
    std::array<Texture, 6> bulletTextureList;
    SynergyHandler *synergyHandler = new SynergyHandler();
    CrewHandler *crewHandler = new CrewHandler();
    
    bool showHitBoxes = false;
    
    void resizeWindow();
    
    void startGame(int W, int H, sf::Text Source, sf::Font font)
    {
        source = Source;
        gameFont = font;
        screenWidth = screenW;
        screenHeight = screenH;
        relUnitX = screenW/100;
        relUnitY = screenH/100;
        
        Texture b1, b2, b3, b4, b5, b6;
        b1.loadFromFile("images/bullet.png");
        bulletTextureList[0] = b1;
        b2.loadFromFile("images/greenBullet.png");
        bulletTextureList[1] = b2;
        b3.loadFromFile("images/redBullet.png");
        bulletTextureList[2] = b3;
        b4.loadFromFile("images/yellowBullet.png");
        bulletTextureList[3] = b4;
        b5.loadFromFile("images/dartBullet.png");
        bulletTextureList[4] = b5;
        b6.loadFromFile("images/missile.png");
        bulletTextureList[5] = b6;
        
    }
    void restartGame()
    {
        area = 1;
        level = 1;
        crewHandler->crewList.clear();
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
    
    int getNextStageChoices()
    {
        if (level == 4)
            return 1;
        //srand(time(NULL));
        //int randNum = rand() % 2 + 1;
        int randNum = 2;
        return randNum;
    
    }
    
    
    void changeState();
    
    void setUpLevel(int &currentLevelType, float &maxLevelProgress)
    {
        currentLevelType = nextStageType;
        if (currentLevelType == 0)
            maxLevelProgress = 3000;
        else if (currentLevelType == 1)
            maxLevelProgress = 3000;
            
    
    }
    
    
    

};
