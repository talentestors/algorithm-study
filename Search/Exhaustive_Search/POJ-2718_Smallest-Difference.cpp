/// https://vjudge.net/problem/POJ-2718

#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

string s;
vector<int> arr;

inline void solve() {
    arr.clear();
    getline(cin, s);
    int n = s.length();
    for (int i = 0; i < n; ++i) {
        if (isdigit(s[i])) {
            arr.push_back(s[i] ^ 48);
        }
    }
    n = arr.size();
    if (n == 2) {
        cout << abs(arr[0] - arr[1]) << '\n';
        return;
    }
    int ans = INT_MAX;
    do {
        if (arr[0] == 0)
            continue;
        int mid = (n + 1) >> 1;
        if (arr[mid] == 0)
            continue;
        int num1 = 0, num2 = 0;
        for (int i = 0; i < mid; ++i) {
            num1 *= 10;
            num1 += arr[i];
        }
        for (int i = mid; i < n; ++i) {
            num2 *= 10;
            num2 += arr[i];
        }
        ans = min(ans, abs(num1 - num2));
    } while (next_permutation(arr.begin(), arr.end()));
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T;
    for (cin >> T, cin.ignore(); T > 0; --T) {
        solve();
    }
    return 0;
}
