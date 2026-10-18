from collections import deque
from typing import List

class Solution:
    def highestPeak(self, isWater: List[List[int]]) -> List[List[int]]:
        m, n = len(isWater), len(isWater[0])
        height = [[-1] * n for _ in range(m)]
        queue = deque()
        
        # Initialize the height matrix and push all water cells into the queue
        for i in range(m):
            for j in range(n):
                if isWater[i][j] == 1:
                    height[i][j] = 0
                    queue.append((i, j))
        
        d_row = [-1, 1, 0, 0]
        d_col = [0, 0, -1, 1]
        
        # Perform Multi-Source BFS
        while queue:
            r, c = queue.popleft()
            
            for i in range(4):
                n_row = r + d_row[i]
                n_col = c + d_col[i]
                
                # If the neighbor is within bounds and unvisited
                if 0 <= n_row < m and 0 <= n_col < n and height[n_row][n_col] == -1:
                    height[n_row][n_col] = height[r][c] + 1
                    queue.append((n_row, n_col))
                    
        return height