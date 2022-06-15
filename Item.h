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
#include "Button.h"

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
    ImageButton button;
    
    Item(string Name, int RarityLevel, int ItemID, string Desc, Texture texture,Sprite Sprite)
    {
        name = Name;
        rarityLevel = RarityLevel;
        itemID = ItemID;
        desc = Desc;
        tex = texture;
        sprite = Sprite;
    }
    
    void createButton(int x, int y, double w, double h)
    {
        //button = new ImageButton;
        button.createImageButton(tex, sprite, x, y, w, h);
        button.icon.setOrigin(w/2, h/2);
        button.rect = button.icon.getGlobalBounds();
    
    
    }


};
