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
void preDFS(int u , int p){
    st[u] = dfs_time++;
    ver[ st[u] ] = u;
    sz[u] = 1, big[u] = -1;
    for(auto v : adj[u]) if(v != p){
        preDFS(v,u);
        sz[u] += sz[v];
        if(big[u] == -1 || sz[v] > sz[ big[u] ]) big[u] = v;
    }
    ft[u] = dfs_time;
}
void sackDFS(int u, int p, bool keep){
    int bigChild = big[u];

    // Process all light children
    for (auto [v, ind] : adj[u]) {
        if (v != p && v != bigChild) {
            sackDFS(v , u , false);
        }
    }

    if(bigChild != -1) sackDFS(bigChild, u, 1);  // bigChild marked as big and not cleared from cnt

    for(auto v : adj[u]){
        if(v != p && v != bigChild){
            for(int p = st[v]; p < ft[v]; p++){
                // TODO: Add your information about ver[p]
                
            }
            
        }
           
    }
    // TODO: Add your information about u


    // TODO: All information about the subtree of  u  is kept, and you can now query it.


    if(keep == 0){
        for(int p = st[u]; p < ft[u]; p++){
            // TODO: Remove the added information about ver[p]

        }
    }
        
}
// Calling -> sackDFS(root, -1 , 0)
