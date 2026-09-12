import bisect
from typing import List


class Solution:
    def maximumWeight(self, intervals: List[List[int]]) -> List[int]:
        n = len(intervals)

        # Sort interval indices by left endpoint (ties: right endpoint, then original index)
        order = sorted(range(n), key=lambda i: (intervals[i][0], intervals[i][1], i))
        L  = [intervals[order[k]][0] for k in range(n)]   # left  (sorted, ascending)
        R  = [intervals[order[k]][1] for k in range(n)]   # right
        W  = [intervals[order[k]][2] for k in range(n)]   # weight
        OI = [order[k]               for k in range(n)]   # original index

        # nxt[k] = first sorted position m with L[m] > R[k]  (strict: shared boundary = overlap)
        nxt = [bisect.bisect_right(L, R[k]) for k in range(n)]

        NEG = float('-inf')

        def better(a, b):
            # higher score wins; on a tie, the lexicographically smaller index-tuple wins
            (sa, ta), (sb, tb) = a, b
            if sa != sb:
                return a if sa > sb else b
            return a if ta <= tb else b

        # dp[k][c] = (best_score, sorted_index_tuple) using EXACTLY c intervals from suffix k.
        # Using exact-c (not "at most c") is what keeps the lexicographic tie-break correct,
        # because inserting one index into two EQUAL-length sorted tuples preserves lex order.
        dp = [None] * (n + 1)
        dp[n] = [(0, ())] + [(NEG, ())] * 4   # c=0 -> empty set feasible; c>=1 infeasible

        for k in range(n - 1, -1, -1):
            cur = [(0, ())] + [None] * 4       # cur[0]: choose nothing
            nk = nxt[k]
            for c in range(1, 5):
                best = dp[k + 1][c]            # skip interval k
                sub_score, sub_tuple = dp[nk][c - 1]   # take interval k
                if sub_score != NEG:
                    cand = (W[k] + sub_score,
                            tuple(sorted(sub_tuple + (OI[k],))))
                    best = better(best, cand)
                cur[c] = best
            dp[k] = cur

        # Best over choosing 0..4 intervals (compared directly as final answer arrays)
        ans = dp[0][0]
        for c in range(1, 5):
            ans = better(ans, dp[0][c])
        return list(ans[1])