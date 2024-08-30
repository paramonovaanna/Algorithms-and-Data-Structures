#include <iostream>
#include <vector>
#include <cstdint>

using number = int64_t;


int main() {
  number n;
  std::cin >> n;
  number num;

  number sum = 0;
  number min_sum = 0;
  number max_sum = 0;
  for (size_t i = 0; i < n; ++i) {
    std::cin >> num;
    if (i == 0) {
      max_sum = num;
    }
    sum += num;
    max_sum = std::max(max_sum, sum - min_sum);
    min_sum = std::min(sum, min_sum);
  }

  std::cout << max_sum;
}