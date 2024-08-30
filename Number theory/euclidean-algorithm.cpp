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
    number a, b;
    std::cin >> a >> b;
    std::cout << gcd(a, b);
}