/// https://leetcode.cn/problems/ways-to-express-an-integer-as-sum-of-powers/description/
// 恰好装满型 0-1 背包的方案数

constexpr int Mod = 1e9 + 7;

class Solution {
public:
    int numberOfWays(int n, int x) {
        vector<long long> dp(n + 1);
        dp[0] = 1;
        long long v = 0;
        for (int i = 1; (v = pow(i, x)) <= n; ++i) {
            for (int j = n; j >= v; --j) {
                dp[j] += dp[j - v];
            }
        }
        return dp[n] % Mod;
    }
};
