#include <iostream>
#include <vector>
#include <cstdint>

using number = int64_t;
using numbers = std::vector<number>;

using Node = number;

class SegmentTree {
public:
  SegmentTree(number size, numbers original) {
    n = size;
    tree.resize(4 * n);
    nums = original;
    build(1, 0, n - 1);
  }

  void build(number now, number left, number right) {
    if (left == right) {
      tree[now] = nums[left];
      return;
    }
    number middle = (left + right) / 2;
    build(2 * now, left, middle);
    build(2 * now + 1, middle + 1, right);
    tree[now] = tree[2 * now] + tree[2 * now + 1];
  }

  void update(number now, number left, number right, number index,
              number new_value) {
    if (left == right) {
      tree[now] = new_value;
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

  void get_prefix_len(number s) {
    if (s == 0) {
        std::cout << 0 << "\n";
        return;
    }
    number now = 1;
    if (tree[now] < s) {
        std::cout << "NONE" << "\n";
        return;
    }
    number result = 0;
    number left = 0;
    number right = n -1;
    while (s) {
        if (left == right) {
            break;
        }
        number middle = (left + right) / 2;
        if (tree[now * 2] < s) {
            result += middle + 1;
            left = middle + 1;

            s -= tree[now * 2];
            now = now * 2 + 1;
        } else {
            right = middle;
            now = now * 2;
        }
    }
    std::cout << right + 1 << "\n";
  }

private:
  number n;
  std::vector<Node> tree;
  numbers nums;
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
        number s;
        std::cin >> s;
        seg_tree.get_prefix_len(s);
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