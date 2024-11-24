#include "game.hpp"
#include <iostream>

game::game() {
  window.setVerticalSyncEnabled(true);
  window.setFramerateLimit(60);

  if (!texture.loadFromFile("sky.png", sf::IntRect(0, 0, 500, 750))) {
    std::cout << "Here is a problem to load a file!\n";
    // error...
  }

  if (!replayTexture.loadFromFile("replay.png", sf::IntRect(0, 0, 50, 50))) {
    std::cout << "Here is a problem to load a file!\n";
    // error...
  }

  if (!font.loadFromFile("Arial.ttf")) {

    std::cout << "Here is a problem to load a file!\n";
  }
  sprite.setTexture(texture);
  text.setFont(font);
  text.setCharacterSize(24);
  text.setFillColor(sf::Color::Black);
  text.setStyle(sf::Text::Bold);
  text.setPosition(400, 0);
  text.setString(score);
  replaySprite.setTexture(replayTexture);
  replaySprite.setPosition(250, 375);
}
void game::stateMachine() {
  switch (state) {
  case GAME_STARTED:
    gameContinue();
    break;
  case GAME_RESET:
    gameReset();
    break;
  case GAME_OVER:
    gameStopped();
    break;
  default:
    break;
  }
}
void game::gameStart() {
  state = GAME_STARTED;
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      /*else if (event.type == sf::Event::KeyPressed) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
          //m_bird.event();
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
          if (state == GAME_OVER) {
            state = GAME_RESET;
          }
        }
      }*/
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      sf::Vector2f mousePos =
          window.mapPixelToCoords(sf::Mouse::getPosition(window));
      sf::FloatRect spritePositon = replaySprite.getGlobalBounds();

      if (spritePositon.contains(mousePos)) {

        state = GAME_RESET;
      }
    }

    stateMachine();
    sf::sleep(sf::microseconds(9));
  }
}

void game::gameReset() {
  state = GAME_STARTED;
  m_ai.startAi();

  m_pipe.pipeReset();
  // m_bird.birdReset();
  score_num = 0;
}
void game::gameEnd() {}

void game::gameContinue() {

  /* if (m_pipe.scoreCheck(m_bird.birdSprite)) {
     ++score_num;
   }
 */
  // if (!m_pipe.collisionCheck(m_bird.birdSprite)) {
  m_pipe.update();
  m_ai.calculatePipe(m_pipe);
  // m_bird.update();
  m_ai.display_update();
  m_ai.scoreCheck(m_pipe);
  m_ai.pipeCollisionCheck(m_pipe);
  if (!m_ai.bird_left) {
    state = GAME_OVER;
  }

  window.clear();
  window.draw(sprite);
  // window.draw(birdSprite);
  // m_bird.draw(window);

  m_pipe.draw(window);
  m_ai.ai_display(window);
  score = std::to_string(score_num);
  // std::cout << "Sxcore: " << score << std::endl;
  text.setString(score);
  window.draw(text);
  window.display();
  /*} else {
    state = GAME_OVER;
  }*/
  /*else {
    m_pipe.pipeReset();
  }*/
}

void game::gameStopped() {
  window.clear();
  window.draw(sprite);
  window.draw(replaySprite);

  ss << score_num;
  ss >> score;

  text.setString(score);
  window.draw(text);

  window.display();

  state = GAME_RESET;
}
