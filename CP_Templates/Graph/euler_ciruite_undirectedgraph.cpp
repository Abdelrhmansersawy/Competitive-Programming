/*
    Eulerian Circuit is an Eulerian Path that starts and ends on the same vertex.

    This solves the "mail delivery" problem: find a route starting and ending at crossing 1
    that uses every undirected street exactly once.

    Conditions for an undirected graph:
      1. Every vertex with non-zero degree is connected to the start (crossing 1).
      2. All vertices have even degree.

    If no solution, prints "IMPOSSIBLE".
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i, st, ed) for (int i = st; i < ed; i++)
#define f first
#define s second

const int N = 100000 + 9;
const int M = 200000 + 9;

vector<pair<int,int>> adj[N];
bool seen[N];
int vis[M];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // Read edges
    rep(i, 0, m) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].emplace_back(v, i);
        adj[v].emplace_back(u, i);
    }

    // If no edges: trivial circuit at node 1
    if (m == 0) {
        cout << 1 << '\n';
        return 0;
    }

    // Must start at node 0 (crossing 1)
    if (adj[0].empty()) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    // 1) Connectivity check from vertex 0
    stack<int> stk;
    stk.push(0);
    seen[0] = true;
    while (!stk.empty()) {
        int u = stk.top(); stk.pop();
        for (auto &pr : adj[u]) {
            int v = pr.f;
            if (!seen[v]) {
                seen[v] = true;
                stk.push(v);
            }
        }
    }
    rep(i, 0, n) {
        if (!adj[i].empty() && !seen[i]) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    // 2) Parity check: every vertex must have even degree
    rep(i, 0, n) {
        if (adj[i].size() % 2 != 0) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    // 3) Hierholzer's algorithm to build the Eulerian circuit
    vector<int> circuit;
    stk.push(0);

    while (!stk.empty()) {
        int v = stk.top();
        // remove already-used edges
        while (!adj[v].empty() && vis[ adj[v].back().s ]) {
            adj[v].pop_back();
        }
        if (adj[v].empty()) {
            // no more edges: add to circuit
            circuit.push_back(v);
            stk.pop();
        } else {
            // traverse next unused edge
            auto [u, eid] = adj[v].back();
            adj[v].pop_back();
            vis[eid] = 1;
            stk.push(u);
        }
    }

    // 4) Verify we used all edges
    if ((int)circuit.size() != m + 1) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    // Print circuit (convert back to 1-based)
    for (int x : circuit) {
        cout << x + 1 << ' ';
    }
    cout << '\n';
    return 0;
}