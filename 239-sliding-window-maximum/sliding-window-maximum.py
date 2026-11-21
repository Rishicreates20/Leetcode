class Solution:
    def maxSlidingWindow(self, nums: list[int], k: int) -> list[int]:
        dq: deque[int] = deque()
        ans: list[int] = []

        for i, val in enumerate(nums):
            if dq and dq[0] <= i - k:
                dq.popleft()

            while dq and nums[dq[-1]] <= val:
                dq.pop()

            dq.append(i)

            if i >= k - 1:
                ans.append(nums[dq[0]])

        return ans