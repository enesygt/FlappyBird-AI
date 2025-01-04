#include "pipe.hpp"
#include <cmath>
#include <iostream>
pipe::pipe() {

  if (!pipeTexture.loadFromFile("pipe.png", sf::IntRect(0, 0, 50, 800))) {
    std::cout << "Here is a problem to load a file!\n";
  }

  if (!pipeOppositeTexture.loadFromFile("pipe.png",
                                        sf::IntRect(0, 0, 50, 800))) {
    std::cout << "Here is a problem to load a file!\n";
  }
}
void pipe::update() {
  int creation_limit = 300 / m_speed;
  if (pipeVec.size() == 0 || creation_count > creation_limit) {
    std::vector<sf::Sprite> vecBasit{};
    for (int j = 0; j < 2; ++j) {
      vecBasit.push_back(sf::Sprite{});
      if (!(j % 2)) {
        vecBasit[j].setOrigin(25, 700);
        vecBasit[j].setTexture(pipeTexture);
        vecBasit[j].setPosition(700, rand() % 150 + 100);
      } else {
        vecBasit[j].setOrigin(25, 400);
        vecBasit[j].setRotation(180);
        vecBasit[j].setTexture(pipeOppositeTexture);
        vecBasit[j].setPosition(700, vecBasit[0].getPosition().y + 650);
      }
    }
    pipeVec.push_back(vecBasit);
    creation_count = 0;
  }
  ++creation_count;

  pipeMove();
}
// TODO: Burada bir sorun var bak!!``
void pipe::pipeMove() {
  for (auto it = pipeVec.begin(); it != pipeVec.end(); ++it) {
    for (sf::Sprite &sprite : *it) {
      if (sprite.getPosition().x < -10) {
        it = pipeVec.erase(it);
        break;
      } else {
        sprite.move(-1 * m_speed, 0);
      }
    }
    if (it == pipeVec.end())
      break;
  }
}

void pipe::draw(sf::RenderWindow &window) {
  for (auto pipes : pipeVec) {
    for (auto sprite : pipes) {
      window.draw(sprite);
    }
  }
}

bool pipe::collisionCheck(const sf::Sprite &object) {
  for (auto spriteVec : pipeVec) {
    for (auto sprite : spriteVec) {
      if (sprite.getGlobalBounds().intersects(object.getGlobalBounds()))

        return true;
    }
  }
  return false;
}

void pipe::pipeReset() { pipeVec.clear(); }

bool pipe::scoreCheck(sf::Sprite &object, int &last_measure) {
  for (auto spriteVec : pipeVec) {
    for (auto sprite : spriteVec) {
      int x = object.getPosition().x - sprite.getPosition().x;
      if (abs(x) < 35) {
        if (x - last_measure > abs(x)) {
          last_measure = x;
          return true;
          std::cout << std::endl;
        }
        last_measure = x;
      }
    }
  }
  return false;
}

std::array<float, 2>
pipe::calculateFirstPipeDistance(const sf::Sprite &object) const {
  float distance{};
  float heigth{};

  for (auto spriteVec : pipeVec) {

    if ((object.getPosition().x - spriteVec[1].getPosition().x) > 0)
      continue;
    float new_distance =
        calculateDistance(object.getPosition(), spriteVec[1].getPosition());
    if (distance == 0) {
      distance = new_distance;
      heigth = spriteVec[1].getPosition().y;
    } else if (new_distance < distance) {
      distance = new_distance;
      heigth = spriteVec[1].getPosition().y;
    }
  }
  std::array<float, 2> result{distance, heigth};
  return result;
}
float pipe::calculateDistance(const sf::Vector2f &point1,
                              const sf::Vector2f &point2) const {
  float dx = (point2.x - 25) - point1.x;
  float dy = (point2.y - 400) - point1.y;

  return std::sqrt(dx * dx + dy * dy);
}
