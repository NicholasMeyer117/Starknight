#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <list>
#include <math.h>
#include <cstring>
#include <unistd.h>
//#include <SFML/CircleShape.hpp>
#define PI 3.14159265

using namespace sf;
using namespace std;

//Base class for physical objects in the game
class Entity
{
   public:
   //x,y refer to current pixel position in window, while xPos and yPos are positons relative to origin
   float x,y,xPos,yPos,w,h,dx,dy,R,angle;
   float absAngle;
   float contactDamage = 0;
   float contactDamageMult = 1.0;
   bool life = 1;
   bool isHit = false;
   bool isActor = false;
   bool visible = true;
   std::string name;
   Sprite sprite;
   sf::FloatRect boundingBox;
   sf::RectangleShape rectangle;
   //sf::CircleShape dumbass;
   //bool isCircle = false;
   
   //sets up an object
   void settings(Sprite &a,float X,float Y, float W, float H, float Angle=0,int radius=1);
   
   //In case the object has no sprite and instead uses mathmatical graphics such as rectangle
   void noSpriteSettings(float X,float Y, float W, float H,  Color color, float Angle=0,int radius=1);
   
   //void circleSpriteSettings(float X,float Y, Color color, int radius);
   
   //sets x and y
   void setPosition(float X, float Y);
   
   //self explanatory
   float getAngle();
   
   //checks if entities with sprites overlap
   bool isCollideWithSprite(Entity *a);
   
   bool circleContains(sf::CircleShape cir, sf::Vector2f corner);
   
   //checks if entity with sprite overlaps with a circle
   bool isSpriteCollideWithCircle(sf::CircleShape cir);
   
   //checks if entity with no sprite overlaps with Entity a
   bool isCollide(Entity *a);
   
   virtual void update();

   //displays to RenderWindow
   void draw(RenderWindow &app);
   void draw(RenderWindow &app, sf::Shader *shader);

   virtual ~Entity();
};
