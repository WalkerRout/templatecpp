#include <iostream>
#include <algorithm>
#include <vector>
#include <ranges>

#define to_vec(expr) (std::vector<typename std::decay<decltype((expr)[0])>::type>{(expr).begin(), (expr).end()})

auto vector_data() { return std::vector<int>{1, 2, 3, 4, 5}; }

auto ranges_pipes() -> std::vector<int> {
  auto r = vector_data()
  | std::ranges::views::drop(1)
  | std::ranges::views::take(2)
  | std::views::transform([](const auto i) {
    return i + 1;
  });
  
  return to_vec(r);
}

auto main(void) -> int {
  auto vd = vector_data();
  for(auto &e : vd){
    std::cout << e << " ";
  }
  std::cout << "\n";

  auto rp = ranges_pipes();
  for(auto &e : rp){
    std::cout << e << " ";
  }
  std::cout << "\n";

  return 0;
}
