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
#include "AOE.h"
#include "ItemHandler.h"
#include "PauseState.h"
#include "ButtonHandler.h"

//Global Variables
extern int screenW;
extern int screenH;
float elapsedTime;

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
    std::vector<AOE*> AOElist;
    Character *character = new Character;
    
    Game *curGame;
    int relUnitX;
    int relUnitY;
    int screenShakeCounter = 0;
    bool shakeScreen = false;
    sf::Font gameFont;
    sf::Text source;
    
    void createState(Game *game)
    {
        //screenW = game->screenWidth;
        //screenH = game->screenHeight;
        source = game->source;
        gameFont = game->gameFont;
        curGame = game;
        character = game->character;
        relUnitX = game->relUnitX;
        relUnitY = game->relUnitY;
    
    }
    
    void emptyState(Actor *player)
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
        entities.push_back(player);
    
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
    
    template <class T1, class T2>
    T2* checkSpriteCollisions(T1 *a, std::vector<T2*> entities)
    {
        for(auto i:entities)
        {
            if (a->isCollideWithSprite(i))
                return i;
        } 
        return NULL;
    }
    
    template <class T1, class T2>
    T2* checkSpriteCollisions(T1 *a, T2* b)
    {
        if (a->isCollideWithSprite(b))
            return b;
        return NULL;
    }

    void spawnAsteroids(Entity *asteroid)
    {
        int randNum = rand() % (relUnitY * 70);
    
        //move rectangle
        asteroid->rectangle.setPosition(screenW + 600, (relUnitY * 10) + randNum);
    
        //move hitbox
        asteroid->setPosition(screenW + 600, (relUnitY * 10) + randNum);
        asteroid->contactDamage = 10;
    }
    
    int moveAsteroids(Entity *asteroid, float speed, int progress)
    {
        asteroid->x = asteroid->x - 1 * speed;
        asteroid->angle = asteroid->angle + 1;
        asteroid->rectangle.setPosition(asteroid->x, asteroid->y);
        
    
        if (asteroid->x <= (-relUnitX * 20))
        {
            spawnAsteroids(asteroid);
            progress++;
        }
    
        return progress;

    }

    void spawnCredit(Entity *credit)
    {
    
        int randY = rand() % screenH/1.5 + screenH/6;
        int randX = rand() % screenW + screenW*2;
    
        credit->rectangle.setPosition(randX, randY);
        credit->setPosition(randX, randY);


    }
    
    const void screenShake(RenderWindow &app, bool isHit)
    {
        if (isHit == true)
        {
            screenShakeCounter = 1;
            shakeScreen = true;
        }
            
        if (shakeScreen)
        {
            sf::View view = app.getView();
            if (0 < screenShakeCounter and screenShakeCounter <= 2)
               view.move(4.f, 4.f);
            else if (2 < screenShakeCounter and screenShakeCounter <=4)
                view.move(-4.f, -4.f);
            else
            {
                screenShakeCounter = -1;
                shakeScreen = false;
            }
            
            app.setView(view);
            screenShakeCounter++;   
            //cout << "\nscreenShakeCounter: " << screenShakeCounter << "\n";
        }
    
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
    
    void drawChallengeText(int gameType, int levelProgress, sf::RenderWindow& window)
    {
        if (gameType == 1)
        {
            if (10 < levelProgress and levelProgress < 40)
            {
                drawText("DONT GET HIT", 50, relUnitX * 40, relUnitY * 45, app);
            }
            else if (levelProgress >= 40)
            {
                drawText("DONT GET HIT", 25, relUnitX * 45, relUnitY * 5, app);
            }
        }
    }
    
    int checkIfPlayerHit(Actor *player, std::vector<Entity*> collidableEntities, Entity *asteroid, std::vector<Enemy*> enemyList, std::vector<Bullet*> enemyBulletList, ParticleSystem *particles, itemActivation *myActiveItems)
    {
        int code = 0; //0 = not hit, 1 = collided, 2 = collided with enemy, 3 = hit by bullet
        if (player -> ticksSinceLastHit > player -> iFrames)
        {
	        if (checkCollisions(player, collidableEntities) != NULL)
	        {
	            player->xPos = 200;
	            player->yPos = 400;
	            player -> health = player->health - 10; 
	            player -> ticksSinceLastHit = 0;
	            code = 1;
	        }
	        
	        if(checkSpriteCollisions(player, asteroid) != NULL)
	        {
                int contDam = asteroid->contactDamage;
                if (myActiveItems->reinforcedHull == myActiveItems->active)
                    contDam = contDam/2;
	            player -> health = player->health - contDam;
	            player -> ticksSinceLastHit = 0;
	            code = 1;
	        }
	        
	        Enemy *enemy = checkSpriteCollisions(player, enemyList);
	        if (enemy != NULL)
	        {
                int contDam = enemy->contactDamage * enemy->contactDamageMult;
                if (myActiveItems->reinforcedHull == myActiveItems->active)
                    contDam = contDam/2;
	            player -> health = player->health - (contDam); 
	            enemy -> takeDamage(player->contactDamage * player->contactDamageMult);
	            player -> ticksSinceLastHit = 0;
	            code = 2;
	            //explosionParticles.setEmitter(sf::Vector2f(enemy->x, enemy->y));
	        }
    
	        Bullet *temp = checkSpriteCollisions(player, enemyBulletList);
	        if (temp != NULL)
	        {
	            player -> health = player->health - temp->damage; 
	            particles->setEmitter(sf::Vector2f(temp->x, temp->y));
	            temp -> life = 0;
	            player -> ticksSinceLastHit = 0;
	            code = 3;
	        }

            if (code > 0)
            {
                if (player->health <= player->maxHealth/2 and myActiveItems->fury == myActiveItems->notActive)
                {
                    myActiveItems->fury = myActiveItems->active;
                    player->damageMult+=0.2;
                    player->fireRateMult+=0.2;
                }
                if (myActiveItems->panic == myActiveItems->notActive)
                {
                    myActiveItems->panic = myActiveItems->active;
                    player->damageMult+=0.2;
                    player->fireRateMult+=0.2;
                }
                if (myActiveItems->cumulativeFirepower == myActiveItems->active)
                {
                    player->damageMult-=myActiveItems->cumFireDamage;
                    myActiveItems->cumFireDamage=0;
                }
            }
	        
	    }

        
	    player -> ticksSinceLastHit++;
	    return code;
    }
    
    
    void createPlayer(int shipNum, Actor *player)
    {
        switch (shipNum)
        {
            case 0:
                player->settings(playerShipSpriteList[character->shipType],200,400,52,75,0,20);
                //health, shields, speed, firerate, is enemy, IFrames, contactDamage, damageMult, fireRateMult, bulletSpeedMult, SpeedMult, HealthMult, HealingMult, utilityMult
                player->createActor(100, 100, 250, 10, false, 50, 10, 1, 1, 1, 1, 1, 1, 1);
                return;
            case 1:
                player->settings(playerShipSpriteList[character->shipType],200,400,75,91,0,20);
                player->createActor(125, 100, 250, 10, false, 50, 15, 1.25, 1, 1, 0.75, 1, 1, 1);
                return;
            case 2:
                player->settings(playerShipSpriteList[character->shipType],200,400,50,50,0,20);
                player->createActor(75, 100, 250, 10, false, 50, 5, 1.25, 1, 1, 1.25, 1, 1, 1);
                return;
        }
    
    }
    
    
    
    int Run(sf::RenderWindow &app)
    {
	Texture p1,p2,p3,p4,b1,b2,b3,b4,b5,b6,e1,e2,e3,e4,e5,e6,e7,e8,e9,e10,t1,t2,t3,t4;
        p1.loadFromFile("images/warhorse.png");
        p2.loadFromFile("images/batteringRam.png");
        p3.loadFromFile("images/serpent.png");
        t1.loadFromFile("images/heart.png");
        t2.loadFromFile("images/asteroid1.png");
        t3.loadFromFile("images/asteroid2.png");
        t4.loadFromFile("images/credit.png");
        b1.loadFromFile("images/bullet.png");
        b2.loadFromFile("images/darkBullet.png");
        b3.loadFromFile("images/blueBullet.png");
        b4.loadFromFile("images/swarmBomb.png");
        b5.loadFromFile("images/swarmBombNew.png"); //re-add siphon bullet
        b6.loadFromFile("images/pirateBlast.png");
        e1.loadFromFile("images/pirateFighter.png");
        e2.loadFromFile("images/pirateGunner.png");
        e3.loadFromFile("images/pirateSkirmisher.png");
        e4.loadFromFile("images/shielder.png");
        e5.loadFromFile("images/pirateLordRobard.png");
        e6.loadFromFile("images/pirateTurret.png");
        e7.loadFromFile("images/swarmer.png");
        e8.loadFromFile("images/swarmSpitter.png");
        e9.loadFromFile("images/pirateTurret2.png");
        e10.loadFromFile("images/pirateMachineGunner.png");
        
        Texture pauseTex;       
        pauseTex.create(screenW, screenH);
        
        //uniform vec4 flashColor;
        //flashColor.a = 1.0;//1.0 for 100% effect to 0.0 for 0% effect
        sf::Shader shader, glowShader;
        shader.loadFromFile("shaders/flash.frag", sf::Shader::Fragment);//use your own 
        //file path
        shader.setUniform("flashColor", sf::Glsl::Vec4(1, 1, 1, 1));//from left to 
        //right: red,green,blue,alpha. Alpha is useless in this shader file.
        //max is 1, not 255.
        //window.draw(yoursprite, &shader);
        glowShader.loadFromFile("shaders/glow.frag", sf::Shader::Fragment);
        glowShader.setUniform("redGlow", sf::Glsl::Vec4(1, 0, 0, 1));
        glowShader.setUniform("blueGlow", sf::Glsl::Vec4(0, 0, 1, 1));   

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
        //Player Ship Sprites
        Sprite warhorse(p1);
        playerShipSpriteList.push_back(warhorse);
        Sprite batteringRam(p2);
        playerShipSpriteList.push_back(batteringRam);
        Sprite serpent(p3);
        playerShipSpriteList.push_back(serpent);
        
        Sprite heartSprite(t1);
        Sprite asteroid1Sprite(t2);
        //asteroid1Sprite.setScale(4, 4);
        Sprite asteroid2Sprite(t3);
        //asteroid2Sprite.setScale(4, 4);
        Sprite creditSprite(t4);
        Sprite creditImageSprite(t4);
        creditImageSprite.setScale(1.25, 1.25);
        
        //Bullet Sprites
        Sprite bulletSprite(b1);
        bulletSpriteList.push_back(bulletSprite);
        
        Sprite darkBulletSprite(b2);
        bulletSpriteList.push_back(darkBulletSprite);
        
        Sprite blueBulletSprite(b3);
        blueBulletSprite.setScale(1.75, 1.75);
        bulletSpriteList.push_back(blueBulletSprite);
        
        Sprite swarmBombSprite(b4);
        bulletSpriteList.push_back(swarmBombSprite);
        
        Sprite swarmBombNewSprite(b5);
        swarmBombNewSprite.setScale(2, 2);
        bulletSpriteList.push_back(swarmBombNewSprite);
        
        Sprite pirateBlast(b6);
        bulletSpriteList.push_back(pirateBlast);
        
        //Enemy ship sprites
        Sprite darkFighterSprite(e1);
        enemySpriteList.push_back(darkFighterSprite);
        
        Sprite triShooterSprite(e2);
        enemySpriteList.push_back(triShooterSprite);
        
        Sprite doubleShooterSprite(e3);
        enemySpriteList.push_back(doubleShooterSprite);
        
        Sprite shielderSprite(e4);
        enemySpriteList.push_back(shielderSprite); 
        
        Sprite pirateLordSprite(e5);
        enemySpriteList.push_back(pirateLordSprite); 
        
        Sprite pirateTurretSprite(e6);
        enemySpriteList.push_back(pirateTurretSprite); 
        
        Sprite swarmer(e7);
        enemySpriteList.push_back(swarmer); 
        
        Sprite swarmSpitter(e8);
        enemySpriteList.push_back(swarmSpitter);
        
        Sprite pirateTurret2Sprite(e9);
        enemySpriteList.push_back(pirateTurret2Sprite); 
        
        Sprite pirateMachineGunner(e10);
        enemySpriteList.push_back(pirateMachineGunner); 
        
        Actor *player = new Actor();
        createPlayer(character->shipType, player);
        entities.push_back(player);
    
        Entity *topBar = new Entity();
        topBar->noSpriteSettings(960, relUnitY * 5, 1920, 100, Color::Black);
        entities.push_back(topBar);
        collidableEntities.push_back(topBar);
    
        Entity *botBar = new Entity();
        botBar->noSpriteSettings(960, relUnitY * 100, 1920, 100, Color::Black);
        entities.push_back(botBar);
        collidableEntities.push_back(botBar);
    
        Entity *asteroid1 = new Entity();
        asteroid1->settings(asteroid1Sprite, screenW + 600, screenH, 50, 50);
        entities.push_back(asteroid1);
        //collidableEntities.push_back(asteroid1);
    
        Entity *asteroid2 = new Entity();
        asteroid2->settings(asteroid2Sprite, screenW + 600, screenH/2, 50, 50);
        entities.push_back(asteroid2);
        //collidableEntities.push_back(asteroid2);
        
        Entity *asteroid = asteroid1;
    
        Entity *credit = new Entity();
        credit -> settings(creditSprite, 3000, 1000, 25, 25);
        entities.push_back(credit);
        creditList.push_back(credit);
    
        Entity *creditImage = new Entity();
        creditImage -> settings(creditImageSprite, 50, 25, 25, 25);
        entities.push_back(creditImage);
    
        Entity *heartImage = new Entity();
        heartImage -> settings(heartSprite,50,75,25,25);
        entities.push_back(heartImage);
    
        std::cout << "\nScreen Width0: " + std::to_string(screenW);
        EnemySpawner *enemySpawner = new EnemySpawner;
        enemySpawner->createSpawner(enemySpriteList, bulletSpriteList, screenW, screenH);
        ItemHandler *itemHandler = new ItemHandler(character);
        ButtonHandler *buttonHandler = new ButtonHandler();
        
        RectangleShape completeScreen;
        completeScreen.setSize(sf::Vector2f(screenW, screenH));
        completeScreen.setFillColor(Color(0,0,0, 0));
        completeScreen.setOrigin(completeScreen.getSize().x/2, completeScreen.getSize().y/2);
        completeScreen.setPosition(screenW/2, screenH/2);
    
        float startGameSpeed = 400;
        float curGameSpeed = startGameSpeed;
        //bool secondBarsSpawned = false;
        float gameProgress = 0; // ticks each time a bar passes (dynamic)
        float levelProgress = 0; // ticks depending on tick (static)
        float maxLevelProgress = 300; // level is over when levelProgress = maxLevelProgress
        float mapTimeDilationPercentage = 0; //percentage that game speed is slowed down
        int progressPercent = 0;
        int tick = 0;
        int numCreditsCollectedRound = 0; //Number of credits collected in that round
        int numEnemiesKilledRound = 0; //Number of enemies killed in that round
        bool spawnedBoss = false;
        bool bossDeath = false;
        bool levelComplete= false;
        bool challengeSucceeded = true;
        bool itemIsChosen = false; //For levels where an item is granted at the end, checks boolean before continuing
        bool isPlayerDead = false;
        int numBossExplosions = 0;
        int completeStage = 0; //0 = levelOngoing, 1 = levelBeaten, 2 = player moved, 3 = completeScreenDone, 4 = textDone, 5 = goldDone
        int completeTick = 0; //used to determine some parts of completion stage
        int ticksTillEnemySpawn = 100;
        int nextLevelSetting = 0; //0 = level in progress, 1 = reg level next, 2 challenge and reg choice next
        int currentLevelType = 0;
        float glowValue = 0.0; //Used to set strength of after level glow
        //int beginningGold = 0;
    
        spawnAsteroids(asteroid);
        spawnCredit(credit);
        
        attachmentList = character->attachments;
        curGame->synergyHandler->applySynergies(player);
        curGame->crewHandler->applyCrew(player);
        curGame->setUpLevel(currentLevelType, maxLevelProgress);
        
        ParticleSystem shipParticles(100, 10, 1, 50, 1, Color::Red, 180,0,0,0,0,255, 30);
        ParticleSystem hitParticles(50, 50, 10, 50, 3, Color::White, 180);
        ParticleSystem explosionParticles(200, 50, 10, 100, 2, Color(255, 165, 0));
        ParticleSystem shipHitParticles(50, 50, 10, 100, 3, Color::Yellow, 0);
        ParticleSystem backParticles1(400, 20000, 2, 100, 4, Color::White, 0, screenH/8, screenH, screenW, 0, 150);
        ParticleSystem backParticles2(800, 20000, 2, 150, 4, Color::White, 0, screenH/8, screenH, screenW, 0, 100);
        ParticleSystem backParticles3(400, 20000, 2, 200, 4, Color::White, 0, screenH/8, screenH, screenW, 0, 50);
        bool shipHit, enemyHit, enemyKilled = false; //used to control particles
        //backParticles.setEmitter(Vector2f(screenW, screenH/2));
        sf::Clock clock; //for movement
        sf::Clock eventClock; //for events
        elapsedTime = clock.getElapsedTime().asSeconds();
        float eventElapsedTime = eventClock.getElapsedTime().asMilliseconds();
        
        //Pre-round attachment check!
        for (auto i:character->attachments)
        {
            if (i->name == "Time Dilator")
                mapTimeDilationPercentage = i->baseDamage;
            else if (i->name == "Hull Booster")
                player->healthMult += (i->baseDamage * player->utilityMult);
            else if (i->name == "Speed Booster")
                player->speedMult = player->speedMult + (i->baseDamage * player->utilityMult);

        }
        
        //Pre-round item check
        cout << "\nPre-round Item Check:\n";
        struct itemActivation myActiveItems;
        for (auto i:character->items)
        {
            cout << i->name;
            if (i->name == "Caliber Upgrade")
               player->damageMult += 0.15;
            else if (i->name == "Advanced Load Mechanism")
                player->fireRateMult+= 0.15;
            else if (i ->name == "Reinforced Hull")
            {
                myActiveItems.reinforcedHull = myActiveItems.active;
                player->speedMult -= 0.1;
            }
            else if (i->name == "Altered Ballistics")
            {
                player->fireRateMult+=0.2;
                player->bulletSpeedMult-=0.2;
            }
            else if (i->name == "Deadly Hull")
            {
                player->contactDamage += 100;
            }
            else if (i->name == "Fury")
                myActiveItems.fury = myActiveItems.notActive;
            else if (i->name == "Ghost Bullets")
                myActiveItems.ghostBullets = myActiveItems.active;
            else if (i->name == "Projectile Disruptor Field")
                myActiveItems.projDisruptorField = myActiveItems.active;
            else if (i->name == "Extra choice [Item]")
                itemHandler->itemChoicesNum = 4;
            else if (i->name == "Panic")
                myActiveItems.panic = myActiveItems.notActive;
            else if (i->name == "Steady Aim")
                myActiveItems.steadyAim = myActiveItems.notActive;
            else if (i->name == "Cumulative Firepower")
                myActiveItems.cumulativeFirepower = myActiveItems.active;
        }
        
        
        startGameSpeed = startGameSpeed * (1 - mapTimeDilationPercentage);
        player -> maxHealth = round(player->maxHealth * player -> healthMult);
        player -> health = player -> maxHealth;
        
        
        sf::Music music;
        if (!music.openFromFile("sounds/mawTheme.wav"))
            return -1; // error
        music.play();
        music.setLoop(true);
    
        while (app.isOpen())
        {
            eventElapsedTime = eventClock.getElapsedTime().asMilliseconds();
            bool advanceTick = false;
            if (eventElapsedTime >= 17)
            {
                tick++;
                advanceTick = true;
                eventElapsedTime = eventClock.restart().asMilliseconds();
            }
            //cout << "\n " << eventElapsedTime << "\n";
            if (completeStage >= 3)
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
                     if (event.key.code == Keyboard::Escape)
                     {
                         //pauseTex.copyToImage().saveToFile("images/screenshot.png");
                         PauseState *pauseState = new PauseState(curGame, pauseTex, player);
	                 pauseState->Run();
	                 app.setView(view);
	                 sf::Time elapsed = clock.restart();
                         elapsedTime = 0;
	                 continue;
                     }             
                }
                else if (event.type == sf::Event::MouseButtonPressed) 
                {
                    for (int i = 0; i < buttonList.size(); i++)
                    {
                        buttonHandler->checkIfButtonLeftClicked(buttonList[i]);
                    }
                }
            }
            
            RectangleShape rectangle;
            rectangle.setSize(Vector2f(screenW, screenH));
            if (curGame -> area == 1)
            	rectangle.setFillColor(Color(56,10,56,200));
            else if (curGame -> area == 2)
            	rectangle.setFillColor(Color(5, 73, 7, 200));
            
            glowShader.setUniform("baseColor", sf::Glsl::Vec4(rectangle.getFillColor()));
            glowShader.setUniform("setting", nextLevelSetting);
            glowShader.setUniform("globalGlowStr", glowValue);
        
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
         
            //set particle emmitter bools to false
            enemyHit = false;
            enemyKilled = false;
            
            //update entities
            itemHandler->checkActiveItems(player, &myActiveItems);

            for (int i = 0; i < bulletList.size(); i++)
            {
                bulletList.at(i)->update(elapsedTime);
            }
            for (int i = 0; i < enemyBulletList.size(); i++)
            {
                enemyBulletList.at(i)->update(elapsedTime);
            }
        
            //remove dead entities
            entities = removeDeadEntity(entities);
            enemyList = removeDeadEntity(enemyList);
            bulletList = removeDeadEntity(bulletList);
            enemyBulletList = removeDeadEntity(enemyBulletList);
            AOElist = removeDeadEntity(AOElist);
        
        
            if (!levelComplete)
            {
                if (asteroid->x <= (-relUnitX * 15))
                {
                   int randNum = rand() % 2;
                   //cout << "\nasteroid: " << randNum << "\n";
                   if (randNum == 1)
                       asteroid = asteroid1;
                   else if(randNum == 0)
                       asteroid = asteroid2;
                }
                gameProgress = moveAsteroids(asteroid, curGameSpeed, gameProgress);
                curGameSpeed = (startGameSpeed + (gameProgress * 25)) * elapsedTime;// * (1 - mapTimeDilationPercentage);
                moveCredit(credit, curGameSpeed);
            }
            else if (completeScreen.getFillColor().a != 200)
            {
                Color curCol = completeScreen.getFillColor();
                completeScreen.setFillColor(Color(curCol.r, curCol.g, curCol.b, curCol.a + 4));
            }
            //Stage 2 of level complete
            else if (completeScreen.getFillColor().a == 200 and completeStage == 2)
            {
                completeStage = 3;
                itemHandler->chooseItems();
                Button *rerollItemButton = new Button;
                rerollItemButton->createButton(relUnitX * 50, relUnitY * 50, 200, 50, &gameFont, "Reroll", 20); 
                rerollItemButton->visible = true;
                buttonList.push_back(rerollItemButton);
            }
        
            //update is player hit
            shipHit = false;
            
            if (completeStage == 0)
            {
                switch(checkIfPlayerHit(player, collidableEntities, asteroid, enemyList, enemyBulletList, &shipHitParticles, &myActiveItems))
                {
            
                    case 3:
                        shipHit = true;
                        player -> isHit = true;
                    case 2:
                        shipHit = true;
                    case 1:
                        shipHit = true;
                }
                if (shipHit and currentLevelType == 1)
                {
                    levelProgress = maxLevelProgress;
                    curGame ->nextStageType = 0;
                    for (int i = 0; i < enemyList.size(); i++)
                        enemyList[i]->life = 0;
                    emptyState(player);
                    completeStage = 2;
                    levelComplete = true;
                    challengeSucceeded = false;
                    entities.clear();
                }
                if (player->health <= 0)
                {
                    isPlayerDead = true;
                    levelProgress = maxLevelProgress;
                    for (int i = 0; i < enemyList.size(); i++)
                        enemyList[i]->life = 0;
                    emptyState(player);
                    completeStage = 2;
                    levelComplete = true;
                    entities.clear();
                
                }
                    
            }

            screenShake(app, shipHit);
            drawText("Ship Coords: " + to_string(player->x) + "," + to_string(player->y), 20, relUnitX * 40, relUnitY * 20, app);
            glowShader.setUniform("shipCoords", sf::Vector2f(player->x, player->y));
            app.draw(rectangle, &glowShader);
            //update misc enemies
            for (auto i:miscEnemyList)
            {
                Bullet *temp = checkSpriteCollisions(i, bulletList);
                if (temp != NULL)
                {
                   hitParticles.setEmitter(sf::Vector2f(temp->x, temp->y));
                   i -> takeDamage(temp->damage);
                   temp -> life = 0;
                   enemyHit = true;
                }
            } 
            
            //check enemy bullet collisions
            for (int i = 0; i < enemyBulletList.size(); i++)
            {
                Bullet *temp = checkSpriteCollisions(asteroid, enemyBulletList);
                if (temp != NULL)
                {
                    temp->life = 0;
                    enemyHit = true;
                    hitParticles.setEmitter(sf::Vector2f(temp->x, temp->y));
                }
            }
            
            //check player bullet collisions
            for (int i = 0; i < bulletList.size(); i++)
            {
                Bullet *temp = checkSpriteCollisions(asteroid, bulletList);
                if (temp != NULL and myActiveItems.ghostBullets != myActiveItems.active)
                {
                    temp->life = 0;
                    enemyHit = true;
                    hitParticles.setEmitter(sf::Vector2f(temp->x, temp->y));
                }
                temp = checkSpriteCollisions(bulletList[i], enemyBulletList);
                if (myActiveItems.projDisruptorField == myActiveItems.active and temp != NULL)
                {
                    temp->life = 0;
                    explosionParticles.setEmitter(sf::Vector2f(temp->x, temp->y));
                    enemyKilled = true;
                }

            }
        
            //check if picked up gold
            Entity* temp = checkSpriteCollisions(player, creditList);
            if (temp != NULL)
            {
                character->credits += 1;
                numCreditsCollectedRound++;
                temp->setPosition(-100, -100);
            }
        
            //check all attachments to activate
            
            
            for (int i = 0; i < AOElist.size(); i++)
            {
                //cout << AOElist.size();
                AOElist.at(i)->AoeUpdate(elapsedTime);
                AOElist.at(i)->update();
                AOElist.at(i)->checkDamage(&enemyList);
                AOElist.at(i)->checkBullets(&enemyBulletList);
            }
             
            //spawn enemies
            if (tick != 0 and tick%ticksTillEnemySpawn == 0 and completeStage == 0)
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
                ticksTillEnemySpawn = rand() % 200 + 250;
            }
            
            //Handles Boss Death
            if (bossDeath == true)
            {
                if (numBossExplosions <= 5 and tick%20 == true)
                {
                    int randW = rand() % int(bosses[0]->w);
                    int randH = rand() % int(bosses[0]->h);
                    explosionParticles.setEmitter(sf::Vector2f(randW + bosses[0]->x - bosses[0]->w/2, randH + bosses[0]->y - bosses[0]->h/2));
                    enemyKilled = true;
                    numBossExplosions++;
                }
                else if (numBossExplosions < 25 and numBossExplosions > 5 and tick%10 == true)
                {
                    int randW = rand() % int(bosses[0]->w);
                    int randH = rand() % int(bosses[0]->h);
                    explosionParticles.setEmitter(sf::Vector2f(randW + bosses[0]->x - bosses[0]->w/2, randH + bosses[0]->y - bosses[0]->h/2));
                    enemyKilled = true;
                    numBossExplosions++;
                }    
                else if (numBossExplosions == 25)
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
                completeStage = 1;
                nextLevelSetting = curGame->getNextStageChoices();
                for (int i = 0; i < enemyList.size(); i++)
                    enemyList[i]->life = 0;
                emptyState(player);
                    
                //return 3;
            }
            
            if (completeStage == 1)
            {
                if (glowValue < 1.0)
                    glowValue = glowValue + 0.01;
                if (player->x >= screenW)
                {
                    if (nextLevelSetting == 1)
                        curGame -> nextStageType = 0;
                    else if (nextLevelSetting == 2)
                    {
                        if (player->y <= screenH/2)
                            curGame -> nextStageType = 0;
                        else if (player->y > screenH/2)
                            curGame -> nextStageType = 1;
                    }
                    completeStage = 2;
                    levelComplete = true;
                    entities.clear();
                }
            }
            
            //Stage 4 of level complete
            else if ((completeTick == 50 and completeStage == 4) or itemIsChosen)
            {
                if (isPlayerDead)
                {
                    character->items.clear();
                    character->attachments.clear();
                    curGame->restartGame();
                    return 0;
                }
                curGame->nextStage();
                return 3;
            }
        
            //draw
            app.draw(backParticles3);
            app.draw(backParticles2);
            app.draw(backParticles1);
            //for(auto i:shieldList) 
                //app.draw(i->circle);
                 
            //Update Conventional Enemies
            for(auto i:entities) i->draw(app, &shader);
            for (auto i:enemyList)
            {

                if (!(i->bulletsPassThrough))
                {
                    Bullet *temp = checkSpriteCollisions(i, bulletList);
                    if (temp != NULL)
                    {
                       hitParticles.setEmitter(sf::Vector2f(temp->x, temp->y));
                       enemyHit = true;
                       temp->onContact(player);
                       i -> takeDamage(temp->damage);
                       i -> isHit = true;
                       temp -> life = 0;
                    }
                }
                
                if (i->life == 0)
                {
                   numEnemiesKilledRound++;
                   explosionParticles.setEmitter(sf::Vector2f(i->x, i->y));
                   enemyKilled = true;
                   if (myActiveItems.cumulativeFirepower == myActiveItems.active)
                   {
                        player->damageMult+=0.025;
                        myActiveItems.cumFireDamage+=0.025;
                   }
                }
                i -> enemyMove(elapsedTime);
                i->enemyAttack(&enemyBulletList, &entities, advanceTick);
                i->ability(enemyList, &bulletList, app);
            
                
                //bulletSound.setBuffer(laserSound);
                //bulletSound.play();
                    //i->ticksSinceLastFire = 0;

            } 
            
            for (auto i:attachmentList)
            {
                i->activate(&entities, &bulletList, player);
                i->activate(&AOElist, player);
            }
            
            for (auto i:AOElist)
            {
                if (i->visible == true)
                    app.draw(i->AOEcircle);
            }
            
             //update particles
            shipParticles.setEmitter(sf::Vector2f(player->x - 30, player->y - 5));
            sf::Time elapsed = clock.restart();
            elapsedTime = elapsed.asSeconds();
            shipParticles.update(elapsed, true);
            hitParticles.update(elapsed, enemyHit);
            explosionParticles.update(elapsed, enemyKilled);
            shipHitParticles.update(elapsed, shipHit);
            backParticles1.update(elapsed, true);
            backParticles2.update(elapsed, true);
            backParticles3.update(elapsed, true);
            
            for (auto i:entities)
            {
                if(curGame->showHitBoxes and i->sprite.getTexture()!=NULL)
                {
                    sf::RectangleShape hitBox;
                    i->boundingBox=i->sprite.getGlobalBounds();
                    hitBox.setSize(sf::Vector2f(i->boundingBox.width, i->boundingBox.height));
                    hitBox.setFillColor(sf::Color::Transparent);
                    hitBox.setOutlineColor(sf::Color::Red);
                    hitBox.setOutlineThickness(5);
                    //hitBox2.setOrigin(i->rect->width/2, i->rect->height/2);
                    hitBox.setPosition(i->boundingBox.left, i->boundingBox.top);
                    
                    /*sf::CircleShape circle;
                    circle.setRadius(5);
                    circle.setOutlineColor(sf::Color::Red);
                    circle.setOutlineThickness(5);
                    circle.setOrigin(5, 5);
                    circle.setPosition(i->sprite.getPosition().x, i->sprite.getPosition().y);
                    
                    sf::CircleShape circle2;
                    circle2.setRadius(5);
                    circle2.setOutlineColor(sf::Color::Blue);
                    circle2.setOutlineThickness(5);
                    circle2.setOrigin(5, 5);
                    circle2.setPosition(i->x, i->y);*/
                    
                    app.draw(hitBox);
                    //app.draw(circle);
                    //app.draw(circle2);
                }
            }
            
            if (completeStage < 2)
                app.draw(shipParticles);
            app.draw(hitParticles);
            app.draw(explosionParticles);
            app.draw(shipHitParticles);

            //check buttons
            if (buttonList.size() > 0 and buttonList[0]->leftClicked == true)
            {
                buttonList[0]->leftClicked = false;
                itemHandler -> chooseItems();
            }
            
            drawText(": " + std::to_string(character->credits), 20, 65, 12, app);
            drawText(": " + std::to_string(player->health), 20, 65, 60, app);
            drawText("Progress: " + std::to_string(levelProgress), 20, 500, 20, app);
            drawText("Progress: " + std::to_string(progressPercent), 20, 500, 50, app);
            drawText("Fury status: " + to_string(myActiveItems.fury), 20, relUnitX * 25, relUnitY * 25, app);
            drawText("Panic status: " + to_string(myActiveItems.panic), 20, relUnitX * 25, relUnitY * 30, app);
            
            drawChallengeText(currentLevelType, levelProgress, app);
            
            app.draw(completeScreen);
            
            //Stage 4 of complete Stage
            if ((completeTick >= 50 and completeStage == 3) or completeStage > 3)
            {
                if (!isPlayerDead)
                {
                    if (currentLevelType == 0 or challengeSucceeded == true)
                        drawText("Level Complete", 60, relUnitX * 40, relUnitY * 20, app);
                    else
                        drawText("Challenge Failed", 60, relUnitX * 40, relUnitY * 20, app);
                    drawText("Credits Collected: " + to_string(numCreditsCollectedRound), 40, relUnitX * 40, relUnitY * 30, app);
                    drawText("Enemies Killed: " + to_string(numEnemiesKilledRound), 40, relUnitX * 40, relUnitY * 35, app);
                }
                else
                {
                    drawText("YOU DIED", 60, relUnitX * 40, relUnitY * 20, app);
                }
                if (currentLevelType == 1 and challengeSucceeded)
                {
                    int itemScreenWidth = relUnitX * 80;
                    int totalShapesWidth = itemHandler -> itemChoices.size() * 150;
                    int remainingWidth = itemScreenWidth - totalShapesWidth;
                    int spaceBetween = remainingWidth/(itemHandler -> itemChoices.size() - 1);

                    for (int i = 0; i < itemHandler -> itemChoices.size(); i++)
                    {
                        Item *curItem = itemHandler -> itemChoices.at(i);
                        int currentTotalShapesWidth = i * 150;
                        int itemPos = (relUnitX * 5) + currentTotalShapesWidth + (i * spaceBetween);

                        drawText(curItem->name + ":", 20, itemPos, (relUnitY * 80), app);
                        drawText(curItem->desc + ":", 14, itemPos, (relUnitY * 85), app);
                        curItem->createButton(itemPos + (relUnitX * 10), (relUnitY * 65), 150, 150);
                        itemHandler->checkIfItemHovered();
                        app.draw(curItem->button.icon);
                    } 
                    itemIsChosen = itemHandler->checkIfItemChosen();
                    for(auto i:buttonList)
                    {
                        if (i->visible == true)
                        {
                            app.draw(i->rectangle);
                            app.draw(i->buttonText);
                        }
                    }
                    
                }
                if (completeStage == 3 and (currentLevelType == 0 or itemIsChosen or !challengeSucceeded))
                {
                    completeStage = 4;
                    completeTick = 0;
                }
                
            }
            app.display();
            pauseTex.update(app);
            app.clear(Color::Black);
            
            //app.draw(randomSprite);
            //app.draw(rectangle);
        }
    
    
    
        return -1;
    }

    
    
};
