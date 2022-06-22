#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <list>
#include <math.h>
#include <cstring>
#include <unistd.h>
#include "Item.h"
#include "Button.h"
#include "Character.h"
#include "ItemActivationHandler.h"

extern RenderWindow app;

struct itemActivation
{
    enum itemStatus {notEquipped, notActive, active};
    itemStatus fury = notEquipped;
    itemStatus projectileDisruptorField = notEquipped;
    itemStatus ghostBullets = notEquipped;
    itemStatus projDisruptorField = notEquipped;
    itemStatus panic = notEquipped;
    itemStatus reinforcedHull = notEquipped;

};

class ItemHandler
{
    public:
    //std::vector<Item*> equippedItems;
    std::vector<Item*> itemChoices;
    std::vector<Item*> commonItemPool;
    std::vector<Item*> rareItemPool;
    std::vector<Item*> legendaryItemPool;
    Character *character;
    Texture t1,t2,t3,t4,t5,t10,t11,t12,t20,t21,t22;
    int itemChoicesNum = 3;
    ItemHandler(Character *Character)
    {
        t1.loadFromFile("images/item1.png");
        t2.loadFromFile("images/item2.png");
        t3.loadFromFile("images/item3.png");
        t4.loadFromFile("images/item4.png");
        t5.loadFromFile("images/item1.png");
        t10.loadFromFile("images/item10.png");
        t11.loadFromFile("images/item11.png");
        t12.loadFromFile("images/item12.png");
        t20.loadFromFile("images/item20.png");
        t21.loadFromFile("images/item21.png");
        t22.loadFromFile("images/item22.png");
        //Common Items
        Sprite sprite(t1);
        Item *item = new Item("Caliber Upgrade", 0, 0, "Fire higher caliber rounds\n\nGuns do 15% more damage", t1, sprite);
        commonItemPool.push_back(item);
        sprite.setTexture(t2);
        item = new Item("Advanced Load Mechanism", 0, 1, "Loads bullets more efficiently, \nleading to increased firerate\n\nGuns have 15% greater firerate", t2, sprite);
        commonItemPool.push_back(item);
        sprite.setTexture(t3);
        item = new Item("Reinforced Hull", 0, 2, "Increases thickness of hull armor\n\nEnemy contact damage reduced by 50%\nSpeed reduced by 10%", t3, sprite);
        commonItemPool.push_back(item);
        sprite.setTexture(t4);
        item = new Item("Altered Ballistics", 0, 3, "Increases fire-rate at the cost of bullet speed\n\nGuns have 20% greater firerate\nGuns have 20% less bullet speed", t4, sprite);
        commonItemPool.push_back(item);
        item = new Item("Panic", 0, 4, "Increase your damage and firerate when hit\n\nDamage and firerate increased by 20%\nfor 5 seconds when hit", t5, sprite);
        commonItemPool.push_back(item);
        
        //Rare Items
        sprite.setTexture(t10);
        item = new Item("Extra choice [Attachment]", 1, 10, "Your patronage is appreciated\n\nExtra attachment option available", t10, sprite);
        rareItemPool.push_back(item);
        sprite.setTexture(t11);
        item = new Item("Extra choice [Item]", 1, 11, "Your patronage is appreciated\n\nExtra item option available", t11, sprite);
        rareItemPool.push_back(item);
        sprite.setTexture(t12);
        item = new Item("Fury", 1, 12, "Unleash your rage as death approaches\n\n20% increased damage when under 50% health\n20%increased firerate when under 50% health", t12, sprite);
        rareItemPool.push_back(item);
        
        //Legendary Items
        sprite.setTexture(t20);
        item = new Item("Deadly Hull", 2, 20, "Hull is surrounded with a sphere of \nsuperheated plasma\n\nHitting regular enemies immediately kills them", t20, sprite);
        legendaryItemPool.push_back(item);
        
        sprite.setTexture(t21);
        item = new Item("Projectile Disruptor Field", 2, 21, "Coats projectiles with a disruptor field that can wipe out enemy shots"
        "\nProjectiles destroy any enemy projectiles they come in contact with", t21, sprite);
        legendaryItemPool.push_back(item);

        sprite.setTexture(t22);
        item = new Item("Ghost Bullets", 2, 22, "Nothing stands in your way\n\nProjectiles pass through asteroids", t22, sprite);
        legendaryItemPool.push_back(item);

        srand(time(NULL));
        
        character = Character;
        
        character->items.push_back(commonItemPool[2]);
        character->items.push_back(legendaryItemPool[0]);
        //character->items.push_back(rareItemPool[1]);
        //character->items.push_back(rareItemPool[2]);
        //character->items.push_back(legendaryItemPool[2]);
        //character->items.push_back(legendaryItemPool[1]);
        //printAllItems();
    }
    
    void checkIfItemHovered()
    {
        sf::Vector2i pixelPos = sf::Mouse::getPosition(app);
        sf::Vector2f worldPos = app.mapPixelToCoords(pixelPos);
        
        for (int i = 0; i < itemChoices.size(); i++)
        {
            if (itemChoices[i]->button.rect.contains(worldPos.x, worldPos.y))
            {
                itemChoices[i]->button.icon.setScale(1.2, 1.2);
                float width = itemChoices[i]->button.icon.getLocalBounds().width/2;
                float height = itemChoices[i]->button.icon.getLocalBounds().height/2;
                itemChoices[i]->button.icon.setOrigin(width, height);
                itemChoices[i]->button.rect = itemChoices[i]->button.icon.getGlobalBounds();
            
            }
        
        }
        return;
    }
    
    
    bool checkIfItemChosen()
    {
        sf::Vector2i pixelPos = sf::Mouse::getPosition(app);
        sf::Vector2f worldPos = app.mapPixelToCoords(pixelPos);
        
        for (int i = 0; i < itemChoices.size(); i++)
        {
            if (Mouse::isButtonPressed(Mouse::Left) and itemChoices[i]->button.rect.contains(worldPos.x, worldPos.y))
            {
                character->items.push_back(itemChoices[i]);
                return true;
            }
        }
    
    
    
    
        return false;
    }
    
    void printAllItems()
    {
        for (int i = 0; i < commonItemPool.size(); i++)
            cout << "\n"<< commonItemPool.at(i)->name;
        for (int i = 0; i < rareItemPool.size(); i++)
            cout << "\n"<< rareItemPool.at(i)->name;
        for (int i = 0; i < legendaryItemPool.size(); i++)
            cout << "\n"<< legendaryItemPool.at(i)->name;
    }
    
    void displayItems()
    {
    
    
    }
    
    void chooseItems()
    {
        itemChoices.clear();
        for (int i = 0; i < itemChoicesNum; i++)
        {
            int randNum = rand() % 100 + 1;
            if (randNum <= 60)
            {
                randNum = rand() % commonItemPool.size();
                itemChoices.push_back(commonItemPool.at(randNum));
            }
            else if (60 < randNum <=90)
            {
                randNum = rand() % rareItemPool.size();
                itemChoices.push_back(rareItemPool.at(randNum));
            }
            else if (90 < randNum <=100)
            {
                randNum = rand() % legendaryItemPool.size();
                itemChoices.push_back(legendaryItemPool.at(randNum));
            }
        }
    }

    void checkActiveItems (Actor *player, itemActivation *myActiveItems)
    {
        if (myActiveItems->fury == myActiveItems->active and player->health > player->maxHealth/2)
        {
            player -> damageMult-=0.2;
            player ->fireRateMult-=0.2;
            myActiveItems->fury = myActiveItems->notActive;

        }
        if (myActiveItems->panic == myActiveItems->active and player->ticksSinceLastHit == 300)
        {
            player -> damageMult-=0.2;
            player -> fireRateMult-=0.2;
            myActiveItems->panic = myActiveItems->notActive;
        }
    }
    
};
