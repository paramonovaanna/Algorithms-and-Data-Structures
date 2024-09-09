#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


#include <iostream>
#include <string>
#include <vector>


int find_length(const std::string& s) {
    std::vector<int> values(s.size(), 0);
    int n = s.size();
    int left, right;
    left = 0;
    right = 0;
    for (int i = 1; i < n; ++i) {
        int length = 0;
        if (i <= right) {
            length = std::min(right - i + 1, values[i - left]);
        }
        while (i + length < s.size() && s[i + length] == s[length]) {
            ++length;
        }
        values[i] = length;
        if (i + length - 1 > right) {
            left = i;
            right = i + length - 1;
            if (right == s.size() - 1) { // если z-блок упирается в конец, то длина строки - его длина = ответ
                return values[left];
        }   
        }
    }
    return values[s.size() - 1]; // если нет z-блока, упирающегося в конец
}


int main() {
    std::string s;
    std::cin >> s;
    if (s.size() == 0) {
        std::cout << 0;
        return 0;
    }
    std::cout << s.size() - find_length(s);
}