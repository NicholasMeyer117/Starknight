#include "Entity.h"
   
   void Entity::settings(Sprite &a,float X,float Y, float W, float H, float Angle,int radius)
   {
     sprite = a;
     x=X; y=Y; //current ever-changing position relative to window
     angle = Angle;
     R = radius;
     w = W; h = H;
     xPos = X, yPos = Y; //static original position on the map
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
         sprite.setPosition(x,y);
         sprite.setRotation(angle);
         app.draw(sprite);
         absAngle = sprite.getRotation();
     }
     else
     {
         app.draw(rectangle);
     }

     CircleShape circle(R);
     circle.setFillColor(Color(255,0,0,170));
     circle.setPosition(x,y);
     circle.setOrigin(R,R);
     //app.draw(circle);
     
   }

   Entity:: ~Entity(){}

