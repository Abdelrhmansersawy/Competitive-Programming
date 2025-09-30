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

int st[MAXN], ft[MAXN], ver[MAXN], sz[MAXN], big[MAXN];
int dfs_timer = 0;

void preDFS(int u, int p) {
    st[u] = dfs_timer++;
    ver[st[u]] = u;
    sz[u] = 1;
    big[u] = -1;
    for (auto v : adj[u]) if (v != p) {
        preDFS(v, u);
        sz[u] += sz[v];
        if (big[u] == -1 || sz[v] > sz[ big[u] ]) big[u] = v;
    }
    ft[u] = dfs_timer;
}

// user-defined actions (specific to SAM problem)
void add_node(int u) {
    if (!st[u].is_clone) insert(st[u].first_pos);
}
void remove_node(int u) {
    if (!st[u].is_clone) erase(st[u].first_pos);
}

void dfs_sack(int u, int p, bool keep) {
    // process all light children
    for (auto v : adj[u]) if (v != p && v != big[u])
        dfs_sack(v, u, 0);

    // process big child (kept data)
    if (big[u] != -1) dfs_sack(big[u], u, 1);

    // merge small children into big child’s data
    for (auto v : adj[u]) if (v != p && v != big[u]) {
        for (int i = st[v]; i < ft[v]; i++) {
            int node = ver[i];
            add_node(node);
        }
    }

    // add current node itself
    add_node(u);

    // answer queries attached to u
    

    // clear if not keeping
    if (!keep) {
        for (int i = st[u]; i < ft[u]; i++) {
            int node = ver[i];
            remove_node(node);
        }
    }
}
