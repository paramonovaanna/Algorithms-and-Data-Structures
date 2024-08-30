#include <iostream>
#include <cstdint>
#include <vector>

using number = int64_t;

number binpow(number x, number n) {
  if (n == 0)
    return 1;
  if (n % 2 == 1)
    return binpow(x, n - 1) * x;
  number b = binpow(x, n / 2);
  return b * b;
}

number factor(number n, std::vector<bool> &is_prime) {
    number result = 1;
    for (size_t i = 2; i * i <= n; ++i) {
        if (is_prime[i] && n % i == 0) {
            result *= i;
        }
    }
    if (result == 1) {
        result *= n;
    }
    return result;
}

void eratosthenes_seive(number n, std::vector<bool> &is_prime) {
    is_prime[0] = false;
    is_prime[1] = false;
    for (number i = 2; i * i < n + 1; ++i) {
        if (is_prime[i]) {
            for (number j = i * i; j < n + 1; j += i) {
                is_prime[j] = false;
            } 
        }
    }
}


int main() {
    number n;
    std::cin >> n;

    std::vector<bool> sieve(n + 1, true);
    eratosthenes_seive(n, sieve);

    number m = factor(n, sieve);
    number delta = 1;
    while (binpow(m, m) % n != 0) {
        ++delta;
        m *= delta;
    }
    std::cout << m;
}