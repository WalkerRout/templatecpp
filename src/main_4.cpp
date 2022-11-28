#include <iostream>
#include <string.h>

template <class T>
struct Mat {
  // default constructors
  Mat() = default;
  Mat(int _dim): rows(_dim), cols(_dim), data(new T[_dim*_dim]) {}
  Mat(int _rows, int _cols): rows(_rows), cols(_cols), data(new T[_rows*_cols]) {}
  
  // ***********************************************************
  //        REMOVE THIS FUNCTION FOR ONLY MOVE SEMANTICS
  // ***********************************************************
  // copy constructor
  Mat(const Mat &other): rows(other.rows), cols(other.cols) {
    std::cout << "Copy constructor...\n";
    auto size = other.rows * other.cols;
    data = new T[size];
    memcpy(data, other.data, size);
  }

  // move constructor
  Mat(Mat &&other): rows(other.rows), cols(other.cols) {
    std::cout << "Move constructor...\n";
    data = std::move(other.data);

    other.rows = 0;
    other.cols = 0;
    other.data = nullptr;
  }

  // ***********************************************************
  //        REMOVE THIS FUNCTION FOR ONLY MOVE SEMANTICS
  // ***********************************************************
  // copy operator
  auto operator=(const Mat &other) -> Mat& {
    this->~Mat();
    std::cout << "Copy operator...\n";

    rows = other.rows;
    cols = other.cols;

    auto size = other.rows * other.cols;
    data = new T[size];
    memcpy(data, other.data, size);

    return *this;
  }

  // move operator
  auto operator=(Mat &&other) -> Mat& {
    this->~Mat();
    std::cout << "Move operator...\n";

    rows = other.rows;
    cols = other.cols;

    data = std::move(other.data);

    other.rows = 0;
    other.cols = 0;
    other.data = nullptr;

    return *this;
  }

  ~Mat() {
    rows = 0;
    cols = 0;
    delete[] data;
  }

  int rows, cols;
  T *data;
};

// proof of concept for the generic capabilities
struct Point {
  float x{0}, y{0};

  Point() = default;
  Point(float _x, float _y): x(_x), y(_y) {}
  Point(float _x): x(_x), y(_x) {}
};

auto consume(auto &&t) {
  auto s = std::move(t);
  std::cout << "Took ownership of of t: " << s.rows << " * " << s.cols << "\n";
}

auto main(void) -> int {
  auto m1 = Mat<Point>(2, 3); // use standard constructor
  auto m2 = m1; // use copy constructor 
  auto m3 = std::move(m1); // use move constructor

  m1 = std::move(m2); // use move assignment operator

  std::cout << m1.rows << " vs " << m3.rows << "\n";

  consume(std::move(m1)); // consume with move constructor (inside the function, 's' moves it)

  std::cout << "m1 now looks like: " << m1.rows << " * " << m1.cols << "\n";

  return 0;
}
