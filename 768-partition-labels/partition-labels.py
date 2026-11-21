class Solution:
    def partitionLabels(self, s: str) -> list[int]:
        # 1. Record the last index of every character in s
        last_index = {char: idx for idx, char in enumerate(s)}
        
        partitions = []
        start = 0
        end = 0
        
        # 2. Greedily expand the partition boundary and cut when i reaches end
        for i, char in enumerate(s):
            end = max(end, last_index[char])
            
            if i == end:
                partitions.append(end - start + 1)
                start = i + 1
                
        return partitions