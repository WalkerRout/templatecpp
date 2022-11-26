#include <iostream>
#include <concepts>

struct Square {
  virtual Square *square() = 0;
};

template<class T>
struct Sum : Square {
  T a;

  Sum(T start): a(start) {}

  Sum *square() override {
    Sum* res = new Sum(0);
    *res = *this * *this;
    return res;
  }

  Sum operator*(Sum &other) { 
    Sum n(0);
    n.a = this->a * other.a;
    return n;
  }
};

template<class T, class Trait>
concept Restrict = std::is_base_of<Trait, T>::value;

template<Restrict<Square> T>
void test_square(T t) {
  T *val = t.square();
  std::cout << val->a << "\n";
  delete val;
}

int main(void) {
  Sum<int> a(2);
  test_square(a);
  return 0;
}
