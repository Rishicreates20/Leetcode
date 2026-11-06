class Solution(object):
    def sortedSquares(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        n = len(nums)
        res = [0] * n
        left, right = 0, n - 1
        pos = n - 1
        
        while left <= right:
            left_val = nums[left] ** 2
            right_val = nums[right] ** 2
            
            if left_val > right_val:
                res[pos] = left_val
                left += 1
            else:
                res[pos] = right_val
                right -= 1
            pos -= 1
            
        return res