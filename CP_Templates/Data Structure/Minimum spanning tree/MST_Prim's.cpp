int n , m; cin >> n >> m;
vector<pair<int,int>> adj[n]; // {v , w}
for(int i = 0;i < m; ++i){
    int u , v , w; cin >> u >> v >> w;
    --u; --v;
    adj[u].emplace_back(v , w);
    adj[v].emplace_back(u , w);
}
priority_queue<pair<int,int>> q; // {-w , u}
vector<int> vis(n);
q.push({0 , 0}); // start from any node
ll cost = 0;
while(q.size()){
    auto [d , u] = q.top(); q.pop();
    if(vis[u]) continue;
    d *= -1; vis[u] = 1;
    cost += d;
    for(auto &[v , w] : adj[u]) if(vis[v] == 0){
        q.push({-w , v});
    }
}
cout << cost;
