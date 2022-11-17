#ifndef BREAKOUTSFML_RENDERHELPER_H
#define BREAKOUTSFML_RENDERHELPER_H

#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include "GameObject.h"


class RenderHelper
{
   public:
    RenderHelper(sf::RenderWindow& window);
    ~RenderHelper();
    bool ObjectRender();
    void renderMenu();
    void renderGame();
    void renderGameOver();
    void update(float dt);
    void mouseMoved(sf::Event event);




    Vector2* vector2;

    int mouseX = sf::Mouse::getPosition().x;
    int mouseY = sf::Mouse::getPosition().y;

    // Paddle Sprite
    GameObject paddle;

    // Bal Sprite
    GameObject ball;

    // Gem Sprite
    GameObject gem;

    // Block Sprite
    int blocks_rows = 10;
    int blocks_columns = 15;
    GameObject block[150];

  // Life
  int int_life = 2;
  sf::Text life;

  // Score
  int int_score = 0;
  sf::Text game_over_score;
  sf::Text score;

  // Menu options
  sf::Text play_menu;
  sf::Text exit_menu;

   private:
    int rand_n = 0;


    sf::Vector2i mouse;
    sf::Event event;
    sf::RenderWindow& window;
    sf::Vertex background[4] =
      {
      sf::Vertex(sf::Vector2f(0, 0), sf::Color::Blue),
      sf::Vertex(sf::Vector2f(0, window.getSize().y), sf::Color::Cyan),
      sf::Vertex(sf::Vector2f(window.getSize().x, window.getSize().y), sf::Color::Cyan),
      sf::Vertex(sf::Vector2f(window.getSize().x, 0), sf::Color::Cyan)
    };


    // Blocks
    int grid_size = 19;
    int row_size = 4;
    sf::RectangleShape menu_blocks[40];

    // Game Title
    sf::Text game_title;
    sf::Font title_font;

    // Game over
    sf::Text game_over;




    // paddle texture
    sf::Texture paddle_texture;

    // Ball Texture
    sf::Texture ball_texture;

    // blocks texture
    sf::Texture red_block_texture;
    sf::Texture green_block_texture;
    sf::Texture blue_block_texture;
    sf::Texture purple_block_texture;
    sf::Texture yellow_block_texture;
    sf::Texture white_block_texture;

    sf::Texture gem_texture;

    int randomize(int min, int max);
};

#endif // BREAKOUTSFML_RENDERHELPER_H
