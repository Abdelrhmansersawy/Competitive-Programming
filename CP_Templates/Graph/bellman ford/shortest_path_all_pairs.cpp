/*
Problem: Minimum Shortest Path
Link: https://codeforces.com/gym/101498/problem/L

Description:
Given a directed weighted graph (possibly with negative weights), find the minimum
shortest path between any pair of distinct nodes. If any path in the graph can be
made arbitrarily short due to a negative-weight cycle, output "-inf".

Approach:
- Used a variant of the Bellman-Ford algorithm to detect the minimum shortest path.
- Initialized distances of all nodes to 0 to simulate starting Bellman-Ford from a
  virtual super-source connected to all nodes with 0-weight edges.
- Relaxed all edges for N iterations:
  - If a distance can still be updated in the N-th iteration, a negative cycle exists,
    and we output "-inf".
- `ans` is computed as the minimum of:
  1. The smallest edge weight in the graph (to handle the case where no relaxation happens).
  2. All updated distances during relaxation (i.e., dis[v] values after successful relaxations).
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
    int tc; cin >> tc;
    while(tc--){
        int n, m; cin >> n >> m;
        vector<array<ll,3>> edges(m);
        ll ans = 1e18;
        for(auto &[u,v,w] : edges){
            cin >> u >> v >> w;
            --u; --v;
            ans = min(ans , w);
        }

        vector<ll> dis(n);
        bool neg_cycle = false;

        for(int i = 0; i < n; ++i){
            for(auto &[u,v,w] : edges){
                if(dis[v] > dis[u] + w){
                    neg_cycle |= (i == n-1);
                    dis[v] = dis[u] + w;
                    ans = min(ans , dis[v]);
                }
            }
        }

        if(neg_cycle){
            cout << "-inf\n";
        }else{
            cout << ans << '\n';
        }
    }
}
