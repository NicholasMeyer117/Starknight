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
#include "Entity.h"
#include "Button.h"
#include "Actor.h"
#include "Character.h"

using namespace sf;
using namespace std;
float DEGTORAD = 0.017453f;
const int screenW = 1200;
const int screenH = 800;

class bullet: public Entity
{
   public:
   bullet()
   {
     name="bullet";
   }

   void update()
   {
     dx=cos((angle - 90)*DEGTORAD)*12;
     dy=sin((angle - 90)*DEGTORAD)*12;
     // angle+=rand()%7-3;  /*try this*/
     x+=dx;
     y+=dy;

     if (x>screenW || x<0 || y>screenH || y<0) life=0;
   }

};


//check if bullet hits player, player bullet hits enemy, player hits bar, etc
bool checkCollisions(Entity a, std::list<Entity*> entities)
{
    for(auto i:entities)
    {
        if (a.isCollide(i))
            return true;
    }
    return false;
}

void spawnBars(Entity *bar1, Entity *bar2)
{
    int randNum = rand() % 225 + -125;
    
    //move rectangle
    bar1->rectangle.setPosition(screenW, 150 + randNum);
    bar2->rectangle.setPosition(screenW, 650 + randNum); 
    
    //move hitbox
    bar1->setPosition(screenW, 150 + randNum);
    bar2->setPosition(screenW, 650 + randNum);
    

}

int moveBars(Entity *bar1, Entity *bar2, float speed, int progress)
{
    bar1->x = bar1->x - 1 * speed;
    bar2->x = bar2->x - 1 * speed;
    bar1->rectangle.setPosition(bar1->x, bar1->y);
    bar2->rectangle.setPosition(bar2->x, bar2->y); 
    
    if (bar1->x <= 0)
    {
        spawnBars(bar1, bar2);
        progress++;
    }
    
    return progress;

}

int main() {

    srand(time(NULL));
    
    sf::Text source;
    sf::Font mainGameFont;
    
    RenderWindow app(VideoMode(screenW, screenH), "Starship Straffer!");
    app.setFramerateLimit(60);
    mainGameFont.loadFromFile("futura.ttf");
    source.setFont(mainGameFont);
    
    Texture t1,t2,t3,t4,t5,t6,t7;
    t1.loadFromFile("images/triShip.png");
    t2.loadFromFile("images/background.jpg");
    t3.loadFromFile("images/bullet.png");

    t1.setSmooth(true);
    t2.setSmooth(true);

    Sprite background(t2);
    Sprite playerShip(t1);
    Sprite bulletSprite(t3);
    
    sf::Sound engineSound;
    sf::Sound bulletSound;
    sf::SoundBuffer laserSound;
    sf::SoundBuffer thrustSound;
    if (!laserSound.loadFromFile("sounds/laser.wav"))
        return -1;
        
    if (!thrustSound.loadFromFile("sounds/thrust.ogg"))
        return -1;
        
    std::list<Entity*> entities;
    std::list<Entity*> collidableEntities;
    //std::list<Entity*> noSpriteEntities;
    std::vector<Button*> listButtons;
        
    Actor *player = new Actor();
    player->settings(playerShip,200,400,32,33,90,20);
    player->createActor(100, 100, 5, 10, false);
    entities.push_back(player);
    
    Entity *topBar = new Entity();
    topBar->noSpriteSettings(600, 50, 1200, 100);
    entities.push_back(topBar);
    collidableEntities.push_back(topBar);
    
    Entity *botBar = new Entity();
    botBar->noSpriteSettings(600, 750, 1200, 100);
    entities.push_back(botBar);
    collidableEntities.push_back(botBar);
    
    Entity *bar1 = new Entity();
    bar1->noSpriteSettings(1100, 150, 80, 300);
    entities.push_back(bar1);
    collidableEntities.push_back(bar1);
    
    Entity *bar2 = new Entity();
    bar2->noSpriteSettings(1100, 650, 80, 300);
    entities.push_back(bar2);
    collidableEntities.push_back(bar2);
    
    Entity *bar3 = new Entity();
    bar3->noSpriteSettings(3000, 150, 80, 300);
    entities.push_back(bar3);
    collidableEntities.push_back(bar3);
    
    Entity *bar4 = new Entity();
    bar4->noSpriteSettings(3000, 650, 80, 300);
    entities.push_back(bar4);
    collidableEntities.push_back(bar4);
    
    float startGameSpeed = 3.5;
    float curGameSpeed = startGameSpeed;
    bool secondBarsSpawned = false;
    float gameProgress = 0;
    
    spawnBars(bar1, bar2);
    
        
    while (app.isOpen())
    {
        Event event;
        while (app.pollEvent(event))
        {
            if (event.type == Event::Closed)
                app.close();
                
            if (event.type == Event::KeyPressed)
            {
                 if (event.key.code == Keyboard::Space)
                 {
                     bullet *b = new bullet();
                     b->settings(bulletSprite,player->x,player->y,5, 5, player->angle, 3);
                     entities.push_back(b);
                     //bulletsFired++;
                     bulletSound.setBuffer(laserSound);
                     bulletSound.play();
                 }
             
             }
                
        }
        
        //Player Movement
        if (Keyboard::isKeyPressed(Keyboard::W))
	     player->moveActor(Actor::up);
        if (Keyboard::isKeyPressed(Keyboard::S))
	     player->moveActor(Actor::down);
        if (Keyboard::isKeyPressed(Keyboard::A))
	     player->moveActor(Actor::left);
        if (Keyboard::isKeyPressed(Keyboard::D))
	     player->moveActor(Actor::right);                  
        
        
        //update
        for(auto i:entities) i->update();
        
        gameProgress = moveBars(bar1, bar2, curGameSpeed, gameProgress);
        gameProgress = moveBars(bar3, bar4, curGameSpeed, gameProgress);
        curGameSpeed = startGameSpeed + gameProgress/4;
        
        if (secondBarsSpawned == false and bar1->x == screenW/2)
        {
            spawnBars(bar3, bar4);
            secondBarsSpawned = true;
        }
        
        if (checkCollisions(*player, collidableEntities))
        {
            player->xPos = 200;
            player->yPos = 400;
            cout << "COLLISION!";
        }
        
        //draw
        app.clear(Color(255,255,255,255));
        for(auto i:entities) i->draw(app);
        app.display();

    
    }
    



    return 0;
}
