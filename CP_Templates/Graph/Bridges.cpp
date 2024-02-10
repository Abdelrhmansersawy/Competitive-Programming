#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i , st , ed) for(int i = st; i < ed; i++)
#define f first
#define s second
const int N = 1e5 + 9;
vector<vector<pair<int,int>>> adj;
vector<vector<int>> BridgeTree;
vector<int> lowLink , dfn , isBridge , comp;
int  ndfn , comp_num , total;
void tarjan(int u , int par){
  dfn[u] = lowLink[u] = ndfn++;
  for(auto &[v , id] : adj[u]){
    if(dfn[v] == -1){
      tarjan(v , u);
      lowLink[u] = min(lowLink[u] , lowLink[v]);
  	  if(lowLink[v] == dfn[v]){
  	  	isBridge[id] = true;
  	  	total++;
  	  }    
    }else if(v != par){
      lowLink[u] = min(lowLink[u] , dfn[v]);
    }
  }
}
void Find_component(int u , int par){
	comp[u] = comp_num;
	for(auto &[v , id] : adj[u]) if(comp[v] == -1 && isBridge[id] == 0)
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
    int q; cin >> q;
    while(q--){
    	int n, m; cin >> n >> m;
	    // reset 
	    dfn.assign(n , -1);
	    comp.assign(n , -1);
	    lowLink.assign(n , 0);
	    isBridge.assign(m , 0);
	    ndfn = comp_num = total = 0;
	    adj.assign(n , vector<pair<int,int>>());

	    for(int i = 0; i < m; i++){
	    	int u , v; cin >> u >> v;
	    	--u; --v;
	    	adj[u].emplace_back(v,  i);
	    	adj[v].emplace_back(u , i);
	    }
	    // Finding Bridges using Tarjan algo.
	    tarjan(0 , 0);
	    // dfs to group all the maximal components together, so that we can shrink it to one node
	    for(int i = 0; i < n; i++) if(comp[i] == -1){
	    	Find_component(i , i);
	    	comp_num++;
	    }
	    // shrinking all the maximal components to one node
	    BridgeTree.assign(comp_num , vector<int>());
	    for(int u = 0; u < n; u++) for(auto &[v , id] : adj[u]) if(isBridge[id]){
	    	BridgeTree[comp[u]].emplace_back(comp[v]);
	    }
	    // Finding the diameter of the Bridgestree
	    int d = diameter(0 , 0).f;
    }
}
