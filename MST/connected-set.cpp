#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
#include <set>
#include <climits>

struct Point {
    double x;
    double y;
};

using Graph = std::vector<std::vector<int>>;

const double INF = std::numeric_limits<double>::max() / 2;

double calculate_distance(const Point p1, const Point p2) {
    return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

void mst(int start, int n, std::vector<double> &edges_mst, const std::vector<Point> &points, const Graph& graph) {
    edges_mst[start] = 0.0;

    std::set<std::pair<double, int>> vertexes_set;
    vertexes_set.insert({0, start});

    std::vector<bool> tree(n);

    for (int i = 0; i < n && !vertexes_set.empty(); ++i) {
        std::pair<int, int> nearest = *vertexes_set.begin();
        vertexes_set.erase(vertexes_set.begin());
        while (tree[nearest.second]) {
            if (vertexes_set.empty())
                return;
            nearest = *vertexes_set.begin();
            vertexes_set.erase(vertexes_set.begin());
        }
        tree[nearest.second] = true;
        for (size_t i = 0; i < n; ++i) {
            if (!tree[i]) {
                double distance = 0.0;
                if (!graph[nearest.second][i]) {
                    distance = calculate_distance(points[nearest.second], points[i]);
                }
                edges_mst[i] = std::min(edges_mst[i], distance);
                vertexes_set.insert({edges_mst[i], i});
            }
        }
    }
}


int main() {
    int n;
    std::cin >> n;
    std::vector<Point> points(n);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> points[i].x >> points[i].y;
    }

    int m;
    std::cin >> m;
    Graph graph(n, std::vector<int>(n, 0));
    for (size_t i = 0; i < m; ++i) {
        int v1, v2;
        std::cin >> v1 >> v2;
        --v1;
        --v2;
        graph[v1][v2] = 1;
        graph[v2][v1] = 1;
    }

    std::vector<double> edges_mst(n, INF);
    mst(0, n, edges_mst, points, graph);

    double answer = 0;
    for (double edge : edges_mst) {
        answer += edge;
    }
    std::cout << std::setprecision(10) << answer;
}