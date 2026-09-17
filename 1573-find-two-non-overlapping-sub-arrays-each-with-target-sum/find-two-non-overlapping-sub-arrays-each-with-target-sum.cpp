class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();
        const int INF = 1e9;
        vector<int> best(n, INF);
        int ans = INF, sum = 0, l = 0, cur = INF;

        for(int r = 0; r < n; r++){
            sum += arr[r];
            while(sum > target) sum -= arr[l++];

            if(sum == target){
                int len = r - l + 1;
                if(l > 0 && best[l-1] != INF)
                   ans = min(ans, len + best[l-1]);
                cur = min(cur, len);
            }
            best[r] = cur;
        }
        return ans == INF ? -1 : ans;
        
    }
};