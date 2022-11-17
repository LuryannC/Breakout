#include "GameObject.h"
#include <iostream>

GameObject::GameObject()
{
  sprite = new sf::Sprite;
  vector2 = new Vector2(40, 60);
  colour = Colour::red;
}

GameObject::~GameObject()
{
  delete sprite;
  delete vector2;
}

bool GameObject::initialiseSprite(sf::Texture& texture, std::string filename)
{
  if (!texture.loadFromFile(filename))
  {
    std::cout << "Failed to load: " + filename << std::endl;
    return false;
  }
  sprite->setTexture(texture);
  return true;
}

sf::Sprite* GameObject::getSprite()
{
  return sprite;
}

void GameObject::moveLeft()
{
  sprite->move(vector2->x * speed, 0);
}

void GameObject::moveRight()
{
  sprite->move(-vector2->x * speed, 0);
}

void GameObject::addSpriteColour(sf::Texture& texture, Colour texture_colour)
{
  sprite->setTexture(texture);
  colour = texture_colour;
}

bool GameObject::collisionCheck(sf::Sprite* object_1, sf::Sprite* object_2)
{
  float object_1_tl_x = object_1->getPosition().x;
  float object_1_tl_y = object_1->getPosition().y;
  float object_1_br_x = object_1->getPosition().x + object_1->getGlobalBounds().width;
  float object_1_br_y = object_1->getPosition().y + object_1->getGlobalBounds().height;


  float object_2_tl_x = object_2->getPosition().x;
  float object_2_tl_y = object_2->getPosition().y;
  float object_2_br_x = object_2->getPosition().x + object_2->getGlobalBounds().width;
  float object_2_br_y = object_2->getPosition().y + object_2->getGlobalBounds().height;


  if (object_1_br_x > object_2_tl_x &&
      object_1_tl_x < object_2_br_x &&
      object_1_br_y > object_2_tl_y &&
      object_1_tl_y < object_2_br_y)
  {
    return true;
  }
  return false;
}

bool GameObject::collisionTB(sf::Sprite* object_1, sf::Sprite* object_2)
{
  float object_1_top = object_1->getGlobalBounds().top;
  float object_1_bottom = object_1->getGlobalBounds().top + object_1->getGlobalBounds().height;

  float object_2_top = object_2->getGlobalBounds().top;
  float object_2_bottom = object_2->getGlobalBounds().top + object_2->getGlobalBounds().height;

  if (object_1_top < object_2_bottom &&
      object_1_bottom > object_2_top)
  {
    return true;
  }
  else if (object_1_top > object_2_bottom &&
           object_1_bottom < object_2_top)
  {
    return true;
  }
  return false;
}

bool GameObject::collisionLR(sf::Sprite* object_1, sf::Sprite* object_2)
{
  float object_1_left = object_1->getGlobalBounds().left;
  float object_1_right = object_1->getGlobalBounds().left + object_1->getGlobalBounds().width;

  float object_2_left = object_2->getGlobalBounds().top;
  float object_2_right = object_2->getGlobalBounds().left + object_2->getGlobalBounds().width;

  if (object_1_left < object_2_right &&
      object_1_right > object_2_left)
  {
    return true;
  }
  else if (object_1_left < object_2_right &&
           object_1_right > object_2_left)
  {
    return true;
  }
  return false;
}

bool GameObject::collisionXBox(sf::Sprite* object_1, sf::Sprite* object_2)
{
  float object_1_mid_point = object_1->getPosition().x + object_1->getGlobalBounds().width / 2;

  float object_2_left = object_2->getPosition().x + 0.2;
  float object_2_right = object_2->getPosition().x + object_2->getGlobalBounds().width - 0.2;

  if (object_1_mid_point < object_2_right &&
      object_1_mid_point > object_2_left)
  {
    return true;
  }

  return false;
}