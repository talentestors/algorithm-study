// https://vjudge.net/problem/POJ-1979

#define _USE_MATH_DEFINES // To use the definition of cmath

#include <iostream>
#include <cstring>

using namespace std;

int w, h;
char mp[22][22];
bool vis[22][22];
int dis[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int dfs(int x, int y) {
    vis[x][y] = 1;
    int sum = 1;
    for (int i = 0; i < 4; i++) {
        int tx = x + dis[i][0];
        int ty = y + dis[i][1];
        if (!tx || !ty || tx > h || ty > w)
            continue;
        if (!vis[tx][ty] && mp[tx][ty] == '.') {
            sum += dfs(tx, ty);
        }
    }
    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    while (cin >> w >> h && w != 0 && h != 0) {
        int s_x = 0, s_y = 0;
        memset(mp, 0, sizeof(mp));
        memset(vis, 0, sizeof(vis));
        for (int i = 1; i <= h; ++i) {
            for (int j = 1; j <= w; ++j) {
                cin >> mp[i][j];
                if (mp[i][j] == '@') {
                    s_x = i, s_y = j;
                }
            }
        }
        cout << dfs(s_x, s_y) << '\n';
    }
    return 0;
}
