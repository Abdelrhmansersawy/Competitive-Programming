/*
 * Generalized Implicit Treap with operator+
 * Features: Lazy Propagation, Cut & Paste, Range Queries
 */

#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// Constants for Identity
const long long INF_VAL = 4e18; // Large value for min query

struct Info {
    long long val;  // The actual value at this specific node
    long long sum;  // Aggregate: Subtree sum
    long long mn;   // Aggregate: Subtree min
    int sz;         // Aggregate: Subtree size
    
    // Lazy Tags
    long long lazy_add;
    long long lazy_set;
    bool is_set;

    // 1. Default Constructor (Identity Element)
    // Used for empty nodes or initial accumulation
    Info() 
        : val(0), sum(0), mn(INF_VAL), sz(0), 
          lazy_add(0), lazy_set(0), is_set(false) {}

    // 2. Value Constructor (Leaf)
    // Used when treating a single node as a range of size 1
    Info(long long v) 
        : val(v), sum(v), mn(v), sz(1), 
          lazy_add(0), lazy_set(0), is_set(false) {}

    // 3. Operator+ (Merge Logic)
    // Combines two ranges: Left Range + Right Range
    friend Info operator+(const Info& l, const Info& r) {
        if (l.sz == 0) return r; // Handle empty cases
        if (r.sz == 0) return l;

        Info res;
        res.sz = l.sz + r.sz;
        res.sum = l.sum + r.sum;
        res.mn = min(l.mn, r.mn);
        
        // Note: lazy tags and 'val' are not merged here because 
        // they belong to specific nodes, not the aggregate result.
        return res;
    }
};

struct Node {
    int prior;
    Node *l = nullptr, *r = nullptr;
    bool rev = false;
    Info info;

    Node(long long v) : prior(rng()), info(v) {}
};

typedef Node* PNode;

struct Treap {
    PNode root = nullptr;

    int sz(PNode t) {
        return t ? t->info.sz : 0;
    }

    // --- Updated Pull Function ---
    // Uses operator+ to combine: Left Subtree + Current Value + Right Subtree
    void pull(PNode t) {
        if (!t) return;
        
        // 1. Treat current node as a standalone range of size 1
        Info current_node(t->info.val); 
        
        // 2. Combine: Left + Current
        if (t->l) current_node = t->l->info + current_node;
        
        // 3. Combine: Result + Right
        if (t->r) current_node = current_node + t->r->info;
        
        // 4. Update Aggregates (sz, sum, mn)
        t->info.sz = current_node.sz;
        t->info.sum = current_node.sum;
        t->info.mn = current_node.mn;

        // CRITICAL: Preserve the lazy tags and raw value of 't'
        // operator+ returns a clean aggregation, but 't' might have pending updates.
        // We do NOT overwrite t->info.lazy_* or t->info.val
    }

    // --- Lazy Propagation (Same as before) ---
    void apply_set(PNode t, long long v) {
        if (!t) return;
        t->info.is_set = true;
        t->info.lazy_set = v;
        t->info.lazy_add = 0;
        t->info.val = v;
        t->info.sum = v * t->info.sz;
        t->info.mn = v;
    }

    void apply_add(PNode t, long long v) {
        if (!t) return;
        if (t->info.is_set) t->info.lazy_set += v;
        else t->info.lazy_add += v;
        t->info.val += v;
        t->info.sum += v * t->info.sz;
        t->info.mn += v;
    }

    void apply_rev(PNode t) {
        if (!t) return;
        t->rev ^= 1;
        swap(t->l, t->r);
    }

    void push(PNode t) {
        if (!t) return;
        if (t->rev) {
            apply_rev(t->l); apply_rev(t->r);
            t->rev = false;
        }
        if (t->info.is_set) {
            apply_set(t->l, t->info.lazy_set);
            apply_set(t->r, t->info.lazy_set);
            t->info.is_set = false; t->info.lazy_set = 0;
        }
        if (t->info.lazy_add != 0) {
            apply_add(t->l, t->info.lazy_add);
            apply_add(t->r, t->info.lazy_add);
            t->info.lazy_add = 0;
        }
    }

    // --- Split & Merge (Standard) ---
    void split(PNode t, int k, PNode &l, PNode &r) {
        if (!t) return void(l = r = nullptr);
        push(t);
        int cur = sz(t->l);
        if (cur < k) split(t->r, k - cur - 1, t->r, r), l = t;
        else split(t->l, k, l, t->l), r = t;
        pull(t);
    }

    void merge(PNode &t, PNode l, PNode r) {
        push(l); push(r);
        if (!l || !r) t = l ? l : r;
        else if (l->prior > r->prior) merge(l->r, l->r, r), t = l;
        else merge(r->l, l, r->l), t = r;
        pull(t);
    }

    // --- Updated Query Function ---
    // Now returns 'Info', allowing access to all aggregates (sum, min, etc.)
    Info query(int l, int r) {
        PNode t1, t2, t3;
        split(root, l, t1, t2);
        split(t2, r - l + 1, t2, t3);
        
        // Return the info of the isolated range
        Info res = t2 ? t2->info : Info(); 
        
        merge(t2, t2, t3);
        merge(root, t1, t2);
        return res;
    }

    // --- Operations ---
    void insert(int pos, long long v) {
        PNode t1, t2;
        split(root, pos, t1, t2);
        merge(t1, t1, new Node(v));
        merge(root, t1, t2);
    }

    void erase(int pos) {
        PNode t1, t2, t3;
        split(root, pos, t1, t2);
        split(t2, 1, t2, t3);
        if (t2) delete t2;
        merge(root, t1, t3);
    }

    void range_add(int l, int r, long long v) {
        PNode t1, t2, t3;
        split(root, l, t1, t2);
        split(t2, r - l + 1, t2, t3);
        apply_add(t2, v);
        merge(t2, t2, t3);
        merge(root, t1, t2);
    }

    void range_set(int l, int r, long long v) {
        PNode t1, t2, t3;
        split(root, l, t1, t2);
        split(t2, r - l + 1, t2, t3);
        apply_set(t2, v);
        merge(t2, t2, t3);
        merge(root, t1, t2);
    }

    void range_reverse(int l, int r) {
        PNode t1, t2, t3;
        split(root, l, t1, t2);
        split(t2, r - l + 1, t2, t3);
        apply_rev(t2);
        merge(t2, t2, t3);
        merge(root, t1, t2);
    }
    
    // Cut [l, r] and Paste before k
    void cut_and_paste(int l, int r, int k) {
        if (l == k) return;
        PNode t1, range, t2;
        split(root, l, t1, range);
        split(range, r - l + 1, range, t2);
        merge(root, t1, t2); 
        int new_k = (k > l) ? k - (r - l + 1) : k;
        PNode L, R;
        split(root, new_k, L, R);
        merge(L, L, range);
        merge(root, L, R);
    }

    void output(PNode t) {
        if (!t) return;
        push(t);
        output(t->l);
        cout << t->info.val << " ";
        output(t->r);
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    Treap tr;

    // {1, 2, 3, 4, 5}
    for(int i=0; i<5; ++i) tr.insert(i, i+1);

    tr.range_add(0, 4, 10); // {11, 12, 13, 14, 15}
    tr.range_set(2, 3, 5);  // {11, 12, 5, 5, 15}

    // Now query returns an object, so you can access whatever you need
    Info res = tr.query(1, 4); 
    cout << "Range [1, 4] -> Sum: " << res.sum << ", Min: " << res.mn << "\n";

    return 0;
}
