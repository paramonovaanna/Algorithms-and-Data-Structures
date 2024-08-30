#include <iostream>
#include <vector>

void possible_partition(size_t now_pos, std::vector<int> components, int max_possible_component, int number_to_part) {
    if (number_to_part == 0) {
        for (size_t i = 0; i < now_pos; ++i) {
            std::cout << components[i] << " ";
        }
        std::cout << "\n";
        return;
    }
    for (int component = 1; component <= std::min(max_possible_component, number_to_part); ++component) {
        components[now_pos] = component;
        possible_partition(now_pos + 1, components, component, number_to_part - component);
    }
}

void print_sums(size_t n) {
    std::vector<int> components(50);
    possible_partition(0, components, n, n);
}

int main() {
    int N;
    std::cin >> N;
    print_sums(N);
}