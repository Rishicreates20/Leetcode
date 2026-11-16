class Solution:
    def subarraysDivByK(self, nums: list[int], k: int) -> int:
        prefix_sum = 0
        res = 0
        prefix_cnt = defaultdict(int)
        prefix_cnt[0]= 1


        for  n in nums:
            prefix_sum += n
            remain = prefix_sum % k


            res += prefix_cnt[remain]
            prefix_cnt[remain] += 1

        return res