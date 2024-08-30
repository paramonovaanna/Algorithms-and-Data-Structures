#include <iostream>
#include <vector>
#include <cstdint>

using number = int64_t;

const number N1 = 1000000007;
const number N2 = 11173;

int main() {
    number n;
    std::cin >> n;
    std::vector<number> nums(n);
    std::vector<number> prefix_sums(n + 1);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> nums[i];
        prefix_sums[i + 1] = nums[i];
        prefix_sums[i + 1] += prefix_sums[i];
    }
    number q, x;
    std::cin >> q >> x;

    number x1 = x;
    number x2 = x;
    number left, right;

    number result = 0;
    for (size_t i = 0; i < q; ++i) {
        if (i > 0) {
            x1 = (N2 * x2 + 1) % N1;
        }
        x2 = (N2 * x1 + 1) % N1;

        left = std::min(x1 % n, x2 % n);
        right = std::max(x1 % n, x2 % n);

        result += (prefix_sums[right + 1] - prefix_sums[left]) % N1;
        result %= N1;
    }

    std::cout << result;
}