/// https://vjudge.net/problem/Aizu-0121

#include <bits/stdc++.h>

using namespace std;

static const auto _ = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return nullptr;
}();

string s;
unordered_map<string, int> mp;
const int dis[4] = {1, 4, -1, -4};

void bfs() {
    queue<string> q;
    q.push("01234567");
    while (!q.empty()) {
        s = q.front();
        q.pop();
        int pos = s.find('0');
        for (int i = 0; i < 4; ++i) {
            int p = pos + dis[i];
            if (p < 0 || p > 7 || (pos == 3 && p == 4) || (pos == 4 && p == 3))
                continue;
            string tmp = s;
            swap(tmp[pos], tmp[p]);
            if (mp.count(tmp) != 0)
                continue;
            mp[tmp] = mp[s] + 1;
            q.push(tmp);
        }
    }
}

inline void solve() {
    mp.reserve(1 << 11), mp.max_load_factor(0.75);
    bfs();
    int num, len = 0;
    s.clear();
    while (cin >> num) {
        s += to_string(num);
        ++len;
        if (len == 8) {
            cout << mp[s] << '\n';
            s.clear();
        }
        len %= 8;
    }
}

int main() {
    int T = 1;
    for (; T > 0; --T) {
        solve();
    }
    return 0;
}
