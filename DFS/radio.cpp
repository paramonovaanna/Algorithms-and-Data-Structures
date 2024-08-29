#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>


struct Point {
    int x;
    int y;
};

double distance(const Point& p1, const Point& p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

bool dfs(int now, int color, double radius, std::vector<int>& colored, const std::vector<Point>& towers) {
    colored[now] = color;
    bool status = true;
    for (size_t i = 0; i != towers.size(); ++i) {
        if (i == now) {
            continue;
        }
        if (distance(towers[now], towers[i]) < radius * radius) {
            if (colored[i] == color) {
                status = 0;
            } else if (!colored[i]) {
                status = dfs(i, 3 - color, radius, colored, towers);
            }
        }
        if (!status) {
            break;
        }
    }
    return status;
}

bool correct_radius(double radius, const std::vector<Point>& towers) {
    bool status;
    std::vector<int> colored(towers.size());
    for (size_t i = 0;i < colored.size(); ++ i){
        if (!colored[i]) {
            status = dfs(i, 1, radius, colored, towers);
        }
        if (!status) {
            break;
        }
    }
    return status;
}

double binary_search(double left, double right, const std::vector<Point>& towers) {
    while (right - left > 1e-9) {
        double middle = (left + right) / 2;
        if (correct_radius(middle, towers)) {
            left = middle;
        } else {
            right = middle;
        }
    }
    return left;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<Point> towers(n);
    for (size_t i = 0; i != n; ++i) {
        int x, y;
        std::cin >> x >> y;
        Point point{x, y};
        towers[i] = point;
    }
    double radius = binary_search(0, std::numeric_limits<int>::max(), towers);
    std::cout << std::setprecision(16) << radius / 2 << std::endl;
    std::vector<int> colored(n);
    for (size_t i = 0;i < colored.size(); ++ i){
        if (!colored[i]) {
            dfs(i, 1, radius, colored, towers);
        }
    }
    for (int color : colored) {
        std::cout << color << ' ';
    }
}