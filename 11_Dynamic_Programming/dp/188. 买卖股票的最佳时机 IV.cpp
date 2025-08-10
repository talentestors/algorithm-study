// https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-iv/

class Solution {
public:
	int maxProfit(int k, vector<int>& prices) {
		const int n = prices.size();
		vector buy(k + 1, -prices[0]);
		vector sell(k + 1, 0);
		for (int i = 1; i < n; ++i) {
			for (int j = 1; j <= min(i, k); ++j) {
				buy[j] = max(buy[j], sell[j - 1] - prices[i]);
				sell[j] = max(sell[j], buy[j] + prices[i]);
			}
		}
		return sell.back();
	}
};