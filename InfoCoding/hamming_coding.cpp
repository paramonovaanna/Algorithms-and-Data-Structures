#include <iostream>
#include <vector>
#include <string>

class HammingCode {
public:
    HammingCode(std::string binary_number) {
        size_t binary_number_index = 0;
        size_t hamming_code_index = 1;
        int skip = 1;
        while (binary_number_index < binary_number.size()) {
            if (hamming_code_index == skip) {
                skip *= 2;
                code_.push_back(0);
                ++hamming_code_index;
                continue;
            }
            code_.push_back(binary_number[binary_number_index] - '0');
            ++binary_number_index;
            ++hamming_code_index;
        }
        size_ = code_.size();
    }

    void build() {
        for (size_t i = 1; i < size_; i *= 2) {
            code_[i] = get_sum(i);
        }
    }

    std::vector<int> get_code() {
        return code_;
    }

private:
    std::vector<int> code_{0};
    size_t size_;

    int get_sum(size_t degree) {
        int sum = 0;
        for (size_t i = degree; i < size_; i += degree * 2) {
            for (size_t j = i; j < std::min(i + degree, size_); ++j) {
                sum += code_[j];
                sum %= 2;
            }
        }
        return sum;
    }
};


int main() {
    std::string binary_number;
    std::cin >> binary_number;
    HammingCode hamming_code(binary_number);
    hamming_code.build();
    std::vector<int> answer = hamming_code.get_code();
    for (size_t i = 1; i < answer.size(); ++i) {
        std::cout << answer[i];
    }
}