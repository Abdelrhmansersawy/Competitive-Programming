struct segtree {
    struct node {
        int val = 0;

        node() {};

        node(int val) {
            this->val = val;
        }
    };

    int n, N, time = 0;
    vector<node> st;
    vector<int> lazy, upd;
    vector<array<int, 4>> stk;

    int l(int p) { return p << 1; }

    int r(int p) { return p << 1 | 1; }

    node unit = node(1e9);

    segtree() {}

    segtree(int sz) : n(sz), N(1 << bit_width(unsigned(sz))),
                      st(2 * N), lazy(vector<int>(2 * N)) {}

    node conq(node a, node b) {
        return node(min(a.val, b.val));
    }

    void build(ll p, ll L, ll R, vector<ll> &A) {
        if (L == R) {
            st[p] = A[L];
        } else {
            ll m = (L + R) / 2;
            build(l(p), L, m, A);
            build(r(p), m + 1, R, A);
            st[p] = conq(st[l(p)], st[r(p)]);
        }
    }

    void add_upd(int node) {
        stk.push_back({time, node, st[node].val, lazy[node]});
    }

    void propagate(int p, int L, int R) {
        if (lazy[p] != 0) {
            add_upd(p);
            st[p].val = max(st[p].val, lazy[p]);
            if (L != R) {
                add_upd(l(p)), add_upd(r(p));
                lazy[l(p)] = max(lazy[l(p)], lazy[p]);
                lazy[r(p)] = max(lazy[r(p)], lazy[p]);
            }
            lazy[p] = 0;
        }
    }

    node query(int p, int L, int R, int i, int j) {
        propagate(p, L, R);
        if (j < L || i > R) return unit;
        if ((L >= i) && (R <= j)) return st[p];
        int m = (L + R) / 2;
        return conq(query(l(p), L, m, i, j), query(r(p), m + 1, R, i, j));
    }

    void update(int p, int L, int R, int i, int j, int val) {
        propagate(p, L, R);
        if (j < L || i > R) return;
        if (L >= i && R <= j) {
            add_upd(p);
            lazy[p] = val;
            propagate(p, L, R);
        } else {
            int m = (L + R) / 2;
            update(l(p), L, m, i, j, val);
            update(r(p), m + 1, R, i, j, val);
            add_upd(p);
            st[p] = conq(st[l(p)], st[r(p)]);
        }
    }

    void update(int i, int j, ll val) {
        upd.push_back(time);
        update(1, 0, n - 1, i, j, val);
        time++;
    }

    node query(int i, int j) {
        return query(1, 0, n - 1, i, j);
    }

    void rollback() {
        int last = upd.back(); upd.pop_back();
        while (stk.size()) {
            auto [t, node, val, lz] = stk.back();
            if (t < last) break;
            st[node].val = val, lazy[node] = lz;
            stk.pop_back();
        }
    }

    void build(vector<ll> &e) { build(1, 0, n - 1, e); }
};
