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
int lowLink[N] , dfn[N];
set<int>artpoints;
int ndfn;
bool root = false;
void tarjan(int u, int par){
  dfn[u] = lowLink[u] = ndfn++;
  for(auto &v : adj[u]){
    if(dfn[v] == -1){
      tarjan(v, u);
      lowLink[u] = min(lowLink[u] , lowLink[v]);
      if (lowLink[v] >= dfn[u]){
        if (dfn[u] == 0 && root == false)
            root = true;
        else artpoints.emplace(u);
      }
    }else if(v != par){
      lowLink[u] = min(lowLink[u] , dfn[v]);
    }
  }
}
int main(){
  burn();
  int n , m; cin >> n >> m;
  for (int i = 0; i < n; ++i)
    dfn[i] = -1;
  adj.resize(n);
  for(int i = 0 ; i < m ; i++){
    int u , v; cin >> u >> v;
    --u; --v;
    adj[u].emplace_back(v);
    adj[v].emplace_back(u);
  }
  tarjan(0, -1);
  // ALL articulation points are stored in **artspoints** set
}
