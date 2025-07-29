/*
 * Li Chao Segment Tree (Max Version) - with Segment Insertion
 *
 * Supports:
 *   - Inserting lines over a segment [L, R] (inclusive input)
 *   - Querying max value at point x
 *
 * Time Complexity:
 *   - Insert: O(log² N)
 *   - Query:  O(log N)
 *
 * Notes:
 *   - Coordinates are compressed; all x-values must be known beforehand.
 *   - Input uses [L, R] (inclusive), but internally handled as [L, R+1).
 *   - Returns "NO" if x is outside the domain of inserted lines.
 */


#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF_LL = 1e18;

struct LiChao {
    struct Line { ll m, b; };
private:
    void insert(int p, int l, int r, Line ln) {
        int m = (l + r) >> 1;
        ll xl = xs[l], xm = xs[m], xr = xs[r-1];
        Line& cur = st[p];
        if (eval(ln, xm) > eval(cur, xm)) swap(cur, ln);
        if (r - l == 1) return;
        if (eval(ln, xl) > eval(cur, xl))
            insert(p<<1, l, m, ln);
        else if (eval(ln, xr) > eval(cur, xr))
            insert(p<<1|1, m, r, ln);
    }

    void insert_seg(int p, int l, int r, Line ln, int ql, int qr) {
        if (qr <= l || r <= ql) return;
        if (ql <= l && r <= qr) {
            insert(p, l, r, ln);
            return;
        }
        int m = (l + r) >> 1;
        insert_seg(p<<1, l, m, ln, ql, qr);
        insert_seg(p<<1|1, m, r, ln, ql, qr);
    }

    ll query_point(int p, int l, int r, ll xq, int idx) const {
        ll res = eval(st[p], xq);
        if (r - l == 1) return res;
        int m = (l + r) >> 1;
        if (idx < m)
            res = max(res, query_point(p<<1, l, m, xq, idx));
        else
            res = max(res, query_point(p<<1|1, m, r, xq, idx));
        return res;
    }

public:
    int n;
    vector<ll> xs;
    vector<Line> st;

    LiChao(const vector<ll>& coords) {
        xs = coords;
        n = xs.size();
        st.assign(4 * n, {0, -INF_LL});
    }

    ll eval(const Line& ln, ll x) const {
        return ln.m * x + ln.b;
    }

    void add_segment(ll m, ll b, ll xl, ll xr) {
        int L = lower_bound(xs.begin(), xs.end(), xl) - xs.begin();
        int R = lower_bound(xs.begin(), xs.end(), xr) - xs.begin();
        if (L < R) insert_seg(1, 0, n, {m, b}, L, R);
    }

    ll query(ll xq) const {
        int idx = lower_bound(xs.begin(), xs.end(), xq) - xs.begin();
        if (idx >= n || xs[idx] != xq) return -INF_LL; // Not in domain
        return query_point(1, 0, n, xq, idx);
    }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;

    vector<ll> xs;
    vector<tuple<int, ll, ll, ll, ll>> ops;
    
    // Read all operations and collect x-coordinates
    for (int i = 0; i < n; ++i) {
        int type;
        cin >> type;
        if (type == 1) {
            ll a, b, l, r;
            cin >> a >> b >> l >> r;
            ++r;  // r is exclusive, still important for correct range mapping
            ops.emplace_back(1, a, b, l, r);
            xs.push_back(l);
            xs.push_back(r); 
        } else {
            ll x;
            cin >> x;
            ops.emplace_back(2, x, 0, 0, 0);
            xs.push_back(x);
        }
    }

    // Remove duplicates and sort
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());

    LiChao cht(xs);

    for (auto& op : ops) {
        int type = get<0>(op);
        if (type == 1) {
            ll a = get<1>(op), b = get<2>(op), l = get<3>(op), r = get<4>(op);
            cht.add_segment(a, b, l, r);
        } else {
            ll x = get<1>(op);
            ll res = cht.query(x);
            if (res == -INF_LL) cout << "NO\n";
            else cout << res << "\n";
        }
    }
}
