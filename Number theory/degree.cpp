#include <cmath>
#include <iostream>
#include <cstdint>
#include <vector>

using number = int64_t;

number binpow(number x, number n, number p) {
  if (n == 0)
    return 1;
  if (n % 2 == 1)
    return (binpow(x, n - 1, p) * x) % p;
  number b = (binpow(x, n / 2, p)) % p;
  return (b * b) % p;
}

number factor(number n) {
    number result = 1;
    number p = 2;  
    while (p <= n) {
        if (n % p == 0) {
            result *= p;
        }
        while (n % p == 0) {
            n /= p;
        }
        ++p;
    }
    return result;
}


int main() {
    number n;
    std::cin >> n;

    number m = factor(n);
    number delta = 1;
    while (binpow(m * delta, m * delta, n) != 0) {
        ++delta;
    }
    std::cout << m * delta;
}