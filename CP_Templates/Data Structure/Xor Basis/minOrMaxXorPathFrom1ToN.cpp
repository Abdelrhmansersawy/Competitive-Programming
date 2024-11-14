/*
Given an undirected connected graph with non-negative integer edge weights and node numbers from 1
 to N, find a path from node 1 to node N such that the XOR of the weights of the edges along the path is maximized.
A path can pass through certain nodes or edges repeatedly. This means you are allowed to revisit the same node more than once, and if an edge is traversed multiple times, its weight must be included in the XOR each time it is used.
The following M lines each contain three integers u, v, and w — representing an edge between nodes u and v with a weight w.
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define f first
#define s second
const int N = 1e5 , LOG = 30;
int Basis[N];
void insert(int x){
    for(int i = LOG - 1; i >= 0; --i){
        if(!(x >> i & 1)) continue;
        if(Basis[i] == 0){
            Basis[i] = x;
            return;
        }
        x ^= Basis[i];
    }
}
int min_xor(int x){
    for(int i = LOG - 1; i >= 0; --i){
        if( (x ^ Basis[i]) < x) x ^= Basis[i];
    }
    return x;
}

int a[N];
bool vis[N];
vector<pair<int,int>> adj[N];
void dfs(int u , int p , int xor_sum){
    if(vis[u]){
        insert(xor_sum ^ a[u]);
        return;
    }
    vis[u] = 1;
    a[u] = xor_sum;
    for(auto &[v , w] : adj[u]) if(v != p){
        dfs(v , u , xor_sum ^ w);
    }
}
int main(){
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
    int n , m; cin >> n >> m;
    for(int i = 0; i < m; ++i){
        int u , v , w; cin >> u >> v >> w;
        --u; --v;
        adj[u].emplace_back(v , w);
        adj[v].emplace_back(u , w);
    }
    dfs(0,-1,0);
    cout << min_xor(a[n - 1]); // u can replace it with max xor
}
