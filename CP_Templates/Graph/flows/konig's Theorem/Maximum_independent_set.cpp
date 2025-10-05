#include <bits/stdc++.h>
using namespace std;

/*
 * ===================== MAXIMUM INDEPENDENT SET (BIPARTITE GRAPH) =====================
 *
 * Problem:
 *   Given a bipartite graph G = (L, R, E),
 *   find the Maximum Independent Set (MIS) and Minimum Vertex Cover (MVC).
 *
 * Key Theorem (Kőnig’s Theorem):
 *   In any bipartite graph:
 *       |Maximum Matching| = |Minimum Vertex Cover|
 *       |MIS| = |V| - |MVC|
 *
 * Algorithm Overview:
 *   1️Use Hopcroft–Karp (O(E * sqrt(V))) to find Maximum Matching.
 *   2️Perform alternating DFS starting from unmatched Left vertices:
 *       - Traverse non-matching edges Left → Right.
 *       - Traverse matching edges Right → Left.
 *   3️Construct:
 *       - MIS = (L ∩ visL) ∪ (R \ visR)
 *       - MVC = (L \ visL) ∪ (R ∩ visR)
 *
 * Outputs:
 *   - All indices (or vertices) belonging to MIS (kept)
 *   - All indices belonging to MVC (removed)
 *
 * -----------------------------------------------------------------------------
 * TIME COMPLEXITY:
 *   Hopcroft–Karp:   O(E * sqrt(V))
 *   Alternating DFS: O(V + E)
 *   Total:           O(E * sqrt(V))
 *
 * SPACE COMPLEXITY:
 *   O(V + E)
 * =============================================================================
 */

struct BipartiteMIS {
    int L, R; // number of vertices on each side
    vector<vector<int>> g;
    vector<int> matchL, matchR, dist;
    vector<int> visL, visR;

    BipartiteMIS(int _L, int _R) : L(_L), R(_R) {
        g.assign(L, {});
        matchL.assign(L, -1);
        matchR.assign(R, -1);
        dist.assign(L, -1);
        visL.assign(L, 0);
        visR.assign(R, 0);
    }

    // Add edge u ∈ L → v ∈ R
    void add_edge(int u, int v) {
        g[u].push_back(v);
    }

    // ------------------- Hopcroft–Karp -------------------
    bool bfs() {
        queue<int> q;
        bool found = false;
        for (int i = 0; i < L; ++i) {
            if (matchL[i] == -1)
                dist[i] = 0, q.push(i);
            else
                dist[i] = -1;
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

    int max_matching() {
        int flow = 0;
        while (bfs())
            for (int i = 0; i < L; ++i)
                if (matchL[i] == -1 && dfs(i))
                    ++flow;
        return flow;
    }

    // ------------------- Alternating Reachability -------------------
    void dfs_alt(int u) {
        if (visL[u]) return;
        visL[u] = 1;
        for (int v : g[u]) {
            if (matchL[u] == v) continue; // skip matched edge
            if (!visR[v]) {
                visR[v] = 1;
                if (matchR[v] != -1)
                    dfs_alt(matchR[v]);
            }
        }
    }

    // ------------------- Compute MIS & MVC -------------------
    pair<vector<pair<int,int>>, vector<pair<int,int>>> solve() {
        max_matching();

        fill(visL.begin(), visL.end(), 0);
        fill(visR.begin(), visR.end(), 0);

        // Start DFS from unmatched left vertices
        for (int i = 0; i < L; ++i)
            if (matchL[i] == -1)
                dfs_alt(i);

        vector<pair<int,int>> MIS, MVC;
        for (int i = 0; i < L; ++i)
            if (visL[i]) MIS.push_back({0, i});
            else MVC.push_back({0, i});
        for (int j = 0; j < R; ++j)
            if (!visR[j]) MIS.push_back({1, j});
            else MVC.push_back({1, j});
        return {MIS, MVC};
    }
};

// ==========================================================================

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Example: bipartite graph with L = {0,1,2}, R = {0,1,2}
    BipartiteMIS G(3, 3);
    G.add_edge(0, 0);
    G.add_edge(0, 1);
    G.add_edge(1, 1);
    G.add_edge(2, 2);

    auto [MIS, MVC] = G.solve();

    cout << "=== Maximum Independent Set ===\n";
    cout << MIS.size() << " nodes\n";
    for (auto [side, id] : MIS)
        cout << (side == 0 ? "L" : "R") << id << ' ';
    cout << "\n\n";

    cout << "=== Minimum Vertex Cover (Removed) ===\n";
    cout << MVC.size() << " nodes\n";
    for (auto [side, id] : MVC)
        cout << (side == 0 ? "L" : "R") << id << ' ';
    cout << '\n';
}
