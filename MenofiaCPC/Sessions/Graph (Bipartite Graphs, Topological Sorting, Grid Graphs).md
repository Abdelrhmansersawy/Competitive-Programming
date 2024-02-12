> Q Success in nothing more than a few straightforward disciplines put into daily practice.
> \- Jim Rohn
<h1 style="text-align:center;"><font color="#ffb703" > Bipartite Graph </font> </h1>

**Standard Problem**
>Given $2 N$ player and asked you if we can divide it into **two  teams**  but there is $M$ restriction.
Each restriction contains two player $(a,b)$ where a player $a$ can't be in the **same** team of player $b$ .
**Constraints**
$2 \leq N \leq 10^5, 0 \leq M \leq 2 * 10^5$
**Test Cases**
N: 4, M: 3
1 3
2 3
4 1
Answer: Yes
**Explanation**
{1, 2} ,  {3,4} -> Valid division
{1,4} , {2, 3} -> Invalid division

<font color = "#00b4d8">Complete search O(2^n):</font>
```c++
const int N = 2e5 + 9;
int n,m;
pair<int,int> v[N];
int id[N];
void solve(int i){
   if(i == n){
    // check
    bool valid = true;
     for(int i = 0; i < m; ++i){
         if(id[v[i].f] == id[v[i].s]) valid = false;
     }
     if(valid){
        for(int i = 0; i < n; ++i)
            cerr << id[i] << " ";
        cerr << '\n';
     }
    return;
   }
   // put player i in team1
   id[i] = 1;
   solve(i + 1);
   // put player i in team2
   id[i] = 2;
   solve(i + 1);
}
int main(){
  cin >> n >> m;
 for(int i = 0; i < m; ++i){
    cin >> v[i].first >> v[i].second;
    v[i].first--;
     v[i].second--;
 }
  solve(0);
}
```
<font color = "#00b4d8">Check if graph is Bipartite or not</font>
```c++
const int N = 2e5 + 9;
vector<int> adj[N];
int color[N];
bool is_Bipartite;
void dfs(int u , int c){
    color[u] = c;
    for(auto &v : adj[u]){
        if(color[v] == -1) // node v doesn't color yet
            dfs(v, c ^ 1);
        else{ // v colored
            if(color[u] == color[v])
                is_Bipartite = false; // graph can't be bipartite
        }
    }
}
int main(){
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
    int n, m; cin >> n >> m;
    for(int i = 0; i < m; ++i){
        int u , v; cin >> u >> v;
        --u; --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    for(int i = 0; i < n; ++i)
        color[i] = -1; // not colored yet
    is_Bipartite = true;
    dfs(0, 0);
    if(is_Bipartite){
        for(int i = 0; i < n; ++i)
            cout << color[i] << " ";
    }else cout << "Impossible";
}
```
***
<h1 style="text-align:center;"><font color="#ffb703" > Topological Sorting </font> </h1>
1. DFS using Pointer
```c++
const int N = 2e5 + 9;
int topo[N] , vis[N],n,m , p;
vector<int> adj[N];
void dfs(int u){
    vis[u] = 1;
    for(auto &v : adj[u]) if(vis[v] == false){
        dfs(v);
    }
    topo[p--] = u;
}
int main(){
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
    cin >> n >> m;
    for(int i = 0; i < m; ++i){
        int u , v; cin >> u >> v;
        --u; --v;
        adj[u].emplace_back(v);
    }
    p = n - 1;
    for(int i = 0; i < n; ++i) if(vis[i] == false)
        dfs(i);
    for(int i = 0; i < n; ++i) cout << topo[i] + 1<< " ";
}
```
2. DFS using vector
```c++
const int N = 2e5 + 9;
int vis[N],n,m , p;
vector<int> adj[N];
vector<int> topo;
void dfs(int u){
    vis[u] = 1;
    for(auto &v : adj[u]) if(vis[v] == false){
        dfs(v);
    }
    topo.emplace_back(u);
}
int main(){
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
    cin >> n >> m;
    for(int i = 0; i < m; ++i){
        int u , v; cin >> u >> v;
        --u; --v;
        adj[u].emplace_back(v);
    }
    p = n - 1;
    for(int i = 0; i < n; ++i) if(vis[i] == false)
        dfs(i);
    reverse(topo.begin(), topo.end());
    for(int i = 0; i < n; ++i) cout << topo[i] + 1<< " ";
}
```
3. Khan's algorthim
```c++
const int N = 2e5 + 9;
int n,m , inDeg[N];
vector<int> adj[N];
int main(){
    cin >> n >> m;
    for(int i = 0; i < m; ++i){
        int u , v; cin >> u >> v;
        --u; --v;
        adj[u].emplace_back(v);
        inDeg[v]++;
    }
    queue<int> q;
    for(int i = 0; i < n; ++i) if(inDeg[i] == 0)
        q.push(i);
    vector<int> topo;
    while(q.size()){
        // there are nodes
        int u = q.front(); q.pop();
        topo.emplace_back(u);
        vector<int> V;
        for(auto &v : adj[u]){
            inDeg[v]--; // remove an edge between {u -> v}
            if(inDeg[v] == 0) q.push(v);
        }
    }
    for(int i = 0; i < n; ++i) cout << topo[i] + 1 << " ";
}
```
4. Khan's algorthim v2
```c++
const int N = 2e5 + 9;
int n,m , inDeg[N];
vector<int> adj[N];
int main(){
    cin >> n >> m;
    for(int i = 0; i < m; ++i){
        int u , v; cin >> u >> v;
        --u; --v;
        adj[u].emplace_back(v);
        inDeg[v]++;
    }
    queue<int> q;
    for(int i = 0; i < n; ++i) if(inDeg[i] == 0)
        q.push(i);
    vector<int> topo;
    while(q.size()){
        int sz = q.size();
        vector<int> V;
        while(sz--){
            // All element from the same level
            int u = q.front(); q.pop();
            debug(u);
            topo.emplace_back(u);
            for(auto &v : adj[u]){
                inDeg[v]--; // remove an edge between {u -> v}
                if(inDeg[v] == 0) V.push_back(v);
            }
        } 
        for(auto &i : V) q.push(i);       
    }
    for(int i = 0; i < n; ++i) cout << topo[i] + 1 << " ";
}
```
***
<h1 style="text-align:center;"><font color="#ffb703" > Grid Graph </font> </h1>
- Instead of representing a graph using adjacent list, we will use from directions (up, down, left, right) as neighbour of vertice.
  ## <font color = "#00b4d8">Basic DFS in grid</font>
```c++
int dx[] = {1,1,0,0};
int dy[] = {0,0,1,1};
int n,m;
int grid[n][m]; // {0: block cell, 1: empty cell}
bool vis[n][m];
bool valid(int i , int j){ return i >= 0 && j >= 0 && i < n && j < m; }
void dfs(int i , int j){
	vis[i][j] = true;
    for(int o = 0; o < 4; ++o){
	    int ii = i + dx[i] , jj = j + dy[j];
	    if(valid(ii,jj) && grid[ii][jj] && vis[ii][jj] == false) dfs(ii,jj);
    }
}
```