#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i , st , ed) for(int i = st; i < ed; i++)
#define f first
#define s second
const int N = 3e5 + 9;
vector<pair<int,int>> adj[N] , edges;
vector<int> BridgeTree[N];
int lowLink[N] , dfn[N] , comp[N] , ndfn , comp_num;
bool isBridge[N] , vis[N];
void tarjan(int u , int par){
  dfn[u] = lowLink[u] = ndfn++;
  for(auto &[v , id] : adj[u]){
    if(dfn[v] == -1){
      tarjan(v , u);
      lowLink[u] = min(lowLink[u] , lowLink[v]);
  	  if(lowLink[v] == dfn[v]){
  	  	int uu = u , vv = v;
  	  	if(uu > vv) swap(uu , vv);
  	  	isBridge[id] = true;
  	  }    
    }else if(v != par){
      lowLink[u] = min(lowLink[u] , dfn[v]);
    }
  }
}
void Find_component(int u , int par){
	vis[u] = true;
	comp[u] = comp_num;
	for(auto &[v , id] : adj[u]) if(vis[v] == 0 && isBridge[id] == 0)
		Find_component(v , u);
}
pair<int, int> diameter(int u, int par = -1)
{
	int diam = 0;
	int mxHeights[3] = {-1, -1, -1};	// keep 2 highest trees
	for(auto &v : BridgeTree[u]) if(v != par)
	{
		auto p = diameter(v , u);
		diam = max(diam, p.f);
		mxHeights[0] = p.s+1;
		sort(mxHeights, mxHeights+3);
	}
	for(int i = 0; i < 3; i++)if(mxHeights[i] == -1)
		mxHeights[i] = 0;
	diam = max(diam, mxHeights[1] + mxHeights[2]);
	return {diam, mxHeights[2]};
}
int main(){
	ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif 
    int n, m; cin >> n >> m;
    for(int i = 0; i < m; i++){
    	int u , v; cin >> u >> v;
    	--u; --v;
    	adj[u].emplace_back(v,  i);
    	adj[v].emplace_back(u , i);
    	edges.emplace_back(u , v);
    }
    // Finding Bridges using Tarjan algo.
    for(int i = 0;i < n; i++){ dfn[i] = -1; lowLink[i] = 0; }
    ndfn = 0;
    tarjan(0 , 0);
    // dfs to group all the maximal components together, so that we can shrink it to one node
    for(int i = 0; i < n; i++) if(vis[i] == 0){
    	Find_component(i , i);
    	comp_num++;
    }
    // shrinking all the maximal components to one node
    for(int i = 0; i < m; i++) {
        if(isBridge[i]) {
            BridgeTree[comp[edges[i].f]].emplace_back(comp[edges[i].s]);
            BridgeTree[comp[edges[i].s]].emplace_back(comp[edges[i].f]);
        }
    }
    // Finding the diameter of the Bridgestree
    int d = diameter(0 , 0).f;
    cout << d;
}
