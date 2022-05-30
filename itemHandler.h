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
    
    }
    
    void displayItems()
    {
    
    
    }
    
    int chooseItem()
    {
    
    }
    
    


}
