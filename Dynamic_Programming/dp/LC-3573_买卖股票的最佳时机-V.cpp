// https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-v/

static const auto _ = []() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	return nullptr;
}();

class Solution {
public:
	long long maximumProfit(vector<int>& prices, int k) {
		const int n = prices.size();
		vector<long long> buy(k + 1, -prices[0]);
		vector<long long> sell(k + 1, 0);
		vector<long long> short_sell(k + 1, prices[0]);
		for (int i = 1; i < n; ++i) {
			for (int j = k; j > 0; --j) {
				sell[j] = max({sell[j], buy[j] + prices[i], short_sell[j] - prices[i]});
				buy[j] = max(buy[j], sell[j - 1] - prices[i]);
				short_sell[j] = max(short_sell[j], sell[j - 1] + prices[i]);
			}
		}
		return sell.back();
	}
};