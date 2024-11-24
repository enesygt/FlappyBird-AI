#ifndef __AI_HPP
#define __AI_HPP
#include "bird.hpp"
#include "pipe.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <array>
class ai {
public:
  ai();
  void startAi();
  bird crossOver(const bird &b1, const bird &b2);
  void ai_display(sf::RenderWindow &window);
  void display_update();
  void pipeInputProcess(std::array<float, 2> pipe_inputs);
  void calculatePipe(const pipe &game_pipes);
  void pipeCollisionCheck(pipe &game_pipes);
  void scoreCheck(pipe &game_pipes);
  void aiLearningStart();
  std::vector<bird> m_birds;
  std::vector<bird> m_best_birds;
  bool bird_left{true};
  size_t generation_counter{};
  size_t m_highest_score{};
};

#endif
