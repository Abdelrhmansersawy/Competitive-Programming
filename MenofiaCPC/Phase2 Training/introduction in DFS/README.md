## _Graph Traversal_
- DFS (Depth First Search)
- BFS (Breath First Search)
## _DFS_ :
 - is an algorithm for traversing or searching tree or graph data structures.
 - can be writted in recursive or iterative (most used is recursive)
![[ezgif.com-resize (2).gif]]

![[new_dfs.gif]]
 ~~~ c++
 // Recursive Code of DFS
 const int N = 1e5; // largest number of nodes
 vector<int> adj[N] , vector<int> vis(N);
 void dfs(int u){
	 vis[u] = true;
	 for(auto &v : adj[u]){
		 if(vis[v] == false){
			 // Code here..
			 dfs(v);
		 }
	 }
 }
 ~~~
***
## _BFS_ :
- is an algorithm for traversing or searching tree or graph data structures.
- one of most it's application is getting shortest path from one node to other node
- written in iterative way _studing code soon_ 
![[ezgif.com-resize (3).gif]]
***
## _Applications of DFS:_

#### 1. Connected Component
- undirected Graph:
	- using DFS
	 ![[anim.gif]]
	![[8dbe5d89e58b67f3d8e4d8e0e8eb3358ba921b28.png]]
``` c++
const int N = 1e5;  // largest number of node in graph
vector<int> adj[N] , vis(N);

// optional
vector<int> comp(N);
vector<vector<int>> comps;

vector<int> comps(N);
void dfs(int u){
   vis[u] =  true;
   for(auto &v : adj[u]){
	if(vis[v] == false) dfs(v)
   }
   // optional
   comps.back().emplace_back(u);
   comp[u] = comps.size() - 1;
}
int main(){
   for(int i = 0 ; i < n ; i++){
      // optional
      comps.emplace_back(vector<int>());

      if(vis[i] == false) dfs(i);
   }
}
```
- directed Graph:
	- use some advanced algrothims you will know it soon but if you are intereseted  search in one of these keywords
		`Strong Connect Component`
		`Tarjan algrothim`
		`kosaraju algrothim`
***

