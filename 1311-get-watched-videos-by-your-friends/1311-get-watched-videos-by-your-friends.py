from collections import deque, Counter
from typing import List

class Solution:
    def watchedVideosByFriends(self, watchedVideos: List[List[str]], friends: List[List[int]], id: int, level: int) -> List[str]:
        # BFS to find people at the exact given level
        queue = deque([id])
        visited = {id}
        current_level = 0
        
        while queue and current_level < level:
            for _ in range(len(queue)):
                curr_person = queue.popleft()
                for friend in friends[curr_person]:
                    if friend not in visited:
                        visited.add(friend)
                        queue.append(friend)
            current_level += 1
            
        # queue now contains all friends at the target level
        video_count = Counter()
        for person in queue:
            for video in watchedVideos[person]:
                video_count[video] += 1
                
        # Sort by frequency (ascending), then alphabetically by video name
        result = sorted(video_count.keys(), key=lambda x: (video_count[x], x))
        
        return result