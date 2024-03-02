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
stack<pair<int,int>> comps;
vector<vector<pair<int, int>>>bi_connected;
int ndfn;
pair<int,int> edge;
bool root = false;
void tarjan(int u, int par){
  dfn[u] = lowLink[u] = ndfn++;
  for(auto &v : adj[u]){
    if (v != par && dfn[v] < dfn[u])
        comps.push(make_pair(u, v));

    if(dfn[v] == -1){
      tarjan(v, u);
      lowLink[u] = min(lowLink[u] , lowLink[v]);
      if (lowLink[v] >= dfn[u]){
        bi_connected.emplace_back(vector<pair<int,int>>());
        do{
            edge = comps.top();
            comps.pop();
            bi_connected.back().emplace_back(edge);

        }while(edge.first != u || edge.second != v);
        reverse(bi_connected.back().begin(), bi_connected.back().end());
      }
    }else if(v != par){
      lowLink[u] = min(lowLink[u] , dfn[v]);
    }
  }
}
int main(){
  //burn();
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
  // bi_connected vector stores all the edges in each biconnected component
  // bi_connected.size() is the number of biconnected componenets
}
