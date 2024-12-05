#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 9;

vector<pair<int,int>> adj[N];
int heavy[N], head[N], par[N], pos[N], dep[N], sz[N], cur_pos, n;
vector<int> values;

int dfs(int u = 0) {
    heavy[u] = -1;
    sz[u] = 1;
    int max_size = 0;
    for(auto &[v, w] : adj[u]) if(v != par[u]) {
        par[v] = u;
        dep[v] = dep[u] + 1;
        int cur = dfs(v);
        if(cur > max_size) {
            heavy[u] = v;
            max_size = cur;
        }
        sz[u] += cur;
    }
    return sz[u];
}

void decomposition(int u = 0, int h = 0) {
    head[u] = h;
    pos[u] = cur_pos++;
    if(~heavy[u])
        decomposition(heavy[u], h);
    for(auto &[v, w] : adj[u]) if(v != par[u] && v != heavy[u])
        decomposition(v, v);
}

void buildWeightArray() {
    values.resize(n);
    for(int u = 0; u < n; u++) {
        for(auto [v, w] : adj[u]) {
            if(dep[u] < dep[v]) {
                values[pos[v]] = w;
            }
        }
    }
}

int queryPath(int u, int v) {
    int ans = -1e9;
    for(; head[u] != head[v]; v = par[head[v]]) {
        if(dep[head[u]] > dep[head[v]]) swap(u,v);
        // process range [pos[head[v]], pos[v]]
    }   
    if(dep[u] > dep[v]) swap(u,v);
    if(u != v) {
        // process range [pos[u] + 1, pos[v]]
    }
    return ans;
}

// Range to query: [pos[u] + 1, pos[u] + sz[u] - 1]
int querySubtree(int u) {
    // process range [pos[u] + 1, pos[u] + sz[u] - 1]
    return 0;  // replace with actual query
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int m, q; cin >> n >> m >> q;
    
    for(int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        --u; --v;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    
    dfs();
    decomposition();
    buildWeightArray();
}
