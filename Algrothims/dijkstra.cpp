#include <bits/stdc++.h>
typedef long long ll;
#define s second
#define f first
using namespace std;
int main(){
  /*
    ------ Dijkstra Algrothim --------
    - use to Find Shortest path from Single Sourse to other vertices
    - can used if weight of edge >= 0
    - Find answer in O(nlog(n))
  */
  int n , m; cin >> n >> m; // n : number of vertices , m : number of edges
  vector<pair<int,ll>> adj[n]; // {v , w}
  for(int i = 0 ; i < m ; i++){
    int u , v; ll w; cin >> u >> v >> w;
    adj[u].emplace_back(v , w);
    adj[v].emplace_back(u , w);
  }
  int Start; cin >> Start; // vertice that you start from
  Start--;
  priority_queue<pair<ll,int>> q; // {dis , u}
  vector<ll> dis(n , 1e15);
  vector<bool> vis(n);
  q.push({0 , Start});
  dis[Start] = 0;
  while(q.size()){
    int u = q.top().s; q.pop();
    if(vis[u]) continue;
    vis[u] = true;
    for(auto &[v , w] : adj[u]){
      if(dis[v] > dis[u] + w){ // relaxing 
        dis[v] = dis[u] + w;
        q.push({-dis[v] , v});
      }
    }
  }
}

