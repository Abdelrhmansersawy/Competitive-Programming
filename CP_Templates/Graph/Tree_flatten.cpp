const int N = 1e5 + 9;
int l[N] , r[N] , timer;
vector<int> adj[N];
void dfs(int u , int par){
    l[u] = ++timer;
    for(auto &v : adj[u]) if(v != par)
        dfs(v , u);
    r[u] = timer;
    // For each subTree u : [ l[u] , r[u] ]
}
