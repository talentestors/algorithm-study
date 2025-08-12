/// https://vjudge.net/problem/Aizu-0033

#define _USE_MATH_DEFINES // To use the definition of cmath

#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;
using ull = unsigned long long;

static const auto _ = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return nullptr;
}();

inline void solve() {
    vector<int> balls(10);
    for (int i = 0; i < 10; ++i) {
        cin >> balls[i];
    }
    int l = 0, r = 0;
    for (int i = 0; i < 10; ++i) {
        if (balls[i] > l) {
            l = balls[i];
        } else if (balls[i] > r) {
            r = balls[i];
        } else {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
}

int main() {
    int T;
    for (cin >> T; T > 0; --T) {
        solve();
    }
    return 0;
}
