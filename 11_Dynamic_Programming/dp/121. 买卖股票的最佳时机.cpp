// https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/

class Solution {
public:
	int maxProfit(vector<int>& prices) {
		const int n = prices.size();
		int m = prices[0];
		int ans = 0;
		for (int i = 1; i < n; ++i) {
			ans = max(ans, prices[i] - m);
			m = min(prices[i], m);
		}
		return ans;
	}
};