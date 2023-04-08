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
//\\//\\//\\/\\//\\//\\//\\//\\//\\//
vector<vector<int>> adj , dag , comps;
vector<int> comp , inStack , lowLink , dfn;
stack<int> st;
int ndfn;
void tarjan(int u){
  dfn[u] = lowLink[u] = ndfn++;
  inStack[u] = true;
  st.push(u);
  for(auto &v : adj[u]){
    if(dfn[v] == -1){
      tarjan(v);
      lowLink[u] = min(lowLink[u] , lowLink[v]);
    }else if(inStack[v]){
      lowLink[u] = min(lowLink[u] , dfn[v]);
    }
  }
  if(dfn[u] == lowLink[u]){
    // head of component
    int x = -1;
    comps.emplace_back(vector<int>());
    while(x != u){
      x = st.top(); st.pop(); inStack[x] = 0;
      comps.back().emplace_back(x);
      comp[x] = comps.size() - 1;  
    }
  }
}
void genDag(){
  dag.resize(comps.size());
  for(int u = 0 ; u < adj.size() ; u++){
    for(auto &v :adj[u]){
      if(comp[u] != comp[v]) 
        dag[comp[u]].emplace_back(comp[v]);
    }
  }
}
void SCC(int n){
  dfn.clear(); dfn.resize(n , -1);
  comp.clear(); comp.resize(n);
  lowLink.clear(); lowLink.resize(n); 
  inStack.clear(); inStack.resize(n);
  for(int i = 0 ; i < n ; i++)
    if(dfn[i] == -1) tarjan(i);
  genDag();
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
