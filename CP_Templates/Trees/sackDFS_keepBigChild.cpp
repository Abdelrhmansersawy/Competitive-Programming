/*
DSU on tree by keeping largest child
Let:
    - st[u] dfs starting time of vertex u,
    - ft[u] be it's finishing time and
    - ver[time] is the vertex which it's starting time is equal to time.
    - sz[u] is the size of subtree of node

Pros: You can keep segment tree for each node with using extra memory
*/

const int N = 1e5; // TODO: change it to maximum possible N
int dfs_time = 0;
int st[N] , ft[N] , big[N] , ver[N] , sz[N];
vector<int> adj[N];
void preDFS(int v = 0){
    st[v] = dfs_time++;
    ver[ st[v] ] = v;
    sz[v] = 1, big[v] = -1;
    for(auto u : adj[v]){
        preDFS(u);
        sz[v] += sz[u];
        if(big[v] == -1 || sz[u] > sz[ big[v] ]) big[v] = u;
    }
    ft[v] = dfs_time;
}
void sackDFS(int u, int p, bool keep){
    int bigChild = big[u];
    if(bigChild != -1) sackDFS(bigChild, u, 1);  // bigChild marked as big and not cleared from cnt
    for(auto v : adj[u]){
        if(v != p && v != bigChild){
            for(int p = st[v]; p < ft[v]; p++){
                // TODO: Add your information about ver[p]
                
            }
            
        }
           
    }
    // TODO: keep information about u


    // TODO: All information about the subtree of  u  is kept, and you can now query it.


    if(keep == 0){
        for(int p = st[u]; p < ft[u]; p++){
            // TODO: Remove the added information about ver[p]

        }
    }
        
}
// Calling -> sackDFS(root, -1 , 0)
