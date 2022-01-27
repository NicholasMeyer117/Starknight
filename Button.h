#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

class Button
{

    public:
    sf::FloatRect rect;
    sf::RectangleShape rectangle;
    sf::Text buttonText;
    bool visible = true;
    bool rightClicked = false;
    bool leftClicked = false;

    void createButton(int x, int y, int w, int h, Font *font, String text, int textSize, Color buttonColor = Color::White);
    void moveTo(int x, int y);

};

class ImageButton: public Button
{
    public:
    Texture texture;
    Sprite icon;
    
    void createImageButton(Texture tex, Sprite sprite, int x, int y, double w, double h);
    
};

class ShopButton: public Button
{
    public:
    Texture texture;
    Sprite icon;
    int cost;
    
    void createIcon(Texture iconTexture, Sprite sprite, int shopNumber, int w, int h, Font *font, String text, int textSize, int Cost);



};
