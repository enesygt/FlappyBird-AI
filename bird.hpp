#ifndef __BIRD_HPP
#define __BIRD_HPP

#include "SFML/Graphics.hpp"
#include "neuron.hpp"
#include <SFML/Graphics/Sprite.hpp>

class bird {
public:
  bird();
  void update();
  void update(float xSpeed);
  void draw(sf::RenderWindow &window);
  void event();
  void birdReset();
  void movement(bool jump);
  sf::Sprite birdSprite;
  neuron m_neuron;
  bool is_bird_live;
  size_t training{};

private:
  sf::Texture birdTexture;
  sf::Texture birdTersTexture;
  int wingCounter{};
  int counter = 0;
  bool move = false;
  float speed = 0;
  float gravity = 0.29;
};

#endif
