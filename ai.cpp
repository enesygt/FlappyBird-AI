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
  for (auto it = m_birds.begin(); it != m_birds.end(); ++it) {
    if (game_pipes.collisionCheck((*it).birdSprite)) {
      // Todo: Try to disapper birds instead of erasing
      (*it).is_bird_live = false;
    }
  }
}

void ai::scoreCheck(pipe &game_pipes) {
  size_t biggest_score = 0;
  for (auto &bird : m_birds) {
    if (bird.is_bird_live && game_pipes.scoreCheck(bird.birdSprite)) {
      ++bird.training;
    }
    if (bird.training > biggest_score) {
      // std::cout << "Score: " << bird.training << std::endl;
      biggest_score = bird.training;
    }
  }
  if (biggest_score > m_highest_score)
    m_highest_score = biggest_score;
  std::cout << "Highest score: " << m_highest_score << std::endl;
  std::cout << "Current score: " << biggest_score << std::endl;
  std::cout << "Generation: " << generation_counter << std::endl;
}

void ai::aiLearningStart() {
  std::sort(m_birds.begin(), m_birds.end(), [](const bird &a, const bird &b) {
    return a.training > b.training;
  });

  m_best_birds.resize(20);
  std::copy(m_birds.begin(), m_birds.begin() + 6, m_best_birds.begin());

  for (auto it = m_birds.begin() + 6; it != m_birds.end(); ++it) {
    int rand_1 = neuron::random_number_generator(0, 5);
    int rand_2 = neuron::random_number_generator(0, 5);
    bird child_bird = crossOver(m_best_birds[rand_1], m_best_birds[rand_2]);
    (*it).m_neuron = child_bird.m_neuron;
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
