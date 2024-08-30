#include <iostream>

void generate(int open1, int open2, int closed1, int closed2, std::string stack,
              std::string result, int n) {
  if (result.size() == n) {
    std::cout << result << "\n";
    return;
  }

  if (open1 + open2 < n / 2) {
    generate(open1 + 1, open2, closed1, closed2, stack + "(", result + "(", n);
    generate(open1, open2 + 1, closed1, closed2, stack + "[", result + "[", n);
  }

  if (stack.size() > 0) {
    auto last_symbol = stack.substr(stack.size() - 1, 1);
    if (open1 > closed1 && last_symbol != "[") {
      generate(open1, open2, closed1 + 1, closed2,
               stack.substr(0, stack.size() - 1), result + ")", n);
    }
    if (open2 > closed2 && last_symbol != ")") {
      generate(open1, open2, closed1, closed2 + 1,
               stack.substr(0, stack.size() - 1), result + "]", n);
    }
  }
}

int main() {
  int n;
  std::cin >> n;
  if (n % 2 != 0 || n == 0) {
    std::cout << "";
    return 0;
  }
  generate(0, 0, 0, 0, "", "", n);
}