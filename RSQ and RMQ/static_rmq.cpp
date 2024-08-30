#include <cmath>
#include <iostream>
#include <vector>
#include <cstdint>

using number = uint64_t;
using table = std::vector<std::vector<number>>;

class RMQ {
public:
  RMQ(std::vector<number> array, number size) {
    n = size;
    data = array;
    sparse_table.resize(std::floor(std::log2(n)) + 1, std::vector<number>(n));
    build();
    calculate_powers();
  }

  void build() {
    for (size_t col = 0; col < n; ++col) {
      sparse_table[0][col] = data[col];
    }

    for (size_t row = 1; (1 << row) <= n; ++row) {
      for (size_t col = 0; (col + (1 << row) - 1) < n; ++col) {
        sparse_table[row][col] =
            std::min(sparse_table[row - 1][col],
                     sparse_table[row - 1][col + (1 << (row - 1))]);
      }
    }
  }

  void calculate_powers() {
    length_power.resize(n + 1);
    number power = 0;
    for (number length = 1; length <= n; ++length) {
      while ((1 << power) <= length) {
        ++power;
      }
      length_power[length] = power - 1;
    }
  }

  number get_min(number left, number right) {
    number length = right - left + 1;
    number index = length_power[length];
    return std::min(sparse_table[index][left], sparse_table[index][right - (1 << index) + 1]);
  }

private:
  table sparse_table;
  number n;
  std::vector<number> data;
  std::vector<number> length_power;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  number n;
  std::cin >> n;
  std::vector<number> nums(n);

  for (size_t i = 0; i < n; ++i) {
    std::cin >> nums[i];
  }
  RMQ rmq(nums, n);
  
  number q;
  std::cin >> q;
  number result = 0;
  number left, right;
  for (size_t i = 0; i < q; ++i) {
    std::cin >> left >> right;
    result += rmq.get_min(left, right);
  }
  std::cout << result;
}