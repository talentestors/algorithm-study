/// https://vjudge.net/problem/Aizu-0558

#define _USE_MATH_DEFINES // To use the definition of cmath

#include <bits/stdc++.h>

using namespace std;

static const auto _ = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return nullptr;
}();

const int Max = 1005;
int h, w, n;
char grid[Max][Max];
int t[Max][Max];

struct Path {
    int x, y;

    Path(int _x, int _y) : x(_x), y(_y) {}
};

const int dis[4][2] = {
    {1, 0}, {-1, 0}, {0, 1}, {0, -1}
};

inline int bfs(int sx, int sy, int ex, int ey) {
    queue<Path> q;
    q.emplace(sx, sy);
    memset(t, -1, sizeof(t));
    t[sx][sy] = 0;
    while (!q.empty()) {
        Path p = q.front();
        q.pop();
        for (int i = 0; i < 4; ++i) {
            int tx = p.x + dis[i][0];
            int ty = p.y + dis[i][1];
            if (tx <= 0 || ty <= 0 || tx > h || ty > w)
                continue;
            if (t[tx][ty] != -1 || grid[tx][ty] == 'X')
                continue;
            t[tx][ty] = t[p.x][p.y] + 1;
            if (tx == ex && ty == ey) {
                return t[tx][ty];
            }
            q.emplace(tx, ty);
        }
    }
    return -1;
}

int main() {
    cin >> h >> w >> n;
    int sx[10], sy[10];
    for (int i = 1; i <= h; ++i) {
        for (int j = 1; j <= w; ++j) {
            cin >> grid[i][j];
            if (grid[i][j] == 'S') {
                sx[0] = i, sy[0] = j;
            } else if (isdigit(grid[i][j])) {
                int tmp = grid[i][j] ^ 48;
                sx[tmp] = i, sy[tmp] = j;
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        ans += bfs(sx[i - 1], sy[i - 1], sx[i], sy[i]);
    }
    cout << ans << '\n';
    return 0;
}
