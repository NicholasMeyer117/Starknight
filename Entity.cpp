#include "Entity.h"
   
   void Entity::settings(Sprite &a,float X,float Y, float W, float H, float Angle,int radius)
   {
     sprite = a;
     boundingBox=sprite.getGlobalBounds();
     x=X; y=Y; //current ever-changing position relative to window
     angle = Angle;
     R = radius;
     w = boundingBox.width; h = boundingBox.height;
     xPos = X, yPos = Y; //static original position on the map
     sprite.setOrigin(w/2,h/2);
   }
   
   void Entity::noSpriteSettings(float X,float Y, float W, float H, sf::Color color, float Angle,int radius)
   {
       x=X; y=Y; //current ever-changing position relative to window
       angle = Angle;
       R = radius;
       w = W; h = H;
       xPos = X, yPos = Y; //static original position on the map
       
       rectangle.setSize(sf::Vector2f(w, h));
       rectangle.setFillColor(color);
       rectangle.setOutlineColor(sf::Color::Black);
       rectangle.setOutlineThickness(1);
       rectangle.setOrigin(w/2, h/2);
       rectangle.setPosition(x, y);
   
   }
   
   void Entity::setPosition(float X, float Y)
   {
       x = X;
       y = Y;
   }
   
   float Entity::getAngle()
   {
       return absAngle;
   }
   
   bool Entity::isCollideWithSprite(Entity *a)
   {
       boundingBox = sprite.getGlobalBounds();
       a->boundingBox = a->sprite.getGlobalBounds();
       return boundingBox.intersects(a->boundingBox);
   
   }
   
   bool Entity::isSpriteCollideWithCircle(sf::CircleShape cir)
   {
       boundingBox = sprite.getGlobalBounds();
       sf::Vector2f topLeft(boundingBox.left, boundingBox.top);
       sf::Vector2f topRight(boundingBox.left + boundingBox.width, boundingBox.top);
       sf::Vector2f botLeft(boundingBox.left, boundingBox.top + boundingBox.height);
       sf::Vector2f botRight(boundingBox.left + boundingBox.width, boundingBox.top + boundingBox.height);

       return circleContains(cir, topLeft) || 
       circleContains(cir, topRight) || 
       circleContains(cir, botLeft) || 
       circleContains(cir, botRight);
   }
   
   bool Entity::circleContains(sf::CircleShape cir, sf::Vector2f corner)
   {
       sf::Vector2f center = cir.getPosition();
       float a = (corner.x - center.x);
       float b = (corner.y - center.y);
       a *= a;
       b *= b;
       float r = cir.getRadius() * cir.getRadius();

       return (( a + b ) < r);
   
   }

   bool Entity::isCollide(Entity *a)
   {
   //dimensions of 

      Vector2f al, ar, bl, br;
      al.x = (a->x - (a->w)/2);
      al.y = (a->y + (a->h)/2);
    
      ar.x = (a->x + (a->w)/2);
      ar.y = (a->y - (a->h)/2);
    
      bl.x = (x - w/2);
      bl.y = (y + h/2);
    
      br.x = (x + w/2);
      br.y = (y - h/2);
    
      // If one rectangle is on left side of other
      if (al.x >= br.x or bl.x >= ar.x)
         return false;
      // If one rectangle is above other
      if (al.y <= br.y or bl.y <= ar.y)
         return false;
      else
         return true;
}

   void Entity::update(){}
   
   void Entity::draw(RenderWindow &app)
   {
     if (sprite.getTexture() != NULL)
     {
         sprite.setOrigin(w/2,h/2);
         sprite.setPosition(x, y);
         sprite.setRotation(angle);
         app.draw(sprite);
         absAngle = sprite.getRotation();
     }
     else
         app.draw(rectangle);
     /*else if (isCircle == false)
     {
         app.draw(rectangle);
     }
     else
         app.draw(circle);*/

     
   }

   void Entity::draw(RenderWindow &app, sf::Shader *shader)
   {
     if (sprite.getTexture() != NULL)
     {
         sprite.setOrigin(w/2,h/2);
         sprite.setPosition(x, y);
         sprite.setRotation(angle);
         if (isHit == true)
             app.draw(sprite, shader);
         else
             app.draw(sprite);
         absAngle = sprite.getRotation();
     }
     else
     {
         app.draw(rectangle);
     }

     isHit = false;
     
   }

   Entity:: ~Entity(){}

