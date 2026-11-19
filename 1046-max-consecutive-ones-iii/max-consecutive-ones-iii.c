int longestOnes(int* nums, int numsSize, int k) {
    int start = 0;
    int max_ones = 0;
    int zeroCount = 0;

    for (int end = 0; end < numsSize; end++) {
        if (nums[end] == 0) {
            zeroCount++;
        }

        while (zeroCount > k) {
            if (nums[start] == 0) {
                zeroCount--;
            }
            start++;
        }

        int current_len = end - start + 1;
        if (current_len > max_ones) {
            max_ones = current_len;
        }
    }

    return max_ones;
}