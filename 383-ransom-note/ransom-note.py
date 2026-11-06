from collections import Counter

class Solution:
    def canConstruct(self, ransomNote: str, magazine: str) -> bool:
        # Count frequencies of characters in both strings
        note_count = Counter(ransomNote)
        mag_count = Counter(magazine)
        
        # Check if every character in ransomNote has enough supply in magazine
        for char, count in note_count.items():
            if mag_count[char] < count:
                return False
        
        return True