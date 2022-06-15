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

extern RenderWindow app;

class ItemHandler
{
    public:
    //std::vector<Item*> equippedItems;
    std::vector<Item*> itemChoices;
    std::vector<Item*> commonItemPool;
    std::vector<Item*> rareItemPool;
    std::vector<Item*> legendaryItemPool;
    Character *character;
    Texture t1,t2,t3,t4,t5,t6,t7;
    ItemHandler(Character *Character)
    {
        t1.loadFromFile("images/item1.png");
        t2.loadFromFile("images/item2.png");
        t3.loadFromFile("images/item3.png");
        t4.loadFromFile("images/item4.png");
        t5.loadFromFile("images/item5.png");
        t6.loadFromFile("images/item6.png");
        t7.loadFromFile("images/item7.png");
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
        
        //Rare Items
        sprite.setTexture(t4);
        item = new Item("Extra choice [Attachment]", 1, 10, "Your patronage is appreciated\n\nExtra attachment option available", t4, sprite);
        rareItemPool.push_back(item);
        sprite.setTexture(t5);
        item = new Item("Extra choice [Item]", 1, 11, "Your patronage is appreciated\n\nExtra item option available", t5, sprite);
        rareItemPool.push_back(item);
        
        
        //Legendary Items
        sprite.setTexture(t6);
        item = new Item("Deadly Hull", 2, 20, "Hull is surrounded with a sphere of \nsuperheated plasma\n\nHitting regular enemies immediately kills them", t6, sprite);
        legendaryItemPool.push_back(item);
        
        sprite.setTexture(t7);
        item = new Item("Projectile Disruptor Field", 2, 21, "Coats out projectiles with a disruptor field that can wipe out enemy shots"
        "\nProjectiles destroy any enemy projectiles they come in contact with", t7, sprite);
        legendaryItemPool.push_back(item);

        chooseItems();
        
        character = Character;
        
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
        srand(time(NULL));
        for (int i = 0; i < 3; i++)
        {
            int randNum = rand() % 100 + 1;
            if (randNum <= 60)
            {
                randNum = rand() % commonItemPool.size();
                itemChoices.push_back(commonItemPool.at(randNum));
            }
            else if (50 < randNum <=90)
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
    
};
