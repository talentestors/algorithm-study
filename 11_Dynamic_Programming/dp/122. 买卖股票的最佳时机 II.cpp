// https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-ii/

class Solution {
public:
	int maxProfit(vector<int>& prices) {
		const int n = prices.size();
		int ans = 0;
		for (int i = 1; i < n; ++i) {
			ans += max(prices[i] - prices[i - 1], 0);
		}
		return ans;
	}
};