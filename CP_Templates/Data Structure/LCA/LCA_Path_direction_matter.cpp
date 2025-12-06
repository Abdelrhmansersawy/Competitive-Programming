struct BinaryLifting {
    int N, LOG;
    vector<int> depth;
    vector<vector<int>> up;
    vector<vector<Node>> go_up, go_down;

    BinaryLifting(vector<vector<int>>& adj, vector<int>& init) 
        : N(adj.size()), LOG(3), depth(N), up(N, vector<int>(LOG)), 
          go_up(N, vector<Node>(LOG)), go_down(N, vector<Node>(LOG)) 
    {
        dfs(0, 0, adj, init);
        for (int j = 1; j < LOG; ++j) {
            for (int i = 0; i < N; ++i) {
                int p = up[i][j-1];
                up[i][j] = up[p][j-1];
                go_up[i][j] = go_up[i][j-1] + go_up[p][j-1];
                go_down[i][j] = go_down[p][j-1] + go_down[i][j-1];
            }
        }
    }

    void dfs(int u, int p, vector<vector<int>>& adj, vector<int>& init) {
        depth[u] = (u == p ? 0 : depth[p] + 1);
        up[u][0] = p;
        go_up[u][0] = go_down[u][0] = Node(init[u]);
        for (int v : adj[u]) if (v != p) dfs(v, u, adj, init);
    }

    int get_lca(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        for (int j = LOG - 1; j >= 0; --j)
            if (depth[u] - (1 << j) >= depth[v]) u = up[u][j];
        if (u == v) return u;
        for (int j = LOG - 1; j >= 0; --j)
            if (up[u][j] != up[v][j]) u = up[u][j], v = up[v][j];
        return up[u][0];
    }

    Node query_up(int u, int k) {
        Node res;
        for (int j = 0; k > 0; ++j) {
            if ((k >> j) & 1) {
                res = res + go_up[u][j];
                u = up[u][j];
                k ^= (1 << j);
            }
        }
        return res;
    }

    Node query_down(int v, int k) {
        Node res;
        for (int j = 0; k > 0; ++j) {
            if ((k >> j) & 1) {
                // Prepend higher segment: (Top -> Bottom)
                res = go_down[v][j] + res;
                v = up[v][j];
                k ^= (1 << j);
            }
        }
        return res;
    }

    Node query(int u, int v) {
        int l = get_lca(u, v);
        // u -> lca (inclusive) + lca -> v (exclusive)
        return query_up(u, depth[u] - depth[l] + 1) + query_down(v, depth[v] - depth[l]);
    }
};
