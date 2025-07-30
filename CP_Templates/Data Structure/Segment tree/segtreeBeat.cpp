#include <bits/stdc++.h>

/*
 * Segment Tree Beats
 * -------------------
 * Data structure supporting on an array A[0..N-1]:
 *   1) Range add (increment every element in [l..r])
 *   2) Range chmin (clamp every element in [l..r] to ≤ x)
 *   3) Range chmax (clamp every element in [l..r] to ≥ x)
 *   4) Range sum query
 * All operations run in O(log N) amortized per update/query.
 * Typical competitive-programming style implementation.
 */
using namespace std;
using ll = long long;

const int MAXN = 200001;  // 1-based

int N;
ll A[MAXN];

struct Node {
    ll sum;   // Sum of segment
    ll max1;  // Maximum
    ll max2;  // Second maximum
    ll maxc;  // Count of maximum
    ll min1;  // Minimum
    ll min2;  // Second minimum
    ll minc;  // Count of minimum
    ll lazy;  // Add-lazy tag

    // Combine two child nodes into one
    Node operator+(const Node &o) const {
        Node res;
        // sum
        res.sum = sum + o.sum;
        // max
        if (max1 == o.max1) {
            res.max1 = max1;
            res.max2 = max(max2, o.max2);
            res.maxc = maxc + o.maxc;
        } else if (max1 > o.max1) {
            res.max1 = max1;
            res.max2 = max(max2, o.max1);
            res.maxc = maxc;
        } else {
            res.max1 = o.max1;
            res.max2 = max(max1, o.max2);
            res.maxc = o.maxc;
        }
        // min
        if (min1 == o.min1) {
            res.min1 = min1;
            res.min2 = min(min2, o.min2);
            res.minc = minc + o.minc;
        } else if (min1 < o.min1) {
            res.min1 = min1;
            res.min2 = min(min2, o.min1);
            res.minc = minc;
        } else {
            res.min1 = o.min1;
            res.min2 = min(min1, o.min2);
            res.minc = o.minc;
        }
        // lazy tags reset for merged node
        res.lazy = 0;
        return res;
    }
};

Node T[MAXN * 4];

void push_add(int t, int tl, int tr, ll v) {
    if (!v) return;
    T[t].sum += (tr - tl + 1) * v;
    T[t].max1 += v;
    if (T[t].max2 != LLONG_MIN) T[t].max2 += v;
    T[t].min1 += v;
    if (T[t].min2 != LLONG_MAX) T[t].min2 += v;
    T[t].lazy += v;
}

void push_max(int t, ll v, bool leaf) {
    if (v >= T[t].max1) return;
    T[t].sum -= T[t].max1 * T[t].maxc;
    T[t].max1 = v;
    T[t].sum += T[t].max1 * T[t].maxc;
    if (leaf) {
        T[t].min1 = v;
    } else {
        if (v <= T[t].min1) T[t].min1 = v;
        else if (v < T[t].min2) T[t].min2 = v;
    }
}

void push_min(int t, ll v, bool leaf) {
    if (v <= T[t].min1) return;
    T[t].sum -= T[t].min1 * T[t].minc;
    T[t].min1 = v;
    T[t].sum += T[t].min1 * T[t].minc;
    if (leaf) {
        T[t].max1 = v;
    } else {
        if (v >= T[t].max1) T[t].max1 = v;
        else if (v > T[t].max2) T[t].max2 = v;
    }
}

void pushdown(int t, int tl, int tr) {
    if (tl == tr) return;
    int tm = (tl + tr) >> 1;
    push_add(t<<1, tl, tm, T[t].lazy);
    push_add(t<<1|1, tm+1, tr, T[t].lazy);
    T[t].lazy = 0;
    push_max(t<<1, T[t].max1, tl==tm);
    push_max(t<<1|1, T[t].max1, tm+1==tr);
    push_min(t<<1, T[t].min1, tl==tm);
    push_min(t<<1|1, T[t].min1, tm+1==tr);
}

void build(int t=1, int tl=0, int tr=N-1) {
    T[t].lazy = 0;
    if (tl == tr) {
        ll v = A[tl];
        T[t] = {v, v, LLONG_MIN, 1, v, LLONG_MAX, 1, 0};
        return;
    }
    int tm = (tl + tr) >> 1;
    build(t<<1, tl, tm);
    build(t<<1|1, tm+1, tr);
    T[t] = T[t<<1] + T[t<<1|1];
}

void update_add(int l, int r, ll v, int t=1, int tl=0, int tr=N-1) {
    if (r<tl || tr<l) return;
    if (l<=tl && tr<=r) { push_add(t, tl, tr, v); return; }
    pushdown(t, tl, tr);
    int tm = (tl + tr) >> 1;
    update_add(l, r, v, t<<1, tl, tm);
    update_add(l, r, v, t<<1|1, tm+1, tr);
    T[t] = T[t<<1] + T[t<<1|1];
}

void update_chmin(int l, int r, ll v, int t=1, int tl=0, int tr=N-1) {
    if (r<tl || tr<l || v>=T[t].max1) return;
    if (l<=tl && tr<=r && v>T[t].max2) { push_max(t, v, tl==tr); return; }
    pushdown(t, tl, tr);
    int tm = (tl + tr) >> 1;
    update_chmin(l, r, v, t<<1, tl, tm);
    update_chmin(l, r, v, t<<1|1, tm+1, tr);
    T[t] = T[t<<1] + T[t<<1|1];
}

void update_chmax(int l, int r, ll v, int t=1, int tl=0, int tr=N-1) {
    if (r<tl || tr<l || v<=T[t].min1) return;
    if (l<=tl && tr<=r && v<T[t].min2) { push_min(t, v, tl==tr); return; }
    pushdown(t, tl, tr);
    int tm = (tl + tr) >> 1;
    update_chmax(l, r, v, t<<1, tl, tm);
    update_chmax(l, r, v, t<<1|1, tm+1, tr);
    T[t] = T[t<<1] + T[t<<1|1];
}

ll query_sum(int l, int r, int t=1, int tl=0, int tr=N-1) {
    if (r<tl || tr<l) return 0;
    if (l<=tl && tr<=r) return T[t].sum;
    pushdown(t, tl, tr);
    int tm = (tl + tr) >> 1;
    return query_sum(l, r, t<<1, tl, tm)
         + query_sum(l, r, t<<1|1, tm+1, tr);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int Q;
    cin >> N >> Q;
    for (int i = 0; i < N; i++) cin >> A[i];
    build();
    while (Q--) {
        int t; cin >> t;
        int l, r; ll x;
        if (t == 0) { cin >> l >> r >> x; update_chmin(l, r-1, x); }
        else if (t == 1) { cin >> l >> r >> x; update_chmax(l, r-1, x); }
        else if (t == 2) { cin >> l >> r >> x; update_add(l, r-1, x); }
        else { cin >> l >> r; cout << query_sum(l, r-1) << '\n'; }
    }
    return 0;
}
