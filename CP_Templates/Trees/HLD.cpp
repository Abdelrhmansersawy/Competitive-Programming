#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i , st , ed) for(int i = st; i < ed; i++)
#define f first
#define s second
#define all(v) v.begin() , v.end()
#ifndef ONLINE_JUDGE 
#define debug(x) cerr << #x << ": " << x << '\n';
#else
#define debug(x)
#endif
const int N = 2e5 + 9;
vector<int> adj[N];
int heavy[N], head[N], par[N], pos[N], dep[N],  cur_pos;
int dfs(int u = 0){
    heavy[u] = -1; // node is leaf
    int size = 1 , max_size = 0;
    for(auto &v : adj[u]) if(v != par[u]){
        par[v] = u;
        dep[v] = dep[u] + 1;
        int cur = dfs(v);
        if(cur > max_size){
            heavy[u] = v;
            max_size = cur;
        }
        size += cur;
    }
    return size;
}
void decomposition(int u = 0, int h = 0){
    head[u] = h;
    pos[u] = cur_pos++;
    if(~heavy[u])
        decomposition(heavy[u], h);
    for(auto &v : adj[u]) if(v != par[u] && v != heavy[u])
        decomposition(v,v);
}
int path(int u , int v){
    int ans = 0;
    for(; head[u] != head[v]; v = par[head[v]]){
        if(dep[head[u]] > dep[head[v]]) swap(u,v);
        // proccess interval: [ pos[head[v]] , pos[v]  ]

    }   
    if(dep[u] > dep[v]) swap(u,v);
    // proccess interval: [ pos[u] , pos[v] ]

    return ans;
}

// Applications

// Required: Flatten tree + lca
vector<pair<int,int>> genPathInterval(int u, int v) {
    if(u == v) return {{in[u], 1}};
    
    int LCA = lca(u, v);
    vector<pair<int,int>> inter;
    
    while(head[u] != head[LCA]) {
        inter.push_back({seq.size() - in[u], in[u] - in[head[u]] + 1});
        u = par[head[u]];
    }
    inter.push_back({seq.size() - in[u], in[u] - in[LCA] + 1});
    
    vector<pair<int,int>> secondPath;
    while(head[v] != head[LCA]) {
        secondPath.push_back({in[head[v]], in[v] - in[head[v]] + 1});
        v = par[head[v]];
    }
    if(in[LCA] + 1 <= in[v]) {
        secondPath.push_back({in[LCA] + 1, in[v] - in[LCA]});
    }
    
    for(int i = secondPath.size() - 1; i >= 0; i--)
        inter.push_back(secondPath[i]);
        
    return inter;
}

int main(){
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif
    int n,q; cin >> n >> q;
    vector<int> a(n);
    for(int i = 0; i < n; ++i) cin >> a[i];
    for(int i = 0; i < n - 1;++i){
        int u , v; cin >> u >> v;
        --u; --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(); decomposition();
}
