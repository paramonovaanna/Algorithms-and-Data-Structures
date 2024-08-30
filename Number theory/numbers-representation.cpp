#include <iostream>

using num = int;


int main() {
    num n;
    std::cin >> n;

    num res = 1;
    for (size_t i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            res = i;
            break;
        }
    }
    if (res == 1) {
        std::cout << 1 << " " << n - 1;
    } else {
        std::cout << n / res << " " << n - n / res;
    }
}