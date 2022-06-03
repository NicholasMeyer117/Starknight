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

class Item
{
    public:
    string name;
    int rarityLevel; //0, 1, 2
    int itemID; //for ID purposes
    
    string desc;
    
    sf::FloatRect rect;
    sf::RectangleShape synRec;
    sf::Sprite sprite;
    sf::Texture tex;
    
    Item(string Name, int RarityLevel, int ItemID, string Desc)
    {
        name = Name;
        rarityLevel = RarityLevel;
        itemID = ItemID;
        desc = Desc;
    }


};
