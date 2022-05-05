class SynergyBox
{
    public:
    
    sf::FloatRect rect;
    sf::RectangleShape synRec;
    sf::Sprite sprite;
    sf::Texture tex;
    sf::Text synText;
    String name;
    
    SynergyBox(int x, int y, String Name, Font *font, sf::Color color, Texture texture, Sprite spr)
    {
        name = Name;
        
        synRec.setSize(sf::Vector2f(100, 100));
        synRec.setOutlineColor(sf::Color::Black);
        synRec.setFillColor(color);
        synRec.setOutlineThickness(5);
        synRec.setPosition(x, y);
        
        rect = synRec.getGlobalBounds();
        sprite = spr;
        tex = texture;
        sprite.setTexture(tex);
        sprite.setOrigin(35, 40);
        sprite.setPosition(synRec.getPosition().x + 50, synRec.getPosition().y + 50);
    }
    
    

};
