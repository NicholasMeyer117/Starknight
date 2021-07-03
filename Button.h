#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

class Button
{

    public:
    sf::IntRect rect;
    sf::RectangleShape rectangle;
    sf::Text buttonText;
    bool visible = false;
    bool clicked = false;

    void createButton(int x, int y, int w, int h, Font *font, String text, int textSize);









};
