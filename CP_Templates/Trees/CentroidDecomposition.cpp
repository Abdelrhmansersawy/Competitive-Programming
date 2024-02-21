const int N = 1e5 + 9;
vector<int> adj[N];
struct CentroidDecomposition{
	vector<int> removal , sz , ans;
	vector<vector<pair<int,int>>> ansestors;
	CentroidDecomposition(int n){
		removal.assign(n , 0);
		sz.assign(n , 0);
		ansestors.assign(n , vector<pair<int,int>>());
		ans.assign(n , (int)1e9);
		build(0, -1);
	}
	void build(int u , int p){
		int n = dfs(u , p);
		int centriod = getCentriod(u , p , n);
		removal[centriod] = true;
		for(auto &v : adj[centriod]) if(!removal[v])
			getDis(v , centriod);
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
	void getDis(int u , int centriod , int p = -1 , int d = 1){
		for(auto &v : adj[u]) if(v != p && !removal[v])
			getDis(v , centriod , u , d + 1);
		ansestors[u].emplace_back(centriod , d);
	}
};
