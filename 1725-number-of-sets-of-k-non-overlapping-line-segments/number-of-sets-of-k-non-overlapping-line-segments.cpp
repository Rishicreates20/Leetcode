class Solution {
public:
    int numberOfSets(int n, int k) {
        const long long MOD = 1e9 + 7;
        int a = n + k - 1, b = 2 * k;
        if(b > a) return 0;

        vector<long long> f(a + 1, 1);
        for(int i = 1; i <= a; i++) f[i] = f[i-1] * i % MOD;

        auto pw = [&](long long x , long long e){
            long long r = 1;
            while(e) {if (e & 1) r = r * x % MOD; x = x * x % MOD; e >>= 1;}
            return r;
        };
        long long den = f[b] * f[a-b] % MOD;
        return (int)(f[a] * pw(den, MOD - 2) % MOD);
    }
};