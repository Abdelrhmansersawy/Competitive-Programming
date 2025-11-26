static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// treap node: key, heap-priority, subtree size, left/right children
struct Node {
    int key, prior, size;
    Node *l, *r;
    Node(int v) : key(v), prior(rng()), size(1), l(NULL), r(NULL) {}
};
using PNode = Node*;

// sz(t): return subtree size (0 if null)
int sz(PNode t) { return t ? t->size : 0; }

// pull(t): recalc t->size from children
void pull(PNode t) {
    if (t) t->size = sz(t->l) + 1 + sz(t->r);
}

// split(t,l,r,key): split t into l (<key) and r (>=key)
void split(PNode t, PNode &l, PNode &r, int key) {
    if (!t) l = r = NULL;
    else if (t->key < key) split(t->r, t->r, r, key), l = t;
    else split(t->l, l, t->l, key), r = t;
    pull(t);
}

// merge(t,l,r): merge BSTs l and r into t (respect priorities)
void merge(PNode &t, PNode l, PNode r) {
    if (!l || !r) t = l ? l : r;
    else if (l->prior > r->prior) merge(l->r, l->r, r), t = l;
    else merge(r->l, l, r->l), t = r;
    pull(t);
}

// split_range(root,l,r): return {<l, [l..r], >r} parts of root by index/key
array<PNode, 3> split_range(PNode& root , int l , int r){
    PNode a,b,c;
    split(root , a , b , l);
    split(b , b , c , r+1);
    return {a,b,c};
}

// get_kth(t, k): return the k-th smallest key (0-based index)
// k should be in range [0, sz(t)-1]
int get_kth(PNode t, int k) {
    if (!t) return -1; // Error or empty
    int current_rank = sz(t->l);
    
    if (k == current_rank) return t->key;
    if (k < current_rank) return get_kth(t->l, k);
    
    return get_kth(t->r, k - current_rank - 1);
}

// insert a value
void insert(PNode &t, int val) {
    PNode l, r;
    split(t, l, r, val);
    merge(l, l, new Node(val));
    merge(t, l, r);
}

// erase a value
void erase(PNode &t, int val) {
    PNode l, m, r;
    split(t, l, r, val);
    split(r, m, r, val + 1);
    delete m; // Free memory
    merge(t, l, r);
}
