class Solution:
    def distinctSubseqII(self, s: str) -> int:
        MOD = 10**9 + 7
        # dp[i] stores the number of distinct subsequences ending with character (ord(i) - ord('a'))
        dp = [0] * 26
        total = 0
        
        for char in s:
            idx = ord(char) - ord('a')
            
            # New subsequences ending with the current character
            new_count = (total + 1) % MOD
            
            # Update total by removing old count ending with 'char' and adding the new count
            total = (total - dp[idx] + new_count) % MOD
            
            # Update the dp table for this character
            dp[idx] = new_count
            
        return total