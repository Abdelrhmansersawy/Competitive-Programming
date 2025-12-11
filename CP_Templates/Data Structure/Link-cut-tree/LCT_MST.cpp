/*
Problem Statement:
Given a connected weighted graph with N vertices and M edges.
Process Q queries. Each query gives a range [L, R].
Count pairs (x, y) such that L <= x <= y <= R and:
MST_Weight(Edges[x...y]) == MST_Weight(Edges[1...M]).
(i.e., the MST of the subgraph formed by edges x through y has the 
 same weight as the global MST).
*/

#include <bits/stdc++.h>

#define all(x) begin(x), end(x)
#define int long long

using namespace std;

const char nl = '\n';
const int INF = 1e18;

// --- Fenwick Tree (Binary Indexed Tree) ---
template <typename T>
struct fenwick {
    int n;
    vector<T> tree;
    fenwick(int n) : n(n), tree(n) {}
    void add(int i, T k) {
        for (; i < n; i |= i + 1) tree[i] += k;
    }
    T query(int i) {
        T res = 0;
        for (; i >= 0; i = (i & (i + 1)) - 1) res += tree[i];
        return res;
    }
    T query(int l, int r) {
        if (l > r) return 0;
        return query(r) - query(l - 1);
    }
};

// --- DSU for Global MST ---
struct DSU {
    vector<int> p;
    DSU(int n) : p(n + 1) { iota(all(p), 0); }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    bool unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        p[x] = y;
        return true;
    }
};

// --- Link Cut Tree ---
struct node {
    int p = 0, c[2] = {0, 0}, pp = 0;
    bool flip = 0;
    int sz = 0;
    // val stores {weight, -index} to prioritize removing older edges (smaller indices)
    pair<int, int> val, mx; 

    node() {
        val = mx = {-INF, -INF}; // Vertices have minimal weight/priority
        sz = 0;
    }
};

struct LCT {
    vector<node> t;

    LCT() {}
    LCT(int n) : t(n + 1) {}

    int dir(int x, int y) { return t[x].c[1] == y; }

    void set(int x, int d, int y) {
        if (x) t[x].c[d] = y, pull(x);
        if (y) t[y].p = x;
    }

    void pull(int x) {
        if (!x) return;
        int &l = t[x].c[0], &r = t[x].c[1];
        push(l); push(r);
        t[x].mx = max({t[l].mx, t[r].mx, t[x].val}); 
        t[x].sz = t[l].sz + t[r].sz + 1;
    }

    void push(int x) {
        if (!x) return;
        int &l = t[x].c[0], &r = t[x].c[1];
        if (t[x].flip) {
            swap(l, r);
            if (l) t[l].flip ^= 1;
            if (r) t[r].flip ^= 1;
            t[x].flip = 0;
        }
    }

    void rotate(int x, int d) {
        int y = t[x].p, z = t[y].p, w = t[x].c[d];
        swap(t[x].pp, t[y].pp);
        set(y, !d, w);
        set(x, d, y);
        set(z, dir(z, y), x);
    }

    void splay(int x) {
        for (push(x); t[x].p;) {
            int y = t[x].p, z = t[y].p;
            push(z); push(y); push(x);
            int dx = dir(y, x), dy = dir(z, y);
            if (!z) rotate(x, !dx);
            else if (dx == dy) rotate(y, !dx), rotate(x, !dx);
            else rotate(x, dy), rotate(x, dx);
        }
    }

    void make_root(int u) {
        access(u);
        int l = t[u].c[0];
        if (l) {
            t[l].flip ^= 1;
            swap(t[l].p, t[l].pp);
            set(u, 0, 0);
        }
    }

    int access(int _u) {
        int v = 0, u = _u;
        for (; u; u = t[v = u].pp) {
            splay(u), splay(v);
            int r = t[u].c[1];
            t[v].pp = 0;
            swap(t[r].p, t[r].pp);
            set(u, 1, v);
        }
        splay(_u);
        return v;
    }

    void link(int u, int v) { 
        make_root(v);
        access(u);
        t[v].pp = u;
    }

    void cut(int u, int v) {
        make_root(u); 
        access(v);
        splay(v); 
        if(t[v].c[0] == u && t[u].c[1] == 0) {
            t[v].c[0] = 0;
            t[u].p = 0;
            pull(v);
        }
    }

    int find_root(int u) {
        access(u);
        push(u);
        while (t[u].c[0]) {
            u = t[u].c[0];
            push(u);
        }
        splay(u);
        return u;
    }

    bool connected(int u, int v) {
        if (u == v) return true;
        return find_root(u) == find_root(v);
    }

    pair<int, int> query(int u, int v) {
        int cur = find_root(u);
        make_root(u);
        access(v);
        auto ans = t[v].mx;
        make_root(cur);
        return ans;
    }

    void update(int u, int x, int i) {
        access(u);
        t[u].val = pair(x, i); // i should be -index passed from caller
        pull(u);
    }
};

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<array<int, 3>> edges(m);
    for (auto &[u, v, w]: edges) {
        cin >> u >> v >> w;
    }

    // --- 1. Calculate Global MST Weight ---
    vector<pair<int, int>> sorted_edges(m);
    for(int i=0; i<m; ++i) sorted_edges[i] = {edges[i][2], i};
    sort(all(sorted_edges));

    DSU dsu(n);
    int global_MST_weight = 0;
    int edges_count = 0;
    for(auto [w, i] : sorted_edges) {
        if(dsu.unite(edges[i][0], edges[i][1])) {
            global_MST_weight += w;
            edges_count++;
        }
    }

    if(edges_count < n - 1) {
        while(q--) cout << 0 << nl;
        return;
    }

    // --- 2. Sliding Window (Generate mnr array) ---
    LCT lct(n + m + 1); 
    for(int i=0; i<m; ++i) {
        lct.update(n + 1 + i, edges[i][2], -i);
    }

    int cur_weight = 0;
    int cur_cnt = 0; 
    vector<bool> used(m, false);

    auto del_edge = [&](int i) {
        if (!used[i]) return;
        auto [u, v, w] = edges[i];
        int node_idx = n + 1 + i;
        lct.cut(u, node_idx);
        lct.cut(v, node_idx);
        cur_weight -= w;
        cur_cnt--;
        used[i] = false;
    };

    auto add_edge = [&](int i) {
        auto [u, v, w] = edges[i];
        int node_idx = n + 1 + i;
        if (lct.connected(u, v)) {
            auto [mx_val, mx_neg_idx] = lct.query(u, v);  
            if (pair(mx_val, mx_neg_idx) > pair(w, -i)) {
                int id = -mx_neg_idx;
                del_edge(id);
                lct.link(u, node_idx);
                lct.link(v, node_idx);
                cur_weight += w;
                cur_cnt++;
                used[i] = true;
            }
        } else {
            lct.link(u, node_idx);
            lct.link(v, node_idx);
            cur_weight += w;
            cur_cnt++;
            used[i] = true;
        }
    };

    vector<int> mnr(m);
    int r = 0;
    for (int l = 0; l < m; l++) {
        while (r < m && (cur_cnt < n - 1 || cur_weight != global_MST_weight)) {
            add_edge(r);
            r++;
        }

        if (cur_cnt == n - 1 && cur_weight == global_MST_weight) {
            mnr[l] = r - 1;
        } else {
            mnr[l] = m + 1; 
        }
        del_edge(l);
    }

    // --- 3. Offline Query Processing ---
    vector<array<int, 4>> qs;
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        --l, --r;
        qs.push_back({r, l, r, i}); // Use 'r' as key, not 'r+1'
    }
    for (int i = 0; i < m; i++) {
        qs.push_back({mnr[i], -1, i, -1});
    }
    sort(all(qs));

    fenwick<int> s(m + 2), c(m + 2); // Increased size slightly for safety
    vector<int> ans(q);

    for (auto &[k, l, r, i]: qs) {
        if (l == -1) {
            // Update: mnr[i] <= k. Here 'r' holds index 'i'.
            s.add(r, k); 
            c.add(r, 1);
            continue;
        }
        // Query
        int sum = s.query(l, r);
        int cnt = c.query(l, r);
        ans[i] = (r + 1) * cnt - sum;
    }

    for (auto &val: ans) cout << val << nl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif
    solve();
}/*
Problem Statement:
Given a connected weighted graph with N vertices and M edges.
Process Q queries. Each query gives a range [L, R].
Count pairs (x, y) such that L <= x <= y <= R and:
MST_Weight(Edges[x...y]) == MST_Weight(Edges[1...M]).
(i.e., the MST of the subgraph formed by edges x through y has the 
 same weight as the global MST).
*/

#include <bits/stdc++.h>

#define all(x) begin(x), end(x)
#define int long long

using namespace std;

const char nl = '\n';
const int INF = 1e18;

// --- Fenwick Tree (Binary Indexed Tree) ---
template <typename T>
struct fenwick {
    int n;
    vector<T> tree;
    fenwick(int n) : n(n), tree(n) {}
    void add(int i, T k) {
        for (; i < n; i |= i + 1) tree[i] += k;
    }
    T query(int i) {
        T res = 0;
        for (; i >= 0; i = (i & (i + 1)) - 1) res += tree[i];
        return res;
    }
    T query(int l, int r) {
        if (l > r) return 0;
        return query(r) - query(l - 1);
    }
};

// --- DSU for Global MST ---
struct DSU {
    vector<int> p;
    DSU(int n) : p(n + 1) { iota(all(p), 0); }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    bool unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        p[x] = y;
        return true;
    }
};

// --- Link Cut Tree ---
struct node {
    int p = 0, c[2] = {0, 0}, pp = 0;
    bool flip = 0;
    int sz = 0;
    // val stores {weight, -index} to prioritize removing older edges (smaller indices)
    pair<int, int> val, mx; 

    node() {
        val = mx = {-INF, -INF}; // Vertices have minimal weight/priority
        sz = 0;
    }
};

struct LCT {
    vector<node> t;

    LCT() {}
    LCT(int n) : t(n + 1) {}

    int dir(int x, int y) { return t[x].c[1] == y; }

    void set(int x, int d, int y) {
        if (x) t[x].c[d] = y, pull(x);
        if (y) t[y].p = x;
    }

    void pull(int x) {
        if (!x) return;
        int &l = t[x].c[0], &r = t[x].c[1];
        push(l); push(r);
        t[x].mx = max({t[l].mx, t[r].mx, t[x].val}); 
        t[x].sz = t[l].sz + t[r].sz + 1;
    }

    void push(int x) {
        if (!x) return;
        int &l = t[x].c[0], &r = t[x].c[1];
        if (t[x].flip) {
            swap(l, r);
            if (l) t[l].flip ^= 1;
            if (r) t[r].flip ^= 1;
            t[x].flip = 0;
        }
    }

    void rotate(int x, int d) {
        int y = t[x].p, z = t[y].p, w = t[x].c[d];
        swap(t[x].pp, t[y].pp);
        set(y, !d, w);
        set(x, d, y);
        set(z, dir(z, y), x);
    }

    void splay(int x) {
        for (push(x); t[x].p;) {
            int y = t[x].p, z = t[y].p;
            push(z); push(y); push(x);
            int dx = dir(y, x), dy = dir(z, y);
            if (!z) rotate(x, !dx);
            else if (dx == dy) rotate(y, !dx), rotate(x, !dx);
            else rotate(x, dy), rotate(x, dx);
        }
    }

    void make_root(int u) {
        access(u);
        int l = t[u].c[0];
        if (l) {
            t[l].flip ^= 1;
            swap(t[l].p, t[l].pp);
            set(u, 0, 0);
        }
    }

    int access(int _u) {
        int v = 0, u = _u;
        for (; u; u = t[v = u].pp) {
            splay(u), splay(v);
            int r = t[u].c[1];
            t[v].pp = 0;
            swap(t[r].p, t[r].pp);
            set(u, 1, v);
        }
        splay(_u);
        return v;
    }

    void link(int u, int v) { 
        make_root(v);
        access(u);
        t[v].pp = u;
    }

    void cut(int u, int v) {
        make_root(u); 
        access(v);
        splay(v); 
        if(t[v].c[0] == u && t[u].c[1] == 0) {
            t[v].c[0] = 0;
            t[u].p = 0;
            pull(v);
        }
    }

    int find_root(int u) {
        access(u);
        push(u);
        while (t[u].c[0]) {
            u = t[u].c[0];
            push(u);
        }
        splay(u);
        return u;
    }

    bool connected(int u, int v) {
        if (u == v) return true;
        return find_root(u) == find_root(v);
    }

    pair<int, int> query(int u, int v) {
        int cur = find_root(u);
        make_root(u);
        access(v);
        auto ans = t[v].mx;
        make_root(cur);
        return ans;
    }

    void update(int u, int x, int i) {
        access(u);
        t[u].val = pair(x, i); // i should be -index passed from caller
        pull(u);
    }
};

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<array<int, 3>> edges(m);
    for (auto &[u, v, w]: edges) {
        cin >> u >> v >> w;
    }

    // --- 1. Calculate Global MST Weight ---
    vector<pair<int, int>> sorted_edges(m);
    for(int i=0; i<m; ++i) sorted_edges[i] = {edges[i][2], i};
    sort(all(sorted_edges));

    DSU dsu(n);
    int global_MST_weight = 0;
    int edges_count = 0;
    for(auto [w, i] : sorted_edges) {
        if(dsu.unite(edges[i][0], edges[i][1])) {
            global_MST_weight += w;
            edges_count++;
        }
    }

    if(edges_count < n - 1) {
        while(q--) cout << 0 << nl;
        return;
    }

    // --- 2. Sliding Window (Generate mnr array) ---
    LCT lct(n + m + 1); 
    for(int i=0; i<m; ++i) {
        lct.update(n + 1 + i, edges[i][2], -i);
    }

    int cur_weight = 0;
    int cur_cnt = 0; 
    vector<bool> used(m, false);

    auto del_edge = [&](int i) {
        if (!used[i]) return;
        auto [u, v, w] = edges[i];
        int node_idx = n + 1 + i;
        lct.cut(u, node_idx);
        lct.cut(v, node_idx);
        cur_weight -= w;
        cur_cnt--;
        used[i] = false;
    };

    auto add_edge = [&](int i) {
        auto [u, v, w] = edges[i];
        int node_idx = n + 1 + i;
        if (lct.connected(u, v)) {
            auto [mx_val, mx_neg_idx] = lct.query(u, v);  
            if (pair(mx_val, mx_neg_idx) > pair(w, -i)) {
                int id = -mx_neg_idx;
                del_edge(id);
                lct.link(u, node_idx);
                lct.link(v, node_idx);
                cur_weight += w;
                cur_cnt++;
                used[i] = true;
            }
        } else {
            lct.link(u, node_idx);
            lct.link(v, node_idx);
            cur_weight += w;
            cur_cnt++;
            used[i] = true;
        }
    };

    vector<int> mnr(m);
    int r = 0;
    for (int l = 0; l < m; l++) {
        while (r < m && (cur_cnt < n - 1 || cur_weight != global_MST_weight)) {
            add_edge(r);
            r++;
        }

        if (cur_cnt == n - 1 && cur_weight == global_MST_weight) {
            mnr[l] = r - 1;
        } else {
            mnr[l] = m + 1; 
        }
        del_edge(l);
    }

    // --- 3. Offline Query Processing ---
    vector<array<int, 4>> qs;
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        --l, --r;
        qs.push_back({r, l, r, i}); // Use 'r' as key, not 'r+1'
    }
    for (int i = 0; i < m; i++) {
        qs.push_back({mnr[i], -1, i, -1});
    }
    sort(all(qs));

    fenwick<int> s(m + 2), c(m + 2); // Increased size slightly for safety
    vector<int> ans(q);

    for (auto &[k, l, r, i]: qs) {
        if (l == -1) {
            // Update: mnr[i] <= k. Here 'r' holds index 'i'.
            s.add(r, k); 
            c.add(r, 1);
            continue;
        }
        // Query
        int sum = s.query(l, r);
        int cnt = c.query(l, r);
        ans[i] = (r + 1) * cnt - sum;
    }

    for (auto &val: ans) cout << val << nl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif
    solve();
}
