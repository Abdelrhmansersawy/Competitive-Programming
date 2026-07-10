const int N = 1e5 + 10, LOG = 20;
vector<int> adj[N];

struct LCA {
    int n;
    vector<int> depth;
    vector<array<int, LOG>> parent;

    void init(int n, int root = 0) {
        this->n = n;
        depth.resize(n);
        parent.resize(n);
        dfs(root, root, 0);
    }

    void dfs(int u, int p, int d) {
        depth[u] = d;
        parent[u][0] = p;

        for (int x = 1; x < LOG; ++x)
            parent[u][x] = parent[parent[u][x - 1]][x - 1];

        for (int v : adj[u]) {
            if (v == p) continue;
            dfs(v, u, d + 1);
        }
    }

    int kth_ancestor(int u, int k) {
        for (int x = 0; x < LOG; ++x) {
            if (k >> x & 1)
                u = parent[u][x];
        }
        return u;
    }

    int lca(int u, int v) {
        if (depth[u] > depth[v]) swap(u, v);

        v = kth_ancestor(v, depth[v] - depth[u]);

        if (u == v) return u;

        for (int x = LOG - 1; x >= 0; --x) {
            if (parent[u][x] != parent[v][x]) {
                u = parent[u][x];
                v = parent[v][x];
            }
        }

        return parent[u][0];
    }
};
