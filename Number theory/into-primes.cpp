#include <iostream>
#include <cstdint>


using number = int64_t;

int main() {
    number n;
    std::cin >> n;

    number p = 2;
    number m = n;
    while (p * p <= m) {
        while (n % p == 0) {
            std::cout << p << " ";
            n /= p;
        }
        ++p;
    }
    if (n != 1) {
        std::cout << n;
    }
}