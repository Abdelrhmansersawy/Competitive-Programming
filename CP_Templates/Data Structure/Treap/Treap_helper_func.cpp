// returns 0-based in-order index of node inside its treap, or -1 for nullptr
int get_node_index(PNode node){
    if (!node) return -1;
    int idx = sz(node->l);
    for (PNode p = node; p->par; p = p->par)
        if (p->par->r == p) idx += 1 + sz(p->par->l);
    return idx;
}

// get the root of a node
PNode get_root(PNode x){ while (x && x->par) x = x->par; return x; }


// return pointer to k-th (0-based) or nullptr
PNode kth(PNode t, int k){                 
    if (!t || k < 0 || k >= sz(t)) return nullptr;
    push(t);
    int ls = sz(t->l);
    if (k < ls) return kth(t->l, k);
    if (k == ls) return t;
    return kth(t->r, k - ls - 1);
}

// Split treap `t` into `l` (orig <= key) and `r` (orig > key).
// NOTE: `orig` must be sorted (BST property).
void split_by_orig(PNode t, int orig, PNode &l, PNode &r){
    if (!t) { l = r = nullptr; return; }
    push(t);
    if (t->orig <= orig){
        split_by_orig(t->r, orig, t->r, r);
        set_parent(t->r, t);
        l = t;
        set_parent(l, nullptr);
    } else {
        split_by_orig(t->l, orig, l, t->l);
        set_parent(t->l, t);
        r = t;
        set_parent(r, nullptr);
    }
    pull(t);
}


// rotate left segment [L..R] by k (k can be >= length)
void rotate_left(PNode &root, int L, int R, long long k){
    if (L > R) return;
    int len = R - L + 1;
    if (len <= 1) return;
    k %= len; if (k < 0) k += len;
    if (k == 0) return;
    PNode a=nullptr, b=nullptr, c=nullptr;
    split(root, L, a, b);         // a | b(=segment+rest)
    split(b, len, b, c);          // b = segment
    PNode x=nullptr, y=nullptr;
    split(b, (int)k, x, y);       // x = first k, y = rest
    PNode merged = nullptr;
    merge(merged, y, x);          // rotated segment
    PNode tmp = nullptr;
    merge(tmp, a, merged);
    merge(root, tmp, c);
}

// rotate right by k => left by len-k
void rotate_right(PNode &root, int L, int R, long long k){
    if (L > R) return;
    int len = R - L + 1;
    if (len <= 1) return;
    k %= len; if (k < 0) k += len;
    if (k == 0) return;
    rotate_left(root, L, R, len - (k % len));
}
