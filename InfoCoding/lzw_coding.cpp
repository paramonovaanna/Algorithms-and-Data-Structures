#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

int main() {
  std::string in;
  std::getline(std::cin, in);
  std::unordered_map<std::string, int> dict;

  for (int i = 0; i < 128; ++i) {
    std::string symbol;
    symbol += char(i);
    dict[symbol] = i;
  }

  std::string substr;
  substr += in[0];

  std::vector<int> answer;
  int current_index = 1;
  int last_code = 127;
  while (true) {
    if (current_index == in.size()) {
      answer.push_back(dict[substr]);
      break;
    }
    substr += in[current_index];
    if (!dict.contains(substr)) {
      substr.pop_back();
      answer.push_back(dict[substr]);
      substr += in[current_index];
      ++last_code;
      dict[substr] = last_code;
      substr = in[current_index];
    }
    ++current_index;
  }
  std::cout << answer.size() << "\n";
  for (int value : answer) {
    std::cout << value << " ";
  }
}
