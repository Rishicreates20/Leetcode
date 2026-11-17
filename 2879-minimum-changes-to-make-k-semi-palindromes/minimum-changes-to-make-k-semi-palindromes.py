class Solution:
    def minimumChanges(self, s: str, k: int) -> int:
        n = len(s)
        
        # Step 1: Precompute divisors for each length to optimize group extraction
        divisors = [[] for _ in range(n + 1)]
        for length in range(1, n + 1):
            for d in range(1, length):
                if length % d == 0:
                    divisors[length].append(d)
        
        # Step 2: Function to calculate changes to make s[i...j] a palindrome for a specific divisor d
        def get_palindrome_changes(i: int, j: int, d: int) -> int:
            changes = 0
            length = j - i + 1
            # Each group has elements at intervals of d
            for start in range(d):
                left = i + start
                right = i + length - 1 - (start % d) # Or map the group correctly
                # Better group traversal:
                group_indices = []
                curr = i + start
                while curr <= j:
                    group_indices.append(curr)
                    curr += d
                
                l_ptr, r_ptr = 0, len(group_indices) - 1
                while l_ptr < r_ptr:
                    if s[group_indices[l_ptr]] != s[group_indices[r_ptr]]:
                        changes += 1
                    l_ptr += 1
                    r_ptr -= 1
            return changes

        # Step 3: Precompute cost[i][j] = min changes to make s[i...j] a semi-palindrome
        cost = [[float('inf')] * n for _ in range(n)]
        for i in range(n):
            for j in range(i + 1, n):
                length = j - i + 1
                min_changes = float('inf')
                for d in divisors[length]:
                    min_changes = min(min_changes, get_palindrome_changes(i, j, d))
                cost[i][j] = min_changes

        # Step 4: DP for partitioning into k parts
        # dp[idx][parts_left] = min changes
        memo = {}
        
        def solve(idx: int, parts: int) -> int:
            if parts == 1:
                return cost[idx][n - 1]
            if idx >= n or n - idx < parts:
                return float('inf')
            
            state = (idx, parts)
            if state in memo:
                return memo[state]
            
            res = float('inf')
            # Try all possible end points for the current substring
            # Leave enough characters for the remaining (parts - 1)
            for j in range(idx, n - parts + 1):
                res = min(res, cost[idx][j] + solve(j + 1, parts - 1))
                
            memo[state] = res
            return res

        return solve(0, k)