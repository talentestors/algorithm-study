/// https://vjudge.net/problem/Aizu-0118

#define _USE_MATH_DEFINES // To use the definition of cmath

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
    return nullptr;
}();

int h, w;
char grid[102][102];
bool visited[102][102];
const int dis[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

void dfs(int x, int y, char& cur) {
    visited[x][y] = true;
    for (int i = 0; i < 4; ++i) {
        const int dx = dis[i][0] + x;
        const int dy = dis[i][1] + y;
        if (!dx || !dy || dx > h || dy > w || grid[dx][dy] != cur)
            continue;
        if (!visited[dx][dy]) dfs(dx, dy, cur);
    }
}

int main() {
    while (cin >> h >> w && h) {
        memset(visited, 0, sizeof(visited));
        for (int i = 1; i <= h; ++i) {
            for (int j = 1; j <= w; ++j) {
                cin >> grid[i][j];
            }
        }
        int cnt = 0;
        for (int i = 1; i <= h; ++i) {
            for (int j = 1; j <= w; ++j) {
                if (!visited[i][j]) {
                    dfs(i, j, grid[i][j]);
                    ++cnt;
                }
            }
        }
        cout << cnt << '\n';
    }
    return 0;
}
