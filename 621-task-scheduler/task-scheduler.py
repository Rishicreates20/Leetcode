from collections import Counter, deque
import heapq

class Solution:
    def leastInterval(self, tasks: list[str], n: int) -> int:
        counts = Counter(tasks)
        # Python's heapq is a min-heap, so store negative frequencies
        max_heap = [-cnt for cnt in counts.values()]
        heapq.heapify(max_heap)

        cooldown_q = deque()  # stores (remaining_neg_count, ready_after_time)
        time = 0

        while max_heap or cooldown_q:
            time += 1

            if max_heap:
                cnt = heapq.heappop(max_heap) + 1  # execute 1 instance (closer to 0)
                if cnt != 0:
                    cooldown_q.append((cnt, time + n))
            # If max_heap is empty, this tick is an 'idle' cycle (we still increment time)

            # Check if the oldest cooling task is ready for the next tick
            if cooldown_q and cooldown_q[0][1] == time:
                heapq.heappush(max_heap, cooldown_q.popleft()[0])

        return time