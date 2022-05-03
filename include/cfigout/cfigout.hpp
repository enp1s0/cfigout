#include <iostream>
#include <memory>
#include <vector>
#include <climits>
#include <cfloat>

namespace mtk {
namespace cfigout {
namespace detail {
template <class T>
inline T max_value();
template <> inline float  max_value<float >() {return FLT_MAX;}
template <> inline double max_value<double>() {return DBL_MAX;}
template <> inline int    max_value<int   >() {return INT_MAX;}
template <> inline long   max_value<long  >() {return LONG_MAX;}
template <class T>
inline T min_value();
template <> inline float  min_value<float >() {return FLT_MIN;}
template <> inline double min_value<double>() {return DBL_MIN;}
template <> inline int    min_value<int   >() {return INT_MIN;}
template <> inline long   min_value<long  >() {return LONG_MIN;}
} // namespace detail

template <class T = int>
class cfigout {
	std::unique_ptr<char[]> fig;

	const unsigned width, height;
	T xmin, xmax;
	T ymin, ymax;

	T xmin_set = 0, xmax_set = 0;
	T ymin_set = 0, ymax_set = 0;

	inline void set_char(const int x, const int y, const char c) {
		if (x >= width || y >= height) return;

		fig.get()[x + y * (width + 1)] = c;
	}

	inline void set_char_force(const int x, const int y, const char c) {
		fig.get()[x + y * (width + 1)] = c;
	}

	inline char get_char(const int x, const int y) const {
		if (x >= width || y >= height) return ' ';

		return fig.get()[x + y * (width + 1)];
	}

	struct data_points {
		char marker;
		std::vector<std::pair<T, T>> points;
		std::string label_name;
	};
	std::vector<data_points> data_points_list;
public:
	cfigout() : cfigout(80, 30) {}
	cfigout(const unsigned w, const unsigned h)
		: width(w), height(h), xmax(detail::min_value<T>()), xmin(detail::max_value<T>()),
		ymax(detail::min_value<T>()), ymin(detail::max_value<T>()) {
	};

	inline cfigout& construct() {
		// Memory allocation
		fig = std::unique_ptr<char[]>(new char[(width + 1) * height]);
		// Init
		for (unsigned h = 0; h < height; h++) {
			for (unsigned w = 0; w < width + 1; w++) {
				if (w == width) {
					set_char_force(w, h, '\0');
				} else {
					set_char(w, h, ' ');
				}
			}
		}

		for (const auto& dp : data_points_list) {
			for (const auto p : dp.points) {
				const auto x = static_cast<double>(p.first  - xmin) / (xmax - xmin) * (width  - 1);
				const auto y = static_cast<double>(p.second - ymin) / (ymax - ymin) * (height - 1);
				set_char(x, y, dp.marker);
			}
		}
		return *this;
	}

	inline cfigout& print() {
		std::printf("+");
		for (unsigned i = 0; i < width; i++) {
			std::printf("-");
		}
		std::printf("+\n");
		for (int h = height - 1; h >= 0; h--) {
			std::printf("|%s|\n", fig.get() + h * (width + 1));
		}
		std::printf("+");
		for (unsigned i = 0; i < width; i++) {
			std::printf("-");
		}
		std::printf("+\n");

		return *this;
	}

	inline cfigout& set_xmin(const T v) {xmin = v; xmin_set = 1; return *this;}
	inline cfigout& set_xmax(const T v) {xmax = v; xmax_set = 1; return *this;}
	inline cfigout& set_ymin(const T v) {ymin = v; ymin_set = 1; return *this;}
	inline cfigout& set_ymax(const T v) {ymax = v; ymax_set = 1; return *this;}

	inline cfigout& add_data_points(
			const char marker,
			const std::vector<std::pair<T, T>> points,
			const std::string label_name
			) {
		const data_points dp = {marker, points, label_name};
		data_points_list.push_back(dp);

		T xmin_local = detail::max_value<T>(), xmax_local = detail::min_value<T>();
		T ymin_local = detail::max_value<T>(), ymax_local = detail::min_value<T>();
		for (const auto p : points) {
			xmin_local = std::min(xmin_local, p.first );
			xmax_local = std::max(xmax_local, p.first );
			ymin_local = std::min(ymin_local, p.second);
			ymax_local = std::max(ymax_local, p.second);
		}
		if (!xmin_set) xmin = std::min(xmin_local, xmin);
		if (!xmax_set) xmax = std::max(xmax_local, xmax);
		if (!ymin_set) ymin = std::min(ymin_local, ymin);
		if (!ymax_set) ymax = std::max(ymax_local, ymax);

		return *this;
	}
};
} // namespace cfigout
} // namespace mtk
