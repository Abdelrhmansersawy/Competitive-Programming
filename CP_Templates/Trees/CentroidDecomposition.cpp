const int N = 1e5 + 9;
vector<int> adj[N];
struct CentroidDecomposition{
	vector<int> removal , sz;
	CentroidDecomposition(int n){
		removal.assign(n , 0);
		sz.assign(n , 0);
		build(0, -1);
	}
	void build(int u , int p){
		int n = dfs(u , p);
		int centriod = getCentriod(u , p , n);
		removal[centriod] = true;
		// depend on the problem
		
		for(auto &v : adj[centriod]) if(!removal[v]) 
			build(v , centriod);
	}
	int dfs(int u , int p){
		sz[u] = 1;
		for(auto &v : adj[u]) if(v != p && !removal[v])
			sz[u] += dfs(v , u);
		return sz[u];
	}
	int getCentriod(int u , int p , int n){
		for(auto &v : adj[u]) if(v != p && !removal[v]){
			if(sz[v] * 2 > n) 
				return getCentriod(v , u , n);
		}
		return u;
	}

};
