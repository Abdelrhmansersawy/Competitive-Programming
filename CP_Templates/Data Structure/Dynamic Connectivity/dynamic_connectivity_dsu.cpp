struct dsu_with_rollbacks {
    vector<int> par, sz;
    stack<array<int, 2>> history; // {u, v}, where u is child, v is parent
    int group;
    
    void init(int n) {
        group = n;
        par.resize(n);
        iota(par.begin(), par.end(), 0);
        sz.resize(n, 1);
    }
    
    int get(int u) {
        return (u == par[u]) ? u : get(par[u]);
    }
    
    bool unite(int u, int v) {
        u = get(u); v = get(v);
        if (u == v) return false;
        
        if (sz[u] > sz[v]) swap(u, v);
        history.push({u, v});
        par[u] = v;
        sz[v] += sz[u]; 
        --group;
        return true;
    }
    
    void roll_back() {
        if (history.empty()) return;
        auto [u, v] = history.top(); history.pop();
        par[u] = u;
        sz[v] -= sz[u]; 
        ++group;
    }
};

struct query {
    int u, v;
    bool united;
    query() {}
    query(int u, int v) : u(u), v(v), united(false) {}
};

struct QueryTree {
    vector<vector<query>> tree;
    vector<int> ans;
    int n; // size of time interval of query
    dsu_with_rollbacks dsu;
    
    void init(int n, int m) {
        this->n = n;
        tree.resize(4 * n);
        ans.resize(n);
        dsu.init(m); // size of nodes in dsu
    }
    
    void add_to_tree(query &q, int lx, int rx, int x, int l, int r) {
        if (rx <= l || lx >= r) return; 
        if (lx <= l && rx >= r) { 
            tree[x].push_back(q);
            return;
        }
        int mid = (l + r) / 2;
        add_to_tree(q, lx, rx, 2 * x + 1, l, mid);
        add_to_tree(q, lx, rx, 2 * x + 2, mid, r);
    }
    
    void add_to_tree(query q, int l, int r) {
        add_to_tree(q, l, r, 0, 0, n);
    }
    
    void dfs(int x, int l, int r) {
        for (auto &q : tree[x]) {
            q.united = dsu.unite(q.u, q.v);
        }
        
        if (r - l == 1) {
            ans[l] = dsu.group;
        } else {
            int mid = (l + r) / 2;
            dfs(2 * x + 1, l, mid);
            dfs(2 * x + 2, mid, r);
        }
        
        for (auto it = tree[x].rbegin(); it != tree[x].rend(); ++it) {
            if (it->united) {
                dsu.roll_back();
            }
        }
    }
    
    vector<int> solve() {
        dfs(0, 0, n);
        return ans;
    }
};
