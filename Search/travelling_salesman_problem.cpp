#include <iostream>
#include <string>
#include <vector>

using Graph = std::vector<std::vector<int>>;

void generate_permutations(std::string result, int now_length, int N, std::string available, std::vector<std::string>& routes) {
    if (now_length == N) {
        routes.push_back("0" + result + "0");
        return;
    }
    for (size_t i = 0; i < available.length(); ++i) {
        generate_permutations(result + available[i], now_length + 1, N, available.substr(0, i) + available.substr(i + 1), routes);
    }
}

int main() {
    int n;
    std::cin >> n;

    std::string available = "123456789";
    std::vector<std::string> routes;
    generate_permutations("", 0, n - 1, available.substr(0, n - 1), routes);

    Graph graph(n, std::vector<int>(n));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            std::cin >> graph[i][j];
        }
    }

    int min_route = 1e9;
    for (std::string route : routes) {
        int route_weight = 0;
        for (size_t i = 1; i <= n; ++i) {
            int v1 = route[i - 1] - '0';
            int v2 = route[i] - '0';
            if (!graph[v1][v2]) {
                route_weight = 1e9;
                break;
            }
            route_weight += graph[v1][v2];
        }
        min_route = std::min(route_weight, min_route);
    }
    if (n == 1) {
        std::cout << graph[0][0];
        return 0;
    }
    if (min_route == 1e9) {
        std::cout << -1;
        return 0;
    }
    std::cout << min_route;
}