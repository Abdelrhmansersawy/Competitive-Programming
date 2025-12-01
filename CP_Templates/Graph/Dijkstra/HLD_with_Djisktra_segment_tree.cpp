/*
Problem: Codeforces 1904F - Beautiful Tree
Assign distinct values 1..N to a tree's nodes such that M constraints are met: for specific paths (a, b), node c must have the min (Type 1) or max (Type 2) value.
These constraints imply strict inequalities (e.g., C < all other nodes on path a-b); output a valid assignment or -1 if impossible.

Approach:
Model the constraints as a Directed Acyclic Graph where an edge u->v implies val(u) < val(v); "C is min" adds edges C -> (Path \ C).
Optimize edge creation using HLD and a "Graph on Segment Tree" technique to connect node C to O(log N) path segments efficiently.
Perform a topological sort to check for cycles (-1) and assign values 1..N based on the topological order.

Problem link: https://codeforces.com/contest/1904/problem/F
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i , st , ed) for(int i = st; i < ed; i++)
#define f first
#define s second
#define all(v) v.begin() , v.end()

vector < vector < pair < int, ll >>> g;

int OFFSET = 0;
const int N = 2e5+9;
// init graph for original n
void init_graph(int n) {
    OFFSET = n;
    g.assign(9 * OFFSET + 5 + 1, {});
}

inline void add_edge(int u, int v, ll w) {
    g[u].push_back({ v, w });
}

// build segtree layers
void build(int node = 1, int l = 0, int r = OFFSET-1) {
    if (l == r) {
        add_edge(l, node + OFFSET, 0);
        add_edge(node + 5 * OFFSET, l, 0);
        return;
    }
    int mid = (l + r) >> 1;
    add_edge(2 * node + OFFSET, node + OFFSET, 0);
    add_edge(2 * node + 1 + OFFSET, node + OFFSET, 0);
    add_edge(node + 5 * OFFSET, 2 * node + 5 * OFFSET, 0);
    add_edge(node + 5 * OFFSET, 2 * node + 1 + 5 * OFFSET, 0);
    build(2 * node, l, mid);
    build(2 * node + 1, mid + 1, r);
}

// Add edges from single vertex u to all vertices in [lx, rx] (dir=1)
// or from all vertices in [lx, rx] to u (dir=0)
void upd(int lx, int rx, int dir, int u, ll w, int node = 1, int l = 0, int r = OFFSET-1) {
    if (rx < l || r < lx) return;
    if (lx <= l && r <= rx) {
        if (dir) add_edge(u, node + 5 * OFFSET, w);
        else add_edge(node + OFFSET, u, w);
        return;
    }
    int mid = (l + r) >> 1;
    upd(lx, rx, dir, u, w, 2 * node, l, mid);
    upd(lx, rx, dir, u, w, 2 * node + 1, mid + 1, r);
}


vector<int> adj[N];
int heavy[N], head[N], par[N], pos[N], dep[N],  who[N] , cur_pos;
int dfs(int u = 0){
    heavy[u] = -1; // node is leaf
    int size = 1 , max_size = 0;
    for(auto &v : adj[u]) if(v != par[u]){
        par[v] = u;
        dep[v] = dep[u] + 1;
        int cur = dfs(v);
        if(cur > max_size){
            heavy[u] = v;
            max_size = cur;
        }
        size += cur;
    }
    return size;
}
void decomposition(int u = 0, int h = 0){
    head[u] = h;
    who[cur_pos] = u;
    pos[u] = cur_pos++;
    if(~heavy[u])
        decomposition(heavy[u], h);
    for(auto &v : adj[u]) if(v != par[u] && v != heavy[u])
        decomposition(v,v);
}

void upd_path(int u, int v, int dir, int target) {
    int target_pos = pos[target];

    for (; head[u] != head[v]; v = par[head[v]]) {
        if (dep[head[u]] > dep[head[v]]) swap(u, v);
        
        int L = pos[head[v]];
        int R = pos[v];

        // Check if C is inside this interval
        if (L <= target_pos && target_pos <= R) {
            upd(L, target_pos - 1, dir, target_pos, 0); 
            upd(target_pos + 1, R, dir, target_pos, 0);
        } else {
            upd(L, R, dir, target_pos, 0);
        }
    }

    if (dep[u] > dep[v]) swap(u, v);
    
    int L = pos[u];
    int R = pos[v];

    if (L <= target_pos && target_pos <= R) {
        upd(L, target_pos - 1, dir, target_pos, 0);
        upd(target_pos + 1, R, dir, target_pos, 0);
    } else {
        upd(L, R, dir, target_pos, 0);
    }
}

int vis[10*N] , p[N] , id;
void topo_dfs(int u){
    vis[u] = 1;
    for(auto &[v,w] : g[u]){
        if(vis[v] == 1){ 
            cout << -1; 
            exit(0);
        }
        if(vis[v] == 0) topo_dfs(v);
    }
    vis[u] = 2;

    if(u < OFFSET) p[who[u]] = id--;
}

int main(){
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif

    int n , m; cin >> n >> m;
    id = n;

    init_graph(n);
    build();

    for(int i = 0; i < n - 1;++i){
        int u , v; cin >> u >> v;
        --u; --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(); decomposition();


    for(int i = 0; i < m; ++i){
        int t , a , b , c; cin >> t >> a >> b >> c;
        --a; --b; --c;
        upd_path(a , b , (t == 1) , c);
    }

    for(int i = 0; i < n; ++i) if(!vis[i]) topo_dfs(i);

    for(int i = 0; i < n; ++i) cout << p[i] << ' ';
}
