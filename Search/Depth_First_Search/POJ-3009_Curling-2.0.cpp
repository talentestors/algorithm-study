/// https://vjudge.net/problem/POJ-3009

#define _USE_MATH_DEFINES // To use the definition of cmath

#include <iostream>
#include <cstring>

using namespace std;

enum {
    SPACE,      // 空格
    OBSTACLE,   // 障碍物
    START,      // 起点
    END         // 终点
};

int w, h;
int grip[22][22];
const int dis[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int sx, sy, ans;

void dfs(int x, int y, int dep) {
    if (dep > 10) return;
    for (int i = 0; i < 4; ++i) {
        int dx = x + dis[i][0], dy = y + dis[i][1];
        // 判断是否可以移动
        if (grip[dx][dy] == OBSTACLE || grip[dx][dy] == -1)
            continue;
        do {
            if (grip[dx][dy] == OBSTACLE) {
                grip[dx][dy] = SPACE;
                dfs(dx - dis[i][0], dy - dis[i][1], dep + 1);
                grip[dx][dy] = OBSTACLE;
                break;
            }
            if (grip[dx][dy] == END) {
                ans = min(ans, dep);
                return;
            }
            dx += dis[i][0];
            dy += dis[i][1];
        } while (dx > 0 && dy > 0 && dx <= h && dy <= w);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    while (cin >> w >> h && w > 0) {
        memset(grip, -1, sizeof(grip));
        for (int i = 1; i <= h; ++i) {
            for (int j = 1; j <= w; ++j) {
                cin >> grip[i][j];
                if (grip[i][j] == START) {
                    sx = i, sy = j;
                }
            }
        }
        ans = 0xF;
        dfs(sx, sy, 1);
        if (ans != 0xF) cout << ans << '\n';
        else cout << -1 << '\n';
    }
    return 0;
}
