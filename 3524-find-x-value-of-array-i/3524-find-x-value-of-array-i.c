/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
long long* resultArray(int* nums, int numsSize, int k, int* returnSize) {
    long long *res = (long long *)calloc(k, sizeof(long long));
    long long cur[5] = {0}, nxt[5];

    for(int i = 0; i < numsSize; i++){
        int a = nums[i] % k;

        for(int v = 0; v < k; v++) nxt[v] = 0;
        for(int v = 0; v < k; v++)
          if (cur[v])  nxt[(v * a) % k] += cur[v];
        nxt[a] += 1;

        for (int v = 0; v < k; v++){
            cur[v] = nxt[v];
            res[v] += nxt[v];
        }
    }
    *returnSize = k;
    return res;
}