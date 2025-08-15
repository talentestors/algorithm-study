/// Willem, Chtholly and Seniorious
/// https://vjudge.net/problem/CodeForces-896C
/// https://codeforces.com/problemset/problem/896/C
/// https://vjudge.net/problem/CodeForces-897E#author=DeepSeek_zh
/// https://codeforces.com/problemset/problem/897/E

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct Node {
    ll l, r; // l和r表示这一段的起点和终点

    // mutable的中文意思是“可变的，易变的”，跟constant（既C++中的const）是反义词。
    // 在C++中，mutable也是为了突破const的限制而设置的。
    // 被mutable修饰的变量，将永远处于可变的状态，即使在一个const函数中。
    mutable ll v; // v表示这一段上所有元素相同的值是多少

    explicit Node(const ll l, const ll r = 0, const ll v = 0) : l(l), r(r), v(v) {}

    bool operator<(const Node &a) const {
        return l < a.l; // 规定按照每段的左端点排序
    }
};

constexpr int MOD = 1e9 + 7;
constexpr int MAXN = 1e5 + 5;

ll n, m, seed, vmax, a[MAXN];
set<Node> s;
set<Node>::iterator it;

// 以pos去做切割，找到一个包含pos的区间，把它分成[l,pos-1],[pos,r]两半
inline set<Node>::iterator split(const int pos) {
    it = s.lower_bound(Node(pos));
    if (it != s.end() && it->l == pos) { return it; }
    --it;
    if (it->r < pos)
        return s.end();
    auto [l, r, v] = *it;
    s.erase(it);
    s.insert(Node(l, pos - 1, v));
    // insert函数返回pair，其中的first是新插入结点的迭代器
    return s.insert(Node(pos, r, v)).first;
}

/*
 * 这里注意必须先计算itr。
 * 比如现在区间是[1,4]，如果要add的是[1,2],如果先split(1)
 * 那么返回的itl是[1,4]，但是下一步计算itr的时候会把这个区间删掉拆成[1,2]和[3,4]
 * 那么itl这个指针就被释放了
 * */
inline void add(const ll l, const ll r, const ll x) {
    const auto itr = split(r + 1), itl = split(l);
    for (auto i = itl; i != itr; ++i) { i->v += x; }
}

inline void assign(const ll l, const ll r, const ll x) {
    const auto itr = split(r + 1), itl = split(l);
    s.erase(itl, itr);
    s.insert(Node(l, r, x));
}

// random
inline ll rnd() {
    const ll ret = seed;
    seed = (seed * 7 + 13) % MOD;
    return ret;
}

struct Rank {
    ll num, cnt;

    bool operator<(const Rank &rank) const { return num < rank.num; }

    Rank(const ll num, const ll cnt) : num(num), cnt(cnt) {}
};

// operator 3
inline ll rnk(const ll l, const ll r, ll x) {
    const auto itr = split(r + 1), itl = split(l);
    vector<Rank> v;
    for (auto i = itl; i != itr; ++i) { v.push_back(Rank(i->v, i->r - i->l + 1)); }
    sort(v.begin(), v.end());
    const int size = v.size();
    for (int i = 0; i < size; ++i) {
        if (v[i].cnt < x) { x -= v[i].cnt; } else { return v[i].num; }
    }
    return -1;
}

// operator 4
inline ll pow(const ll x, ll y, const ll p) {
    ll r = 1;
    ll base = x % p;
    while (y) {
        if (y & 1)
            r = r * base % p;
        base = base * base % p;
        y >>= 1;
    }
    return r;
}

ll calP(const ll l, const ll r, const ll x, const ll y) {
    const auto itr = split(r + 1), itl = split(l);
    ll ans = 0LL;
    for (auto i = itl; i != itr; ++i) { ans = (ans + pow(i->v, x, y) * (i->r - i->l + 1) % y) % y; }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m >> seed >> vmax;
    for (int i = 1; i <= n; ++i) {
        a[i] = (rnd() % vmax) + 1;
        s.insert(Node(i, i, a[i]));
    }
    while (m--) {
        ll l, r, x, y = 0;
        const ll op = rnd() % 4 + 1;
        l = rnd() % n + 1;
        r = rnd() % n + 1;
        if (l > r)
            swap(l, r);
        if (op == 3)
            x = rnd() % (r - l + 1) + 1;
        else
            x = rnd() % vmax + 1;
        if (op == 4)
            y = rnd() % vmax + 1;
        switch (op) {
        case 1:
            add(l, r, x);
            break;
        case 2:
            assign(l, r, x);
            break;
        case 3:
            cout << rnk(l, r, x) << '\n';
            break;
        default:
            cout << calP(l, r, x, y) << '\n';
        }
    }
    return 0;
}
