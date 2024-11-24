#ifndef __NEURON_HPP_
#define __NEURON_HPP_

#include <array>

using weigth1 = std::array<std::array<double, 3>, 7>;
using weigth2 = std::array<std::array<double, 1>, 7>;

class neuron {
public:
  static double random_number_generator(double lower_limit, double upper_limit);
  neuron(weigth1 w1, weigth2 w2);
  neuron();
  void predict(std::array<float, 3> inputs);
  double sigmoid(double x);
  weigth1 m_weigth1;
  weigth2 m_weigth2;
  bool m_jump_result;
};

template <std::size_t Rows, std::size_t Cols>
void assign_random_values(std::array<std::array<double, Cols>, Rows> &matris) {

  for (auto &rows : matris) {
    for (auto &element : rows) {
      element = neuron::random_number_generator(-1.0, 1.0);
    }
  }
}
#endif
