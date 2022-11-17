
#ifndef BREAKOUT_GAMEOBJECT_H
#define BREAKOUT_GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include "Vector2.h"

class GameObject
{
 public:
  GameObject();
  ~GameObject();
  sf::Sprite* getSprite();
  bool initialiseSprite(sf::Texture &texture, std::string filename);
  enum Colour{
    red, green, blue, purple,
    yellow, white
  };
  void addSpriteColour(sf::Texture &texture, Colour texture_colour);
  bool collisionCheck(sf::Sprite* object_1, sf::Sprite* object_2);
  bool collisionTB(sf::Sprite* object_1, sf::Sprite* object_2);
  bool collisionLR(sf::Sprite* object_1, sf::Sprite* object_2);
  bool collisionXBox(sf::Sprite* object_1, sf::Sprite* object_2);

  void moveRight();
  void moveLeft();
  float speed = 0.3;
  Colour colour;

  bool visibility = true;

 private:
  sf::Sprite* sprite = nullptr;
  Vector2* vector2;

};


#endif // BREAKOUT_GAMEOBJECT_H
