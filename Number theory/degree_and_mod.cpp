#pragma GCC optimize("O3")

#include <iostream>
#include <algorithm>
#include <random>
#include <unordered_map>
#include <vector>

const int N = 100100 * 2;
std::mt19937 gen(12345);

void process(int dx, std::unordered_map<int, int> &used, int n, const std::vector<int> &numbers) {
  if (used[dx]) {
    return;
  }
  used[dx] = 1;

  std::unordered_map<int, int> dp;
  int mx = 0;
  size_t id = 0;
  for (size_t i = 0; i < 2 * n; ++i) {
    dp[numbers[i]] = dp[numbers[i] - dx] + 1;
    if (mx < dp[numbers[i]]) {
      mx = dp[numbers[i]];
      id = i;
    }
  }
  if (mx >= n) {
    std::cout << numbers[id] - dx * (n - 1) << ' ' << dx;
    exit(0);
  }
}

void sample(int n, const std::vector<int> numbers) {
  std::unordered_map<int, int> divs;
  for (size_t i = 2; i < 2 * n; ++i) {
    ++divs[numbers[i] - numbers[i - 1]];
    ++divs[numbers[i] - numbers[i - 2]];
  }
  std::vector<std::pair<int, int>> dvs;
  for (auto elem : divs) {
    dvs.push_back({-elem.second, elem.first});
  }
  std::sort(dvs.begin(), dvs.end());

  std::unordered_map<int, int> used;
  for (auto elem : dvs) {
    process(elem.second, used, n, numbers);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);

  int n;
  std::cin >> n;

  std::vector<int> numbers(N);
  for (size_t i = 0; i < 2 * n; ++i) {
    std::cin >> numbers[i];
  }

  std::sort(numbers.begin(), numbers.end());

  if (n == 1) {
    std::cout << numbers[0] << ' ' << 0 << '\n';
    return 0;
  }

  sample(n, numbers);
}
