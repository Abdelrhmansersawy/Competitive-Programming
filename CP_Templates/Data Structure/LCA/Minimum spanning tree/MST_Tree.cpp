/*
 Problem: MST + Binary Lifting (Max Edge on Path)
 Approach: DSU acts as the MST structure (no path compression) to allow
           O(log N) LCA and max-edge queries on the resulting tree.
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define rep(i, st, ed) for(int i = st; i < ed; i++)
#define all(v) v.begin(), v.end()
#define f first
#define s second

const int LOG = 20;

struct DSU {
    vector<int> par, sz, dep;
    // up[i][u]: 2^i-th ancestor of u
    // val[i][u]: Max edge weight on the path to the 2^i-th ancestor
    vector<int> up[LOG], val[LOG]; 
    int n;

    // Initializes DSU and Lifting tables.
    void init(int n) {
        this->n = n;
        par.resize(n); iota(all(par), 0);
        sz.assign(n, 1); dep.resize(n);
        rep(i, 0, LOG) { up[i].resize(n); val[i].resize(n); }
    }

    // Finds the root of 'a' and its depth in the DSU tree.
    // NOTE: Does NOT use path compression to preserve tree structure for LCA.
    pair<int, int> get(int a) { // {root, depth}
        if (par[a] == a) return {a, 0};
        auto p = get(par[a]); p.s++;
        return p;
    }

    // Unites two sets if they are different.
    // Stores the edge weight 'w' at the child node (par[a] = b).
    bool unite(int a, int b, int w) {
        a = get(a).f; b = get(b).f;
        if (a == b) return false;
        if (sz[a] > sz[b]) swap(a, b);
        
        par[a] = b; sz[b] += sz[a];
        val[0][a] = w; // Edge weight stored at child
        return true;
    }

    // Precomputes Binary Lifting tables (ancestors and max edge weights).
    // Must be called AFTER all unite operations are finished.
    void build() {
        rep(i, 0, n) {
            up[0][i] = par[i];
            dep[i] = get(i).s;
        }
        rep(j, 1, LOG) rep(i, 0, n) {
            up[j][i] = up[j - 1][up[j - 1][i]];
            val[j][i] = max(val[j - 1][i], val[j - 1][up[j - 1][i]]);
        }
    }

    // Returns the maximum edge weight on the path between u and v.
    // Uses Binary Lifting to ascend to the LCA. Complexity: O(log N).
    int query(int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);
        int mx = 0;
        
        // Lift u to same depth as v
        for (int j = LOG - 1; j >= 0; --j) {
            if (dep[u] - (1 << j) >= dep[v]) {
                mx = max(mx, val[j][u]);
                u = up[j][u];
            }
        }
        if (u == v) return mx;
        
        // Lift both until just below LCA
        for (int j = LOG - 1; j >= 0; --j) {
            if (up[j][u] != up[j][v]) {
                mx = max({mx, val[j][u], val[j][v]});
                u = up[j][u]; v = up[j][v];
            }
        }
        // Final check for the edges connecting to LCA
        return max({mx, val[0][u], val[0][v]});
    }
};

struct edge { int u, v, w; };

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    #endif

    int n, m; cin >> n >> m;
    vector<edge> e(m);
    rep(i, 0, m) {
        cin >> e[i].u >> e[i].v >> e[i].w;
        --e[i].u; --e[i].v;
    }

    sort(all(e), [](edge a, edge b) { return a.w < b.w; });

    DSU d; d.init(n);
    rep(i, 0, m) d.unite(e[i].u, e[i].v, e[i].w);
    
    d.build();
    
    // Example: Query max edge on path between 0 and n-1
    // cout << d.get_max_edge(0, n - 1) << endl;
}
