#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <list>
#include <math.h>

class ProgressBar
{
    public:
    Texture texture;
    float percentage = 1.00; //0 to 1.0
    float w, h, x, y;
    int detail; // 500 means 100%, 99.8%, 99.6% etc
    RectangleShape rectangle;
    std::vector<RectangleShape> bars;
    
    
    ProgressBar(int Detail, float Width, float Height, float X, float Y)
    {
        detail = Detail;
        w = Width;
        h = Height;
        x = X;
        y = Y;
        
        rectangle.setSize(sf::Vector2f(w, h));
        rectangle.setFillColor(sf::Color::Transparent);
        rectangle.setOutlineColor(sf::Color::Black);
        rectangle.setOutlineThickness(1);
        //rectangle.setOrigin(w/2, h/2);
        rectangle.setPosition(x, y);
        
        addBars();
    
    }
    
    void addBars()
    {
        for (int i = 0; i < detail*percentage; i++)
        {
            RectangleShape bar;
            bar.setSize(sf::Vector2f(w/detail, h));
            bar.setFillColor(sf::Color::Red);
            bar.setPosition(x  + ((w/detail) * i), y);
            bars.push_back(bar);
            
        }
    }
    
    void changePercentage(float per)
    {
        percentage = per;
        bars.clear();
        addBars();
    }





};
