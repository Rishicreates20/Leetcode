class Solution {
public:
    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {

        std::sort(robot.begin(), robot.end());
        std::sort(factory.begin(), factory.end());

        std::vector<long long> factorySlots;
        for (const auto& f : factory){
            int pos = f[0];
            int limit = f[1];
            for(int i = 0; i < limit; ++i){
                factorySlots.push_back(pos);
            }
        }

        int m = robot.size();
        int n = factorySlots.size();


        std::vector<std::vector<long long>> dp(m + 1, std::vector<long long>(n+1, 1e18));

        for (int j = 0; j <= n; ++j){
            dp[0][j] = 0;
        }

        for(int i =  1; i <= m; i++){
            for(int j = 1; j <= n; j++){
                long long skip = dp[i][j-1];

                long long use = std::abs((long long) robot[i - 1] - factorySlots[j - 1]) + dp[i - 1][j - 1];

                dp[i][j] = std::min(skip, use);
            }
        }
        
        return dp[m][n];
    }
};