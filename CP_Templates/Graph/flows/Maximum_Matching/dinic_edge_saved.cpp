#include <bits/stdc++.h>
using namespace std;

using ll = long long;

//====================//

static const ll oo = 2e15;

struct Edge {
    ll u, v, flow = 0, cap = 0; // keep the order

    Edge(ll u, ll v): u(u), v(v) {}
    Edge(ll u, ll v, ll c): u(u), v(v), cap(c) {}

    ll rem() { return cap - flow; }
};

struct Dinic {
    ll n, s, t, id = 1, flow = 0;
    vector<Edge> edges;
    vector<vector<int>> adj;
    vector<int> lvl, ptr;

    Dinic(ll n, ll src, ll sink): n(n), s(src), t(sink) {
        adj.assign(n + 1, {});
        ptr.assign(n + 1, {});
    }

    void addEdge(int u, int v, ll w = oo, int undir = 0) {
        adj[u].push_back(edges.size());
        edges.push_back(Edge(u, v, w));
        adj[v].push_back(edges.size());
        edges.push_back(Edge(v, u, w * undir));
    }

    void move() {
        while (bfs()) {
            ptr.assign(n + 1, {});
            while (ll f = dfs(s)) flow += f;
        }
    }

    bool bfs() {
        lvl.assign(n + 1, -1);
        queue<int> q;
        q.push(s), lvl[s] = 0;

        while (!q.empty()) {
            auto u = q.front();
            q.pop();

            for (auto &i: adj[u]) {
                auto &[_, v, f, c] = edges[i];
                if (~lvl[v] || f == c) continue;
                lvl[v] = lvl[u] + 1;
                q.push(v);
            }
        }

        return lvl[t] != -1;
    }

    ll dfs(int u, ll currFlow = oo) {
        if (u == t) return currFlow;
        if (!currFlow) return 0;

        for (; ptr[u] < adj[u].size(); ++ptr[u]) {
            int i = adj[u][ptr[u]];
            auto [_, v, f, c] = edges[i];
            if (f == c || (lvl[v] != lvl[u] + 1)) continue;

            ll bottleNeck = dfs(v, min(currFlow, c - f));
            if (!bottleNeck) continue;

            edges[i].flow += bottleNeck;
            edges[i ^ 1].flow -= bottleNeck;

            return bottleNeck;
        }

        return 0;
    }
};
