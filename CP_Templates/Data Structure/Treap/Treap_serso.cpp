mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Node{
    Node *l, *r, *par;
    int prior;
    int key;
    bool is_rev;
    int sz;
    Node(int v) : l(nullptr), r(nullptr), par(nullptr), prior((int)rng()), key(v), is_rev(false), sz(1) {}
};
using PNode = Node*;

// --- helpers ---
inline int sz(PNode t)            { return t ? t->sz : 0; }
inline void set_parent(PNode c, PNode p){ if (c) c->par = p; }

void push(PNode t){
    if (!t || !t->is_rev) return;
    swap(t->l, t->r);
    if (t->l) t->l->is_rev ^= 1;
    if (t->r) t->r->is_rev ^= 1;
    t->is_rev = false;
}

void pull(PNode t){
    if (!t) return;
    t->sz = sz(t->l) + 1 + sz(t->r);
    // Update parent pointers for children during pull to ensure consistency
    set_parent(t->l, t);
    set_parent(t->r, t);
}

// --- split / merge ---
void split(PNode t, int k, PNode &l, PNode &r){
    if (!t) { l = r = nullptr; return; }
    push(t);
    if (sz(t->l) >= k){
        split(t->l, k, l, t->l);
        set_parent(t->l, t); // Update parent after recursive split returns
        r = t;
        set_parent(r, nullptr); // Root of this subtree has no parent yet
    } else {
        split(t->r, k - sz(t->l) - 1, t->r, r);
        set_parent(t->r, t);
        l = t;
        set_parent(l, nullptr);
    }
    pull(t);
}

void merge(PNode &t, PNode a, PNode b){
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
PNode kth(PNode t, int k){
    if (!t || k < 0 || k >= sz(t)) return nullptr;
    push(t);
    int ls = sz(t->l);
    if (k < ls) return kth(t->l, k);
    if (k == ls) return t;
    return kth(t->r, k - ls - 1);
}

// --- NEW FUNCTION IMPLEMENTATION ---
int get_index_of(PNode n) {
    if (!n) return -1;

    // 1. Trace up to find the path from node to root
    vector<PNode> path;
    PNode curr = n;
    while (curr) {
        path.push_back(curr);
        curr = curr->par;
    }

    // 2. Push lazy flags from Root down to Node
    // We iterate backwards through the path vector
    for (int i = (int)path.size() - 1; i >= 0; --i) {
        push(path[i]);
    }

    // 3. Calculate index using clean tree structure
    // Since we pushed, physical l/r matches logical l/r
    int idx = sz(n->l);
    while (n->par) {
        PNode p = n->par;
        if (p->r == n) {
            idx += sz(p->l) + 1;
        }
        n = p;
    }
    return idx;
}
// -----------------------------------

void insert_at(PNode &root, int pos, int v){
    PNode a = nullptr, b = nullptr;
    split(root, pos, a, b);
    PNode n = new Node(v);
    PNode tmp = nullptr;
    merge(tmp, a, n);
    merge(root, tmp, b);
}

void reverse_range(PNode &root, int L, int R){
    if (L > R) return;
    PNode a=nullptr, b=nullptr, c=nullptr;
    split(root, L, a, b);
    split(b, R - L + 1, b, c);
    if (b) b->is_rev ^= 1;
    PNode tmp = nullptr;
    merge(tmp, a, b);
    merge(root, tmp, c);
}
