from collections import defaultdict

class Solution:
    def subarraysWithKDistance(self, nums: list[int], k: int) -> int:
        pass

    def subarraysWithKDistinct(self, nums: list[int], k: int) -> int:
        def atMost(k):
            count = defaultdict(int)
            res = 0
            l = 0
            for r in range(len(nums)):
                if count[nums[r]] == 0:
                    k -= 1
                count[nums[r]] += 1
                
                while k < 0:
                    count[nums[l]] -= 1
                    if count[nums[l]] == 0:
                        k += 1
                    l += 1
                res += r - l + 1
            return res

        return atMost(k) - atMost(k - 1)