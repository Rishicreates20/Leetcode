#include <vector>

class Solution {
public:
    std::vector<std::vector<int>> generate(int numRows) {
        std::vector<std::vector<int>> result;

        if (numRows <= 0) {
            return result;
        }

        for (int r = 0; r < numRows; ++r) {
            std::vector<int> row(r + 1, 1);

            for (int c = 1; c < r; ++c) {
                row[c] = result[r - 1][c - 1] + result[r - 1][c];
            }

            result.push_back(row);
        }
        
        return result;
    }
};