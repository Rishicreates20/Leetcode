class Solution {
    public int uniquePaths(int[][] grid) {
        int m = grid.length;
        int n = grid[0].length;
        int MOD = 1_000_000_007;
        
        // memoR[r][c] stores the 1D coordinate of the empty cell the robot lands on 
        // if it enters the mirror at (r,c) moving RIGHT. (-1 if it goes out of bounds)
        int[][] memoR = new int[m][n];
        
        // memoD[r][c] stores the 1D coordinate of the empty cell the robot lands on 
        // if it enters the mirror at (r,c) moving DOWN. (-1 if it goes out of bounds)
        int[][] memoD = new int[m][n];
        
        // dp[r][c] stores the total valid paths to (m-1, n-1) from the empty cell (r,c)
        int[][] dp = new int[m][n];
        
        dp[m - 1][n - 1] = 1; // Base Case
        
        // Bottom-up Dynamic Programming
        for (int r = m - 1; r >= 0; r--) {
            for (int c = n - 1; c >= 0; c--) {
                if (grid[r][c] == 1) {
                    // Entered moving RIGHT -> Reflects DOWN into (r+1, c)
                    if (r + 1 >= m) {
                        memoR[r][c] = -1;
                    } else if (grid[r + 1][c] == 0) {
                        memoR[r][c] = (r + 1) * n + c;
                    } else {
                        memoR[r][c] = memoD[r + 1][c]; // Now it enters the next mirror moving DOWN
                    }
                    
                    // Entered moving DOWN -> Reflects RIGHT into (r, c+1)
                    if (c + 1 >= n) {
                        memoD[r][c] = -1;
                    } else if (grid[r][c + 1] == 0) {
                        memoD[r][c] = r * n + (c + 1);
                    } else {
                        memoD[r][c] = memoR[r][c + 1]; // Now it enters the next mirror moving RIGHT
                    }
                } else {
                    // Cell is empty (0), so we can calculate valid paths outward
                    if (r == m - 1 && c == n - 1) continue; // Skip target cell which is initialized to 1
                    
                    int ways = 0;
                    
                    // Branch 1: Try moving RIGHT
                    if (c + 1 < n) {
                        int dest = (grid[r][c + 1] == 0) ? (r * n + c + 1) : memoR[r][c + 1];
                        if (dest != -1) {
                            ways = (ways + dp[dest / n][dest % n]) % MOD;
                        }
                    }
                    
                    // Branch 2: Try moving DOWN
                    if (r + 1 < m) {
                        int dest = (grid[r + 1][c] == 0) ? ((r + 1) * n + c) : memoD[r + 1][c];
                        if (dest != -1) {
                            ways = (ways + dp[dest / n][dest % n]) % MOD;
                        }
                    }
                    
                    dp[r][c] = ways;
                }
            }
        }
        
        return dp[0][0];
    }
}