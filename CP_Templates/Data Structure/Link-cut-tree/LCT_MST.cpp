#include <bits/stdc++.h>

#define all(x) begin(x), end(x)
#define int long long

using namespace std;
using ll = long long;

const char nl = '\n';


struct node {
    int p = 0, c[2] = {0, 0}, pp = 0;
    bool flip = 0;
    int sz = 0;
    pair<int, int> val, mx;

    node() {}

    node(int x, int i) {
        val = mx = pair(x, i);
        sz = 1;
    }
};

struct LCT {
    vector<node> t;

    LCT() {}

    LCT(int n) : t(n + 1) {}

    // <independant splay tree code>
    int dir(int x, int y) { return t[x].c[1] == y; }

    void set(int x, int d, int y) {
        if (x) t[x].c[d] = y, pull(x);
        if (y) t[y].p = x;
    }

    void pull(int x) {
        if (!x) return;
        int &l = t[x].c[0], &r = t[x].c[1];
        push(l);
        push(r);
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
            push(z);
            push(y);
            push(x);
            int dx = dir(y, x), dy = dir(z, y);
            if (!z) rotate(x, !dx);
            else if (dx == dy) rotate(y, !dx), rotate(x, !dx);
            else rotate(x, dy), rotate(x, dx);
        }
    }
    // </independant splay tree code>

    // making it a root in the rep. tree
    void make_root(int u) {
        access(u);
        int l = t[u].c[0];
        if (l) {
            t[l].flip ^= 1;
            swap(t[l].p, t[l].pp);
            set(u, 0, 0);
        }
    }

    // make the path from root to u a preferred path
    // returns last path-parent of a node as it moves up the tree
    int access(int _u) {
        int v = 0, u = _u;
        for (; u; u = t[v = u].pp) {
            splay(u), splay(v);
            // remove v's contribution from u's virtual children
            int r = t[u].c[1];
            // add r as virtual child (it was right child)
            t[v].pp = 0;
            swap(t[r].p, t[r].pp);
            set(u, 1, v);
        }
        splay(_u);
        return v;
    }

    void link(int u, int v) { // u -> v (make u parent of v in rep tree)
        // ensure they are separate
        make_root(v);
        access(u);
        t[v].pp = u;
    }

    void cut(int u) { // cut par[u] -> u, u is non root vertex
        access(u);
        if (t[u].c[0] == 0) return;
        t[t[u].c[0]].p = 0;
        t[u].c[0] = 0;
        pull(u);
    }

    void cut(int u, int v) {
        if (get_parent(u) == v) cut(u);
        else if (u == get_parent(v)) cut(v);
    }

    // parent of u in the rep. tree (direct parent)
    int get_parent(int u) {
        access(u);
        push(u);
        int cur = t[u].c[0];
        if (!cur) return 0;
        push(cur);
        while (t[cur].c[1]) {
            cur = t[cur].c[1];
            push(cur);
        }
        splay(cur);
        return cur;
    }

    // root of the rep. tree containing this node
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

    // depth in the rep. tree (length of path from root to u in aux terms)
    int depth(int u) {
        access(u);
        return t[u].sz;
    }

    int lca(int u, int v) {
        if (u == v) return u;
        if (depth(u) > depth(v)) swap(u, v);
        access(v);
        return access(u);
    }

    int is_root(int u) {
        return get_parent(u) == 0;
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
        t[u].val = pair(x, i);
        pull(u);
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<array<int, 3>> edges(m);
    for (auto &[u, v, w]: edges) {
        cin >> u >> v >> w;
    }
    int weight = 0;
    LCT lct(n + m + 1);
    vector<bool> used(m);
    auto del_edge = [&](int i) {
        if (!used[i]) return;
        auto [u, v, w] = edges[i];
        lct.make_root(u);
        int edge_node = i + n + 1;
        lct.cut(v), lct.cut(edge_node);
        weight -= w;
        used[i] = false;
    };
    auto add_edge = [&](int i) {
        auto [u, v, w] = edges[i];
        int edge_node = i + n + 1;
        lct.update(edge_node, w, i);
        lct.link(u, edge_node);
        lct.link(edge_node, v);
        weight += w;
        used[i] = true;
    };
    for (int i = 0; i < m; i++) {
        auto &[u, v, w] = edges[i];
        if (lct.connected(u, v)) {
            auto [mx, id] = lct.query(u, v);
            if (mx <= w) continue;
            del_edge(id);
        }
        add_edge(i);
    }
    cout << weight << nl;
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
