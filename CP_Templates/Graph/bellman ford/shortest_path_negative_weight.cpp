/*
Problem: Single-Source Shortest Paths with Negative Weights and Queries
Description:
Given a directed graph with possibly negative edge weights, answer shortest path queries
from a single source node to several destination nodes. If a destination node is unreachable,
output "Impossible". If the node is reachable via a negative-weight cycle, output "-Infinity".

Approach:
- Used Bellman-Ford algorithm to compute shortest paths from the source.
- First, ran standard Bellman-Ford for n iterations to relax edges.
- Then, ran another full pass to detect nodes reachable through negative-weight cycles,
  marking them with a special value (-INF) to distinguish them.
- Each query is answered based on the final computed distances.
*/
#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);

    int n , m , q , s; 
    while(cin >> n >> m >> q >> s){
        if(!n) break;
        vector<array<int,3>> edges(m); // {u,v,w}
        for(auto &[u,v,w] : edges) cin >> u >> v >> w;
        vector<int> dis(n , 2e9);
        dis[s] = 0; // source
        for(int i = 0; i < n; ++i){
            for(auto &[u,v,w] : edges) if(dis[u] != 2e9){ // can reach node u from source s
                if(dis[v] > dis[u] + w){
                    dis[v] = dis[u] + w;
                }
            }
        }

        for(int i = 0; i < n; ++i){
            for(auto &[u,v,w] : edges) if(dis[u] != 2e9){
                if(dis[v] > dis[u] + w){
                    dis[v] = -2e9; // can reach it through negative cycle
                }
            }
        }

        while(q--){
            int x; cin >> x;
            if(dis[x] == 2e9) cout << "Impossible\n";
            else if(dis[x] == -2e9) cout << "-Infinity\n";
            else cout << dis[x] << '\n';
        }

        cout << '\n';
    }
}
