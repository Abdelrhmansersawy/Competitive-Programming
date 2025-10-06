/*
 * ===================== KUHN (DFS) BIPARTITE MATCHING =====================
 *
 * Usage:
 *   Kuhn solver(n, m);
 *   solver.add_edge(u, v); // 0-based
 *   int matching = solver.max_matching();
 *   // solver.matchL[u] = matched v or -1
 *   // solver.matchR[v] = matched u or -1
 *
 * Time complexity:
 *   Worst-case O(V * E) but in practice fast for many graphs.

 * ==========================================================================
 */

struct Kuhn {
    int n, m;                        // sizes: left = n, right = m
    vector<vector<int>> g;           // adjacency: left u -> list of right vertices v
    vector<int> matchL, matchR;      // matchL[u] = v (or -1), matchR[v] = u (or -1)
    vector<int> seen;                // seen[v] holds timestamp when visited
    int seen_id = 1;                 // increment per DFS call

    Kuhn(int _n = 0, int _m = 0) { init(_n, _m); }

    void init(int _n, int _m) {
        n = _n; m = _m;
        g.assign(n, {});
        matchL.assign(n, -1);
        matchR.assign(m, -1);
        seen.assign(m, 0);
        seen_id = 1;
    }

    void add_edge(int u, int v) {
        g[u].push_back(v);
    }

private:
    bool dfs(int u) {
        for (int v : g[u]) {
            if (seen[v] == seen_id) continue;
            seen[v] = seen_id;
            if (matchR[v] == -1 || dfs(matchR[v])) {
                matchR[v] = u;
                matchL[u] = v;
                return true;
            }
        }
        return false;
    }

public:
    // public wrapper that main can call
    bool try_kuhn(int u) {
        if (matchL[u] != -1) return false; // already matched — no new augment
        ++seen_id;
        return dfs(u);
    }

    int max_matching(){
        int ans = 0;
        for(int i = 0; i < n; ++i) ans += try_kuhn(i);
        return ans;
    }
};
