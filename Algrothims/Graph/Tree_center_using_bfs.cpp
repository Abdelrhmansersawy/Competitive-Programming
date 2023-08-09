/*
    Finding Tree Center and Tree diameter in Time O(n).
    Algo : 
        1- Starting BFS from any node.
        2- Find the farthest node (Start) from it.
        3- Starting BFS from (Start).
        5- Find the farthest node (End) from (Start)
        6- The path from (Start) and (End) is one possible diameter for the tree.
*/
int n; cin >> n;   
    for(int i = 0; i < n - 1; ++i){
    	int u , v; cin >> u >> v;
    	--u; --v;
    	adj[u].emplace_back(v);
    	adj[v].emplace_back(u);
    }
    auto bfs = [&](int st){
    	vector<int> dis(n , -1);
    	queue<int> q;
    	q.push(st); dis[st] = 0;
   		while(q.size()){
   			int u = q.front(); q.pop();
   			for(auto &v : adj[u]) if(dis[v] == -1){
   				dis[v] = dis[u] + 1; pre[v] = u;
   				q.push(v);
   			}
   		}
   		return max_element(dis.begin() , dis.end()) - dis.begin();
    };
    int Start = bfs(0) , End = bfs(Start);
    vector<int> v;
    for(int i = End; i != Start; i = pre[i])
    	v.emplace_back(i);
    int center = v[v.size() / 2];
