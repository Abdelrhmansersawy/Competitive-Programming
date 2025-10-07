#include <bits/stdc++.h>
using namespace std;

/*
 * ===================== HOPCROFT–KARP MAXIMUM MATCHING =====================
 *
 * Problem:
 *   Given a bipartite graph G = (L, R, E),
 *   find the maximum matching — the largest set of edges
 *   such that no two share a common endpoint.
 *
 * Algorithm (Hopcroft–Karp):
 *   1. BFS builds level graph from unmatched Left vertices.
 *   2. DFS augments along shortest alternating paths.
 *   3. Repeat until no augmenting path exists.
 *
 * Time Complexity:
 *   O(E * sqrt(V))
 *
 * Space Complexity:
 *   O(V + E)
 *
 * Usage:
 *   HopcroftKarp G(L, R);
 *   G.add_edge(u, v);
 *   int res = G.max_matching();
 *
 * --------------------------------------------------------------------------
 * Notes:
 *   - L: number of vertices on left side
 *   - R: number of vertices on right side
 *   - Left vertices indexed [0 .. L-1]
 *   - Right vertices indexed [0 .. R-1]
 *   - Matching result: matchL[u] = v, matchR[v] = u (or -1 if unmatched)
 * ==========================================================================
 */

struct HopcroftKarp {
    int L, R; // number of vertices on each side
    vector<vector<int>> g;
    vector<int> matchL, matchR, dist;

    HopcroftKarp(int _L, int _R) : L(_L), R(_R) {
        g.assign(L, {});
        matchL.assign(L, -1);
        matchR.assign(R, -1);
        dist.assign(L, -1);
    }

    // Add edge u ∈ L → v ∈ R
    void add_edge(int u, int v) {
        g[u].push_back(v);
    }

    // ------------------- BFS: Build level graph -------------------
    bool bfs() {
        queue<int> q;
        bool found = false;

        for (int u = 0; u < L; ++u) {
            if (matchL[u] == -1)
                dist[u] = 0, q.push(u);
            else
                dist[u] = -1;
        }

        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : g[u]) {
                int nxt = matchR[v];
                if (nxt == -1) found = true;
                else if (dist[nxt] == -1)
                    dist[nxt] = dist[u] + 1, q.push(nxt);
            }
        }
        return found;
    }

    // ------------------- DFS: Find augmenting paths -------------------
    bool dfs(int u) {
        for (int v : g[u]) {
            int nxt = matchR[v];
            if (nxt == -1 || (dist[nxt] == dist[u] + 1 && dfs(nxt))) {
                matchL[u] = v;
                matchR[v] = u;
                return true;
            }
        }
        dist[u] = -1;
        return false;
    }

    // ------------------- Main matching function -------------------
    int max_matching() {
        int flow = 0;
        while (bfs())
            for (int u = 0; u < L; ++u)
                if (matchL[u] == -1 && dfs(u))
                    ++flow;
        return flow;
    }
};

// ==========================================================================

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Example: bipartite graph L = {0,1,2}, R = {0,1,2}
    HopcroftKarp G(3, 3);
    G.add_edge(0, 0);
    G.add_edge(0, 1);
    G.add_edge(1, 1);
    G.add_edge(2, 2);

    int res = G.max_matching();
    cout << "Maximum Matching = " << res << "\n";

    cout << "Matched pairs (L->R):\n";
    for (int u = 0; u < G.L; ++u)
        if (G.matchL[u] != -1)
            cout << "L" << u << " -> R" << G.matchL[u] << "\n";
}
