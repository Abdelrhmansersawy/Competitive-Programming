#include <bits/stdc++.h>

#define all(x) begin(x), end(x)
#define int long long

using namespace std;
using ll = long long;

const char nl = '\n';

struct node {
    int p = 0, c[2] = {0, 0}, pp = 0;
    bool flip = 0;
    // sz -> aux tree size
    int sz = 0, val = 0, sum = 0, pre = 0, suf = 0;

    node() {}

    node(int x) {
        val = sum = pre = suf = x;
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

    // Updated pull: Pure logic, assumes children are already correct
    void pull(int x) {
        if (!x) return;
        int l = t[x].c[0], r = t[x].c[1];
        
        // No need to push children here in standard LCT pull
        // as long as children's aggregates are invariant to their own lazy tags.
        
        t[x].sz = t[l].sz + t[r].sz + 1;
        t[x].sum = t[l].sum + t[r].sum + t[x].val;
        
        // Direct calculation without conditional ternary operators
        t[x].pre = min({t[l].pre, t[l].sum + t[x].val, t[l].sum + t[x].val + t[r].pre});
        t[x].suf = min({t[r].suf, t[r].sum + t[x].val, t[r].sum + t[x].val + t[l].suf});
    }

    // Updated push: Handles data swapping here
    void push(int x) {
        if (!x) return;
        if (t[x].flip) {
            int &l = t[x].c[0], &r = t[x].c[1];
            swap(l, r); // Structure swap
            
            // Propagate flip AND data swap to left child
            if (l) {
                t[l].flip ^= 1;
                swap(t[l].pre, t[l].suf);
            }
            
            // Propagate flip AND data swap to right child
            if (r) {
                t[r].flip ^= 1;
                swap(t[r].pre, t[r].suf);
            }
            
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

    // Updated make_root: Standard LCT reversal logic
    void make_root(int u) {
        access(u);
        splay(u);
        // Apply flip and swap data immediately to root
        t[u].flip ^= 1;
        swap(t[u].pre, t[u].suf); 
        // Note: t[u].c[0/1] will be swapped when push(u) is called later
    }

    // make the path from root to u a preferred path
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

    void cut(int u) { 
        access(u);
        if (t[u].c[0] == 0) return;
        t[t[u].c[0]].p = 0;
        t[u].c[0] = 0;
        pull(u);
    }

    bool cut(int u, int v) {
        if (get_parent(u) == v) {
            cut(u);
            return true;
        } else if (u == get_parent(v)) {
            cut(v);
            return true;
        }
        return false;
    }

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

    // Returns {sum, pre}
    array<int, 2> query(int u, int v) {
        int cur = find_root(u);
        make_root(u);
        access(v);
        return {t[v].sum, t[v].pre};
    }

    void upd(int u, int x) {
        access(u);
        t[u].val = x;
        pull(u);
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    LCT lct(n);
    
    auto get_ans = [&](int u, int v) {
        if (!lct.connected(u, v)) {
            cout << "invalid\n";
            return;
        }
        auto [sum, pre] = lct.query(u, v);
        if (pre == 0 && sum == 0) {
            cout << "balanced\n";
            return;
        }
        // Logic for balancing cost:
        // Needs -pre opening brackets to fix prefix.
        // Then remaining open brackets (sum - pre) need closing.
        cout << max(0ll, -pre) + max(0ll, sum + max(0ll, -pre)) << '\n';
    };

    for (int i = 1; i <= n; i++)
        lct.upd(i, (s[i - 1] == '(' ? 1 : -1));

    for (int i = 0; i < q; i++) {
        string ty;
        cin >> ty;
        if (ty[0] == 'b') { // balanced?
            int u, v;
            cin >> u >> v;
            get_ans(u, v);
        } else if (ty[0] == 'c') { // connect
            int u, v;
            cin >> u >> v;
            if (!lct.connected(u, v)) {
                cout << "yes\n";
                lct.link(u, v);
            } else {
                cout << "no\n";
            }
        } else if (ty[0] == 'd') { // disconnect
            int u, v;
            cin >> u >> v;
            bool flag = lct.cut(u, v);
            cout << (flag ? "yes" : "no") << nl;
        } else { // update value
            int u;
            cin >> u;
            // Toggle bracket type (1 -> -1 or -1 -> 1) is effectively * -1
            // But we need to query the current value first.
            // Since LCT stores path aggregates, to get single node val:
            int x = lct.t[u].val; 
            lct.upd(u, -x);
        }
    }
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
