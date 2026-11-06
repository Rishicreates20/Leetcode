class Solution(object):
    def moveZeroes(self, nums):
        """
        :type nums: List[int]
        :rtype: None Do not return anything, modify nums in-place instead.
        """
        non_zero_found_at = 0

        for i in range(len(nums)):
            if nums[i] != 0:
                nums[non_zero_found_at], nums[i] = nums[i] , nums[non_zero_found_at]
                non_zero_found_at += 1