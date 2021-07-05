#include "Actor.h"

void Actor::createActor(int Health, int Shields, float Speed, float Firerate, bool IsEnemy, int IFrames)
{
    health = Health;
    shields = Shields;
    speed = Speed;
    firerate = Firerate;
    isEnemy = IsEnemy;
    iFrames = IFrames;
    xPos = x;
    yPos = y;

}

void Actor::moveActor(enum direction dir)
{

    switch(dir)
    {
        case up : 
            yPos = yPos - speed;
            break;
        case down : 
            yPos = yPos + speed;
            break;
        case right : 
            xPos = xPos + speed;
            break;
        case left : 
            xPos = xPos - speed;
            break;
        
    }
}

void Actor::setActorPosition(float X, float Y)
{
    xPos = X;
    yPos = Y;
}

void Actor::update()
{

    x = xPos;
    y = yPos;


}
