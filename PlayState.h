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
#include "Attachment.h"
#include "EnergyShield.h"
#include "ProgressBar.h"
#include "ParticleSystem.h"

class PlayState: public State
{
    public:
    std::vector<Button*> buttonList;
    std::vector<Entity*> entities;
    std::vector<Entity*> collidableEntities;
    std::vector<Entity*> creditList;
    std::vector<Button*> listButtons;
    std::vector<Enemy*> enemyList;
    std::vector<Bullet*> bulletList;
    std::vector<Bullet*> enemyBulletList;
    std::vector<Sprite> enemySpriteList;
    std::vector<Sprite> bulletSpriteList; //0: bullet, 1:dark bullet
    std::vector<Sprite> playerShipSpriteList;
    std::vector<Attachment*> attachmentList;
    std::vector<Enemy*> miscEnemyList; //uncoventional enemies i dont want in enemyList: shields, etc
    std::vector<Boss*> bosses;
    Character *character = new Character;
    
    Game *curGame;
    int screenW;
    int screenH;
    sf::Font gameFont;
    sf::Text source;
    
    void createState(Game *game)
    {
        screenW = game->screenWidth;
        screenH = game->screenHeight;
        source = game->source;
        gameFont = game->gameFont;
        curGame = game;
        character = game->character;
    
    }
    
    void emptyState()
    {
        buttonList.clear();
        entities.clear();
        collidableEntities.clear();
        creditList.clear();
        listButtons.clear();
        enemyList.clear();
        bulletList.clear();
        enemyBulletList.clear();
        enemySpriteList.clear();
        bulletSpriteList.clear();
    
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
        bar2->rectangle.setPosition(screenW, 850 + randNum); 
    
        //move hitbox
        bar1->setPosition(screenW, 150 + randNum);
        bar2->setPosition(screenW, 850 + randNum);
    

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
    
        int randY = rand() % screenH/1.5 + screenH/6;
        int randX = rand() % screenW/2 + screenW;
    
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
    
    void checkIfPlayerHit(Actor *player, std::vector<Entity*> collidableEntities, std::vector<Bullet*> enemyBulletList, ParticleSystem *particles)
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
	        player -> health = player->health - temp->damage; 
	        particles->setEmitter(sf::Vector2f(temp->x, temp->y));
	        temp -> life = 0;
	        player -> ticksSinceLastHit = 0;
	    }
	}
	
	player -> ticksSinceLastHit++;
    }
    
    void createPlayer(int shipNum, Actor *player)
    {
        switch (shipNum)
        {
            case 0:
                player->settings(playerShipSpriteList[character->shipType],200,400,32,33,90,20);
                player->createActor(100, 100, 5, 10, false, 50);
                return;
            case 1:
                player->settings(playerShipSpriteList[character->shipType],200,400,22,51,0,20);
                player->createActor(150, 100, 3, 10, false, 50, 1.25);
                return;
            case 2:
                player->settings(playerShipSpriteList[character->shipType],200,400,35,21,0,20);
                player->createActor(75, 100, 7, 10, false, 50, 1.25);
                return;
        }
    
    }
    
    
    
    int Run(sf::RenderWindow &app)
    {
	Texture p1,p2,p3,p4,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12;
        p1.loadFromFile("images/triShip.png");
        p2.loadFromFile("images/batteringRam.png");
        p3.loadFromFile("images/serpent.png");
        //t2.loadFromFile("images/background.jpg");
        t3.loadFromFile("images/cannonBullet.png");
        t4.loadFromFile("images/heart.png");
        t5.loadFromFile("images/darkFighter.png");
        t6.loadFromFile("images/darkBullet.png");
        t7.loadFromFile("images/triShooter.png");
        t8.loadFromFile("images/doubleShooter.png");
        t9.loadFromFile("images/shielder.png");
        t10.loadFromFile("images/pirateLordRobard.png");
        t11.loadFromFile("images/pirateTurret.png");
        t12.loadFromFile("images/blueBullet.png");

        p1.setSmooth(true);
        //t2.setSmooth(true);
    
        sf::Sound engineSound;
        sf::Sound bulletSound;
        sf::SoundBuffer laserSound;
        sf::SoundBuffer thrustSound;
        if (!laserSound.loadFromFile("sounds/laser.wav"))
            return -1;
        
        if (!thrustSound.loadFromFile("sounds/thrust.ogg"))
            return -1;
        
        
        //Sprite background(t2);
        Sprite warhorse(p1);
        playerShipSpriteList.push_back(warhorse);
        Sprite batteringRam(p2);
        playerShipSpriteList.push_back(batteringRam);
        Sprite serpent(p3);
        playerShipSpriteList.push_back(serpent);
        
        Sprite bulletSprite(t3);
        bulletSpriteList.push_back(bulletSprite);
        Sprite heartSprite(t4);
        Sprite darkFighterSprite(t5);
        enemySpriteList.push_back(darkFighterSprite);
        Sprite triShooterSprite(t7);
        enemySpriteList.push_back(triShooterSprite);
        Sprite doubleShooterSprite(t8);
        doubleShooterSprite.setScale(1.25, 1.25f);
        enemySpriteList.push_back(doubleShooterSprite);
        Sprite darkBulletSprite(t12);
        bulletSpriteList.push_back(darkBulletSprite);
        Sprite blueBulletSprite(t12);
        bulletSpriteList.push_back(blueBulletSprite);
        
        Sprite shielderSprite(t9);
        //shielderSprite.setScale(2.5, 2.5);
        enemySpriteList.push_back(shielderSprite); 
        
        Sprite pirateLordSprite(t10);
        enemySpriteList.push_back(pirateLordSprite); 
        
        Sprite pirateTurretSprite(t11);
        enemySpriteList.push_back(pirateTurretSprite); 
        
        Actor *player = new Actor();
        createPlayer(character->shipType, player);
        entities.push_back(player);
    
        Entity *topBar = new Entity();
        topBar->noSpriteSettings(960, 50, 1920, 100, Color::Black);
        entities.push_back(topBar);
        collidableEntities.push_back(topBar);
    
        Entity *botBar = new Entity();
        botBar->noSpriteSettings(960, 1000, 1920, 100, Color::Black);
        entities.push_back(botBar);
        collidableEntities.push_back(botBar);
    
        Entity *bar1 = new Entity();
        bar1->noSpriteSettings(1920, 150, 80, 550, Color::Black);
        entities.push_back(bar1);
        collidableEntities.push_back(bar1);
    
        Entity *bar2 = new Entity();
        bar2->noSpriteSettings(1920, 850, 80, 550, Color::Black);
        entities.push_back(bar2);
        collidableEntities.push_back(bar2);
    
        Entity *bar3 = new Entity();
        bar3->noSpriteSettings(3000, 150, 80, 550, Color::Black);
        entities.push_back(bar3);
        collidableEntities.push_back(bar3);
    
        Entity *bar4 = new Entity();
        bar4->noSpriteSettings(3000, 850, 80, 550, Color::Black);
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
    
        std::cout << "\nScreen Width0: " + std::to_string(screenW);
        EnemySpawner *enemySpawner = new EnemySpawner;
        enemySpawner->createSpawner(enemySpriteList, bulletSpriteList, screenW, screenH);
        
        RectangleShape completeScreen;
        completeScreen.setSize(sf::Vector2f(screenW, screenH));
        completeScreen.setFillColor(Color(0,0,0, 0));
        completeScreen.setOrigin(completeScreen.getSize().x/2, completeScreen.getSize().y/2);
        completeScreen.setPosition(screenW/2, screenH/2);
    
        float startGameSpeed = 3.5;
        float curGameSpeed = startGameSpeed;
        bool secondBarsSpawned = false;
        float gameProgress = 0; // ticks each time a bar passes (dynamic)
        float levelProgress = 0; // ticks depending on tick (static)
        float maxLevelProgress = 4000; // level is over when levelProgress = maxLevelProgress
        float mapTimeDilationPercentage = 0; //percentage that game speed is slowed down
        int progressPercent = 0;
        int tick = 0;
        int numCreditsCollectedRound = 0; //Number of credits collected in that round
        int numEnemiesKilledRound = 0; //Number of enemies killed in that round
        bool spawnedBoss = false;
        bool bossDeath = false;
        bool levelComplete= false;
        int numBossExplosions = 0;
        int completeStage = 0; //0 = levelOngoing, 1 = levelBeaten, 2 = completeScreenDone, 3 = textDone, 4 = goldDone
        int completeTick = 0; //used to determine some parts of completion stage
        //int beginningGold = 0;
    
        spawnBars(bar1, bar2);
        spawnCredit(credit);
        
        attachmentList = character->attachments;
        
        ParticleSystem shipParticles(1000, 100, 5, 50, 1, Color::Red, 180);
        ParticleSystem hitParticles(1000, 50, 10, 50, 3, Color::White, 180);
        ParticleSystem explosionParticles(4000, 50, 10, 100, 2, Color(255, 165, 0));
        ParticleSystem shipHitParticles(1000, 50, 10, 100, 3, Color::Yellow, 0);
        ParticleSystem backParticles1(400, 20000, 10, 100, 4, Color::White, 0, screenH/8, screenH, screenW, 0);
        ParticleSystem backParticles2(800, 20000, 10, 150, 4, Color::White, 0, screenH/8, screenH, screenW, 0, 200);
        ParticleSystem backParticles3(400, 20000, 10, 200, 4, Color::White, 0, screenH/8, screenH, screenW, 0, 100);
        //backParticles.setEmitter(Vector2f(screenW, screenH/2));
        sf::Clock clock;
        
        //Pre-round attachment check!
        for (auto i:character->attachments)
        {
            cout << "\n" + i->name;
            if (i->name == "Time Dilator")
            {
                cout << "\nSuccess!";
                cout << "\n" + to_string(i->baseDamage) + "\n";
                mapTimeDilationPercentage = i->baseDamage;
            }
            
            else if (i->name == "Hull Booster")
            {
                player->maxHealth = player->maxHealth + (player->maxHealth * i->baseDamage);
                player -> health = player -> maxHealth;
            }
        }
        startGameSpeed = startGameSpeed * (1 - mapTimeDilationPercentage);
        
        
        cout << "\ntime dilation %: " + to_string(mapTimeDilationPercentage) + "\n";
        
        sf::Music music;
        if (!music.openFromFile("sounds/mawTheme.wav"))
            return -1; // error
        music.play();
        music.setLoop(true);
    
        while (app.isOpen())
        {
            tick++;
            if (completeStage >= 2)
            {
                completeTick++;
            }
            
            if (curGame->level!=5)
            {
                levelProgress++;
                progressPercent = (levelProgress/maxLevelProgress) * 100;
            }
            else if (bosses.size() > 0 and bosses[0]->health <= 0)
            {
                bossDeath = true;
            }
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
	         
	     //Quit Game
	     if (Keyboard::isKeyPressed(Keyboard::Q))
	         return -1;                   
         
            //update
        
        
            //remove dead entities
            entities = removeDeadEntity(entities);
            enemyList = removeDeadEntity(enemyList);
            bulletList = removeDeadEntity(bulletList);
        
        
            if (!levelComplete)
            {
                gameProgress = moveBars(bar1, bar2, curGameSpeed, gameProgress);
                gameProgress = moveBars(bar3, bar4, curGameSpeed, gameProgress);
                curGameSpeed = (startGameSpeed + (gameProgress/2));// * (1 - mapTimeDilationPercentage);
                moveCredit(credit, curGameSpeed);
            }
            else if (completeScreen.getFillColor().a != 200)
            {
                Color curCol = completeScreen.getFillColor();
                completeScreen.setFillColor(Color(curCol.r, curCol.g, curCol.b, curCol.a + 2));
            }
            //Stage 2 of level complete
            else if (completeScreen.getFillColor().a == 200 and completeStage == 1)
            {
                completeStage = 2;
            }
        
            if (secondBarsSpawned == false and bar1->x <= screenW/2)
            {
                spawnBars(bar3, bar4);
                secondBarsSpawned = true;
            }
        
            //update is player hit
            checkIfPlayerHit(player, collidableEntities, enemyBulletList, &shipHitParticles);
        
            //update misc enemies
            for (auto i:miscEnemyList)
            {
                Bullet *temp = checkCollisions(i, bulletList);
                if (temp != NULL)
                {
                   hitParticles.setEmitter(sf::Vector2f(temp->x, temp->y));
                   i -> takeDamage(temp->damage);
                   temp -> life = 0;
                }
            } 
        
            //check if picked up gold
            Entity* temp = checkCollisions(player, creditList);
            if (temp != NULL)
            {
                character->credits += 1;
                numCreditsCollectedRound++;
                temp->setPosition(0, 0);
            }
        
            //check all attachments to activate
            for (auto i:attachmentList)
            {
                i->activate(tick, &entities, &bulletList, player);
            }
             
            //spawn enemies
            if (tick%200 == 0 and !levelComplete)
            {
                Enemy* newEnemy = enemySpawner->checkToSpawn(curGame->level, curGame->area, tick, enemyList);
                if (newEnemy != NULL)
                {
                    entities.push_back(newEnemy);
                    enemyList.push_back(newEnemy);
                }
                
                if (spawnedBoss == false)
                {
                    spawnedBoss = true;
                    vector<Boss*> tempBosses = enemySpawner->checkToSpawnBoss(curGame->level, curGame->area);
                    for (auto i:tempBosses)
                    {
                        entities.push_back(i);
                        enemyList.push_back(i);
                        bosses.push_back(i);
                    }
                }
            }
            
            //Handles Boss Death
            if (bossDeath == true)
            {
                if (numBossExplosions <= 20 and tick%20 == true)
                {
                    int randW = rand() % int(bosses[0]->w);
                    int randH = rand() % int(bosses[0]->h);
                    explosionParticles.setEmitter(sf::Vector2f(randW + bosses[0]->x/1.2, randH + bosses[0]->y/1.2));
                    numBossExplosions++;
                }
                else if (numBossExplosions < 40 and numBossExplosions > 20 and tick%10 == true)
                {
                    int randW = rand() % int(bosses[0]->w);
                    int randH = rand() % int(bosses[0]->h);
                    explosionParticles.setEmitter(sf::Vector2f(randW + bosses[0]->x/1.2, randH + bosses[0]->y/1.2));
                    numBossExplosions++;
                }    
                else if (numBossExplosions == 40)
                {
                    progressPercent = 100;
                    bosses[0]->life=0;
                }
                
            }
        
            //Restart Tick Counter
            if (tick == 1000)
            {
                tick = 0;
            }
            
            //Stage 1 of level complete
            if (progressPercent >= 100 and completeStage == 0)
            {
                curGame->level++;
                completeStage = 1;
                levelComplete = true;
                for (auto i:enemyList)
                    i->health = 0;
                emptyState();
                //return 3;
            }
            
            //Stage 4 of level complete
            else if (completeTick == 300 and completeStage == 3)
            {
                cout << "\n Time Manip: " + to_string(mapTimeDilationPercentage) + "\n";
                cout << "\nCurrent Speed: " + to_string(curGameSpeed) + "\n";
                return 3;
            }
        
            //draw
            app.draw(backParticles3);
            app.draw(backParticles2);
            app.draw(backParticles1);
            for(auto i:entities) i->draw(app);
            //for(auto i:shieldList) 
                //app.draw(i->circle);
                
            //Update Conventional Enemies
            for (auto i:enemyList)
            {
                i -> enemyMove();
                
                if (!(i->bulletsPassThrough))
                {
                    Bullet *temp = checkCollisions(i, bulletList);
                    if (temp != NULL)
                    {
                       hitParticles.setEmitter(sf::Vector2f(temp->x, temp->y));
                       temp->onContact(player);
                       i -> takeDamage(temp->damage);
                       cout <<"\nBullet Damage: " + to_string(temp->damage);
                       cout << "\nEnemy Health: " + to_string(i->health) + "\n";
                       if (i->health <= 0)
                       {
                           numEnemiesKilledRound++;
                           explosionParticles.setEmitter(sf::Vector2f(i->x, i->y));
                       }
                       temp -> life = 0;
                    }
                }
            
                i->enemyAttack(&enemyBulletList, &entities);
                i->ability(enemyList, &bulletList, app);
                //bulletSound.setBuffer(laserSound);
                //bulletSound.play();
                    //i->ticksSinceLastFire = 0;

            } 
            
             //update particles
            shipParticles.setEmitter(sf::Vector2f(player->x - 20, player->y - 5));
            sf::Time elapsed = clock.restart();
            shipParticles.update(elapsed);
            hitParticles.update(elapsed);
            explosionParticles.update(elapsed);
            shipHitParticles.update(elapsed);
            backParticles1.update(elapsed);
            backParticles2.update(elapsed);
            backParticles3.update(elapsed);
            
            app.draw(shipParticles);
            app.draw(hitParticles);
            app.draw(explosionParticles);
            app.draw(shipHitParticles);
            drawText(": " + std::to_string(character->credits), 20, 65, 12, app);
            drawText(": " + std::to_string(player->health), 20, 65, 60, app);
            drawText("Progress: " + std::to_string(levelProgress), 20, 500, 20, app);
            drawText("Progress: " + std::to_string(progressPercent), 20, 500, 50, app);
            
            app.draw(completeScreen);
            cout << to_string(completeStage);
            
            //Stage 3 of complete Stage
            if ((completeTick == 100 and completeStage == 2) or completeStage > 2)
            {
                drawText("Level Complete", 60, screenW/3, screenH - 16 * (screenH/20), app);
                drawText("Credits Collected: " + to_string(numCreditsCollectedRound), 40, screenW/3, screenH - 13 * (screenH/20), app);
                drawText("Enemies Killed: " + to_string(numEnemiesKilledRound), 40, screenW/3, screenH - 12 * (screenH/20), app);
                if (completeStage == 2)
                {
                    completeStage = 3;
                    completeTick = 0;
                    cout << "\n Time Manip: " + to_string(mapTimeDilationPercentage) + "\n";
                    cout << "\nCurrent Speed: " + to_string(curGameSpeed) + "\n";
                }
                
            }
            
            app.display();
            app.clear(Color::Black);
            RectangleShape rectangle;
            rectangle.setSize(Vector2f(screenW, screenH));
            rectangle.setFillColor(Color(56,10,56,200));
            app.draw(rectangle);
        }
    
    
    
        return -1;
    }

    
    
};
