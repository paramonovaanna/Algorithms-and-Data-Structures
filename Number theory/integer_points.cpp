#include <iostream>
#include <cstdint>

using number = int64_t;

number gcd(number a, number b) {
    while (b != 0) {
        a %= b;
        std::swap(a, b);
    }
    return a;
}

int main() {
    number x1, y1, x2, y2;
    std::cin >> x1 >> y1 >> x2 >> y2;

    std::cout << gcd(std::abs(x2 - x1), std::abs(y2 - y1)) + 1;
}