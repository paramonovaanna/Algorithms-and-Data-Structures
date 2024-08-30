#include <iostream>
#include <vector>

using GraphType = std::vector<std::vector<int>>;

struct DistanceInfo {
    int vertex;
    int distance;
};

class Graph {
public:

    Graph(int n, int m) : n_(n), m_(m) {
        for (size_t i = 0; i != n_; ++i) {
            std::vector<int> a;
            graph_.push_back(a);
        }
    }

    void Add_edge(int v1, int v2) {
        --v1;
        --v2;
        graph_[v1].push_back(v2);
        graph_[v2].push_back(v1);        
    }

    void dfs(int now, std::vector<DistanceInfo>& distances, std::vector<int>& colored) {
        colored[now] = 1;
        distances[now].vertex = now;
        for (int neighb : graph_[now]) {
            if (!colored[neighb]) {
                dfs(neighb, distances, colored);
                if (distances[now].distance < distances[neighb].distance + 1) {
                    distances[now] = distances[neighb];
                    ++distances[now].distance;
                }
            }
        }
        colored[now] = 2;
    }

    DistanceInfo Get_Max_Dist_Vertex(int v) {
        std::vector<DistanceInfo> distances(n_);
        std::vector<int> colored(n_);
        dfs(v, distances, colored);
        return distances[v];
    }

    int Calculate_Max_Dist_Graph() {
        int v1 = Get_Max_Dist_Vertex(0).vertex;
        int max_dist = Get_Max_Dist_Vertex(v1).distance;
        return max_dist;
    }


private:
    int n_ = 0;
    int m_ = 0;
    GraphType graph_;
};

int main() {
    int n, m;
    std::cin >> n;

    Graph graph(n, n - 1);

    for (size_t i = 0; i != n - 1; ++i) {
        int v1, v2;
        std::cin >> v1 >> v2;

        graph.Add_edge(v1, v2);
    }

    std::cout << graph.Calculate_Max_Dist_Graph();
}
