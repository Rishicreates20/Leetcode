#include <vector>
#include <queue>
#include <algorithm>

class Solution {
public:
    long long minimumWeight(int n, std::vector<std::vector<int>>& edges, int src1, int src2, int dest) {
        std::vector<std::vector<std::pair<int, int>>> adj(n);
        std::vector<std::vector<std::pair<int, int>>> revAdj(n);

        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            adj[u].push_back({v, w});
            revAdj[v].push_back({u, w});
        }

        auto dijkstra = [&](int start, const std::vector<std::vector<std::pair<int, int>>>& graph) {
            std::priority_queue<std::pair<long long, int>, 
                                std::vector<std::pair<long long, int>>, 
                                std::greater<std::pair<long long, int>>> pq;
            std::vector<long long> dist(n, 1e18);

            dist[start] = 0;
            pq.push({0, start});

            while (!pq.empty()) {
                auto [d, u] = pq.top();
                pq.pop();

                if (d > dist[u]) continue;

                for (const auto& [v, w] : graph[u]) {
                    if (dist[u] + w < dist[v]) {
                        dist[v] = dist[u] + w;
                        pq.push({dist[v], v});
                    }
                }
            }
            return dist;
        };

        std::vector<long long> dist1 = dijkstra(src1, adj);
        std::vector<long long> dist2 = dijkstra(src2, adj);
        std::vector<long long> distDest = dijkstra(dest, revAdj);

        long long min_total_weight = 1e18;

        for (int i = 0; i < n; ++i) {
            if (dist1[i] != 1e18 && dist2[i] != 1e18 && distDest[i] != 1e18) {
                long long current_weight = dist1[i] + dist2[i] + distDest[i];
                min_total_weight = std::min(min_total_weight, current_weight);
            }
        }

        return min_total_weight == 1e18 ? -1 : min_total_weight;
    }
};