/*
 * Segment Tree (Range Mod + Point Set + Range Sum)
 * ------------------------------------------------
 * Supports:
 *  - upd_mod(l, r, x): for each i in [l, r], a[i] %= x (skips segments where max < x)
 *  - upd_set(i, x):       a[i] = x
 *  - query(l, r):         sum of a[l..r]
 *
 * Usage:
 *  SegTree st(N);
 *  st.build(a);                   // a is 1‑indexed vector<ll> of size N+1
 *  st.upd_mod(l, r, x);
 *  st.upd_set(i, x);
 *  ll ans = st.query(l, r);
 *
 * Time complexity:
 *  upd_mod, upd_set, query:  O(log N) amortized
 */

struct SegTree {
    using ll = long long;
    int n;
    vector<ll> sum, mx;

    SegTree(int _n): n(_n) {
        sum.assign(4*n, 0);
        mx .assign(4*n, 0);
    }

    // Build from 1‑indexed array a[1..n]
    void build(const vector<ll> &a, int x = 1, int l = 1, int r = -1) {
        if (r == -1) r = n;
        if (l == r) {
            sum[x] = mx[x] = a[l];
            return;
        }
        int m = (l + r) >> 1;
        build(a, x<<1,     l, m);
        build(a, x<<1|1, m+1, r);
        pull(x);
    }

    // Public API
    void upd_mod(int L, int R, ll v) { upd_mod(L, R, v, 1, 1, n); }
    void upd_set(int i, ll v)        { upd_set(i, v, 1, 1, n); }
    ll  query(int L, int R)          { return query(L, R, 1, 1, n); }

private:
    void pull(int x) {
        sum[x] = sum[x<<1] + sum[x<<1|1];
        mx [x] = max(mx[x<<1], mx[x<<1|1]);
    }

    void upd_mod(int L, int R, ll v, int x, int l, int r) {
        if (R < l || r < L || mx[x] < v) return;
        if (l == r) {
            ll t = mx[x] % v;
            sum[x] = mx[x] = t;
            return;
        }
        int m = (l + r) >> 1;
        upd_mod(L, R, v, x<<1,     l, m);
        upd_mod(L, R, v, x<<1|1, m+1, r);
        pull(x);
    }

    void upd_set(int i, ll v, int x, int l, int r) {
        if (l == r) {
            sum[x] = mx[x] = v;
            return;
        }
        int m = (l + r) >> 1;
        if (i <= m) upd_set(i, v, x<<1,     l, m);
        else        upd_set(i, v, x<<1|1, m+1, r);
        pull(x);
    }

    ll query(int L, int R, int x, int l, int r) {
        if (R < l || r < L) return 0;
        if (L <= l && r <= R) return sum[x];
        int m = (l + r) >> 1;
        return query(L, R, x<<1,     l, m)
             + query(L, R, x<<1|1, m+1, r);
    }
};
