#include <bits/stdc++.h>
typedef long long ll;
#define s second
#define f first
#define rep(i , st , ed) for(int i = st ; i < ed ; i++)
using namespace std;
const int N = 4000;
void burn(){
ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
  #endif
}
//\//\//\/\//\//\//\//\//\//
int n;
vector<int> adj[N];
void tree_center(){
  vector<int> deg(n);
  queue<int> leaf;
  rep(i , 0 , n){
    deg[i] = adj[i].size();
    if(deg[i] <= 1) leaf.push(i);
  }
  int rem = n;
  while(rem > 2){
    int sz = leaf.size();
    while(sz--){
      rem--;
      int u = leaf.front(); leaf.pop();
      for(auto &v : adj[u]){
        deg[v]--;
        if(deg[v] == 1) leaf.push(v);
      }
    }
  }
  int c1 = leaf.front(); leaf.pop();
  int c2 = (leaf.size()) ? leaf.front() : -1;
}
int main(){
  burn();
}
