const int N = 1e5 + 10 , LOG = 20;
vector<int> adj[N];
struct lca{
    int n;
    vector<int> depth , parent[LOG];
    void init(int n , int root = 0){
        this->n = n;
        depth.resize(n);
        for(int i = 0; i < LOG; ++i) parent[i].resize(n);
        dfs(root , root , 0);
    }
    void dfs(int u, int p, int d) {
        depth[u] = d;
        parent[0][u] = p;
        for (int i = 1; i < LOG; ++i) {
            parent[i][u] = parent[i - 1][parent[i - 1][u]];
        }
        for (int v : adj[u]) {
            if (v == p) continue;
            dfs(v, u, d + 1);
        }
    }
    int kth_ancestor(int u, int k) {
        for (int i = 0; i < LOG; ++i) {
            if ((1 << i) & k) {
                u = parent[i][u];
            }
        }
        return u;
    }
    int LCA(int u, int v) {
        if (depth[u] > depth[v]) swap(u, v);
        int k = depth[v] - depth[u];
        v = kth_ancestor(v, depth[v] - depth[u]);
        if (u == v) return u;

        for (int i = LOG - 1; ~i; --i) {
            if (parent[i][u] != parent[i][v]) {
                u = parent[i][u];
                v = parent[i][v];
            }
        }
        assert(parent[0][u] == parent[0][v]); 
        return parent[0][u];
    }
};

