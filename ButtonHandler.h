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

extern RenderWindow app;

class ButtonHandler
{
    public:


    bool checkIfButtonLeftClicked(Button *b)
    {

        Vector2i pixelPos = sf::Mouse::getPosition(app);
        Vector2f worldPos = app.mapPixelToCoords(pixelPos);

        if (b -> visible == true and b->rect.contains(worldPos.x, worldPos.y) == true)
        {
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                b->leftClicked = true;
                return true;
            }
        }


        return false;
    }

    int checkIfButtonClickedFromList()
    {
        return -1;
    }




};