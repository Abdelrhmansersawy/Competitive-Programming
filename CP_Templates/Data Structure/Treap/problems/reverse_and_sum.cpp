/**
 * Implicit Treap with Range Reverse and Range Sum Queries
 * ---------------------------------------------------------
 * - Supports reverse(l, r) and query_sum(l, r) in O(log n) per operation.
 * - Maintains segment sums and sizes with lazy propagation for reversal.
 *
 * Operations:
 * - reverse(l, r): reverse subarray in range [l, r] (0-indexed)
 * - query_sum(l, r): sum of values in subarray [l, r]
 *
 * Time: O(log n) per operation
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

/// Implicit Treap Node with sum
struct Node {
    int key, size, prior;
    ll sum;
    bool rev;
    Node *l, *r;

    Node(int v) : key(v), size(1), prior(rand()), sum(v), rev(false), l(nullptr), r(nullptr) {}
};

typedef Node* PNode;

/// Treap structure with split/merge/reverse/sum
struct Treap {
    PNode root = nullptr;

    int sz(PNode t) { return t ? t->size : 0; }
    ll get_sum(PNode t) { return t ? t->sum : 0; }

    // Pull info from children
    void pull(PNode t) {
        if (!t) return;
        t->size = 1 + sz(t->l) + sz(t->r);
        t->sum = t->key + get_sum(t->l) + get_sum(t->r);
    }

    // Push lazy reverse flag
    void push(PNode t) {
        if (!t || !t->rev) return;
        swap(t->l, t->r);
        if (t->l) t->l->rev ^= 1;
        if (t->r) t->r->rev ^= 1;
        t->rev = false;
    }

    // Split treap t into l (first k elements) and r (rest)
    void split(PNode t, int k, PNode &l, PNode &r) {
        if (!t) { l = r = nullptr; return; }
        push(t);
        if (sz(t->l) < k) {
            split(t->r, k - sz(t->l) - 1, t->r, r);
            l = t;
        } else {
            split(t->l, k, l, t->l);
            r = t;
        }
        pull(t);
    }

    // Merge two treaps l and r into t
    void merge(PNode &t, PNode l, PNode r) {
        push(l); push(r);
        if (!l || !r) t = l ? l : r;
        else if (l->prior > r->prior) {
            merge(l->r, l->r, r);
            t = l;
        } else {
            merge(r->l, l, r->l);
            t = r;
        }
        pull(t);
    }

    // Reverse values in range [l, r]
    void reverse(int l, int r) {
        PNode t1, t2, t3;
        split(root, l, t1, t2);
        split(t2, r - l + 1, t2, t3);
        if (t2) t2->rev ^= 1;
        merge(t2, t2, t3);
        merge(root, t1, t2);
    }

    // Query sum of range [l, r]
    ll query_sum(int l, int r) {
        PNode t1, t2, t3;
        split(root, l, t1, t2);
        split(t2, r - l + 1, t2, t3);
        ll res = get_sum(t2);
        merge(t2, t2, t3);
        merge(root, t1, t2);
        return res;
    }

    // Clear all nodes
    void clear(PNode &t) {
        if (!t) return;
        clear(t->l);
        clear(t->r);
        delete t;
        t = nullptr;
    }

    ~Treap() { clear(root); }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    srand(time(0));  // Random seed for treap priorities

    #ifndef ONLINE_JUDGE
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
        freopen("error.txt", "w", stderr);
    #endif

    int n, m;
    cin >> n >> m;

    Treap tr;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        tr.merge(tr.root, tr.root, new Node(x));
    }

    while (m--) {
        int type, a, b;
        cin >> type >> a >> b;
        // 1-based to 0-based
        if (type == 1) tr.reverse(a - 1, b - 1);
        else cout << tr.query_sum(a - 1, b - 1) << '\n';
    }

    return 0;
}
