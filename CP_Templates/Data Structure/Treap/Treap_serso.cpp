#include <bits/stdc++.h>
using namespace std;

// 0-based implicit treap (rope) — compact and readable for quick copy
// Node struct kept as requested.
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Node{
    Node *l, *r, *par;
    int prior;
    int key;
    bool is_rev;
    int sz;
    Node(int v) : l(nullptr), r(nullptr), par(nullptr), prior((int)rng()), key(v), is_rev(false), sz(1) {}
};
using P = Node*;

// --- helpers ---
inline int sz(P t)            { return t ? t->sz : 0; }
inline void set_parent(P c,P p){ if (c) c->par = p; }

void push(P t){
    if (!t || !t->is_rev) return;
    swap(t->l, t->r);
    if (t->l) t->l->is_rev ^= 1;
    if (t->r) t->r->is_rev ^= 1;
    t->is_rev = false;
}

void pull(P t){
    if (!t) return;
    t->sz = sz(t->l) + 1 + sz(t->r);
}

// --- split / merge ---
// split t into l (first k nodes) and r (rest)
void split(P t, int k, P &l, P &r){
    if (!t) { l = r = nullptr; return; }
    push(t);
    if (sz(t->l) >= k){
        split(t->l, k, l, t->l);
        set_parent(t->l, t);
        r = t;
        set_parent(r, nullptr);
    } else {
        split(t->r, k - sz(t->l) - 1, t->r, r);
        set_parent(t->r, t);
        l = t;
        set_parent(l, nullptr);
    }
    pull(t);
}

// merge a and b into t (t becomes root)
void merge(P &t, P a, P b){
    if (!a || !b){
        t = a ? a : b;
        set_parent(t, nullptr);
        return;
    }
    push(a); push(b);
    if (a->prior > b->prior){
        merge(a->r, a->r, b);
        set_parent(a->r, a);
        t = a;
        set_parent(t, nullptr);
    } else {
        merge(b->l, a, b->l);
        set_parent(b->l, b);
        t = b;
        set_parent(t, nullptr);
    }
    pull(t);
}

P kth(P t, int k){                 // return pointer to k-th (0-based) or nullptr
    if (!t || k < 0 || k >= sz(t)) return nullptr;
    push(t);
    int ls = sz(t->l);
    if (k < ls) return kth(t->l, k);
    if (k == ls) return t;
    return kth(t->r, k - ls - 1);
}

int get_val(P root, int pos){ P n = kth(root, pos); if(!n) throw out_of_range("get_val oob"); return n->key; }
void set_val(P root, int pos, int v){ P n = kth(root, pos); if(!n) throw out_of_range("set_val oob"); n->key = v; }

void insert_at(P &root, int pos, int v){
    P a = nullptr, b = nullptr;
    split(root, pos, a, b);
    P n = new Node(v);
    P tmp = nullptr;
    merge(tmp, a, n);
    merge(root, tmp, b);
}

void erase_at(P &root, int pos){
    P a=nullptr, b=nullptr, c=nullptr;
    split(root, pos, a, b);       // a: [0..pos-1], b: [pos..]
    split(b, 1, b, c);            // b: [pos], c: rest
    // free b
    function<void(P)> cleanup = [&](P x){
        if (!x) return;
        cleanup(x->l); cleanup(x->r);
        delete x;
    };
    cleanup(b);
    merge(root, a, c);
}

void erase_range(P &root, int L, int R){
    if (L > R) return;
    P a=nullptr, b=nullptr, c=nullptr;
    split(root, L, a, b);
    split(b, R - L + 1, b, c);
    function<void(P)> cleanup = [&](P x){
        if (!x) return;
        cleanup(x->l); cleanup(x->r);
        delete x;
    };
    cleanup(b);
    merge(root, a, c);
}

void reverse_range(P &root, int L, int R){
    if (L > R) return;
    P a=nullptr, b=nullptr, c=nullptr;
    split(root, L, a, b);
    split(b, R - L + 1, b, c);
    if (b) b->is_rev ^= 1;
    P tmp = nullptr;
    merge(tmp, a, b);
    merge(root, tmp, c);
}

// rotate left segment [L..R] by k (k can be >= length)
void rotate_left(P &root, int L, int R, long long k){
    if (L > R) return;
    int len = R - L + 1;
    if (len <= 1) return;
    k %= len; if (k < 0) k += len;
    if (k == 0) return;
    P a=nullptr, b=nullptr, c=nullptr;
    split(root, L, a, b);         // a | b(=segment+rest)
    split(b, len, b, c);          // b = segment
    P x=nullptr, y=nullptr;
    split(b, (int)k, x, y);       // x = first k, y = rest
    P merged = nullptr;
    merge(merged, y, x);          // rotated segment
    P tmp = nullptr;
    merge(tmp, a, merged);
    merge(root, tmp, c);
}

// rotate right by k => left by len-k
void rotate_right(P &root, int L, int R, long long k){
    if (L > R) return;
    int len = R - L + 1;
    if (len <= 1) return;
    k %= len; if (k < 0) k += len;
    if (k == 0) return;
    rotate_left(root, L, R, len - (k % len));
}

// build from vector (O(n log n) merges)
P build(const vector<int> &a){
    P root = nullptr;
    for (int v : a){
        P n = new Node(v);
        P tmp = nullptr;
        merge(tmp, root, n);
        root = tmp;
    }
    return root;
}

void to_vector(P t, vector<int> &out){
    if (!t) return;
    push(t);
    to_vector(t->l, out);
    out.push_back(t->key);
    to_vector(t->r, out);
}

P get_root(P x){ while (x && x->par) x = x->par; return x; }

void delete_all(P t){
    if (!t) return;
    delete_all(t->l);
    delete_all(t->r);
    delete t;
}

// optional debug print
void print_inorder(P root){
    vector<int> v;
    to_vector(root, v);
    for (size_t i = 0; i < v.size(); ++i){
        if (i) cout << ' ';
        cout << v[i];
    }
    cout << '\n';
}

// Example usage (uncomment in local testing)
/*
int main(){
    vector<int> a = {1,2,3,4,5};
    P root = build(a);
    rotate_left(root, 1, 4, 2); // rotate segment [1..4] left by 2
    print_inorder(root); // expected: 1 4 5 2 3
    delete_all(root);
    return 0;
}
*/

#include <bits/stdc++.h>
using namespace std;

// 0-based implicit treap (rope) — compact and readable for quick copy
// Node struct kept as requested.
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Node{
    Node *l, *r, *par;
    int prior;
    int key;
    bool is_rev;
    int sz;
    Node(int v) : l(nullptr), r(nullptr), par(nullptr), prior((int)rng()), key(v), is_rev(false), sz(1) {}
};
using P = Node*;

// --- helpers ---
inline int sz(P t)            { return t ? t->sz : 0; }
inline void set_parent(P c,P p){ if (c) c->par = p; }

void push(P t){
    if (!t || !t->is_rev) return;
    swap(t->l, t->r);
    if (t->l) t->l->is_rev ^= 1;
    if (t->r) t->r->is_rev ^= 1;
    t->is_rev = false;
}

void pull(P t){
    if (!t) return;
    t->sz = sz(t->l) + 1 + sz(t->r);
}

// --- split / merge ---
// split t into l (first k nodes) and r (rest)
void split(P t, int k, P &l, P &r){
    if (!t) { l = r = nullptr; return; }
    push(t);
    if (sz(t->l) >= k){
        split(t->l, k, l, t->l);
        set_parent(t->l, t);
        r = t;
        set_parent(r, nullptr);
    } else {
        split(t->r, k - sz(t->l) - 1, t->r, r);
        set_parent(t->r, t);
        l = t;
        set_parent(l, nullptr);
    }
    pull(t);
}

// merge a and b into t (t becomes root)
void merge(P &t, P a, P b){
    if (!a || !b){
        t = a ? a : b;
        set_parent(t, nullptr);
        return;
    }
    push(a); push(b);
    if (a->prior > b->prior){
        merge(a->r, a->r, b);
        set_parent(a->r, a);
        t = a;
        set_parent(t, nullptr);
    } else {
        merge(b->l, a, b->l);
        set_parent(b->l, b);
        t = b;
        set_parent(t, nullptr);
    }
    pull(t);
}

// --- basic operations ---
P kth(P t, int k){                 // return pointer to k-th (0-based) or nullptr
    if (!t || k < 0 || k >= sz(t)) return nullptr;
    push(t);
    int ls = sz(t->l);
    if (k < ls) return kth(t->l, k);
    if (k == ls) return t;
    return kth(t->r, k - ls - 1);
}

int get_val(P root, int pos){ P n = kth(root, pos); return n->key; }
void set_val(P root, int pos, int v){ P n = kth(root, pos); return n->key = v; }

void insert_at(P &root, int pos, int v){
    P a = nullptr, b = nullptr;
    split(root, pos, a, b);
    P n = new Node(v);
    P tmp = nullptr;
    merge(tmp, a, n);
    merge(root, tmp, b);
}

void erase_at(P &root, int pos){
    P a=nullptr, b=nullptr, c=nullptr;
    split(root, pos, a, b);       // a: [0..pos-1], b: [pos..]
    split(b, 1, b, c);            // b: [pos], c: rest
    // free b
    function<void(P)> cleanup = [&](P x){
        if (!x) return;
        cleanup(x->l); cleanup(x->r);
        delete x;
    };
    cleanup(b);
    merge(root, a, c);
}

void erase_range(P &root, int L, int R){
    if (L > R) return;
    P a=nullptr, b=nullptr, c=nullptr;
    split(root, L, a, b);
    split(b, R - L + 1, b, c);
    function<void(P)> cleanup = [&](P x){
        if (!x) return;
        cleanup(x->l); cleanup(x->r);
        delete x;
    };
    cleanup(b);
    merge(root, a, c);
}

void reverse_range(P &root, int L, int R){
    if (L > R) return;
    P a=nullptr, b=nullptr, c=nullptr;
    split(root, L, a, b);
    split(b, R - L + 1, b, c);
    if (b) b->is_rev ^= 1;
    P tmp = nullptr;
    merge(tmp, a, b);
    merge(root, tmp, c);
}

// rotate left segment [L..R] by k (k can be >= length)
void rotate_left(P &root, int L, int R, long long k){
    if (L > R) return;
    int len = R - L + 1;
    if (len <= 1) return;
    k %= len; if (k < 0) k += len;
    if (k == 0) return;
    P a=nullptr, b=nullptr, c=nullptr;
    split(root, L, a, b);         // a | b(=segment+rest)
    split(b, len, b, c);          // b = segment
    P x=nullptr, y=nullptr;
    split(b, (int)k, x, y);       // x = first k, y = rest
    P merged = nullptr;
    merge(merged, y, x);          // rotated segment
    P tmp = nullptr;
    merge(tmp, a, merged);
    merge(root, tmp, c);
}

// rotate right by k => left by len-k
void rotate_right(P &root, int L, int R, long long k){
    if (L > R) return;
    int len = R - L + 1;
    if (len <= 1) return;
    k %= len; if (k < 0) k += len;
    if (k == 0) return;
    rotate_left(root, L, R, len - (k % len));
}

// build from vector (O(n log n) merges)
P build(const vector<int> &a){
    P root = nullptr;
    for (int v : a){
        P n = new Node(v);
        P tmp = nullptr;
        merge(tmp, root, n);
        root = tmp;
    }
    return root;
}

void to_vector(P t, vector<int> &out){
    if (!t) return;
    push(t);
    to_vector(t->l, out);
    out.push_back(t->key);
    to_vector(t->r, out);
}

P get_root(P x){ while (x && x->par) x = x->par; return x; }

void delete_all(P t){
    if (!t) return;
    delete_all(t->l);
    delete_all(t->r);
    delete t;
}


