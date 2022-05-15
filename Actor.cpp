#include "Actor.h"

void Actor::createActor(int Health, int Shields, float Speed, float Firerate, bool IsEnemy, int IFrames, 
float DamageMult, float FireRateMult, float BulletSpeedMult, float SpeedMult, float HealthMult, float HealingMult, float UtilityMult)
{
    health = Health;
    maxHealth = Health;
    shields = Shields;
    speed = Speed;
    firerate = Firerate;
    isEnemy = IsEnemy;
    iFrames = IFrames;
    xPos = x;
    yPos = y;
    
    damageMult = DamageMult;
    fireRateMult = FireRateMult;
    bulletSpeedMult = BulletSpeedMult;
    speedMult = SpeedMult;
    healthMult = HealthMult;
    healingMult = HealingMult;
    utilityMult = UtilityMult;
    
    isActor = true;

}

void Actor::moveActor(enum direction dir)
{

    switch(dir)
    {
        case up : 
            yPos = yPos - (speed * speedMult);
            break;
        case down : 
            yPos = yPos + (speed * speedMult);
            break;
        case right : 
            xPos = xPos + (speed * speedMult);
            break;
        case left : 
            xPos = xPos - (speed * speedMult);
            break;
        
    }
}

void Actor::update()
{

    x = xPos;
    y = yPos;


}


void Actor::setActorPosition(float X, float Y)
{
    xPos = X;
    yPos = Y;
}
