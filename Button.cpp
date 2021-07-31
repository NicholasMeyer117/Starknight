#include "Button.h"

void Button::createButton(int x, int y, int w, int h, Font *font, String text, int textSize)
{
        rectangle.setSize(sf::Vector2f(w, h));
        rectangle.setOutlineColor(sf::Color::Black);
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
