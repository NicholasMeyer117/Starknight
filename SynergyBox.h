class SynergyBox
{
    public:
    
    sf::FloatRect rect;
    sf::RectangleShape synRec;
    sf::Text synText;
    String name;
    
    SynergyBox(int width, int height, String Name, Font *font, sf::Color color)
    {
        name = Name;
        
        synRec.setSize(sf::Vector2f(100, 100));
        synRec.setOutlineColor(sf::Color::Black);
        synRec.setFillColor(color);
        synRec.setOutlineThickness(5);
        synRec.setPosition(width, height);
        
        synText.setString(name);
        synText.setFont(*font);
        synText.setCharacterSize(20);
        synText.setFillColor(sf::Color::Black);
        synText.setPosition(synRec.getPosition().x + 15, synRec.getPosition().y + 30);
        
        rect = synRec.getGlobalBounds();
    }
    
    

};
