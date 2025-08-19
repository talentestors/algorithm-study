/// https://vjudge.net/problem/POJ-3187

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

template <typename Iterator, typename T>
void iota(Iterator first, Iterator last, T value) {
    for (; first != last; ++first) {
        *first = value;
        ++value;
    }
}

int n, final_sum;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> final_sum;
    vector<int> nums(n);
    iota(nums.begin(), nums.end(), 1);
    vector<int> san(n + 1);
    san[1] = 1;
    for (int i = 2; i <= n; ++i) {
        for (int j = i; j > 0; --j) {
            san[j] = san[j] + san[j - 1];
        }
    }
    san.erase(san.begin());
    vector<int> ans;
    do {
        long long sum = 0;
        for (int i = 0; i < n; ++i) {
            sum += nums[i] * san[i];
        }
        if (sum == final_sum) {
            ans = nums;
            break;
        }
    } while (next_permutation(nums.begin(), nums.end()));
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << ' ';
    }
    cout << endl;
    return 0;
}
