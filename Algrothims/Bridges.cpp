#include <bits/stdc++.h>
typedef long long ll;
#define s second
#define f first
#define rep(i , st , ed) for(int i = st ; i < ed ; i++)
using namespace std;
void burn(){
ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
  #endif
}
const int N = 1e5;
//\\//\\//\\/\\//\\//\\//\\//\\//\\//
vector<vector<int>> adj;
int lowLink[N] , dfn[N] , vis[N];
int ndfn;
map<pair<int,int> , bool> bridge;
void tarjan(int u , int par){
  dfn[u] = lowLink[u] = ndfn++;
  for(auto &v : adj[u]){
    if(dfn[v] == -1){
      tarjan(v , u);
      lowLink[u] = min(lowLink[u] , lowLink[v]);
  	  if(lowLink[v] == dfn[v]){
  	  	int uu = u , vv = v;
  	  	if(uu > vv) swap(uu , vv);
  	  	bridge[{uu , vv}] = true; // edge from {u , v} if bridge
  	  }    
    }else if(v != par){
      lowLink[u] = min(lowLink[u] , dfn[v]);
    }
  }
}
void SCC(int n){
  ndfn = 0;
  rep(i , 0 , n){
  	dfn[i] = -1;
  	lowLink[i] = 0;
  }
  tarjan(0 , 0);
}
// this function is to remove bridge
void dfs(int u){
	vis[u] = true;
	safe++;
	for(auto &v : adj[u]) if(vis[v] == 0){
		int uu = u , vv = v;
  	  	if(uu > vv) swap(uu , vv);
  	  	if(!bridge[{uu , vv}]) dfs(v); 
	}
}
int main(){
  burn();
  int n , m; cin >> n >> m;
  adj.resize(n); 
  for(int i = 0 ; i < m ; i++){
    int u , v; cin >> u >> v;
    --u; --v;
    adj[u].emplace_back(v);
  }
  SCC(n);
}
