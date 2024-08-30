#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <vector>

using number = int;
using numbers = std::vector<number>;

const int INF = 1e9;

using Node = std::multiset<number>;

class SegmentTree {
public:
  SegmentTree(number size, numbers array) {
    n = size;
    tree.resize(4 * n);
    data = array;
    build(1, 0, n - 1);
  }

  void build(number now, number left, number right) {
    if (left == right) {
      int a = 1;
      tree[now] = std::multiset{data[left]};
      return;
    }
    number middle = (left + right) / 2;
    build(2 * now, left, middle);
    build(2 * now + 1, middle + 1, right);
    tree[now] = std::multiset<number>();
    for (number elem : tree[now * 2]) {
      tree[now].insert(elem);
    }
    for (number elem : tree[now * 2 + 1]) {
      tree[now].insert(elem);
    }
  }

  void update(number now, number left, number right, number index,
              number new_value) {
    tree[now].erase(tree[now].find(data[index]));
    tree[now].insert(new_value);
    if (left == right) {
      data[index] = new_value;
      return;
    }
    number middle = (left + right) / 2;
    if (index <= middle) {
      update(now * 2, left, middle, index, new_value);
    } else {
      update(now * 2 + 1, middle + 1, right, index, new_value);
    }
  }

  number get_greater_elem(number now, number left, number right, number x,
                          number left_border, number right_border) {
    if (left_border > right_border) {
      return INF;
    }
    if (left_border == left && right == right_border) {
      auto index = tree[now].upper_bound(x);
      if (index == tree[now].end()) {
        return INF;
      }
      return *index;
    }
    number middle = (left + right) / 2;
    return std::min(get_greater_elem(now * 2, left, middle, x, left_border,
                                     std::min(right_border, middle)),
                    get_greater_elem(now * 2 + 1, middle + 1, right, x,
                                     std::max(middle + 1, left_border),
                                     right_border));
  }

  void greater_elem(number x, number left_border, number right_border) {
    number result = get_greater_elem(1, 0, n - 1, x, left_border, right_border);
    if (result == INF) {
      std::cout << "NONE"
                << "\n";
      return;
    }
    std::cout << result << "\n";
  }

private:
  number n;
  std::vector<Node> tree;
  numbers data;
};

int main() {
  number n;
  std::cin >> n;
  numbers nums(n);
  for (size_t i = 0; i < n; ++i) {
    std::cin >> nums[i];
  }
  SegmentTree seg_tree(n, nums);

  number q;
  std::cin >> q;
  for (size_t j = 0; j < q; ++j) {
    number t;
    std::cin >> t;
    if (t == 1) {
      number left, right, x;
      std::cin >> left >> right >> x;
      seg_tree.greater_elem(x, left, right);
    } else if (t == 2) {
      number index, new_value;
      std::cin >> index >> new_value;
      seg_tree.update(1, 0, n - 1, index, new_value);
    }
  }
}