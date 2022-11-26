#include <iostream>
#include <vector>

// default values
#define X_DEFAULT 0
#define Y_DEFAULT 0
struct Point {
  double x{X_DEFAULT}, y{Y_DEFAULT};

  // default constructor (required for the 'sum_and_double' function)
  Point(): x(X_DEFAULT), y(Y_DEFAULT) {} 
  Point(double _x, double _y): x(_x), y(_y) {}

  auto operator+(const Point &rhs) const -> Point {
    return Point(x + rhs.x, y + rhs.y);
  }

  // not a member function, must declare prototype in scope and declaration outside -> friend
  friend auto operator<<(std::ostream &os, const Point &point) -> std::ostream&;
};

auto operator<<(std::ostream &os, const Point &point) -> std::ostream& {
  return (os << point.x << ", " << point.y);
}

template <class T>
using Scalar = typename std::decay<decltype(T()[0])>::type;

template <class T>
auto sum_and_double(const T &t) -> Scalar<T> {
  // -> requires that a default constructor exists for the type Scalar<T>
  Scalar<T> s;
  // use constexpr to evaluate this branch at compile time; otherwise will get a type
  // error since Scalar<T> might not be an int, and therefore cannot be set to 0
  if constexpr(std::is_integral<Scalar<T>>::value) s = 0;

  // could change this loop to check for a .size() method on the type, iterating
  // the amount of times corresponding the the result (ie.. Point2D could have a .size() of 2)
  for(auto &ele : t) {
    s = s + ele + ele;
  }
  
  return s;
}

auto main(void) -> int {
  std::vector<int> ds{1, 2, 3, 4, 5};
  std::vector<Point> ps{Point(1, 2), Point(3, 4), Point(5, 4)};
  
  std::cout << sum_and_double(ds) << "\n";
  std::cout << sum_and_double(ps) << "\n";

  return 0;
}
