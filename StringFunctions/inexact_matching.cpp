#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

std::vector<int> zfunc(const std::string &s)
{
    std::vector<int> values(s.size(), 0);
    int n = s.size();
    int left, right;
    left = 0;
    for (int i = 1; i < n; ++i)
    {
        int length = 0;
        if (i <= right)
        {
            length = std::min(right - i + 1, values[i - left]);
        }
        while (i + length < s.size() && s[i + length] == s[length])
        {
            ++length;
        }
        values[i] = length;
        if (i + length - 1 > right)
        {
            left = i;
            right = i + length - 1;
        }
    }
    return values;
}

int main()
{
    std::string pattern, text;
    std::cin >> pattern >> text;

    std::vector<int> z_values_pref = zfunc(pattern + '#' + text);

    reverse(pattern.begin(), pattern.end());
    reverse(text.begin(), text.end());
    std::vector<int> z_values_suf = zfunc(pattern + '#' + text);

    std::vector<size_t> indexes;
    for (size_t i = pattern.size() + 1; i < text.size() + 2; ++i)
    {
        size_t suf_index = pattern.size() + text.size() - i + 2;
        if (z_values_pref[i] + z_values_suf[suf_index] >= pattern.size() - 1)
        {
            indexes.push_back(i - pattern.size());
        }
    }
    std::cout << indexes.size() << '\n';
    for (size_t index : indexes)
    {
        std::cout << index << ' ';
    }
}