/*
 * Explicit Treap with Parent Pointers
 * -----------------------------------
 * A randomized Binary Search Tree (Treap) implementation.
 * Features:
 * - Standard BST operations (Insert, Erase, Search) in O(log N)
 * - Order Statistics (K-th element, Rank of value) in O(log N)
 * - Direct Index Lookup: Find rank of any value in O(log N) using Map + Parent Pointers
 * - Range Operations: Split/Merge by rank or value
 * * Note: Uses std::map to maintain value-to-node mapping for O(1) node access.
 */

static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Node;
using PNode = Node*;
map<int, PNode> mp;

// Node structure: stores key, priority, size, children, and parent pointer
struct Node {
    int key, prior, size;
    Node *l = 0, *r = 0, *par = 0;
    Node(int v) : key(v), prior(rng()), size(1) { mp[key] = this; }
    ~Node() { if (mp.count(key) && mp[key] == this) mp.erase(key); }
};

// Returns the size of the subtree rooted at t (handles nullptr)
int sz(PNode t) { return t ? t->size : 0; }

// Updates the size of node t based on its children
void pull(PNode t) { if (t) t->size = sz(t->l) + 1 + sz(t->r); }

// Splits tree t into two trees: l (keys < key) and r (keys >= key)
void split(PNode t, PNode &l, PNode &r, int key) {
    if (!t) { l = r = NULL; return; }
    if (t->key < key) {
        split(t->r, t->r, r, key);
        if (t->r) t->r->par = t;
        l = t; pull(l);
        if (r) r->par = NULL;
    } else {
        split(t->l, l, t->l, key);
        if (t->l) t->l->par = t;
        r = t; pull(r);
        if (l) l->par = NULL;
    }
}

// Splits tree t into two trees: l (first k elements) and r (rest)
void split_k(PNode t, PNode &l, PNode &r, int k) {
    if (!t) { l = r = NULL; return; }
    int cur = sz(t->l);
    if (k <= cur) {
        split_k(t->l, l, t->l, k);
        if (t->l) t->l->par = t;
        r = t; pull(r);
        if (l) l->par = NULL;
    } else {
        split_k(t->r, t->r, r, k - cur - 1);
        if (t->r) t->r->par = t;
        l = t; pull(l);
        if (r) r->par = NULL;
    }
}

// Merges two trees l and r into t (all keys in l < all keys in r)
void merge(PNode &t, PNode l, PNode r) {
    if (!l || !r) t = l ? l : r;
    else if (l->prior > r->prior) {
        merge(l->r, l->r, r);
        if (l->r) l->r->par = l;
        t = l;
    } else {
        merge(r->l, l, r->l);
        if (r->l) r->l->par = r;
        t = r;
    }
    pull(t);
}

// Inserts a new value into the treap (if it doesn't already exist)
void insert(PNode &t, int val) {
    if (mp.count(val)) return;
    PNode l, r;
    split(t, l, r, val);
    merge(l, l, new Node(val));
    merge(t, l, r);
}

// Erases a value from the treap
void erase(PNode &t, int val) {
    PNode l, m, r;
    split(t, l, r, val);
    split(r, m, r, val + 1);
    if(m) delete m;
    merge(t, l, r);
}

// Returns the k-th smallest element (0-based index)
int get_kth(PNode t, int k) {
    if (!t) return -1;
    int cur = sz(t->l);
    if (k == cur) return t->key;
    if (k < cur) return get_kth(t->l, k);
    return get_kth(t->r, k - cur - 1);
}

// Returns the number of elements strictly less than val
int count_less(PNode t, int val) {
    if (!t) return 0;
    if (t->key >= val) return count_less(t->l, val);
    return sz(t->l) + 1 + count_less(t->r, val);
}

// Returns the 0-based index (rank) of a specific value using the map and parent pointers
int get_index_of(int val) {
    if (mp.find(val) == mp.end()) return -1;
    PNode curr = mp[val];
    int idx = sz(curr->l);
    while (curr->par) {
        PNode p = curr->par;
        if (p->r == curr) idx += sz(p->l) + 1;
        curr = p;
    }
    return idx;
}

// Insert val after the element at 0-based index k
// Note: Use with caution in Explicit Treap as it may break BST property if val is out of order
void insert_after(PNode &t, int k, int val) {
    PNode l, r;
    split_k(t, l, r, k + 1);
    merge(l, l, new Node(val));
    merge(t, l, r);
}

// Erase elements in 0-based index range [l_idx, r_idx]
void erase_range(PNode &t, int l_idx, int r_idx) {
    PNode l, m, r;
    split_k(t, l, r, r_idx + 1);
    split_k(l, l, m, l_idx);
    delete_tree(m);
    merge(t, l, r);
}

// Prints keys in strictly increasing order
void print(PNode t) {
    if (!t) return;
    print(t->l);
    cout << t->key << " ";
    print(t->r);
}
