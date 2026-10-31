#include <vector>
#include <queue>
#include <algorithm>

class Graph {
private:
    int num_nodes;
    std::vector<std::vector<std::pair<int, int>>> adj;

public:
    Graph(int n, std::vector<std::vector<int>>& edges) {
        num_nodes = n;
        adj.resize(n);
        for (const auto& edge : edges) {
            adj[edge[0]].push_back({edge[1], edge[2]});
        }
    }
    
    void addEdge(std::vector<int> edge) {
        adj[edge[0]].push_back({edge[1], edge[2]});
    }
    
    int shortestPath(int node1, int node2) {
        std::priority_queue<std::pair<int, int>, 
                            std::vector<std::pair<int, int>>, 
                            std::greater<std::pair<int, int>>> pq;
        std::vector<int> dist(num_nodes, 1e9);

        dist[node1] = 0;
        pq.push({0, node1});

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();

            if (u == node2) return d;
            if (d > dist[u]) continue;

            for (const auto& [v, w] : adj[u]) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }

        return -1;
    }
};