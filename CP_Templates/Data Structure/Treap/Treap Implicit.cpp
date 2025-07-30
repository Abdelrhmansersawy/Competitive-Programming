/*
--------------------------------------------------------
      Implicit Treap with Lazy Propagation & Reversal
--------------------------------------------------------

Features:
---------
This is an Implicit Treap (Indexed Treap) that supports the following in O(log n):
  - Point Insertion and Deletion
  - Range Addition (Lazy Propagation)
  - Range Reversal (Lazy Tag)
  - Range Rotation (Left or Right)
  - Range Queries: Size, Sum, Minimum

Node Metadata (Info):
---------------------
Each node tracks:
  - size of subtree
  - sum of values
  - minimum value
  - pending lazy addition

Operations are implemented using:
  - Treap split/merge techniques
  - Lazy propagation and reverse flag
  - Efficient subtree recomputation (pull)

Time Complexity:
----------------
Each operation is O(log n) amortized due to randomized treap structure.

--------------------------------------------------------

/// Call clear() to clear the treap, then use each function carefully following the comments
/// If there is propagation, uncomment propagate() inside the functions
/// Note 1: All the operations are zero based
/// Note 2: Remember to propagate if you try to access the treap nodes outside split and merge
/*
*/

#include <bits/stdc++.h>
using namespace std;

const int INF = numeric_limits<int>::max();

struct Info {
    int size, sum, mn, lazy;
    Info() : size(0), sum(0), mn(INF), lazy(0) {}
    Info(int _size, int _sum, int _mn, int _lazy)
        : size(_size), sum(_sum), mn(_mn), lazy(_lazy) {}

    Info operator+(const Info &o) const {
        return Info(
            size + o.size,
            sum + o.sum,
            min(mn, o.mn),
            0 // lazy is not carried forward in merge
        );
    }
};

struct Node {
    int key, prior;
    bool rev;
    Info info;
    Node *l, *r;

    Node(int v)
        : key(v), prior(rand()), rev(false),
          info(1, v, v, 0), l(nullptr), r(nullptr) {}
};

typedef Node* PNode;

struct Treap {
    PNode root = nullptr;

    int sz(PNode t) { return t ? t->info.size : 0; }

    void push(PNode t) {
        if (!t) return;

        if (t->rev) {
            swap(t->l, t->r);
            if (t->l) t->l->rev ^= 1;
            if (t->r) t->r->rev ^= 1;
            t->rev = false;
        }

        if (t->info.lazy) {
            t->key += t->info.lazy;
            t->info.sum += t->info.lazy * sz(t);
            t->info.mn += t->info.lazy;

            if (t->l) t->l->info.lazy += t->info.lazy;
            if (t->r) t->r->info.lazy += t->info.lazy;

            t->info.lazy = 0;
        }
    }

    void pull(PNode t) {
        if (!t) return;
        t->info = Info(1, t->key, t->key, 0);
        if (t->l) t->info = t->l->info + t->info;
        if (t->r) t->info = t->info + t->r->info;
    }

    void split(PNode t, int k, PNode &l, PNode &r) {
        if (!t) return void(l = r = nullptr);
        push(t);
        if (sz(t->l) < k)
            split(t->r, k - sz(t->l) - 1, t->r, r), l = t;
        else
            split(t->l, k, l, t->l), r = t;
        pull(t);
    }

    void merge(PNode &t, PNode l, PNode r) {
        push(l); push(r);
        if (!l || !r) t = l ? l : r;
        else if (l->prior > r->prior)
            merge(l->r, l->r, r), t = l;
        else
            merge(r->l, l, r->l), t = r;
        pull(t);
    }

    void insert(int pos, int val) {
        PNode t1, t2;
        split(root, pos, t1, t2);
        merge(t1, t1, new Node(val));
        merge(root, t1, t2);
    }

    void erase(int pos) {
        PNode t1, t2, t3;
        split(root, pos, t1, t2);
        split(t2, 1, t2, t3);
        delete t2;
        merge(root, t1, t3);
    }

    void updateRangeAdd(int l, int r, int v) {
        PNode t1, t2, t3;
        split(root, l, t1, t2);
        split(t2, r - l + 1, t2, t3);
        if (t2) t2->info.lazy += v;
        merge(t2, t2, t3);
        merge(root, t1, t2);
    }

    void updateRangeReverse(int l, int r) {
        PNode t1, t2, t3;
        split(root, l, t1, t2);
        split(t2, r - l + 1, t2, t3);
        if (t2) t2->rev ^= 1;
        merge(t2, t2, t3);
        merge(root, t1, t2);
    }

    void updateRangeRotateRight(int l, int r, int k) {
        int len = r - l + 1;
        k %= len;
        if (k == 0) return;
        PNode t1, t2, t3, t4;
        split(root, l, t1, t2);
        split(t2, len, t2, t3);
        split(t2, len - k, t2, t4);
        merge(t2, t4, t2);
        merge(t2, t2, t3);
        merge(root, t1, t2);
    }

    void updateRangeRotateLeft(int l, int r, int k) {
        int len = r - l + 1;
        k %= len;
        if (k == 0) return;
        updateRangeRotateRight(l, r, len - k);
    }

    Info query(int l, int r) {
        PNode t1, t2, t3;
        split(root, l, t1, t2);
        split(t2, r - l + 1, t2, t3);
        Info res = t2 ? t2->info : Info();
        merge(t2, t2, t3);
        merge(root, t1, t2);
        return res;
    }

    Info getInfo() {
        if (root) push(root);
        return root ? root->info : Info();
    }

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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(time(0)); // Random priority seed

    Treap tr;
    tr.insert(0, 5);
    tr.insert(1, 3);
    tr.insert(2, 9);
    tr.insert(3, 1);
    tr.insert(4, 7);

    // Initial: {5, 3, 9, 1, 7}

    tr.updateRangeReverse(1, 3);      // -> {5, 1, 9, 3, 7}
    tr.updateRangeAdd(2, 4, 2);       // -> {5, 1, 11, 5, 9}
    tr.updateRangeRotateRight(0, 4, 2); // -> {5, 9, 5, 1, 11}
    tr.updateRangeRotateLeft(0, 4, 1);  // -> {9, 5, 1, 11, 5}

    Info meta = tr.getInfo();
    cout << "Final stats: Size=" << meta.size
         << " Sum=" << meta.sum
         << " Min=" << meta.mn << '\n';

    Info q = tr.query(1, 3);
    cout << "Range [1,3] stats: Sum=" << q.sum << " Min=" << q.mn << '\n';

    return 0;
}
