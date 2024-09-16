#include <iostream>
#include <vector>
#include <string>

using Code = std::vector<int>;
using BinaryNumber = std::vector<int>;

class HammingDecode {
public:
    HammingDecode(std::string to_decode) {
        size_ = to_decode.size() + 1;
        code_.resize(size_, 0);
        for (size_t i = 1; i < size_; ++i) {
            code_[i] = to_decode[i - 1] - '0';
        }
    }

    void correct_wrong_bit() {
        int wrong_bit = 0;
        for (size_t i = 1; i < size_; i *= 2) {
            if (get_sum(i) == 1) {
                wrong_bit += i;
            }
        }
        code_[wrong_bit] = (code_[wrong_bit] + 1) % 2;
    }

    BinaryNumber decode() {
        correct_wrong_bit();
        size_t index = 1;
        size_t skip = 1;
        while (index < code_.size()) {
            if (index == skip) {
                skip *= 2;
                ++index;
                continue;
            }
            decoded_.push_back(code_[index]);
            ++index;
        }
        return decoded_;
    }

private:
    Code code_;
    BinaryNumber decoded_;
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
    std::string to_decode;
    std::cin >> to_decode;

    HammingDecode decoder(to_decode);
    BinaryNumber answer = decoder.decode();
    for (size_t i = 0; i < answer.size(); ++i) {
        std::cout << answer[i];
    }
}