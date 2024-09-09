#include <iostream>
#include <string>
#include <vector>

class PrefixFunc {
public: 
    PrefixFunc(const std::string& s): size_(s.size()) {
        values_.resize(size_, 0);
        for (size_t i = 1; i < size_; ++i) {
            int current = values_[i - 1];
            while (current > 0 && s[i] != s[current]) {
                current = values_[current - 1];
            }
            if (s[i] == s[current]) {
                values_[i] = current + 1;
            } else {
                values_[i] = 0;
            }
        }
    }

    std::vector<int> get_values() {
        return values_;
    }

private:
    size_t size_;
    std::vector<int> values_;
};


int main() {
    std::string s;
    std::cin >> s;
    PrefixFunc calculator(s);
    std::vector<int> answer = calculator.get_values();
    for (int value : answer) {
        std::cout << value << " ";
    }
}