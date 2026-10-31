#include <vector>
#include <algorithm>

class Solution {
public:
    int findTheCity(int n, std::vector<std::vector<int>>& edges, int distanceThreshold) {
        // Floyd-Warshall Algorithm to find shortest paths between all pairs of cities.
        // Time Complexity: O(n^3), Space Complexity: O(n^2). 
        // Given n <= 100, n^3 = 1,000,000 operations, which runs well within the time limit.
        
        std::vector<std::vector<int>> dist(n, std::vector<int>(n, 1e9));

        for (int i = 0; i < n; ++i) {
            dist[i][i] = 0;
        }

        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];
            dist[u][v] = w;
            dist[v][u] = w;
        }

        // Floyd-Warshall core logic
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (dist[i][k] != 1e9 && dist[k][j] != 1e9) {
                        dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
                    }
                }
            }
        }

        int minReachableCount = n + 1;
        int bestCity = -1;

        for (int i = 0; i < n; ++i) {
            int reachableCount = 0;
            for (int j = 0; j < n; ++j) {
                if (i != j && dist[i][j] <= distanceThreshold) {
                    reachableCount++;
                }
            }

            // We want the city with the smallest number of reachable neighbors.
            // If there's a tie, we choose the city with the greatest index (hence >=).
            if (reachableCount <= minReachableCount) {
                minReachableCount = reachableCount;
                bestCity = i;
            }
        }

        return bestCity;
    }
};