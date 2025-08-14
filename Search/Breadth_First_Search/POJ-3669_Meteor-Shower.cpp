/// https://vjudge.net/problem/POJ-3669

#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

const int M = 400;
int mp[M][M]; // 地图
int ts[M][M]; // 时间图层
int dis[5][2] = {{-1, 0}, {0, 1}, {0, -1}, {1, 0}, {0, 0}};

int bfs() {
    if (mp[0][0] == 0x7f7f7f7f)
        return 0;
    memset(ts, -1, sizeof(ts));
    queue<pair<int, int> > q;
    if (mp[0][0] > 0) {
        q.push(make_pair(0, 0));
        ts[0][0] = 0;
    }
    while (!q.empty()) {
        pair<int, int> p = q.front();
        q.pop();
        int &x = p.first;
        int &y = p.second;
        for (int i = 0; i < 4; ++i) {
            int dx = x + dis[i][0];
            int dy = y + dis[i][1];
            if (dx >= 0 && dx < M && dy >= 0 && dy < M && ts[dx][dy] == -1 &&
                mp[dx][dy] > ts[x][y] + 1) {
                ts[dx][dy] = ts[x][y] + 1;
                if (mp[dx][dy] == 0x7f7f7f7f) {
                    return ts[dx][dy];
                }
                q.push(make_pair(dx, dy));
            }
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    memset(mp, 0x7f, sizeof(mp));
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int x, y, t;
        cin >> x >> y >> t;
        for (int j = 0; j < 5; ++j) {
            int dx = x + dis[j][0];
            int dy = y + dis[j][1];
            if (dx >= 0 && dx < M && dy >= 0 && dy < M) {
                mp[dx][dy] = min(mp[dx][dy], t);
            }
        }
    }
    cout << bfs() << endl;
    return 0;
}
