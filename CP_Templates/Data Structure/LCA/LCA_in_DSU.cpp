#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i , st , ed) for(int i = st; i < ed; i++)
#define f first
#define s second
const int LOG = 20;
struct DSU
{
  vector<int> par , size  , W[LOG] , up[LOG] , dep;
  ll MST = 0;
  int n;
  DSU(int n){
    this->n = n;
    par.resize(n); size.resize(n , 1); dep.resize(n);
    rep(i , 0 , n) par[i] = i;
    rep(i , 0 , LOG) up[i].resize(n);
  }
  pair<int,int> get(int a){ // {par , depth}
    if(par[a] == a) return {a , 0};
    auto p = get(par[a]); p.s++;
    return p;
  } // no path compression
  void Union(int a, int b , int w){
    a = get(a).f; b = get(b).f;
    if(a == b) return; // same component
    if(size[a] > size[b]) swap(a , b);
    size[b] += size[a];
    par[a] = b;
    MST += w;
  }
  void Build(){
    rep(i , 0 , n){
        up[0][i] = par[i];
        dep[i] = get(i).s;
    }
    rep(x , 1 , LOG) rep(u , 0 , n){
        up[x][u] = up[x - 1][ up[x - 1][u] ];
    }
  }
  ll lca(int u , int v, int w){
    int mx = 0;
    if(dep[u] < dep[v]) swap(u , v);
    int k = dep[u] - dep[v];
    for(int i = LOG - 1; i >= 0; i--) if((k >> i) & 1){
        mx = max(mx , W[i][u]);
        u = up[i][u];
    } 
    if(u == v) return ;
    for(int i = LOG - 1; i >= 0; --i) if(up[i][u] != up[i][v]){
        mx = max({mx , W[i][u] , W[i][v]});
        u = up[i][u];
        v = up[i][v];
    }
    assert(up[0][u] == up[0][v]);
    return ;
  }
};
struct edge{ int u , v , w; };
int main(){
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif 
    int n , m; cin >> n >> m;
    vector<edge> e(m); // {w , u , v}
    rep(i , 0 , m){
        cin >> e[i].u >> e[i].v >> e[i].w;
        --e[i].u; --e[i].v;
    }
    int idx[m];
    iota(idx , idx + m , 0);
    sort(idx , idx + m , [&](int x , int y){
        return e[x].w < e[y].w;
    });
    // Building MST 
    DSU d(n);
    for(int i = 0; i < m; ++i){
        int I = idx[i];
        d.Union(e[I].u , e[I].v , e[I].w);
    }
    d.Build();
    
}
