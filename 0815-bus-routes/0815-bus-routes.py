from collections import defaultdict, deque
from typing import List

class Solution:
    def numBusesToDestination(self, routes: List[List[int]], source: int, target: int) -> int:
        if source == target:
            return 0

        # stop -> list of buses that pass through it
        stop_to_buses = defaultdict(list)
        for bus, route in enumerate(routes):
            for stop in route:
                stop_to_buses[stop].append(bus)

        if source not in stop_to_buses or target not in stop_to_buses:
            return -1

        visited_bus = [False] * len(routes)
        visited_stop = {source}
        q = deque()

        # Board every bus available at the source
        for bus in stop_to_buses[source]:
            visited_bus[bus] = True
            q.append(bus)

        buses_taken = 1
        while q:
            for _ in range(len(q)):
                bus = q.popleft()
                for stop in routes[bus]:
                    if stop == target:
                        return buses_taken
                    if stop in visited_stop:
                        continue
                    visited_stop.add(stop)
                    for nxt in stop_to_buses[stop]:
                        if not visited_bus[nxt]:
                            visited_bus[nxt] = True
                            q.append(nxt)
            buses_taken += 1

        return -1