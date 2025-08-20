/// https://vjudge.net/problem/POJ-3050

#include <iostream>
#include <set>

using namespace std;

const int N = 5;
int matrix[N][N];
set<int> cnt_set;
const int dis[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

void dfs(int x, int y, int num, int dep) {
    if (dep >= 6) {
        cnt_set.insert(num);
        return;
    }
    for (int i = 0; i < 4; ++i) {
        int dx = dis[i][0] + x;
        int dy = dis[i][1] + y;
        if (dx < 0 || dy < 0 || dx >= N || dy >= N)
            continue;
        dfs(dx, dy, num * 10 + matrix[dx][dy], dep + 1);
    }
}

inline void solve() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> matrix[i][j];
        }
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            dfs(i, j, matrix[i][j], 1);
        }
    }
    cout << cnt_set.size() << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("../in.txt", "r", stdin);
#endif
    int T = 1;
    for (/*cin >> T*/; T > 0; --T) {
        solve();
    }
    return 0;
}
