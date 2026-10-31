class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        std::vector<std::vector<std::pair<int, int >>> adj(n+1);
        for (const auto& edge : times){
            adj[edge[0]].push_back({edge[1],edge[2]});
        }

      std::priority_queue<std::pair<int, int>, 
                            std::vector<std::pair<int, int>>, 
                            std::greater<std::pair<int, int>>> pq;
        
        std::vector<int> dist(n + 1, 1e9);

        dist[k] = 0;
        pq.push({0,k});

        while(!pq.empty()){
            auto [d,u] = pq.top();
            pq.pop();

            if( d > dist[u]) continue;


           for (const auto& [v, w] : adj[u]) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }
        int max_time = 0;
        for(int i = 1; i <= n; ++i){
            if(dist[i] == 1e9) return  -1;
            max_time = std::max(max_time, dist[i]);
        }

        return max_time;
    }
};