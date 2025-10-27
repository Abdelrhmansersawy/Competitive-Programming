// returns 0-based in-order index of node inside its treap, or -1 for nullptr
int get_node_index(PNode node){
    if (!node) return -1;
    int idx = sz(node->l);
    for (PNode p = node; p->par; p = p->par)
        if (p->par->r == p) idx += 1 + sz(p->par->l);
    return idx;
}
