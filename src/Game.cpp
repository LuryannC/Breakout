#include "Game.h"
#include <iostream>
#include "math.h"

/// Fix the vectors to be between 0 and 1 float for all classes
/// add gems
///


Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));

  renderHelper = new RenderHelper(window);
  vector2 = new Vector2(0, 0);
}

Game::~Game()
{
  delete renderHelper;
  delete vector2;
  delete gameObject;
}



void Game::randVector()
{
  float randY = float_min + (float)(rand()) / ((float)(RAND_MAX/(float_max - float_min)));

  if (rand() % 2 == 0)
  {
    randY = -randY;
  }

  vector2->y = randY;
}

int Game::randomize(int min, int max)
{
  int value = min + rand() / (RAND_MAX /(max - min));
  return value;
}


bool Game::init()
{
  randVector();
  renderHelper->ObjectRender();
  rand_seconds = randomize(3, 7);
  return true;
}

void Game::update(float dt)
{
  renderHelper->update(dt);
  if (current_state == in_menu)
  {
    score = 0;
    gem_clock.restart();
    start_clock.restart();
  }
  if (current_state == game_play)
  {
    movePaddle();
    moveBall();
    blockCollision();
    paddleCollision();
    wallsCollision();
    releaseGems(dt);
  }
  if (current_state == game_over)
  {
    gem_clock.restart();
    start_clock.restart();
  }
  if ((renderHelper->int_life == 0) || (renderHelper->int_score == 800))
  {
    current_state = game_over;
    renderHelper->game_over_score.setString("FINAL SCORE: " + std::to_string((renderHelper->int_score)));
    resetGame();
  }
  if (inside_play){
    renderHelper->play_menu.setCharacterSize(60);
    renderHelper->play_menu.setPosition(window.getSize().x /2 - renderHelper->play_menu.getLocalBounds().width/2 - 20, window.getSize().y /2 - renderHelper->play_menu.getGlobalBounds().height / 2);
  }
  else{
    renderHelper->play_menu.setCharacterSize(40);
    renderHelper->play_menu.setPosition(window.getSize().x /2 - renderHelper->play_menu.getLocalBounds().width/2 - 20, window.getSize().y /2 - renderHelper->play_menu.getGlobalBounds().height / 3);
  }
  if (inside_exit){
    renderHelper->exit_menu.setCharacterSize(60);
    renderHelper->exit_menu.setPosition(window.getSize().x /2 - renderHelper->exit_menu.getLocalBounds().width/2 - 22, window.getSize().y /2 - renderHelper->exit_menu.getGlobalBounds().height / 3 + 120);
  }
  else{
    renderHelper->exit_menu.setCharacterSize(40);
    renderHelper->exit_menu.setPosition(window.getSize().x /2 - renderHelper->exit_menu.getLocalBounds().width/2 - 22, window.getSize().y /2 - renderHelper->exit_menu.getGlobalBounds().height / 3 + 120);
  }
}

void Game::render()
{
  if (current_state == in_menu)
  {
    renderHelper->renderMenu();
  }
  else if (current_state == game_play)
  {
    renderHelper->renderGame();
  }
  else if (current_state == game_over)
  {
    renderHelper->renderGameOver();
  }

}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);
  if (event.type == sf::Event::MouseButtonPressed)
  {
    if (current_state == in_menu)
    {
      if (event.mouseButton.button == sf::Mouse::Left)
      {
        if (inside_play)
        {
          current_state = game_play;
        }
        else if (inside_exit)
        {
          window.close();
        }
      }
    }
    else
    {
      if (event.mouseButton.button == sf::Mouse::Left)
      {
        if (inside_play)
        {
          current_state = game_play;
        }
        else if (inside_exit)
        {
          window.close();
        }
      }
    }
  }

}

void Game::mouseMoved(sf::Event event)
{
  renderHelper->mouseMoved(event);
  isInside(event);
}

void Game::keyPressed(sf::Event event)
{

}
void Game::movePaddle()
{
  auto keyA = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
  auto keyD = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
  if (keyA)
  {
    renderHelper->paddle.moveRight();
  }
  else if (keyD)
  {
    renderHelper->paddle.moveLeft();
  }
  if((renderHelper->paddle.getSprite()->getPosition().x +
     renderHelper->paddle.getSprite()->getGlobalBounds().width) >= window.getSize().x)
  {
    renderHelper->paddle.getSprite()->move(-12, 0);
  }
  else if (renderHelper->paddle.getSprite()->getPosition().x <= 0)
  {
    renderHelper->paddle.getSprite()->move(12, 0);
  }
}


void Game::moveBall()
{
  if (start_clock.getElapsedTime().asSeconds() >= 2)
  {
    ball_released = true;
  }
  if (ball_released)
  {
    vector2->normalise();
    renderHelper->ball.getSprite()->move(
      vector2->x * ball_speed, -vector2->y * ball_speed);
  }
  else
  {
    renderHelper->ball.getSprite()->setPosition(renderHelper->paddle.getSprite()->getPosition().x + renderHelper->paddle.getSprite()->getGlobalBounds().width / 2 - renderHelper->ball.getSprite()->getGlobalBounds().width / 2, renderHelper->paddle.getSprite()->getPosition().y - 50);
  }
}



void Game::blockCollision()
{

  for (int i = 0; i < renderHelper->blocks_rows*renderHelper->blocks_columns; ++i)
  {
    if (renderHelper->block[i].visibility){
      if (gameObject->collisionCheck(renderHelper->ball.getSprite(), renderHelper->block[i].getSprite()))
      {
        if (gameObject->collisionXBox(renderHelper->ball.getSprite(), renderHelper->block[i].getSprite()))
        {
          vector2->y = -vector2->y;
          renderHelper->block[i].visibility = false;
          renderHelper->int_score += 20;
          renderHelper->score.setString("SCORE: " + std::to_string((renderHelper->int_score)));
        }
        else
        {
          vector2->x = -vector2->x;
          renderHelper->block[i].visibility = false;
          renderHelper->int_score += 20;
          renderHelper->score.setString("SCORE: " + std::to_string((renderHelper->int_score)));
        }
      }
    }
  }
}

void Game::paddleCollision()
{
  float ball_mid = renderHelper->ball.getSprite()->getPosition().x +
                   renderHelper->ball.getSprite()->getGlobalBounds().width / 2;
  float paddle_mid =
    renderHelper->paddle.getSprite()->getPosition().x +
    renderHelper->paddle.getSprite()->getGlobalBounds().width / 2;

  float delta_mid = ball_mid - paddle_mid;

  float x_P = float(fabs(delta_mid) / (paddle_mid / 2));
  float y_P = (1 - x_P);

  if (
    gameObject->collisionCheck(
      renderHelper->paddle.getSprite(), renderHelper->ball.getSprite()) &&
    vector2->y < 0)
  {
    vector2->y = -vector2->y;
    if (x_P > float_max)
    {
      x_P = float_max;
    }
    if (delta_mid < 0)
    {
      x_P = -x_P;
    }

    vector2->x = x_P;
    vector2->y = y_P;
  }
}

void Game::wallsCollision()
{
  int top_wall = 0;
  int left_wall = 0;
  int right_wall = window.getSize().x;
  int bottom_wall = window.getSize().y;

  if (renderHelper->ball.getSprite()->getPosition().y < top_wall)
  {
    vector2->y = -vector2->y;
  }
  else if (
    renderHelper->ball.getSprite()->getPosition().x +
    renderHelper->ball.getSprite()->getGlobalBounds().width > right_wall)
  {
    vector2->x = -vector2->x;
  }
  else if (
    renderHelper->ball.getSprite()->getPosition().y +
    renderHelper->ball.getSprite()->getGlobalBounds().height > bottom_wall + 10)
  {
    renderHelper->ball.getSprite()->setPosition(renderHelper->paddle.getSprite()->getPosition().x + renderHelper->paddle.getSprite()->getGlobalBounds().width / 2 - renderHelper->ball.getSprite()->getGlobalBounds().width, renderHelper->paddle.getSprite()->getPosition().y - 30);
    vector2->y = -vector2->y;
    randVector();
    renderHelper->int_life--;
    renderHelper->life.setString("LIFE: " + std::to_string((renderHelper->int_life)));
    gem_count--;
    start_clock.restart();
    ball_released = false;
  }
  else if (
    renderHelper->ball.getSprite()->getPosition().x +
    renderHelper->ball.getSprite()->getGlobalBounds().left < left_wall)
  {
    vector2->x = -vector2->x;
  }
}

void Game::releaseGems(float dt)
{
  if(gem_count <= 5)
  {
    if (gem_clock.getElapsedTime().asSeconds() >= rand_seconds)
    {
      gem_released = true;
    }
  }
  else
  {
    gem_clock.restart();
  }
  if (gem_released)
  {
    renderHelper->gem.getSprite()->move(0, 90 * dt);
    if (gameObject->collisionCheck(renderHelper->gem.getSprite(), renderHelper->paddle.getSprite()))
    {
      renderHelper->gem.getSprite()->setPosition(randomize(20, window.getSize().x - renderHelper->gem.getSprite()->getGlobalBounds().width - 20), -renderHelper->gem.getSprite()->getGlobalBounds().height);
      gem_released = false;
      gem_clock.restart();
      rand_seconds = randomize(3, 6);
      renderHelper->int_life += 1;
      renderHelper->life.setString("LIFE: " + std::to_string((renderHelper->int_life)));
      gem_count++;
    }
    else if (renderHelper->gem.getSprite()->getPosition().y + renderHelper->gem.getSprite()->getGlobalBounds().height / 2 >= window.getSize().y)
    {
      renderHelper->gem.getSprite()->setPosition(randomize(20, window.getSize().x - 20), -renderHelper->gem.getSprite()->getGlobalBounds().height);
      gem_released = false;
      gem_clock.restart();
      rand_seconds = randomize(3, 6);
    }
  }
}
bool Game::isInside(sf::Event event)
{
  if (
    event.mouseMove.x > renderHelper->play_menu.getPosition().x &&
    renderHelper->play_menu.getGlobalBounds().width + renderHelper->play_menu.getPosition().x > event.mouseMove.x)
  {
    if (
      event.mouseMove.y > renderHelper->play_menu.getPosition().y &&
      renderHelper->play_menu.getPosition().y + renderHelper->play_menu.getGlobalBounds().height > event.mouseMove.y)
    {
      {
        inside_play = true;
        return true;
      }
    }
  }
  if (event.mouseMove.x > renderHelper->exit_menu.getPosition().x &&
      renderHelper->exit_menu.getGlobalBounds().width + renderHelper->exit_menu.getPosition().x > event.mouseMove.x)
  {
    if (event.mouseMove.y > renderHelper->exit_menu.getPosition().y &&
        renderHelper->exit_menu.getPosition().y + renderHelper->exit_menu.getGlobalBounds().height > event.mouseMove.y)
    {
      inside_exit = true;
      return true;
    }
  }
  inside_play = false;
  inside_exit = false;
  return false;
}
void Game::resetGame()
{
  ball_released = false;
  gem_released = false;
  renderHelper->int_life = 2;
  renderHelper->life.setString("LIFE: " + std::to_string((renderHelper->int_life)));
  gem_count = 0;
  renderHelper->int_score = 0;
  renderHelper->score.setString("SCORE: " + std::to_string((renderHelper->int_score)));
  for (int i = 0; i < renderHelper->blocks_rows*renderHelper->blocks_columns; ++i)
  {
    renderHelper->block[i].visibility = true;
  }
  start_clock.restart();
  gem_clock.restart();
  renderHelper->ball.getSprite()->setPosition(renderHelper->paddle.getSprite()->getPosition().x + renderHelper->paddle.getSprite()->getGlobalBounds().width / 2 - renderHelper->ball.getSprite()->getGlobalBounds().width / 2, renderHelper->paddle.getSprite()->getPosition().y - 50);
  renderHelper->gem.getSprite()->setPosition(randomize(20, window.getSize().x - 20), -renderHelper->gem.getSprite()->getGlobalBounds().height);
}
