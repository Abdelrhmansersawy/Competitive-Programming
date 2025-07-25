#include <bits/stdc++.h>
using namespace std;

/*
 * ============================= LCA STRUCT =============================
 *
 * Purpose:
 *   - Preprocesses a tree for LCA (Lowest Common Ancestor) queries in O(log N).
 *   - Also supports computing distance between two nodes.
 *
 * Approach:
 *   - Binary lifting technique: up[k][v] stores the 2^k-th ancestor of node v.
 *   - Tree is traversed via DFS to fill depth and up tables.
 *
 * Time:
 *   - Preprocessing: O(N log N)
 *   - LCA Query: O(log N)
 *   - Distance Query: O(log N)
 * ======================================================================
 */
struct LCA {
    int N, LG;
    vector<int> depth;
    vector<vector<int>> up;  // up[k][v] = 2^k-th ancestor of v
    vector<vector<int>> adj;

    LCA(int n) : N(n), LG(32 - __builtin_clz(n)), depth(n), up(LG, vector<int>(n)), adj(n) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int v, int p) {
        up[0][v] = p;
        depth[v] = (p == -1 ? 0 : depth[p] + 1);
        for (int k = 1; k < LG; k++)
            up[k][v] = (up[k - 1][v] == -1 ? -1 : up[k - 1][up[k - 1][v]]);
        for (int to : adj[v])
            if (to != p)
                dfs(to, v);
    }

    void build(int root = 0) { dfs(root, -1); }

    int climb(int v, int k) {
        for (int i = 0; i < LG; i++)
            if (k >> i & 1)
                v = up[i][v];
        return v;
    }

    int lca(int a, int b) {
        if (depth[a] < depth[b]) swap(a, b);
        a = climb(a, depth[a] - depth[b]);
        if (a == b) return a;
        for (int k = LG - 1; k >= 0; k--)
            if (up[k][a] != up[k][b])
                a = up[k][a], b = up[k][b];
        return up[0][a];
    }

    int dist(int a, int b) {
        int c = lca(a, b);
        return depth[a] + depth[b] - 2 * depth[c];
    }
};

/*
 * ========================== DSU DIAMETER ROLLBACK ==========================
 *
 * Purpose:
 *   - A disjoint set union (Union-Find) with rollback support and diameter tracking.
 *
 * Core Idea:
 *   - Maintains the diameter of each component dynamically as unions happen.
 *   - Can rollback to a previous union state using a stack of history snapshots.
 *
 * Techniques:
 *   - Classic union by size.
 *   - For diameter update: consider the best diameter from both components
 *     and check all combinations between endpoints to find new diameter.
 *
 * Time:
 *   - Union: O(1) amortized + O(log N) for LCA operations
 *   - Rollback: O(1)
 *   - Diameter Query: O(1)
 * ===========================================================================
 */
struct DSUdiamRB {
    struct Hist {
        int ru, rv;
        int sz_ru_before;
        array<int, 2> ends_ru_before;
        int len_ru_before;
        bool merged;
        int prev_diam;
    };

    int mx_diam;

    vector<int> parent, sz;
    vector<array<int, 2>> ends;
    vector<int> len;
    LCA &lca;
    vector<Hist> stk;

    DSUdiamRB(int n, LCA &L) : parent(n), sz(n, 1), ends(n), len(n, 0), lca(L) {
        iota(parent.begin(), parent.end(), 0);
        for (int i = 0; i < n; i++) ends[i] = {i, i};
        mx_diam = 0;
    }

    int find(int x) {
        while (parent[x] != x) x = parent[x];
        return x;
    }

    void unite(int u, int v) {
        int ru = find(u), rv = find(v);
        if (ru == rv) {
            stk.push_back({});
            stk.back().merged = false;
            return;
        }

        if (sz[ru] < sz[rv]) swap(ru, rv), swap(u, v);

        stk.push_back({ru, rv, sz[ru], ends[ru], len[ru], true, mx_diam});

        parent[rv] = ru;
        sz[ru] += sz[rv];

        auto [a1, b1] = ends[ru];
        auto [a2, b2] = ends[rv];
        int bestLen = len[ru], bestA = a1, bestB = b1;

        if (len[rv] > bestLen) {
            bestLen = len[rv];
            bestA = a2;
            bestB = b2;
        }

        for (int x : {a1, b1}) {
            for (int y : {a2, b2}) {
                int cand = lca.dist(x, u) + 1 + lca.dist(v, y);
                if (cand > bestLen) {
                    bestLen = cand;
                    bestA = x;
                    bestB = y;
                }
            }
        }

        ends[ru] = {bestA, bestB};
        len[ru] = bestLen;
        mx_diam = max(mx_diam, bestLen);
    }

    void rollback() {
        if (stk.empty()) return;
        Hist h = stk.back();
        stk.pop_back();

        if (!h.merged) return;

        int ru = h.ru, rv = h.rv;
        parent[rv] = rv;
        mx_diam = h.prev_diam;
        sz[ru] = h.sz_ru_before;
        ends[ru] = h.ends_ru_before;
        len[ru] = h.len_ru_before;
    }

    int diameter(int x) {
        return len[find(x)];
    }
};

/*
 * ============================= MAIN FUNCTION =============================
 * Handles input/output for a basic interactive simulation.
 * ========================================================================
 */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    LCA lca(n);

    // Read tree edges
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        lca.addEdge(u, v);
    }

    lca.build();

    DSUdiamRB dsu(n, lca);

    while (q--) {
        string op;
        cin >> op;
        if (op == "union") {
            int u, v;
            cin >> u >> v;
            dsu.unite(u, v);
        } else if (op == "diam") {
            int x;
            cin >> x;
            cout << dsu.diameter(x) << '\n';
        } else if (op == "rollback") {
            dsu.rollback();
        }
    }

    return 0;
}
