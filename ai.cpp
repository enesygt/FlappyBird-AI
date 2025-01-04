#include "ai.hpp"
#include <algorithm>
#include <iostream>
ai::ai() {

  for (int i = 0; i < 300; ++i) {
    m_birds.push_back(bird());
    m_birds[i].is_bird_live = true;
    m_birds[i].training = 0;
  }
}
void ai::startAi() {

  std::cout << "Highest score: " << m_highest_score << std::endl;
  std::cout << "Generation: " << generation_counter << std::endl;
  aiLearningStart();
  for (auto &bird : m_birds) {
    bird.birdSprite.setPosition(200, 250);
    bird.is_bird_live = true;

    bird.training = 0;
  }
  generation_counter++;
}

void ai::ai_display(sf::RenderWindow &window) {
  for (auto &bird : m_birds) {

    if (bird.is_bird_live)
      bird.draw(window);
  }
}

void ai::display_update() {
  bool birds_status = false;
  for (auto &bird : m_birds) {
    if (bird.is_bird_live) {
      bird.update();
      birds_status = true;
    }
  }
  bird_left = birds_status;
}

void ai::pipeInputProcess(std::array<float, 2> pipe_inputs) {
  for (auto &bird : m_birds) {
    std::array<float, 3> inputs{pipe_inputs[0], pipe_inputs[1],
                                bird.birdSprite.getPosition().y};

    bird.m_neuron.predict(inputs);
    bird.movement(bird.m_neuron.m_jump_result);
  }
}

void ai::calculatePipe(const pipe &game_pipes) {

  for (auto &bird : m_birds) {
    if (bird.is_bird_live) {
      pipeInputProcess(game_pipes.calculateFirstPipeDistance(bird.birdSprite));
    }
  }
}

void ai::pipeCollisionCheck(pipe &game_pipes) {
  for (int i = 0; i < 300; ++i) {
    if (game_pipes.collisionCheck(m_birds[i].birdSprite)) {
      // Todo: Try to disapper birds instead of erasing
      m_birds[i].is_bird_live = false;
    }
  }
}

void ai::scoreCheck(pipe &game_pipes) {
  size_t biggest_score = 0;
  static size_t current_score = 0;
  for (int i = 0; i < 300; ++i) {
    if (m_birds[i].is_bird_live &&
        game_pipes.scoreCheck(m_birds[i].birdSprite, m_birds[i].last_measure)) {
      m_birds[i].training += 1;
    }
    if (m_birds[i].training > biggest_score) {
      // std::cout << "Score: " << bird.training << std::endl;
      biggest_score = m_birds[i].training;
    }
  }
  if (biggest_score > m_highest_score)
    m_highest_score = biggest_score;
  if (current_score != biggest_score) {
    current_score = biggest_score;
    std::cout << "Current score: " << current_score << std::endl;
  }
}

void ai::aiLearningStart() {
  std::sort(m_birds.begin(), m_birds.end(), [](const bird &a, const bird &b) {
    return a.training > b.training;
  });
  for (int i = 0; i < 6; ++i)
    std::cout << i << " bird score: " << m_birds[i].training << std::endl;
  m_best_birds.clear();
  m_best_birds.resize(4);
  std::copy(m_birds.begin(), m_birds.begin() + 3, m_best_birds.begin());

  for (int i = 3; i < 300; ++i) {
    int rand_1 = neuron::random_number_generator(0, 3);
    int rand_2 = neuron::random_number_generator(0, 3);
    bird child_bird = crossOver(m_best_birds[rand_1], m_best_birds[rand_2]);
    m_birds[i].m_neuron = child_bird.m_neuron;
  }
}

bird ai::crossOver(const bird &b1, const bird &b2) {
  bird child_bird;

  for (int i = 0; i < 7; ++i) {
    for (int j = 0; j < 3; ++j) {
      double possibility = neuron::random_number_generator(0.0, 1.0);
      if (possibility < 0.47)
        child_bird.m_neuron.m_weigth1[i][j] = b1.m_neuron.m_weigth1[i][j];
      else if (possibility < 0.94)
        child_bird.m_neuron.m_weigth1[i][j] = b2.m_neuron.m_weigth1[i][j];
      else
        child_bird.m_neuron.m_weigth1[i][j] =
            neuron::random_number_generator(-1.0, 1.0);
    }
  }

  for (int i = 0; i < 7; ++i) {
    double possibility = neuron::random_number_generator(0.0, 1.0);
    if (possibility < 0.47)
      child_bird.m_neuron.m_weigth2[0][i] = b1.m_neuron.m_weigth2[0][i];
    else if (possibility < 0.94)
      child_bird.m_neuron.m_weigth2[0][i] = b2.m_neuron.m_weigth2[0][i];
    else
      child_bird.m_neuron.m_weigth2[0][i] =
          neuron::random_number_generator(-1.0, 1.0);
  }

  return child_bird;
}
