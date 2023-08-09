#include <bits/stdc++.h>
typedef long long ll;
#define s second
#define f first
using namespace std;
int main(){
  /*
    ------ BFS Algrothim --------
    - use to Find Shortest path from Single Sourse to other vertices
    - can used if weight of edge == 1
    - Find answer in O(n + m)
  */
  int n , m; cin >> n >> m; // n : number of vertices , m : number of edges
  vector<int> adj[n];
  for(int i = 0 ; i < m ; i++){
    int u , v; cin >> u >> v;
    adj[u].emplace_back(v);
    adj[v].emplace_back(u);
  }
  int Start; cin >> Start; // vertice that you start from
  Start--;
  queue<int> q;
  vector<int> dis(n , -1);
  vector<int> par(n , -1);
  dis[Start] = 0; q.push(Start);
  while(q.size()){
    int u = q.front(); q.pop();
    for(auto &v : adj[u]){
      if(!~dis[v]){
        dis[v] = dis[u] + 1;
        q.push(v);
        par[v] = u;
      }
    }
  }
  // Find the path
  vector<int> path;
  function<void(int)> gen = [&](int i){
    path.emplace_back(i);
    if(~par[i]) gen(par[i]);
  };
  reverse(path.begin() , path.end());
}
