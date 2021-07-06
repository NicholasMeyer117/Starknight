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
#include "Entity.h"
#include "Button.h"
#include "Actor.h"
#include "Character.h"
#include "Enemy.h"
#include "DarkFighter.h"
#include "Bullets.h"
#include "EnemySpawner.h"
#include "Game.h"
#include "State.h"
#include "MenuState.h"
#include "HubState.h"

class PlayState: public State
{
    public:
    std::vector<Button*> buttonList;
    Game *curGame;
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
        curGame = game;
        
        
    
    }
    
    template<typename Base, typename T>
    inline bool instanceof(const T*) {
       return is_base_of<Base, T>::value;
    }


    //check if bullet hits player, player bullet hits enemy, player hits bar, etc
    template <class T1, class T2>
    T2* checkCollisions(T1 *a, std::vector<T2*> entities)
    {
        for(auto i:entities)
        {
            if (a->isCollide(i))
                return i;
        } 
        return NULL;
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

    void spawnCredit(Entity *credit)
    {
    
        int randY = rand() % 500 + 100;
        int randX = rand() % 400 + 1200;
    
        credit->rectangle.setPosition(randX, randY);
        credit->setPosition(randX, randY);


    }
    
    template <class T>
    std::vector<T*> removeDeadEntity(std::vector<T*> entities)
    {
        for(auto i=entities.begin();i!=entities.end();)
         {
            Entity *e = *i;

            e->update();
            //e->anim.update();

            if (e->life==false) 
            {
                i=entities.erase(i); 
                //delete e;
            }
            else i++;
        }
    return entities;

    }

    void moveCredit(Entity *credit, float speed)
    {
        credit->x = credit->x - 1 * speed;
        credit->rectangle.setPosition(credit->x, credit->y);

        if (credit->x <= 0)
            spawnCredit(credit);
    }

    void drawText( const sf::String &str, const int Size, const float xposition, const float yposition, sf::RenderWindow& window)
    {
        source.setString(str);
        source.setCharacterSize(Size); //only the lower cased word size is reserved. A capital S fixes that.
        source.setPosition(xposition,yposition);
        source.setFillColor(Color::White);
        window.draw(source);
    }
    
    void checkIfPlayerHit(Actor *player, std::vector<Entity*> collidableEntities, std::vector<Bullet*> enemyBulletList)
    {
        if (player -> ticksSinceLastHit > player -> iFrames)
        {
	    if (checkCollisions(player, collidableEntities) != NULL)
	    {
	        player->xPos = 200;
	        player->yPos = 400;
	        player -> health = player->health - 10; 
	        player -> ticksSinceLastHit = 0;
	    }

	    Bullet *temp = checkCollisions(player, enemyBulletList);
	    if (temp != NULL)
	    {
	        player -> health = player->health - 10; 
	        temp -> life = 0;
	        player -> ticksSinceLastHit = 0;
	    }
	}
	
	player -> ticksSinceLastHit++;
    }
    
    int Run(sf::RenderWindow &app)
    {
	Texture t1,t2,t3,t4,t5,t6,t7;
        t1.loadFromFile("images/triShip.png");
        t2.loadFromFile("images/background.jpg");
        t3.loadFromFile("images/bullet.png");
        t4.loadFromFile("images/heart.png");
        t5.loadFromFile("images/darkFighter.png");
        t6.loadFromFile("images/darkBullet.png");

        t1.setSmooth(true);
        t2.setSmooth(true);
    
        sf::Sound engineSound;
        sf::Sound bulletSound;
        sf::SoundBuffer laserSound;
        sf::SoundBuffer thrustSound;
        if (!laserSound.loadFromFile("sounds/laser.wav"))
            return -1;
        
        if (!thrustSound.loadFromFile("sounds/thrust.ogg"))
            return -1;
        
        std::vector<Entity*> entities;
        std::vector<Entity*> collidableEntities;
        std::vector<Entity*> creditList;
        //std::list<Entity*> noSpriteEntities;
        std::vector<Button*> listButtons;
        std::vector<Enemy*> enemyList;
        std::vector<Bullet*> bulletList;
        std::vector<Bullet*> enemyBulletList;
        std::vector<Sprite> spriteList;
        
        Sprite background(t2);
        Sprite playerShip(t1);
        Sprite bulletSprite(t3);
        Sprite heartSprite(t4);
        Sprite darkFighterSprite(t5);
        spriteList.push_back(darkFighterSprite);
        Sprite darkBulletSprite(t6);
         
        
        Actor *player = new Actor();
        player->settings(playerShip,200,400,32,33,90,20);
        player->createActor(100, 100, 5, 10, false, 50);
        entities.push_back(player);
    
        Entity *topBar = new Entity();
        topBar->noSpriteSettings(600, 50, 1200, 100, Color::Black);
        entities.push_back(topBar);
        collidableEntities.push_back(topBar);
    
        Entity *botBar = new Entity();
        botBar->noSpriteSettings(600, 750, 1200, 100, Color::Black);
        entities.push_back(botBar);
        collidableEntities.push_back(botBar);
    
        Entity *bar1 = new Entity();
        bar1->noSpriteSettings(1100, 150, 80, 350, Color::Black);
        entities.push_back(bar1);
        collidableEntities.push_back(bar1);
    
        Entity *bar2 = new Entity();
        bar2->noSpriteSettings(1100, 650, 80, 350, Color::Black);
        entities.push_back(bar2);
        collidableEntities.push_back(bar2);
    
        Entity *bar3 = new Entity();
        bar3->noSpriteSettings(3000, 150, 80, 350, Color::Black);
        entities.push_back(bar3);
        collidableEntities.push_back(bar3);
    
        Entity *bar4 = new Entity();
        bar4->noSpriteSettings(3000, 650, 80, 350, Color::Black);
        entities.push_back(bar4);
        collidableEntities.push_back(bar4);
    
        Entity *credit = new Entity();
        credit -> noSpriteSettings(3000, 1000, 8, 8, Color::Yellow);
        entities.push_back(credit);
        creditList.push_back(credit);
    
        Entity *creditImage = new Entity();
        creditImage -> noSpriteSettings(50, 25, 25, 25, Color::Yellow);
        entities.push_back(creditImage);
    
        Entity *heartImage = new Entity();
        heartImage -> settings(heartSprite,50,75,25,25);
        entities.push_back(heartImage);
    
        Character *character = new Character;
        EnemySpawner *enemySpawner = new EnemySpawner;
        enemySpawner->createSpawner(spriteList);
    
        float startGameSpeed = 3.5;
        float curGameSpeed = startGameSpeed;
        bool secondBarsSpawned = false;
        float gameProgress = 0; // ticks each time a bar passes (dynamic)
        float levelProgress = 0; // ticks depending on tick (static)
        float maxLevelProgress = 4000; // level is over when levelProgress = maxLevelProgress
        int progressPercent;
        int tick = 0;
    
        spawnBars(bar1, bar2);
        spawnCredit(credit);
    
        while (app.isOpen())
        {
            tick++;
            levelProgress++;
            progressPercent = (levelProgress/maxLevelProgress) * 100;
            Event event;
            while (app.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    app.close();
                
                if (event.type == Event::KeyPressed)
                {
                     if (event.key.code == Keyboard::Space)
                     {
                   
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
        
        
            //remove dead entities
            entities = removeDeadEntity(entities);
            enemyList = removeDeadEntity(enemyList);
            bulletList = removeDeadEntity(bulletList);
        
            gameProgress = moveBars(bar1, bar2, curGameSpeed, gameProgress);
            gameProgress = moveBars(bar3, bar4, curGameSpeed, gameProgress);
            curGameSpeed = startGameSpeed + gameProgress/4;
            moveCredit(credit, curGameSpeed);
        
            if (secondBarsSpawned == false and bar1->x <= screenW/2)
            {
                spawnBars(bar3, bar4);
                secondBarsSpawned = true;
            }
        
            //update is player hit
            checkIfPlayerHit(player, collidableEntities, enemyBulletList);
        
            //update enemies
            for (auto i:enemyList)
            {
                cout<<"\nHi!\n";
                i -> enemyMove();
                Bullet *temp = checkCollisions(i, bulletList);
                if (temp != NULL)
                {
                   i -> takeDamage(temp->damage);
                   temp -> life = 0;
                }
            
                if (i->ticksSinceLastFire == i->firerate)
                {
                    DarkBullet *b = new DarkBullet();
                    b->settings(darkBulletSprite,i->x,i->y,5, 5, i->angle, 3);
                    b->createBullet (5, 20);
                    entities.push_back(b);
                    enemyBulletList.push_back(b);
                    bulletSound.setBuffer(laserSound);
                    bulletSound.play();
                    i->ticksSinceLastFire = 0;
            
                }
                else
                    i->ticksSinceLastFire++;

            } 
        
            //check if picked up gold
            Entity* temp = checkCollisions(player, creditList);
            if (temp != NULL)
            {
                character->credits += 1;
                temp->setPosition(0, 0);
            }
        
            if (tick%50 == 0)
            {
                NormalBullet *b = new NormalBullet();
                b->settings(bulletSprite,player->x,player->y,5, 5, player->angle, 3);
                b->createBullet (5, 20);
                entities.push_back(b);
                bulletList.push_back(b);
                bulletSound.setBuffer(laserSound);
                bulletSound.play();

            }
        
            if (tick%400 == 0)
            {
                Enemy* newEnemy = enemySpawner->checkToSpawn(curGame->level, curGame->area, tick);
                if (newEnemy != NULL)
                {
                    entities.push_back(newEnemy);
                    enemyList.push_back(newEnemy);
                }
            }
        
            if (tick == 1000)
            {
                tick = 0;
            }
            
            if (progressPercent >= 100)
            {
                curGame->level++;
                return 3;
            }
        
            //draw
            app.clear(Color(255,255,255,255));
            for(auto i:entities) i->draw(app);
            drawText(": " + std::to_string(character->credits), 20, 65, 12, app);
            drawText(": " + std::to_string(player->health), 20, 65, 60, app);
            drawText("Progress: " + std::to_string(levelProgress), 20, 500, 20, app);
            drawText("Progress: " + std::to_string(progressPercent), 20, 500, 50, app);
            app.display();
        }
    
    
    
        return -1;
    }

    
    
};