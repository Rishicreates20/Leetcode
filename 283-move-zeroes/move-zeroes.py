class Solution(object):
    def moveZeroes(self,nums):
        last_non_zero_at = 0

        for i in range(len(nums)):
            if nums[i] != 0:
                nums[last_non_zero_at], nums[i] = nums[i] , nums[last_non_zero_at]
                last_non_zero_at += 1