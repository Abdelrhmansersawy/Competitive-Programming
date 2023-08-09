#include <bits/stdc++.h>
typedef long long ll;
#define s second
#define f first
#define rep(i , st , ed) for(int i = st ; i < ed ; i++)
const int N = 500;
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
int reach[N][N] , dag[N][N];
vector<int> comp , sz;
void SCC(int n){
  comp.clear(); comp.resize(n , -1);
  sz.clear();
  // Floyed
  rep(k , 0 , n) rep(i , 0 , n) rep(j , 0 , n)
      reach[i][j] |= (reach[i][k] && reach[k][j]); // Warshall Transitive closure
  int cnt = 0;
  // detect SCC
  rep(i , 0 , n){
    if(comp[i] == -1){
      comp[i] = cnt++;
      rep(j , 0 , n) 
        if(reach[i][j] && reach[j][i]) comp[j] = comp[i];
    }
  }
  sz.resize(cnt);
  rep(i , 0 , n) sz[comp[i]]++;
  // Create Dag
  rep(i , 0 , n) rep(j , 0 , n)
    if(reach[i][j]) dag[comp[i]][comp[j]] = 1;
}
int main(){
  burn();
  int n , m; cin >> n >> m;
  for(int i = 0 ; i < m ; i++){
    int u , v; cin >> u >> v;
    --u; --v;
    reach[u][v] = 1;
  }
  SCC(n);
}
