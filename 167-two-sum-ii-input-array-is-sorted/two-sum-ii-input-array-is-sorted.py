class Solution(object):
    def twoSum(self, numbers, target):
        """
        :type numbers: List[int]
        :type target: int
        :rtype: List[int]
        """
        lft = 0
        rght = len(numbers) - 1

        while lft < rght:
            current_sum = numbers[lft]  + numbers[rght]

            if current_sum == target:
                return [lft + 1, rght + 1]

            elif current_sum < target:
                lft += 1
            else:
                rght -= 1