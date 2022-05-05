#include "SynergyBox.h"
#include "Attachment.h"

struct Synergy{
  string name;
  int level; 
  int num;
  sf::Color color;
};

class SynergyHandler
{
    public:
    std::vector<SynergyBox*> synergyBoxes;
    std::vector<Sprite> synergySpriteList;
    std::vector<Texture> synergyTextureList;
    //std::vector<Synergy> synergies;
    Synergy synergies[12] = {{"Gun", 0, 0, sf::Color::Red},
                            {"Repair", 0, 1, sf::Color::Green},
                            {"Utility", 0, 2, Color(255, 165, 0)},
                            {"Seeker", 0},
                            {"AOE", 0},
                            {"Support", 0},
                            {"Bleeder", 0},
                            {"Merchant", 0},
                            {"Orbital", 0},
                            {"Summoner", 0},
                            {"Chainer", 0},
                            {"Manipulator", 0}};
                            
    SynergyHandler()
    {
        Texture s1, s2, s3;
        s1.loadFromFile("images/gun.png");
        synergyTextureList.push_back(s1);
        
        s2.loadFromFile("images/repair.png");
        synergyTextureList.push_back(s2);
        
        s3.loadFromFile("images/utility.png");
        synergyTextureList.push_back(s3);
        
        for (auto i:synergyTextureList)
        {
            Sprite sprite;
            sprite.setTexture(i);
            synergySpriteList.push_back(sprite);
           
        }
    }
    
    void addSynergyBox(int x, int y, String name, Font *font, sf::Color color, int num)
    {
        SynergyBox *synBox = new SynergyBox(x, y, name, font, color, synergyTextureList[num], synergySpriteList[num]);
        synergyBoxes.push_back(synBox);
    }
    
    void applySynergies(Actor *player)
    {
        if (synergies[0].level >= 2)
            player->bulletSpeedMult = 2;
        if (synergies[1].level >= 2)
            player->healingMult = 1.5;
        if (synergies[2].level >= 2)
            player->utilityMult = 1.5;
    }
    
    
    void checkSynergies(std::vector<Attachment*> attachments)
    {
        for (int i = 0; i < 12; i++)
            synergies[i].level = 0;
        for (int i = 0; i < attachments.size(); i++)
        {
            for(auto attachClass: attachments[i]->classList)
            {
                if (attachClass==Attachment::attachClass::Gun)
                    synergies[0].level++;
                else if (attachClass==Attachment::attachClass::Repair)
                    synergies[1].level++;
                else if (attachClass==Attachment::attachClass::Utility)
                    synergies[2].level++;
            }
        }
    }




};


