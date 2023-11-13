#include <cfigout/cfigout.hpp>

int main() {
  mtk::cfigout::cfigout<float> fig;

  // #
  {
    std::vector<std::pair<float, float>> ps;
    for (int x = -10; x <= 5; x++) {
      ps.push_back(std::pair<int, int>(x, x * x));
    }
    fig.add_data_points(
      '#',
      ps,
      "test points"
      );
  }
  // *
  {
    std::vector<std::pair<float, float>> ps;
    for (int x = -10; x <= 5; x++) {
      ps.push_back(std::pair<int, int>(x, 90 - 2 * x * x));
    }
    fig.add_data_points(
      '*',
      ps,
      "test points"
      );
  }
  // f
  {
    std::vector<float> x_list, y_list;
    for (int x = -10; x <= 5; x++) {
      x_list.push_back(x);
      y_list.push_back(x * x / 2.);
    }
    fig.add_data_points(
      'f',
      x_list, y_list,
      "test points"
      );
  }
  fig.construct().print();
}
