/// https://vjudge.net/problem/CodeForces-3A

#define _USE_MATH_DEFINES  // To use the definition of cmath

#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;
using ull = unsigned long long;

// mp.reserve(1024), mp.max_load_factor(0.75);
// Used only for basic types, pair and tuple.
template <typename T>
struct custom_hash_base {
    size_t operator()(const T& x) const {
        static const size_t seed = chrono::steady_clock::now().time_since_epoch().count();
        return _Hash_bytes(&x, sizeof(x), seed);
    }
};

static const auto _ = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("../in.txt", "r", stdin);
#endif
    return nullptr;
}();

inline void solve() {
    int yy, y;
    char a, b;
    cin >> a >> yy >> b >> y;
    int xx = a - 'a' + 1;
    int x = b - 'a' + 1;
    int m = min(abs(x - xx), abs(y - yy));
    int n = max(abs(x - xx), abs(y - yy)) - m;
    cout << n + m << endl;
    string step0 = "";
    if (xx < x)
        step0 += "R";
    else if (xx > x)
        step0 += "L";
    if (yy < y)
        step0 += "U";
    else if (yy > y)
        step0 += "D";
    for (int i = 0; i < m; ++i)
        cout << step0 << '\n';
    if (abs(x - xx) < abs(y - yy)) {
        if (yy < y) step0 = "U";
        else step0 = "D";
    } else if (abs(x - xx) > abs(y - yy)) {
        if (xx < x) step0 = "R";
        else step0 = "L";
    }
    for (int i = 0; i < n; ++i) {
        cout << step0 << '\n';
    }
}

int main() {
    int T = 1;
    for (/*cin >> T*/; T > 0; --T) {
        solve();
    }
    return 0;
}
