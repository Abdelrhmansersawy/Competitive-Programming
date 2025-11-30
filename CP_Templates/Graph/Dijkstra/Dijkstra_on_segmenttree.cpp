/*
Problem: Given n cities and q portal plans, find min cost from start city s to all cities (-1 if unreachable).

Plan types:
Type 1: edge v -> u, cost w      // O(1)
Type 2: edges v -> [l,r], cost w // naive O(r-l+1), optimized O(log n) with segment tree
Type 3: edges [l,r] -> v, cost w // naive O(r-l+1), optimized O(log n) with segment tree

Dijkstra complexity: O((V + E) log V),  
V = n + segment-tree nodes, E = plan edges + segment-tree edges
*/
// standard problem: https://codeforces.com/contest/786/problem/B


#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template < typename T >
using minQ = priority_queue < T, vector < T > , greater < T >> ;

vector < vector < pair < int, ll >>> g;
int OFFSET = 0;
int N; // size of Nodes

// init graph for original n
void init_graph(int n) {
    OFFSET = n;
    N = n;
    g.assign(9 * OFFSET + 5 + 1, {});
}

inline void add_edge(int u, int v, ll w) {
    g[u].push_back({ v, w });
}

// build segtree layers
void build(int node = 1, int l = 0, int r = N-1) {
    if (l == r) {
        add_edge(l, node + OFFSET, 0);
        add_edge(node + 5 * OFFSET, l, 0);
        return;
    }
    int mid = (l + r) >> 1;
    add_edge(2 * node + OFFSET, node + OFFSET, 0);
    add_edge(2 * node + 1 + OFFSET, node + OFFSET, 0);
    add_edge(node + 5 * OFFSET, 2 * node + 5 * OFFSET, 0);
    add_edge(node + 5 * OFFSET, 2 * node + 1 + 5 * OFFSET, 0);
    build(2 * node, l, mid);
    build(2 * node + 1, mid + 1, r);
}

// Add edges from single vertex u to all vertices in [lx, rx] (dir=1)
// or from all vertices in [lx, rx] to u (dir=0)
void upd(int lx, int rx, int dir, int u, ll w, int node = 1, int l = 0, int r = N-1) {
    if (rx < l || r < lx) return;
    if (lx <= l && r <= rx) {
        if (dir) add_edge(u, node + 5 * OFFSET, w);
        else add_edge(node + OFFSET, u, w);
        return;
    }
    int mid = (l + r) >> 1;
    upd(lx, rx, dir, u, w, 2 * node, l, mid);
    upd(lx, rx, dir, u, w, 2 * node + 1, mid + 1, r);
}

vector< ll>dijkstra(int s) {
    const ll INF = (ll) 1e18;
    minQ <pair<ll,int>> pq;
    int total = g.size() - 1;
    vector < ll > dist(total + 1, INF);
    vector < char > vis(total + 1, 0);
    dist[s] = 0;
    pq.push({
        0,
        s
    });
    while (!pq.empty()) {
        auto[du, u] = pq.top();
        pq.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto & [v, w]: g[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({
                    dist[v],
                    v
                });
            }
        }
    }
    return dist;
}

int main(){

    int n , m , source; cin >> n >> m >> source;
    --source;
    
    // initialize
    init_graph(n);
    build();


    for(int i = 0; i < m; ++i){
        int t; cin >> t;
        if(t == 1){
            int u,v,w; cin >> u >> v >> w;
            --u; --v;
            g[u].emplace_back(v,w);
        }else{
            int u; cin >> u;
            --u;
            int lx , rx; cin >> lx >> rx;
            --lx; --rx;
            int w; cin >> w;

            if(t == 2){
                upd(lx,rx,1,u,w);
            }else{
                upd(lx,rx,0,u,w);
            }
        }
    }

    auto dis = dijkstra(source);
    for(int i = 0; i < n; ++i){
        cout << (dis[i] == (ll) 1e18 ? -1LL : dis[i]) << ' ';
    }
}
