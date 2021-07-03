#include "Button.h"

void Button::createButton(int x, int y, int w, int h, Font *font, String text, int textSize)
{
        rectangle.setSize(sf::Vector2f(w, h));
        rectangle.setOutlineColor(sf::Color::Black);
        rectangle.setOutlineThickness(1);
        rectangle.setOrigin(h/2, w/2);
        rectangle.setPosition(x, y);
        
        buttonText.setFont(*font);
        buttonText.setString(text);
        buttonText.setCharacterSize(textSize);
        buttonText.setFillColor(sf::Color::Black);
        buttonText.setOrigin(w/2, h/2);
        buttonText.setPosition(rectangle.getPosition().x + w/2, rectangle.getPosition().y - h*1.3);
        
        rect = IntRect(x - (w*.1), y - (h*2), w, h);
}
