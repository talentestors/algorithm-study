/// https://vjudge.net/problem/Aizu-0525

#include <bits/stdc++.h>

using namespace std;

static const auto _ = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return nullptr;
}();

int h, w, ans;
int mp[15][10005];

void dfs(int x) {
    if (x == h) {
        int sum = 0;
        for (int i = 0; i < w; ++i) {
            int tmp_sum = 0;
            for (int j = 0; j < h; ++j) {
                if (mp[j][i] == 1) ++tmp_sum;
            }
            sum += max(tmp_sum, h - tmp_sum);
        }
        ans = max(ans, sum);
        return;
    }
    dfs(x + 1);
    for (int i = 0; i < w; ++i) {
        mp[x][i] ^= 1;
    }
    dfs(x + 1);
}

inline void solve() {
    while (cin >> h >> w && h | w) {
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                cin >> mp[i][j];
            }
        }
        ans = 0;
        dfs(0);
        cout << ans << '\n';
    }
}

int main() {
    int T = 1;
    for (; T > 0; --T) {
        solve();
    }
    return 0;
}
