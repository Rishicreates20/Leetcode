#include <vector>
#include <unordered_map>

class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        std::unordered_map<int, int> numMap;
        int n = nums.size();
        
        for (int i = 0; i < n; i++) {
            int complement = target - nums[i];
            
            // Check if the complement exists in our map
            if (numMap.count(complement)) {
                return {numMap[complement], i};
            }
            
            // Otherwise, store the current number and its index
            numMap[nums[i]] = i;
        }
        
        return {}; // Return an empty vector if no solution is found
    }
};