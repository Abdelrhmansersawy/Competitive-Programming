/*
Problem link: https://codeforces.com/group/Rilx5irOux/contest/564406/problem/H
  Problem Statement:
- Given n towns connected by n-1 roads forming a tree
- m trade agreements between towns
- Each agreement affects all towns on shortest path between si and ti
- Towns u,v can trade if shortest path between them covered by an agreement
- Must count valid trading pairs where u<v

Input:
- n, m (2≤n,m≤105)
- n-1 lines: xi,yi road connections
- m lines: si,ti trade agreement paths

Output: 
- Number of valid trading pairs
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define f first
#define s second
const int N = 1e5 + 9; // TODO: change it to maximum possible N
const int LOG = 17;
int dfs_time = 0, cur_pos = 0;
int st[N] , ft[N] , big[N] , ver[N] , sz[N];
int head[N], par[N], dep[N] , up[N][LOG];
int n , m , bst[N];
ll ans;
vector<int> adj[N] , paths[N];

// Lazy segment tree
struct node{
    int mn , cnt;
    node(int x){ mn = x; cnt = 1;}
    node(){};
    node operator + (const node other) const{
        node res;
        res.mn = min(mn , other.mn);
        if(mn < other.mn) res.cnt = cnt;
        else if(other.mn < mn) res.cnt = other.cnt;
        else res.cnt = cnt + other.cnt;
        return res;
    }

} tree[4*N];
int lazy[4*N];
void push_down(int x , int par){
    lazy[x] += lazy[par];
    tree[x].mn += lazy[par];
}
void propogate(int x , int l , int r){
    if(r - l == 1) return;
    push_down(2*x+1,x);
    push_down(2*x+2,x);
    lazy[x] = 0;
}
void build(int x = 0 , int l = 0 , int r = n){
    if(r - l == 1){ tree[x] = node(0); return; }
    int mid = (l+r)/2;
    build(2*x+1,l,mid);
    build(2*x+2,mid,r);
    tree[x] = tree[2*x+1] + tree[2*x+2];
}
void upd(int lx , int rx , int v, int x = 0 , int l = 0 , int r = n){
    propogate(x,l,r);
    if(l >= lx && r <= rx){
        tree[x].mn += v;
        lazy[x] = v;
        return;
    }
    if(r <= lx || l >= rx) return;
    int mid = (l+r)/2;
    upd(lx,rx,v,2*x+1,l,mid);
    upd(lx,rx,v,2*x+2,mid,r);
    tree[x] = tree[2*x+1] + tree[2*x+2];
}
node qry(int lx , int rx , int x = 0 , int l = 0 , int r = n){
    propogate(x,l,r);
    if(l >= lx && r <= rx) return tree[x];
    if(r <= lx || l >= rx) return node(2e9);
    int mid = (l+r)/2;
    return qry(lx,rx,2*x+1,l,mid) + qry(lx,rx,2*x+2,mid,r);
}
int countZero(int l , int r){
    if(l > r) return 0;
    auto ans = qry(l,r+1);
    if(ans.mn) return 0;
    // cerr << "\n" << "Min: " << ans.mn <<  " cnt: " << ans.cnt  << " sz: " << r - l + 1 << '\n';
    return ans.cnt;
}

// HLD
void preDFS(int u = 0, int p = 0){
    sz[u] = 1, big[u] = -1;
    
    // Build LCA
    dep[u] = dep[p] + 1;
    up[u][0] = p;
    par[u] = p; 
    for(int x = 1; x < LOG; ++x){
        up[u][x] = up[ up[u][x-1] ][x-1];
    }

    for(auto v : adj[u]) if(v != p){
        preDFS(v,u);
        sz[u] += sz[v];
        if(big[u] == -1 || sz[v] > sz[ big[u] ]) big[u] = v;
    }
}

void decomposition(int u = 0, int h = 0){
    head[u] = h;
    st[u] = dfs_time++;
    // cerr << u + 1 << ' ';
    ver[ st[u] ] = u;
    
    if(~big[u])
        decomposition(big[u], h);
    for(auto &v : adj[u]) if(v != par[u] && v != big[u])
        decomposition(v,v);
    ft[u] = dfs_time;
}
void upd_path(int u , int v , int val){
    int ans = 0;
    for(; head[u] != head[v]; v = par[head[v]]){
        if(dep[head[u]] > dep[head[v]]) swap(u,v);
        // proccess interval: [ st[head[v]] , st[v]  ]
        upd(st[head[v]] , st[v] + 1, val);

    }   
    if(dep[u] > dep[v]) swap(u,v);
    // proccess interval: [ st[u] , st[v] ]
    upd(st[u] , st[v] + 1, val);
}

// DSU on tree
void sackDFS(int u, int p, bool keep){
    int bigChild = big[u];

     // run a dfs on small childs
    for(auto v : adj[u]){
        if(v != p && v != bigChild) sackDFS(v , u, 0); 
    }

    if(bigChild != -1) sackDFS(bigChild, u, 1);  // bigChild marked as big and not cleared from cnt
    for(auto v : adj[u]){
        if(v != p && v != bigChild){
            for(int p = st[v]; p < ft[v]; p++){
                // Add your information about ver[p]
                int x = ver[p];
                // cerr << "+ " << x + 1 << '\n';
                for(auto &y : paths[x]) upd_path(x,y,+1);
            }
            
        }
           
    }
    // Add your information about u
    // cerr << "+ " << u + 1 << '\n';
    for(auto &y : paths[u]) upd_path(u,y,+1);

    // All information about the subtree of  u  is kept, and you can now query it.
    // cerr << "u: " << u + 1 << " , ans: " << (n - ft[u]) - countZero(ft[u] , n-1) << '\n';
    // cerr << "After: " << n - ft[u] << ' ' << " zero: " << countZero(ft[u] , n - 1) << '\n';
    ans += (n - ft[u]) - countZero(ft[u] , n-1);
    ans += dep[u] - bst[u];

    if(keep == 0){
        for(int p = st[u]; p < ft[u]; p++){
            // Remove the added information about ver[p]
            int x = ver[p];
            // cerr << "- " << x+1 << '\n';
            for(auto &y : paths[x]) upd_path(x,y,-1);
        }
    }
        
}

// Compute LCA
int getLCA(int x , int y){
    if(dep[x] < dep[y]) swap(x,y);
    int k = dep[x] - dep[y];
    for(int i = 0; i < LOG; ++i) if((k>>i) & 1) x = up[x][i];
    if(x == y) return x;

    for(int i = LOG - 1; i >= 0; --i) if(up[x][i] != up[y][i]){
        x = up[x][i];
        y = up[y][i];
    } 

    assert(up[x][0] == up[y][0]);
    return up[x][0];
}

void _dfs(int u , int p){
    for(auto &v : adj[u]) if(v != p){
        _dfs(v,u);
        bst[u] = min(bst[u] , bst[v]);
    }
}
int main(){
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif
    cin >> n >> m;
    for(int i = 1; i < n; ++i){
        int u,v; cin >> u >> v;
        --u; --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    preDFS(0,0);
    decomposition(0,0);
    build();

    for(int i = 0; i < n; ++i) bst[i] = dep[i];

    for(int i = 0; i < m; ++i){
        int x,y; cin >> x >> y;
        --x; --y;
        if(st[x] > st[y]) swap(x,y);
        int lca = getLCA(x,y);
        bst[x] = min(bst[x] , dep[lca]);
        bst[y] = min(bst[y] , dep[lca]);
        if(lca == x) continue;
        paths[x].emplace_back(y);
    }

    _dfs(0,0);
    sackDFS(0,0,0);

    cout << ans;
}
