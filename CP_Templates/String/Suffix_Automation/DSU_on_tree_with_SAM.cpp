// ------------------------- DSU on Tree (Big-Child Keep for SAM) -------------------------
//
// We build the suffix automaton, then construct its link tree.
// Each node in the link tree corresponds to a SAM state.
// We'll run DSU-on-tree (Sack technique) to process queries on subtrees.
//
// Key points for SAM:
// - Each state has `first_pos`. For clones, this may duplicate → skip clones!
// - So in add/remove, check `if (!st[u].is_clone)` before using first_pos.
// - Queries attached to SAM nodes are answered during `calc(u)`.
//
// -------------------------------------------------------------------------------


int tin[MAXN], tout[MAXN], ver[MAXN], subsz[MAXN], bigChild[MAXN];
int dfs_timer = 0;

void preDFS(int u, int p) {
    tin[u] = dfs_timer++;
    ver[tin[u]] = u;
    subsz[u] = 1;
    bigChild[u] = -1;
    for (auto v : adj[u]) if (v != p) {
        preDFS(v, u);
        subsz[u] += subsz[v];
        if (bigChild[u] == -1 || subsz[v] > subsz[ bigChild[u] ]) bigChild[u] = v;
    }
    tout[u] = dfs_timer;
}

void insert(int pos) {
    // TODO: implement insertion action (e.g., update a freq Fenwick/segment tree)
    (void)pos;
}
void erase_pos(int pos) {
    // TODO: implement erase action
    (void)pos;
}

void add_node(int u) {
    if (!st[u].is_clone) insert(st[u].first_pos);
}
void remove_node(int u) {
    if (!st[u].is_clone) erase_pos(st[u].first_pos);
}

void dfs_sack(int u, int p, bool keep) {
    // process all light children
    for (auto v : adj[u]) if (v != p && v != bigChild[u])
        dfs_sack(v, u, 0);

    // process big child (kept data)
    if (bigChild[u] != -1) dfs_sack(bigChild[u], u, 1);

    // merge small children into big child’s data
    for (auto v : adj[u]) if (v != p && v != bigChild[u]) {
        for (int i = tin[v]; i < tout[v]; i++) {
            int node = ver[i];
            add_node(node);
        }
    }

    // add current node itself
    add_node(u);

    // answer queries attached to u
    // (user should add code here)

    // clear if not keeping
    if (!keep) {
        for (int i = tin[u]; i < tout[u]; i++) {
            int node = ver[i];
            remove_node(node);
        }
    }
}
