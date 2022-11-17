#include "RenderHelper.h"
#include <iostream>

RenderHelper::RenderHelper(sf::RenderWindow& game_window) : window(game_window)
  {
    vector2 = new Vector2(40, 145);
      srand (time(0));
  }

RenderHelper::~RenderHelper()
{
  delete vector2;
}

int RenderHelper::randomize(int min, int max)
{
  int value = min + rand() / (RAND_MAX /(max - min));
  return value;
}

bool RenderHelper::ObjectRender()
{
  // Menu blocks
  for (int i = 0; i < grid_size; ++i)
  {
    menu_blocks[i].setSize(sf::Vector2f(40,20));
    menu_blocks[i].setPosition(vector2->getX(), vector2->getY());
    menu_blocks[i].setFillColor(sf::Color::Black);
    menu_blocks[i].getLocalBounds().height - 90;

  }

  // Game title
  game_title.setString("Break out!");
  game_title.setFont(title_font);
  game_title.setFillColor(sf::Color::White);
  game_title.setPosition(window.getSize().x /3 - 130,  42);
  game_title.setCharacterSize(120);

  // Game Over
  game_over.setString("Game Over");
  game_over.setFont(title_font);
  game_over.setFillColor(sf::Color::White);
  game_over.setPosition(window.getSize().x /3 - 150,  20);
  game_over.setCharacterSize(120);

  // Game Over Score
  game_over_score.setString("FINAL SCORE: " + std::to_string((int_score)));
  game_over_score.setFont(title_font);
  game_over_score.setFillColor(sf::Color::Red);
  game_over_score.setPosition(window.getSize().x /2 - 200,  220);
  game_over_score.setCharacterSize(50);


  // Menu options
  play_menu.setString("Play");
  play_menu.setFont(title_font);
  play_menu.setFillColor(sf::Color::Black);
  play_menu.setPosition(window.getSize().x /2 - play_menu.getLocalBounds().width/2 - 20, window.getSize().y /2 - play_menu.getGlobalBounds().height / 3);
  play_menu.setCharacterSize(40);

  // Menu options
  exit_menu.setString("Exit");
  exit_menu.setFont(title_font);
  exit_menu.setFillColor(sf::Color::Black);
  exit_menu.setPosition(window.getSize().x /2 - exit_menu.getLocalBounds().width/2 - 22, window.getSize().y /2 - exit_menu.getGlobalBounds().height / 3 + 120);
  exit_menu.setCharacterSize(40);

  // life
  life.setString("LIFE: " + std::to_string((int_life)));
  life.setFont(title_font);
  life.setCharacterSize(40);
  life.setPosition(10, 10);

  // score
  score.setString("SCORE: " + std::to_string((int_score)));
  score.setFont(title_font);
  score.setCharacterSize(40);
  score.setPosition(window.getSize().x - 300, 10);

  //Ball
  ball.initialiseSprite(ball_texture, "Data/Images/ball.png");
  ball.getSprite()->setTexture(ball_texture);
  ball.getSprite()->setScale(0.17, 0.17);
  ball.getSprite()->setPosition(window.getSize().x / 2 - (ball.getSprite()->getGlobalBounds().width / 2), window.getSize().y - ball.getSprite()->getGlobalBounds().height - 50);

  // Paddle
  paddle.initialiseSprite(paddle_texture, "Data/Images/paddleRed.png");
  paddle.getSprite()->setPosition(2,4);
  paddle.getSprite()->setTexture(paddle_texture);
  paddle.getSprite()->setPosition(window.getSize().x / 2 - (paddle.getSprite()->getGlobalBounds().width / 2), window.getSize().y - paddle.getSprite()->getGlobalBounds().height - 20);

  // Textures & Blocks
  if ((!red_block_texture.loadFromFile("Data/Images/element_red_rectangle.png")) ||
      (!green_block_texture.loadFromFile("Data/Images/element_green_rectangle.png")) ||
      (!blue_block_texture.loadFromFile("Data/Images/element_blue_rectangle.png")) ||
      (!purple_block_texture.loadFromFile("Data/Images/element_purple_rectangle.png")) ||
      (!yellow_block_texture.loadFromFile("Data/Images/element_yellow_rectangle.png")) ||
      (!white_block_texture.loadFromFile("Data/Images/element_grey_rectangle.png")))
  {
    std::cout << "Failed to load block textures" << std::endl;
  }

  for (int i = 0; i < blocks_rows; i++)
  {
    for (int j = 0; j < blocks_columns; j++)
    {
      block[i * blocks_columns + j].addSpriteColour(red_block_texture, GameObject::Colour::red);
      block[i * blocks_columns + j].getSprite()->setScale(0.9, 0.9);
      block[i * blocks_columns + j].getSprite()->setPosition(j * 70 + 25, i * 40 + 75);
    }
  }

  // Gems

  gem.initialiseSprite(gem_texture, "Data/Images/element_grey_diamond.png");
  gem.getSprite()->setPosition(randomize(20, window.getSize().x - 20), -gem.getSprite()->getGlobalBounds().height);

  // Font

  if (!title_font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf")){
    std::cout << "Title font did not load" << std::endl;
  }
  return true;
}


void RenderHelper::update(float dt)
{
  rand_n = rand() %100 + 1;

}

void RenderHelper::mouseMoved(sf::Event event)
{


}


void RenderHelper::renderMenu()
{
  window.draw(background, 10, sf::Quads);


  // Render Blocks
  for (int i = 0; i < grid_size; ++i)
    {
      for (int j = 0; j < row_size; ++j)
      {
        window.draw(menu_blocks[i]);
        menu_blocks[i].setPosition(menu_blocks[i+1].getPosition().x  + 52,
          vector2->getX() * j + vector2->getY());
      }
    }

    // Render title
    window.draw(game_title);
    window.draw(play_menu);
    window.draw(exit_menu);
}

void RenderHelper::renderGame()
{
  window.draw(background, 10, sf::Quads);
  window.draw(life);
  window.draw(score);
  for (int i = 0; i < blocks_rows*blocks_columns; i++)
  {
    if (block[i].visibility)
    {
      window.draw(*block[i].getSprite());
    }
  }
  window.draw(*paddle.getSprite());
  window.draw(*ball.getSprite());
  window.draw(*gem.getSprite());
}

void RenderHelper::renderGameOver()
{
  window.draw(background, 10, sf::Quads);
  window.draw(game_over);
  window.draw(game_over_score);
  window.draw(play_menu);
  window.draw(exit_menu);
}


