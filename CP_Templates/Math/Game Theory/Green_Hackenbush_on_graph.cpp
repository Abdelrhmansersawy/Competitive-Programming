/**
Consider a two player game on a graph with a specified vertex (root).
In each turn, a player eliminates one edge.
Then, if a subgraph that is disconnected from the root, it is removed.
If a player cannot select an edge (i.e., the graph is singleton),
he will lose.
Compute the Grundy number of the given graph.

We will use two principles:
1. Colon Principle:
    Grundy number of a tree is the xor of
    Grundy number of child subtrees.

2. Fusion Principle:
    Consider a pair of adjacent vertices u, v
    that has another path (i.e., they are in a cycle). Then,
    we can contract u and v without changing Grundy number.

We first decompose graph into two-edge connected components.
Then, by contracting each components by using Fusion Principle,
we obtain a tree (and many self loops) that has the same Grundy
number to the original graph. By using Colon Principle, we can
compute the Grundy number.

Complexity: O(m + n).

Verified:
SPOJ 1477: Play with a Tree
IPSC 2003 G: Got Root?
**/
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,int>;
const int N = 3e5 + 9;

int n, m, disc[N], low[N], timer_;
struct Edge { int u, v; };
vector<Edge> edges;
vector<pii> g[N]; // {to, directed_edge_id}

int dfs(int u, int peid) {
    disc[u] = low[u] = ++timer_;
    int res = 0;
    for (auto &[v, eid] : g[u]) {
        if (eid == peid) continue;
        if (!disc[v]) {
            int sub = dfs(v, eid ^ 1);
            low[u] = min(low[u], low[v]);
            if (low[v] > disc[u]) res ^= ((sub + 1) ^ 1); // bridge
            else res ^= sub;                               // non-bridge
        } else {
            low[u] = min(low[u], disc[v]); // back edge
        }
    }
    for (auto &[v, eid] : g[u]) {
        if (eid == peid) continue;
        if (disc[u] <= disc[v]) res ^= 1; // back-edges in DFS subtree
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T; 
    cin >> T;
    while (T--) {
        cin >> n >> m;
        edges.clear();
        for (int i = 1; i <= n; i++) g[i].clear();
        edges.reserve(m);

        for (int i = 0; i < m; i++) {
            int u, v; cin >> u >> v;
            edges.push_back({u, v});
        }

        for (int i = 0; i < m; i++) {
            int u = edges[i].u, v = edges[i].v;
            g[u].push_back({v, 2*i});
            g[v].push_back({u, 2*i+1});
        }

        timer_ = 0;
        fill(disc+1, disc+n+1, 0);
        fill(low+1, low+n+1, 0);

        int grundy = dfs(1, -1);
        cout << (grundy ? "Alice\n" : "Bob\n");
    }
}
