#include <bits/stdc++.h>
using namespace std;

struct MCMF {
    static const int INF = 1e9;
    struct Edge { int to, cap, cost, flow, rev; };

    int n;
    vector<vector<Edge>> g;
    vector<int> dist, par, parEdge;
    vector<char> inq;

    MCMF(int n = 0) : n(n), g(n), dist(n), par(n), parEdge(n), inq(n) {}

    void init(int N){
        n = N;
        g.assign(n, {});
        dist.assign(n, INF);
        par.assign(n, -1);
        parEdge.assign(n, -1);
        inq.assign(n, 0);
    }

    void addEdge(int u, int v, int cap, int cost){
        g[u].push_back({v, cap, cost, 0, (int)g[v].size()});
        g[v].push_back({u, 0, -cost, 0, (int)g[u].size()-1});
    }

    bool spfa(int s, int t){
        fill(dist.begin(), dist.end(), INF);
        fill(inq.begin(), inq.end(), 0);
        queue<int> q; q.push(s);
        dist[s] = 0; inq[s] = 1;
        while(!q.empty()){
            int u = q.front(); q.pop(); inq[u] = 0;
            for(int i = 0; i < (int)g[u].size(); ++i){
                auto &e = g[u][i];
                if(e.flow < e.cap && dist[e.to] > dist[u] + e.cost){
                    dist[e.to] = dist[u] + e.cost;
                    par[e.to] = u;
                    parEdge[e.to] = i;
                    if(!inq[e.to]) { inq[e.to] = 1; q.push(e.to); }
                }
            }
        }
        return dist[t] < INF;
    }

    // returns {flow, cost} or {-1,-1} if can't reach maxF
    pair<int,int> solve(int s, int t, int maxF = INT_MAX){
        int flow = 0, cost = 0;
        while(flow < maxF && spfa(s,t)){
            int add = INF;
            for(int v = t; v != s; v = par[v])
                add = min(add, g[par[v]][parEdge[v]].cap - g[par[v]][parEdge[v]].flow);

            for(int v = t; v != s; v = par[v]){
                auto &e = g[par[v]][parEdge[v]];
                e.flow += add;
                g[v][e.rev].flow -= add;
                cost += add * e.cost;
            }
            flow += add;
        }
        if(flow < maxF) return {-1, -1};
        return {flow, cost};
    }

    // extract k paths from s->t following positive flow edges (decrements flow)
    vector<vector<int>> get_paths(int s, int t, int k){
        vector<vector<int>> res;
        for(int it = 0; it < k; ++it){
            vector<int> path;
            int u = s;
            while(u != t){
                path.push_back(u);
                bool moved = false;
                for(auto &e : g[u]){
                    if(e.flow > 0){
                        e.flow--;
                        u = e.to;
                        moved = true;
                        break;
                    }
                }
                if(!moved){ path.clear(); break; } // no augmenting step -> no more paths
            }
            if(path.empty()) break;
            path.push_back(t);
            res.push_back(path);
        }
        return res;
    }
};
