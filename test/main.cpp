#include <cfigout/cfigout.hpp>

int main() {
	mtk::cfigout::cfigout<> fig;

	// #
	{
		std::vector<std::pair<int, int>> ps;
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
		std::vector<std::pair<int, int>> ps;
		for (int x = -10; x <= 5; x++) {
			ps.push_back(std::pair<int, int>(x, 90 - 2 * x * x));
		}
		fig.add_data_points(
			'*',
			ps,
			"test points"
			);
	}
	fig.construct().print();
}
