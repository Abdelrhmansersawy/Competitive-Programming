/*
Problem: Cycle Finding
Link: https://cses.fi/problemset/task/1197/

Description:
Given a directed weighted graph (with possibly negative edge weights), determine if the graph contains a **negative-weight cycle**.
If such a cycle exists, print "YES" and provide any one of them in correct order (as a cycle of nodes). Otherwise, print "NO".

Approach:
- This is a classic application of the Bellman-Ford algorithm to detect negative-weight cycles.
- We initialize all distances to zero (as we only care about cycle detection, not actual shortest paths).
- Run Bellman-Ford for n iterations:
  - If we can still relax an edge in the n-th iteration, then a negative cycle exists.
  - Track the last updated node `x`, and use the parent array `p[]` to trace back the cycle.
- To ensure we get a valid cycle, we walk back `n` times from `x` to reach a guaranteed node within the cycle.
- Then, we traverse until we revisit the start node to build the cycle path.

Note:
- The problem guarantees that if a cycle exists, it will be reachable within `n` relaxations due to the size of the graph.
- The printed cycle may start at any node in the cycle.

Time complexity: O(n * m), suitable for the constraints.
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll inf = 1e18;
int main(){
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif
    
    int n , m; cin >> n >> m;
    vector<array<ll,3>> edges(m);
    for(auto &[u,v,w] : edges){
        cin >> u >> v >> w;
        --u; --v;
    }
 
    vector<ll> dis(n,0);
    vector<int> p(n);
 
    int x;
    for(int i = 0; i < n; ++i){
        x = -1;
        for(auto &[u,v,w] : edges){
            if(dis[v] > dis[u] + w){ // find shortest-path
                dis[v] = dis[u] + w;
                x = v;
                p[v] = u;
            }
        }
    }
 
    if(x == -1){ // no negative cycle
        cout << "NO";
        return 0;
    }
 
    // ensure that node x is a node of cycle 
    for(int _ = 0; _ < n; ++_) x = p[x];
    vector<int> cycle;
    while(cycle.size() <= 1 || cycle.front() != cycle.back()){
        cycle.emplace_back(x);
        x = p[x];
    }
 
 
    // Print cycle
    cout << "YES\n";
    reverse(cycle.begin(), cycle.end());
    for(auto &x : cycle) cout << x+1 << ' ';
 
}
