#ifndef _PIPE_HPP
#define _PIPE_HPP

#include "SFML/Graphics.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <vector>

#include <array>
class pipe {
public:
  pipe();
  void update();
  void draw(sf::RenderWindow &window);
  bool collisionCheck(const sf::Sprite &object);
  std::array<float, 2>
  calculateFirstPipeDistance(const sf::Sprite &object) const;
  void pipeReset();
  bool scoreCheck(sf::Sprite &object, int &last_measure);

private:
  void pipeMove();
  float calculateDistance(const sf::Vector2f &point1,
                          const sf::Vector2f &point2) const;
  std::vector<std::vector<sf::Sprite>> pipeVec{};
  sf::Texture pipeTexture;
  sf::Texture pipeOppositeTexture;
  sf::Sprite pipeSprite;
  sf::Sprite pipeOppositeSprite;
  int creation_count = 0;
  int m_speed = 5;
};

#endif
