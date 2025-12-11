struct DSU {
    vector<int> par, sz;
    vector<pair<int, int>> history; // Stores {child, parent}

    DSU(int n) : par(n + 1), sz(n + 1, 1) {
        iota(par.begin(), par.end(), 0);
    }

    int find(int i) {
        return (i == par[i]) ? i : find(par[i]); // No Path Compression
    }

    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);

        if (root_i == root_j) {
            history.push_back({-1, -1}); // 1. Push dummy state
            return false;
        }

        if (sz[root_i] < sz[root_j]) swap(root_i, root_j);
        
        sz[root_i] += sz[root_j];
        par[root_j] = root_i;
        history.push_back({root_j, root_i}); // 2. Push actual state
        return true;
    }

    void rollback() {
        auto [child, parent] = history.back();
        history.pop_back();

        if (child == -1) return; // 3. Check for dummy

        sz[parent] -= sz[child];
        par[child] = child;
    }
};
