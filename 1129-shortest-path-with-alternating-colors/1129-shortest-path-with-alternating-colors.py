from collections import defaultdict, deque
from typing import List

class Solution:
    def shortestAlternatingPaths(self, n: int, redEdges: List[List[int]], blueEdges: List[List[int]]) -> List[int]:
        # Build separate adjacency lists for red and blue edges
        red_adj = defaultdict(list)
        blue_adj = defaultdict(list)
        
        for u, v in redEdges:
            red_adj[u].append(v)
        for u, v in blueEdges:
            blue_adj[u].append(v)
            
        # dist[node][color] where color: 0 for Red, 1 for Blue
        # Initialize distances with -1
        answer = [[-1, -1] for _ in range(n)]
        
        # Queue stores tuples of (node, last_edge_color)
        # last_edge_color: -1 for start, 0 for Red, 1 for Blue
        queue = deque([(0, -1)])
        answer[0][0] = 0
        answer[0][1] = 0
        
        distance = 0
        
        while queue:
            for _ in range(len(queue)):
                curr, edge_color = queue.popleft()
                
                # If we came via Red (-1 or 0), next we can take a Blue edge
                if edge_color != 1:
                    for neighbor in blue_adj[curr]:
                        if answer[neighbor][1] == -1:
                            answer[neighbor][1] = answer[curr][0] + 1
                            queue.append((neighbor, 1))
                            
                # If we came via Blue (-1 or 1), next we can take a Red edge
                if edge_color != 0:
                    for neighbor in red_adj[curr]:
                        if answer[neighbor][0] == -1:
                            answer[neighbor][0] = answer[curr][1] + 1
                            queue.append((neighbor, 0))
                            
        # Combine the minimum distances for each node
        res = []
        for i in range(n):
            valid_dists = [d for d in answer[i] if d != -1]
            if valid_dists:
                res.append(min(valid_dists))
            else:
                res.append(-1)
                
        return res