#include "neuron.hpp"
#include <cmath>
#include <iostream>
#include <random>

neuron::neuron(weigth1 weigth1, weigth2 weigth2)
    : m_weigth1{weigth1}, m_weigth2{weigth2} {}

neuron::neuron() {
  assign_random_values(m_weigth1);
  assign_random_values(m_weigth2);
}

// Returns a random number between -1.0 and 1.0
double neuron::random_number_generator(double lower_limit, double upper_limit) {
  // Rastgele sayı üretici
  std::random_device rd;  // Gerçek rastgelelik için veya bir tohum kaynağı
  std::mt19937 gen(rd()); // Mersenne Twister motoru

  // -1 ile 1 arasında rastgele sayı dağılımı
  std::uniform_real_distribution<double> dist(lower_limit, upper_limit);

  // Rastgele bir sayı üret ve yazdır
  double random_number = dist(gen);

  return random_number;
}

void neuron::predict(std::array<float, 3> inputs) {
  std::array<double, 7> first_layer{};
  double jump_result{};
  int k = 0;
  // Calculate first layer
  for (auto &rows : m_weigth1) {
    double calc{};
    for (int i = 0; i < 3; ++i) {
      calc += rows[i] * inputs[i];
    }
    first_layer[k] = sigmoid(calc);
    ++k;
  }

  for (int i = 0; i < 7; ++i) {
    jump_result += first_layer[i] * m_weigth2[0][i];
  }

  jump_result = sigmoid(jump_result);

  if (jump_result >= 0.5)
    m_jump_result = true;
  else
    m_jump_result = false;
}
// Sigmoid fonksiyonu
double neuron::sigmoid(double x) {
  return 1.0 /
         (1.0 +
          std::exp(
              -x)); // Sigmoid fonksiyonunun matematiksel ifadeyi uyguluyoruz
}
