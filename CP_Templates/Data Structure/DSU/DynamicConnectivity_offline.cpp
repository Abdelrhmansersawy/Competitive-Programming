int ans;

struct Query {
    int u, v;   // Vertices to connect
    int l, r;   // Time interval [l,r] when edge exists (in case large time use compression)
};

struct Elem {
    int u;      // Parent vertex
    int v;      // Child vertex being attached
    int szU;    // Original size of set u
    int cnt;    // Previous count of disjoint sets
};

struct DSURollback {
    int cnt;
    int currentTime = 0;  // initialized
    stack<Elem> st;
    vector<int> sz, par;
    vector<vector<pair<int, int>>> g;
    
    DSURollback(int n) : cnt(n), currentTime(0) {  // initialized in constructor
        int seg = 1;
        while (seg < n) seg *= 2;
        g.resize(2 * seg + 5);
        par.resize(n + 1);
        sz.resize(n + 1, 1);
        iota(par.begin(), par.end(), 0);
    }
    
    int findSet(int u) { return par[u] == u ? u : findSet(par[u]); }
    
    void update(int u, int v) {
        st.push({u, v, sz[u], cnt});
        cnt--, par[v] = u;
        sz[u] += sz[v];
        ans = max(ans, currentTime);  // using tracked time
    }
    
    void unionSet(int u, int v) {
        u = findSet(u), v = findSet(v);
        if (u != v) {
            if (sz[u] < sz[v]) swap(u, v);
            update(u, v);
        }
    }
    
    void rollback(int x) {
        while (st.size() > x) {
            auto e = st.top(); st.pop();
            cnt = e.cnt;
            sz[e.u] = e.szU;
            par[e.v] = e.v;
        }
    }
    
    void traverse(int x, int lX, int rX, const int &l, const int &r, const int &u, const int &v) {
        if (rX < l || lX > r) return;
        if (lX >= l && rX <= r) { g[x].emplace_back(u, v); return; }
        int m = (lX + rX) / 2;
        traverse(x * 2, lX, m, l, r, u, v);
        traverse(x * 2 + 1, m + 1, rX, l, r, u, v);
    }
    
    void solve(int x, int l, int r) {
        int cur = st.size();
        currentTime = l;  // updating current time
        for (auto &i : g[x]) unionSet(i.first, i.second);
        if (l == r) { rollback(cur); return; }
        int m = (l + r) / 2;
        solve(x * 2, l, m);
        solve(x * 2 + 1, m + 1, r);
        rollback(cur);
    }
    
    void build(vector<Query> &queries) {
        for (auto &q : queries) traverse(1, 0, cnt - 1, q.l, q.r, q.u, q.v);
        solve(1, 0, cnt - 1);
    }
};
