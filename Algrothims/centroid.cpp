vector<int> adj[N] , centriod, sz(N);
int n;
void dfs(int u , int par){
  sz[u] = 1;
  bool is_Centriod = true;
  for(auto &v : adj[u]){
    if(v != par){
      dfs(v , u);
      sz[u] += sz[v];
      if(sz[v] * 2 > n) is_Centriod = false;
    }
  }
  // check above tree
  if((n - sz[u]) * 2 > n) is_Centriod = false;
  if(is_Centriod) centriod.emplace_back(u);
}
/*
  in main 
  dfs(0 , -1)
*/
