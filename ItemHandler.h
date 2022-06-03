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

class ItemHandler
{
    public:
    std::vector<Item*> equippedItems;
    std::vector<Item*> commonItemPool;
    std::vector<Item*> rareItemPool;
    std::vector<Item*> legendaryItemPool;
    ItemHandler()
    {
        //Common Items
        Item *item = new Item("Caliber Upgrade", 0, 0, "Fire higher caliber rounds\nGuns do 15% more damage");
        commonItemPool.push_back(item);
        item = new Item("Advanced Load Mechanism", 0, 1, "Loads bullets more efficiently, leading to increased firerate\nGuns have 15% greater firerate");
        commonItemPool.push_back(item);
        item = new Item("Reinforced Hull", 0, 2, "Enemy contact damage reduced by 50%");
        commonItemPool.push_back(item);
        
        //Rare Items
        item = new Item("Deadly Hull", 1, 10, "Hitting regular enemies immediately kills them");
        rareItemPool.push_back(item);
        
        
        //Legendary Items
        item = new Item("Projectile Disruptor Field", 2, 20, "Coats out projectiles with a disruptor field that can wipe out enemy shots"
        "\nProjectiles destroy any enemy projectiles they come in contact with");
        legendaryItemPool.push_back(item);

        
        
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
    
    int chooseItem()
    {
    
        return 0;
    }
    
};
