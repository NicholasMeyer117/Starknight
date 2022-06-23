#include "Actor.h"

void Actor::createActor(int Health, int Shields, float Speed, float Firerate, bool IsEnemy, int IFrames, 
float ContactDamage, float DamageMult, float FireRateMult, float BulletSpeedMult, float SpeedMult, float HealthMult, 
float HealingMult, float UtilityMult, float AoeRadiusMult, float ContactDamageMult)
{
    health = Health;
    maxHealth = Health;
    shields = Shields;
    speed = Speed;
    firerate = Firerate;
    contactDamage = ContactDamage;
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
    aoeRadiusMult = AoeRadiusMult;
    contactDamageMult = ContactDamageMult;
    
    isActor = true;

}

void Actor::moveActor(enum direction dir)
{
    isMoving = true;
    switch(dir)
    {
        case up : 
            yPos = yPos - ((speed * speedMult) * elapsedTime);
            break;
        case down : 
            yPos = yPos + ((speed * speedMult) * elapsedTime);
            break;
        case right : 
            xPos = xPos + ((speed * speedMult) * elapsedTime);
            break;
        case left : 
            xPos = xPos - ((speed * speedMult) * elapsedTime);
            break;
        
    }
}

void Actor::update()
{
    if (x == xPos and y == yPos)
        isMoving = false;
    x = xPos;
    y = yPos;


}


void Actor::setActorPosition(float X, float Y)
{
    xPos = X;
    yPos = Y;
}
