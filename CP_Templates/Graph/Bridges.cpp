#include <bits/stdc++.h>
using namespace std;

/**
 * Bridge Tree — O(n + m)
 *
 * BridgeTree bt(n, m);
 * bt.addEdge(u, v, id);
 * bt.build();
 *
 * bt.isBridge[id] : whether edge id is a bridge
 * bt.comp[u]      : component ID of node u
 * bt.nodes[id]    : nodes inside component id
 * bt.tree[id]     : adjacent bridge-tree components
 * bt.count()      : number of components
 * bt.diameter()   : maximum bridge-tree diameter
 */

struct BridgeTree {
    int n, timer = 0;
    vector<vector<pair<int, int>>> adj;
    vector<vector<int>> nodes, tree;
    vector<int> dfn, low, comp, isBridge;

    BridgeTree(int n, int m) : n(n), adj(n), dfn(n, -1),
        low(n), comp(n, -1), isBridge(m) {}

    void addEdge(int u, int v, int id) {
        adj[u].push_back({v, id});
        adj[v].push_back({u, id});
    }

    void dfs(int u, int parentEdge = -1) {
        dfn[u] = low[u] = timer++;

        for (auto [v, id] : adj[u]) {
            if (id == parentEdge) continue;

            if (dfn[v] == -1) {
                dfs(v, id);
                low[u] = min(low[u], low[v]);
                isBridge[id] = low[v] > dfn[u];
            } else
                low[u] = min(low[u], dfn[v]);
        }
    }

    void color(int u, int id) {
        comp[u] = id;
        nodes[id].push_back(u);

        for (auto [v, edgeId] : adj[u])
            if (comp[v] == -1 && !isBridge[edgeId])
                color(v, id);
    }

    void build() {
        for (int u = 0; u < n; u++)
            if (dfn[u] == -1) dfs(u);

        for (int u = 0; u < n; u++) {
            if (comp[u] == -1) {
                nodes.push_back({});
                color(u, count() - 1);
            }
        }

        tree.assign(count(), {});

        for (int u = 0; u < n; u++)
            for (auto [v, id] : adj[u])
                if (isBridge[id] && comp[u] != comp[v])
                    tree[comp[u]].push_back(comp[v]);
    }

    pair<int, int> farthest(int src) const {
        queue<int> q;
        vector<int> dist(count(), -1);
        q.push(src), dist[src] = 0;

        int last = src;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            last = u;

            for (int v : tree[u])
                if (dist[v] == -1)
                    dist[v] = dist[u] + 1, q.push(v);
        }

        return {last, dist[last]};
    }

    int diameter() const {
        int ans = 0;
        vector<int> vis(count());

        for (int root = 0; root < count(); root++) {
            if (vis[root]) continue;

            queue<int> q;
            q.push(root), vis[root] = 1;

            while (!q.empty()) {
                int u = q.front();
                q.pop();

                for (int v : tree[u])
                    if (!vis[v]) vis[v] = 1, q.push(v);
            }

            int endpoint = farthest(root).first;
            ans = max(ans, farthest(endpoint).second);
        }

        return ans;
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

    BridgeTree bt(n, m);

    for (int id = 0; id < m; id++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        bt.addEdge(u, v, id);
    }

    bt.build();

    cout << bt.count() << '\n';
    cout << bt.diameter() << '\n';

    for (int u = 0; u < n; u++)
        cout << bt.comp[u] << " \n"[u == n - 1];
}
