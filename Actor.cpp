#include "Actor.h"

void Actor::createActor(int Health, int Shields, float Speed, float Firerate, bool IsEnemy)
{
    health = Health;
    shields = Shields;
    speed = Speed;
    firerate = Firerate;
    isEnemy = IsEnemy;
    xPos = x;
    yPos = y;

}

void Actor::moveActor(enum direction dir)
{

    switch(dir)
    {
        case up : 
            yPos = yPos - speed;
            cout << "\nup";
            break;
        case down : 
            yPos = yPos + speed;
            cout << "\ndown";
            break;
        case right : 
            xPos = xPos + speed;
            cout << "\nright";
            break;
        case left : 
            xPos = xPos - speed;
            cout << "\nleft";
            break;
        
        //sprite.setPosition(x,y);
    }
}

void Actor::update()
{

    x = xPos;
    y = yPos;


}
