class Solution {
public:
    vector<string> maxNumOfSubstrings(string s) {
        int n = s.size();
        vector<int> L(26, n), R(26, -1);
        for(int i  = 0; i < n; i++){
            int c = s[i] - 'a';
            L[c] = min(L[c], i);
            R[c] = i;
        }
        vector<string> res;
        int prevR = -1;
        for(int i = 0; i < n; i++){
            if(i != L[s[i] - 'a']) continue;

            int r = R[s[i] - 'a'];
            bool ok = true;
            for(int j = i; j <= r; j++){
                int d = s[j] - 'a';
                if(L[d] < i){ ok = false; break;}
                r = max(r, R[d]);
            }
            if (!ok) continue;

            if(i > prevR) res.push_back("");
            res.back() = s.substr(i, r - i + 1);
            prevR = r;
        }
        return res;
    }
};