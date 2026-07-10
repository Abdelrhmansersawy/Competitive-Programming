#include <bits/stdc++.h>
using namespace std;

/**
 * Tarjan SCC
 * Finds strongly connected components in a directed graph and builds
 * the condensation DAG.
 *
 * API:
 * SCC scc(n);
 * scc.addEdge(u, v);
 * scc.build();
 * scc.buildDAG();
 *
 * scc.comp[u]       : component ID of node u
 * scc.nodes[id]     : nodes inside component id
 * scc.DAG_adj[id]   : outgoing edges from component id
 * scc.indegree[id]  : in-degree of component id
 * scc.outdegree[id] : out-degree of component id
 * scc.count()       : number of components
 *
 * Complexity:
 * build()    : O(n + m)
 * buildDAG() : O(m log m)
 */

struct SCC {
    int n, timer = 0;
    vector<vector<int>> adj, nodes, DAG_adj;
    vector<int> comp, dfn, low, inStack, indegree, outdegree, st;

    SCC(int n)
        : n(n), adj(n), comp(n), dfn(n, -1),
          low(n), inStack(n) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    void dfs(int u) {
        dfn[u] = low[u] = timer++;
        st.push_back(u);
        inStack[u] = 1;

        for (int v : adj[u]) {
            if (dfn[v] == -1)
                dfs(v), low[u] = min(low[u], low[v]);
            else if (inStack[v])
                low[u] = min(low[u], dfn[v]);
        }

        if (dfn[u] != low[u]) return;

        int id = nodes.size();
        nodes.emplace_back();

        while (true) {
            int v = st.back();
            st.pop_back();

            inStack[v] = 0;
            comp[v] = id;
            nodes[id].push_back(v);

            if (v == u) break;
        }
    }

    void build() {
        for (int u = 0; u < n; u++)
            if (dfn[u] == -1)
                dfs(u);
    }

    void buildDAG() {
        DAG_adj.assign(count(), {});
        indegree.assign(count(), 0);
        outdegree.assign(count(), 0);

        for (int u = 0; u < n; u++) {
            for (int v : adj[u]) {
                if (comp[u] != comp[v])
                    DAG_adj[comp[u]].push_back(comp[v]);
            }
        }

        for (int u = 0; u < count(); u++) {
            auto &edges = DAG_adj[u];

            sort(edges.begin(), edges.end());
            edges.erase(unique(edges.begin(), edges.end()), edges.end());

            outdegree[u] = edges.size();

            for (int v : edges)
                indegree[v]++;
        }
    }

    int count() const {
        return nodes.size();
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    SCC scc(n);

    while (m--) {
        int u, v;
        cin >> u >> v;
        --u, --v;

        scc.addEdge(u, v);
    }

    scc.build();
    scc.buildDAG();

    cout << "SCC count: " << scc.count() << '\n';

    cout << "Component of each node:\n";
    for (int u = 0; u < n; u++)
        cout << scc.comp[u] << " \n"[u == n - 1];

    cout << "Components:\n";
    for (int id = 0; id < scc.count(); id++) {
        cout << id << ": ";

        for (int u : scc.nodes[id])
            cout << u + 1 << ' ';

        cout << '\n';
    }

    cout << "Condensation DAG:\n";
    for (int id = 0; id < scc.count(); id++) {
        cout << id
             << " | indegree: " << scc.indegree[id]
             << " | outdegree: " << scc.outdegree[id]
             << " | edges: ";

        for (int to : scc.DAG_adj[id])
            cout << to << ' ';

        cout << '\n';
    }

    return 0;
}
