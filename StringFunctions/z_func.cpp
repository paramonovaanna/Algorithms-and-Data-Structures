#include <iostream>
#include <string>
#include <vector>


std::vector<int> zfunc(const std::string& s) {
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
        }
    }
    return values;
}

int main() {
    std::string s;
    std::cin >> s;
    std::vector<int> answer = zfunc(s);
    for (int value : answer) {
        std::cout << value << " ";
    }
}