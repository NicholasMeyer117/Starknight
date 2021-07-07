#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class State
{
    public :
    virtual int Run (sf::RenderWindow &App) = 0;

};


