#ifndef __GAME_HPP
#define __GAME_HPP
#include "ai.hpp"
#include "bird.hpp"
#include "pipe.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <array>
#include <sstream>
enum GAME_STATES { GAME_STARTED, GAME_RESET, GAME_OVER };

class game {

public:
  game();
  void gameStart();
  void gameEnd();
  ai m_ai;

private:
  sf::RenderWindow window{sf::VideoMode(500, 750), "flappy bird"};
  void stateMachine();
  void gameContinue();
  void gameStopped();
  void gameReset();
  std::string score{};
  std::stringstream ss;
  int score_num{0};
  // bird m_bird;

  pipe m_pipe;
  sf::Sprite sprite;
  sf::Sprite replaySprite;

  sf::Texture texture;
  sf::Texture replayTexture;
  sf::Text text;
  sf::Font font;
  GAME_STATES state;
};

#endif
