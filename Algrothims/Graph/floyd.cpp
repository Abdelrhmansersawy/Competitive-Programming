int n , m; cin >> n >> m;
vector<vector<ll>> adj(n , vector<ll>(n , OOLL));
for(int i = 0; i < n; ++i) adj[i][i] = 0;
for(int i = 0; i < m; ++i){
int u , v; ll w; cin >> u >> v >> w;
--u; --v;
adj[u][v] = min(adj[u][v] , w);
adj[v][u] = min(adj[v][u] , w);
}
// Floyd
rep(k , 0, n) rep(i , 0 , n) rep(j , 0, n){
adj[i][j] = min(adj[i][j] , adj[i][k] + adj[k][j]);
}
