#include "Button.h"
#include <iostream>

void Button::createButton(int x, int y, int w, int h, Font *font, String text, int textSize, Color buttonColor)
{
        rectangle.setSize(sf::Vector2f(w, h));
        rectangle.setOutlineColor(sf::Color::Black);
        rectangle.setFillColor(buttonColor);
        rectangle.setOutlineThickness(1);
        rectangle.setOrigin(w/2, h/2);
        rectangle.setPosition(x, y);
        
        buttonText.setFont(*font);
        buttonText.setString(text);
        buttonText.setCharacterSize(textSize);
        buttonText.setFillColor(sf::Color::Black);
        sf::FloatRect textRect = buttonText.getLocalBounds();
        buttonText.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
        buttonText.setPosition(rectangle.getPosition().x, rectangle.getPosition().y);
        
        rect = rectangle.getGlobalBounds();
        
        
}

void Button::moveTo(int x, int y)
{
    rectangle.setPosition(x, y);
    rect = rectangle.getGlobalBounds();
    sf::FloatRect textRect = buttonText.getLocalBounds();
    buttonText.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    buttonText.setPosition(rectangle.getPosition().x, rectangle.getPosition().y);
    
}

void ImageButton::createImageButton(Texture tex, Sprite sprite, int x, int y, double w, double h)
{
    texture = tex;
    icon = sprite;
    icon.setTexture(texture);
    //icon.setOrigin(w/2, h/2);
    double test = w/tex.getSize().x;
    //std::cout << "Bruh" + std::to_string(test);
    icon.setScale(w/tex.getSize().x, h/tex.getSize().y);
    icon.setPosition(sf::Vector2f(x, y)); 
    rect = icon.getGlobalBounds();
    
    /*rectangle.setSize(sf::Vector2f(w, h));
    rectangle.setOutlineColor(sf::Color::Black);
    rectangle.setOutlineThickness(1);
    rectangle.setOrigin(w/2, (h)/2);
    rectangle.setPosition(sf::Vector2f(x, y));*/
     
    
}

void ShopButton::createIcon(Texture iconTexture, Sprite sprite, int shopNumber, int w, int h, Font *font, String text, int textSize, int Cost)
{
    texture = iconTexture;
    icon = sprite;
    icon.setTexture(texture);
    
    icon.setOrigin(w/2, h/2);
    
    rectangle.setSize(sf::Vector2f(w, h + 50));
    rectangle.setOutlineColor(sf::Color::Black);
    rectangle.setOutlineThickness(1);
    rectangle.setOrigin(w/2, (h)/2);
    rectangle.setPosition((300 * shopNumber) + 300, 300);
    icon.setPosition((300 * shopNumber) + 300, 300);
    
    buttonText.setFont(*font);
    buttonText.setString(text);
    buttonText.setCharacterSize(textSize);
    buttonText.setFillColor(sf::Color::Black);
    sf::FloatRect textRect = buttonText.getLocalBounds();
    buttonText.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    buttonText.setPosition(rectangle.getPosition().x, rectangle.getPosition().y + h - 100);
        
    rect = icon.getGlobalBounds();
    cost = Cost;
    

}
