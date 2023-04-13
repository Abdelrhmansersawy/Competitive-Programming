# Content of Table
- [DFS](https://github.com/Abdelrhmansersawy/Competitive_Programming/tree/main/MenofiaCPC/Phase2%20Training/introduction%20in%20DFS#dfs)
- [BFS](https://github.com/Abdelrhmansersawy/Competitive_Programming/tree/main/MenofiaCPC/Phase2%20Training/introduction%20in%20DFS#bfs)
- [Applications of DFS](https://github.com/Abdelrhmansersawy/Competitive_Programming/tree/main/MenofiaCPC/Phase2%20Training/introduction%20in%20DFS#applications-of-dfs)
	- [connected component](https://github.com/Abdelrhmansersawy/Competitive_Programming/tree/main/MenofiaCPC/Phase2%20Training/introduction%20in%20DFS#1-connected-component)
	- [detect cycle](https://github.com/Abdelrhmansersawy/Competitive_Programming/tree/main/MenofiaCPC/Phase2%20Training/introduction%20in%20DFS#2-detect-cycle)
	- [Bipartite graph](https://github.com/Abdelrhmansersawy/Competitive_Programming/tree/main/MenofiaCPC/Phase2%20Training/introduction%20in%20DFS#3-bipartite-graph-)
***
## _Graph Traversal_
- DFS (Depth First Search)
- BFS (Breath First Search)
## _DFS_ 
 - is an algorithm for traversing or searching tree or graph data structures.
 - can be writted in recursive or iterative (most used is recursive)

![ezgif com-resize (2)](https://user-images.githubusercontent.com/65075626/231601722-86c404af-15f9-4a86-9bdc-3cd4fb55fcb5.gif)
![new_dfs](https://user-images.githubusercontent.com/65075626/231601711-953953b8-f10e-4a50-b42d-c710d3397c05.gif)
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
## _BFS_
- is an algorithm for traversing or searching tree or graph data structures.
- one of most it's application is getting shortest path from one node to other node
- written in iterative way _studing code soon_ 
![ezgif com-resize (3)](https://user-images.githubusercontent.com/65075626/231601717-ad1a68a9-c926-4e23-83bf-572240a14c01.gif)
***
## _Applications of DFS:_

### 1. Connected Component
#### undirected Graph:
![anim](https://user-images.githubusercontent.com/65075626/231601724-6581ce32-3917-465d-b80d-bf8e362f2a24.gif)
![8dbe5d89e58b67f3d8e4d8e0e8eb3358ba921b28](https://user-images.githubusercontent.com/65075626/231601734-a5cb3b12-01ec-4b39-8ae1-a3dcad00fc7e.png)
##### using DFS
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
#### directed Graph:
	- use some advanced algrothims you will know it soon but if you are intereseted  search in one of these keywords
		`Strong Connect Component`
		`Tarjan algrothim`
		`kosaraju algrothim`
***
### 2. Detect Cycle
#### undirected Graph:
![1_VHzWi2uzMN1TYv8mUmYqnA](https://user-images.githubusercontent.com/65075626/231610533-f4227d5c-1d16-4cfb-98c0-74715b790199.gif)
- code : run normal dfs if you go to node that already visited , it 's cylce.
``` c++
const int N = 1e5;  // largest number of node in graph
vector<int> adj[N] , vis(N);
bool cycle;
void dfs(int u){
   vis[u] =  true;
   for(auto &v : adj[u]){
	if(vis[v] == false) dfs(v)
	else{
            // detect Cycle
	    cycle = true;
	}
   }
}
int main(){
   for(int i = 0 ; i < n ; i++){
      if(vis[i] == false) dfs(i);
   }
   cout << (cycle ? 1 : 0);
}
```
#### directed Graph:
![dfs](https://user-images.githubusercontent.com/65075626/231611124-237affcb-0e66-42f3-a5d5-f868b81d0836.gif)
- code : you will use three color (white : node not visited , Gray : node visited + in stack , Black : node visited + not in stack) , run normal dfs  
  first color node with gray then go to it's neighbours if you find node colored with gray after finish it's neighbours color node with black
``` c++
const int N = 1e5;  // largest number of node in graph
vector<int> adj[N] , vis(N);
bool cycle;
void dfs(int u){
   vis[u] =  1; // Gray
   for(auto &v : adj[u]){
	if(vis[v] == 0) dfs(v)
	else if(vis[v] == 1) cycle = 1;
   }
   vis[u] = 2; // Black
}
int main(){
   for(int i = 0 ; i < n ; i++){
      if(vis[i] == false) dfs(i);
   }
   cout << (cycle ? 1 : 0);
}
```
***
### 3. Bipartite Graph :
is a graph whose vertices can be divided into two disjoint and independent sets and , that is every edge connects a vertex in to one in.
![tumblr_nmi642nElc1unvfcho1_400](https://user-images.githubusercontent.com/65075626/231614867-79ce4e4a-8369-40be-985d-063a99ff363a.gif)
``` c++
const int N = 1e5;  // largest number of node in graph
vector<int> adj[N] , color(N , -1); // -1 refer to node isn't colored yet
bool can = true;
void dfs(int u , int c){
   color[u] = c;
   for(auto &v : adj[u]){
	if(color[v] == -1) dfs(v , 1 - c); // toggle for color
	else if(color[u] == color[v]) can = false; // you can't make this graph bipartite
   }
}
int main(){
   for(int i = 0 ; i < n ; i++){
      if(color[i] == -1) dfs(i);
   }
   if(can == false) cout << "You can't make graph bipartite";
   else{
        cout << "Color of every Node is";
   	for(int i = 0 ; i < n ; i++) cout << c[i] << " ";
   }
}
```
### 4. Topolgical Sorting :
#### What 's mean by DAG ?
 directed acyclic graph (DAG) is a directed graph with no directed cycles.
 ![Directed_acyclic_graph svg](https://user-images.githubusercontent.com/65075626/231617659-4aed372e-9455-48c2-b334-625a870be8bb.png)
#### Topolgical Sorting :is a linear ordering of vertices such that for every directed edge u v, vertex u comes before v in the ordering.
- Note: Topological Sorting for a graph is not possible if the graph is not a DAG.
 ![algo](https://user-images.githubusercontent.com/65075626/231617727-6682681e-d122-46dd-bae8-dc0346bce41e.gif)
##### Coding using DFS
``` c++
const int N = 1e5;  // largest number of node in graph
vector<int> adj[N];
int n , m , i , topo[N] , vis[N];
void dfs(int u){
   vis[u] = 0;
   for(auto &v : adj[u]){
	if(vis[v] == 0) dfs(v);
   }
   topo[i--] = u;
}
int main(){
   cin >> n >> m;
   for(int i = 0 ; i < m ; i++){
   	int u , v; cin >> u >> v;
	--u; --v; cin >> u >> v;
	adj[u].emplace_back(v);
   }
   i = n - 1; // make pointer point to that last of array
   for(int j = 0 ; j < n ; j++)
   	if(vis[j] == 0) dfs(j);
   // output one of possible Topolgical sorting
   for(int j = 0 ; j < n ; j++) cout << topo[j] << " ";
}
