class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size();

        vector<vector<int>> dp = matrix;

        for (int i = 1; i < n; i++) {
            for (int j = 0; j < n; j++) {

                int up = dp[i - 1][j];
                int leftDiag = (j > 0) ? dp[i - 1][j - 1] : INT_MAX;
                int rightDiag = (j < n - 1) ? dp[i - 1][j + 1] : INT_MAX;

                dp[i][j] += min({up, leftDiag, rightDiag});
            }
        }

        return *min_element(dp[n - 1].begin(), dp[n - 1].end());
    }
};