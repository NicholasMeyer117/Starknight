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

extern RenderWindow app;

class ItemHandler
{
    public:
    std::vector<Item*> equippedItems;
    std::vector<Item*> itemChoices;
    std::vector<Item*> commonItemPool;
    std::vector<Item*> rareItemPool;
    std::vector<Item*> legendaryItemPool;
    ItemHandler()
    {
        //Common Items
        Item *item = new Item("Caliber Upgrade", 0, 0, "Fire higher caliber rounds\n\nGuns do 15% more damage");
        commonItemPool.push_back(item);
        item = new Item("Advanced Load Mechanism", 0, 1, "Loads bullets more efficiently, \nleading to increased firerate\n\nGuns have 15% greater firerate");
        commonItemPool.push_back(item);
        item = new Item("Reinforced Hull", 0, 2, "Increases thickness of hull armor\n\nEnemy contact damage reduced by 50%\nSpeed reduced by 10%");
        commonItemPool.push_back(item);
        
        //Rare Items
        item = new Item("Extra choice [Attachment]", 1, 10, "Your patronage is appreciated\n\nExtra attachment option available");
        rareItemPool.push_back(item);
        item = new Item("Extra choice [Item]", 1, 11, "Your patronage is appreciated\n\nExtra item option available");
        rareItemPool.push_back(item);
        
        
        //Legendary Items
        item = new Item("Deadly Hull", 2, 20, "Hull is surrounded with a sphere of \nsuperheated plasma\n\nHitting regular enemies immediately kills them");
        legendaryItemPool.push_back(item);
        
        item = new Item("Projectile Disruptor Field", 2, 21, "Coats out projectiles with a disruptor field that can wipe out enemy shots"
        "\nProjectiles destroy any enemy projectiles they come in contact with");
        legendaryItemPool.push_back(item);

        chooseItems();
        
        //printAllItems();
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
