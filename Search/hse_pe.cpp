#include <iostream>
#include <vector>

using Roads = std::vector<std::vector<int>>;

Roads distribute(int n, int m) {
  Roads roads;

  if (m == 0) {
    return roads;
  }

  int length = n * (n + 1) / (2 * m);

  if (length == n) {
    roads.push_back({n});
    for (int i = 1; i <= n / 2; ++i) {
      roads.push_back({n - i, i});
    }
    return roads;
  }

  if (length >= 2 * n) {
    roads = distribute(n - 2 * m, m);
    for (int i = n - m + 1; i <= n; ++i) {
      roads[n - i].push_back(i);
      roads[n - i].push_back(2 * (n - m) + 1 - i);
    }
    return roads;
  }

  if (length % 2 != 0) {
    roads = distribute(length - n - 1, m - n + (length - 1) / 2);
    for (int i = n; i >= (length + 1) / 2; --i) {
      roads.push_back({i, length - i});
    }
    return roads;
  }

  Roads splitted_roads = distribute(length - n - 1, 2 * m - 2 * n + length - 1);
  splitted_roads.push_back({length / 2});
  for (int i = 0; i < m + length / 2 - n; ++i) {
    std::vector<int> road = splitted_roads[2 * i];
    for (int j = 0; j < splitted_roads[2 * i + 1].size(); ++j) {
      road.push_back(splitted_roads[2*i + 1][j]);
    }
    roads.push_back(road);
  }

  for (int i = n; i >= 1 + length / 2; --i) {
    roads.push_back({i, length - i});
  }
  return roads;
}


int main() {
  int m, n;
  std::cin >> m >> n;

  int length = n * (n + 1) / (2 * m);

  if (n * (n + 1) % (2 * m) != 0 || length < n) {
    std::cout << "NO";
    return 0;
  }

  Roads roads = distribute(n, m);

  std::cout << "YES" << '\n';
  for (std::vector<int> road : roads) {
    std::cout << road.size() << " ";
    for (int a : road) {
      std::cout << a << " ";
    }
    std::cout << '\n';
  }

}