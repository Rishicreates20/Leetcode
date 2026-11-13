#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    int lengthOfLongestSubstring(std::string s) {
        // Keeps track of the last seen index of each ASCII character (size 128)
        std::vector<int> lastIndex(128, -1);
        int maxLen = 0;
        int left = 0;

        for (int right = 0; right < s.length(); right++) {
            char currentChar = s[right];

            // If the character is inside the current window, move the left pointer
            if (lastIndex[currentChar] >= left) {
                left = lastIndex[currentChar] + 1;
            }

            // Update the last seen position of the current character
            lastIndex[currentChar] = right;

            // Track the maximum length found so far
            maxLen = std::max(maxLen, right - left + 1);
        }

        return maxLen;
    }
};