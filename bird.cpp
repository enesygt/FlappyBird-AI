#include "bird.hpp"
#include <iostream>

bird::bird() {
  if (!birdTexture.loadFromFile("bird.png", sf::IntRect(0, 0, 43, 32))) {
    std::cout << "Here is a problem to load a file!\n";
  }

  if (!birdTersTexture.loadFromFile("bird_ters.png",
                                    sf::IntRect(0, 0, 43, 32))) {

    std::cout << "Here is a problem to load a file!\n";
  }

  birdSprite.setPosition(200, 250);
}

void bird::event() {
  // move = true;
  counter = 0;
  speed = -6;
}

void bird::movement(bool jump) {
  if (jump)
    speed = -6;
}
void bird::update() {
  if (wingCounter < 15) {
    birdSprite.setTexture(birdTersTexture);
    wingCounter++;
  } else if (wingCounter >= 15 && wingCounter < 30) {

    birdSprite.setTexture(birdTexture);
    wingCounter++;
  } else
    wingCounter = 0;

  // TODO: Reduntant move here.
  if (!move) {
    if (birdSprite.getPosition().y < 722 && birdSprite.getPosition().y > 5) {
      speed += gravity;
      if (speed > 8)
        speed = 8;
      birdSprite.move(0, speed);
    }
  } /*else if (counter < 9) {
    if (birdSprite.getPosition().y > 5)
      birdSprite.move(0, -6);
    counter++;
  } // else if (counter < 20) {
    // counter++;
  //}
  else {
    counter = 0;
    move = false;
  }*/
}

void bird::update(float yPos) {
  if (wingCounter < 15) {
    birdSprite.setTexture(birdTersTexture);
    wingCounter++;
  } else if (wingCounter >= 15 && wingCounter < 30) {

    birdSprite.setTexture(birdTexture);
    wingCounter++;
  } else
    wingCounter = 0;

  if (!move) {
    if (birdSprite.getPosition().y < 722 && birdSprite.getPosition().y > 5) {
      speed += gravity;
      if (speed > 8)
        speed = 8;
      birdSprite.move(5, 0);
      birdSprite.setPosition(100, yPos);
    }
  } /*else if (counter < 9) {
    if (birdSprite.getPosition().y > 5)
      birdSprite.move(0, -6);
    counter++;
  } // else if (counter < 20) {
    // counter++;
  //}
  else {
    counter = 0;
    move = false;
  }*/
}

void bird::draw(sf::RenderWindow &window) { window.draw(birdSprite); }

void bird::birdReset() { birdSprite.setPosition(200, 250); }
