
#define random(min, max) rand() % (max + 1 - min) + min

#ifndef BREAKOUT_GAME_H
#define BREAKOUT_GAME_H

#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include "RenderHelper.h"
#include "GameObject.h"


class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void mouseMoved(sf::Event event);
  void keyPressed(sf::Event event);
  void movePaddle();
  void moveBall();
  void blockCollision();
  void paddleCollision();
  void wallsCollision();
  int randomize(int min, int max);
  void releaseGems(float dt);
  bool isInside(sf::Event event);
  void resetGame();

  void randVector();

  RenderHelper* renderHelper;
  GameObject* gameObject;
  Vector2* vector2;

  enum GameState
  {
    in_menu,
    game_play,
    game_over
  };

  GameState current_state = in_menu;


 private:

  sf::Event event;

  bool inside_play = false;
  bool inside_exit = false;

  sf::RenderWindow& window;

  float ball_speed = 8.0;

  float float_min = 0.2;
  float float_max = 1;

  int seconds = 5;
  sf::Clock start_clock;
  sf::Clock gem_clock;

  bool ball_released = false;
  bool gem_released = false;

  int life = 2;
  int rand_seconds;
  int gem_count = 0;

  int score = 0;

};

#endif // BREAKOUT_GAME_H
