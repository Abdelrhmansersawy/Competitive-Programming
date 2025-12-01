/**
 * Solution Idea: Difference Array + Linear Basis
 * * Core Logic:
 * 1. Basis Property: The Linear Basis of a subarray A[L...R] is equivalent to the 
 * Linear Basis of the set { A[L], D[L], D[L+1], ..., D[R-1] },
 * where D[i] = A[i] ^ A[i+1] (the difference array).
 * * 2. Range Update Trick:
 * - A Range XOR update on A[L...R] with value X changes every element in that range of A.
 * - However, for the difference array D, the inner elements (L <= i < R) do NOT change
 * because (A[i] ^ X) ^ (A[i+1] ^ X) = A[i] ^ A[i+1] = D[i].
 * - Only the boundaries of the update affect D: D[L-1] ^= X and D[R] ^= X.
 * - This converts a Range Update on A into two Point Updates on D.
 * * 3. Data Structures:
 * - Fenwick Tree (BIT): Maintains the actual values of A to specificially query A[L].
 * (Uses Range Update, Point Query logic).
 * - Segment Tree: Maintains the Linear Basis of the difference array D.
 * * 4. Query:
 * - Fetch A[L] from the Fenwick Tree.
 * - Fetch the Basis of D[L...R-1] from the Segment Tree.
 * - Insert A[L] into the fetched Basis to complete the set.
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define fastio ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define rep(i, st, ed) for(int i = st; i < ed; i++)
#define all(v) v.begin(), v.end()

const int N = 2e5 + 5;
const int B = 30;

struct XorBasis {
    int basis[B];
    int sz;

    XorBasis() {
        sz = 0;
        memset(basis, 0, sizeof(basis));
    }

    void insert(int x) {
        if (x == 0) return;
        for (int i = B - 1; i >= 0; --i) {
            if ((x >> i) & 1) {
                if (!basis[i]) {
                    basis[i] = x;
                    sz++;
                    return;
                }
                x ^= basis[i];
            }
        }
    }

    void merge(const XorBasis &other) {
        for (int i = 0; i < B; ++i) {
            if (other.basis[i]) {
                insert(other.basis[i]);
            }
        }
    }
};

XorBasis combine(XorBasis a, const XorBasis &b) {
    a.merge(b);
    return a;
}

struct FenwickTree {
    int tree[N];
    int n;

    void init(int _n) {
        n = _n;
        memset(tree, 0, sizeof(tree));
    }

    void update(int idx, int val) {
        for (++idx; idx <= n; idx += idx & -idx)
            tree[idx] ^= val;
    }

    void range_update(int l, int r, int val) {
        update(l, val);
        update(r + 1, val);
    }

    int query(int idx) {
        int res = 0;
        for (++idx; idx > 0; idx -= idx & -idx)
            res ^= tree[idx];
        return res;
    }
} bit;

struct SegmentTree {
    XorBasis tree[4 * N];
    int size;

    void init(int n, const vector<int>& initial_diffs) {
        size = n;
        build(0, 0, size - 1, initial_diffs);
    }

    void build(int node, int l, int r, const vector<int>& diffs) {
        if (l == r) {
            tree[node] = XorBasis();
            tree[node].insert(diffs[l]);
            return;
        }
        int mid = (l + r) / 2;
        build(2 * node + 1, l, mid, diffs);
        build(2 * node + 2, mid + 1, r, diffs);
        tree[node] = combine(tree[2 * node + 1], tree[2 * node + 2]);
    }

    void update(int node, int l, int r, int idx, int val) {
        if (l == r) {
            int current_val = 0;
            for(int i=0; i<B; ++i) current_val ^= tree[node].basis[i];
            
            current_val ^= val;
            
            tree[node] = XorBasis();
            tree[node].insert(current_val);
            return;
        }
        int mid = (l + r) / 2;
        if (idx <= mid) update(2 * node + 1, l, mid, idx, val);
        else update(2 * node + 2, mid + 1, r, idx, val);
        
        tree[node] = combine(tree[2 * node + 1], tree[2 * node + 2]);
    }

    XorBasis query(int node, int l, int r, int ql, int qr) {
        if (ql > qr) return XorBasis();
        if (l >= ql && r <= qr) return tree[node];
        
        int mid = (l + r) / 2;
        if (qr <= mid) return query(2 * node + 1, l, mid, ql, qr);
        if (ql > mid) return query(2 * node + 2, mid + 1, r, ql, qr);
        
        return combine(
            query(2 * node + 1, l, mid, ql, qr),
            query(2 * node + 2, mid + 1, r, ql, qr)
        );
    }
} seg;

int main() {
    fastio;

    int n, q;
    if (!(cin >> n >> q)) return 0;

    vector<int> a(n);
    rep(i, 0, n) cin >> a[i];

    bit.init(n);
    rep(i, 0, n) {
        bit.range_update(i, i, a[i]); 
    }

    vector<int> d(n, 0); 
    rep(i, 0, n - 1) {
        d[i] = a[i] ^ a[i+1];
    }
    
    seg.init(n, d);

    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            --l; --r;

            bit.range_update(l, r, x);

            if (l > 0) {
                seg.update(0, 0, n - 1, l - 1, x);
            }
            if (r < n - 1) {
                seg.update(0, 0, n - 1, r, x);
            }
        } else {
            int l, r;
            cin >> l >> r;
            --l; --r;

            int first_val = bit.query(l);
            XorBasis res = seg.query(0, 0, n - 1, l, r - 1);
            res.insert(first_val);

            cout << (1LL << res.sz) << "\n";
        }
    }

    return 0;
}
