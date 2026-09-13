class Solution:
    def largestOverlap(self, img1: List[List[int]], img2: List[List[int]]) -> int:
        n = len(img1)
        
        # Collect coordinates of all 1s in both images
        list1 = [(r, c) for r in range(n) for c in range(n) if img1[r][c] == 1]
        list2 = [(r, c) for r in range(n) for c in range(n) if img2[r][c] == 1]
        
        # Count frequencies of each translation vector
        from collections import defaultdict
        vector_counts = defaultdict(int)
        
        for r1, c1 in list1:
            for r2, c2 in list2:
                vector = (r2 - r1, c2 - c1)
                vector_counts[vector] += 1
                
        # Return the maximum frequency, or 0 if no 1s overlap
        return max(vector_counts.values()) if vector_counts else 0
        