/*
Find all biconnected components of an undirected graph
using Tarjan's algorithm.

Definitions:
    - A biconnected component (block) is a maximal set of vertices
      such that the removal of any single vertex does not disconnect the component.
    - The algorithm outputs all such components as collections of vertices.

Input:
    - n (number of vertices)
    - m (number of edges)
    - m edges (u, v) with 1 ≤ u, v ≤ n

Output:
    - bi_connected (vector of components)
    - Each component is a list of vertices
    - bi_connected.size() = number of biconnected components

Time complexity:
    - Tarjan DFS traversal: O(n + m)

Space complexity:
    - O(n + m) (adjacency list, stacks, dfs arrays)
*/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 10;

vector<int> adj[MAXN];                 // adjacency list
vector<vector<int>> bi_connected;      // stores components

int dfn[MAXN], low[MAXN], id;
int s[MAXN], tp;                       // stack for vertices
int p[MAXN], cnt;                      // component id

void tarjan(int u, int f = -1) {
    dfn[u] = low[u] = ++id;
    s[++tp] = u;
    for (int v : adj[u]) {
        if (!dfn[v]) {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
        } else if (v != f) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        cnt++;
        bi_connected.push_back({});
        for (int x = -1; x != u;) {
            x = s[tp--];
            p[x] = cnt;
            bi_connected.back().push_back(x);
        }
    }
}

void init_biconnected(int n) {
    id = cnt = tp = 0;
    bi_connected.clear();
    for (int i = 0; i < n; i++) dfn[i] = low[i] = p[i] = 0;

    for (int i = 0; i < n; i++) {
        if (!dfn[i]) tarjan(i);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m; cin >> n >> m;
    for (int i = 0; i < n; ++i) adj[i].clear();

    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        --u; --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    init_biconnected(n);

    // bi_connected vector stores all the vertices in each biconnected component
    cout << "Number of components: " << bi_connected.size() << "\n";
    for (int i = 0; i < (int)bi_connected.size(); i++) {
        cout << "Component " << i+1 << ": ";
        for (int v : bi_connected[i]) cout << v+1 << " ";
        cout << "\n";
    }
}
