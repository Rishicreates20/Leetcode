int minOperations(int* nums, int numsSize, int x) {
    int total = 0;
    for(int i = 0; i < numsSize; i++) total += nums[i];

    int target = total - x;
    if(target < 0) return -1;

    int best = -1, sum = 0, left = 0;
    for(int right = 0; right < numsSize; right++){
        sum += nums[right];
        while(sum > target) sum -= nums[left++];
        if(sum == target && right - left + 1 > best)
            best = right - left + 1;
    }
    return best == -1 ? -1 : numsSize - best;
}