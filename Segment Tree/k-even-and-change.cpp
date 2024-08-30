#include <iostream>
#include <vector>

using number = int;
using numbers = std::vector<number>;

using Node = number;

class SegmentTree {
public:
  SegmentTree(number n, numbers array) {
    n = n;
    tree.resize(4 * n);
    data = array;
    build(1, 0, n - 1);
  }

  void build(number now, number left, number right) {
    if (left == right) {
      if (data[left] % 2 == 0) {
        tree[now] = 1;
      } else {
        tree[now] = 0;
      }
      return;
    }
    number middle = (left + right) / 2;
    build(2 * now, left, middle);
    build(2 * now + 1, middle + 1, right);
    tree[now] = tree[now * 2] + tree[now * 2 + 1];
  }

  void update(number now, number left, number right, number index,
              number new_value) {
    if (left == right) {
      if (new_value % 2 == 0) {
        tree[now] = 1;
      } else {
        tree[now] = 0;
      }
      return;
    }
    number middle = (left + right) / 2;
    if (index <= middle) {
      update(now * 2, left, middle, index, new_value);
    } else {
      update(now * 2 + 1, middle + 1, right, index, new_value);
    }
    tree[now] = tree[now * 2] + tree[now * 2 + 1];
  }

  number get_even_amount(number now, number left, number right,
                         number left_border, number right_border) {
    if (left_border > right_border) {
      return 0;
    }
    if (left == left_border && right == right_border) {
      return tree[now];
    }
    number middle = (left + right) / 2;
    return get_even_amount(2 * now, left, middle, left_border,
                           std::min(right_border, middle)) +
           get_even_amount(2 * now + 1, middle + 1, right,
                           std::max(left_border, middle + 1), right_border);
  }

private:
  number n = 0;
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
  std::vector<number> result;
  for (size_t j = 0; j < q; ++j) {
    number t;
    std::cin >> t;
    if (t == 1) {
      number left, right;
      std::cin >> left >> right;
      result.push_back(seg_tree.get_even_amount(1, 0, n - 1, left, right));
    } else if (t == 2) {
      number index, new_value;
      std::cin >> index >> new_value;
      seg_tree.update(1, 0, n - 1, index, new_value);
    }
  }

  for (size_t i = 0; i < result.size(); ++i) {
    std::cout << result[i] << "\n";
  }
}