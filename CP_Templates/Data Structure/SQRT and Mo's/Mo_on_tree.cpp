#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i , st , ed) for(int i = st; i < ed; i++)
#define f first
#define s second
#define all(v) v.begin() , v.end()

// ────────────────────────────────
// Mo's Algorithm on Tree Template
// ────────────────────────────────

const int MAXN = 200005;
const int LOGN = 20;

int n , q , BLOCK;
vector<int> adj[MAXN];
int val[MAXN];              // node value (if needed)
int answer[MAXN];

// Euler tour
int timer_e = 0;
int euler[2 * MAXN];
int tin[MAXN] , tout[MAXN];

// LCA
int up[MAXN][LOGN];
int depthArr[MAXN];

void dfs(int u , int p){
    up[u][0] = (p < 0 ? u : p);
    for(int j = 1; j < LOGN; ++j) up[u][j] = up[ up[u][j-1] ][j-1];

    tin[u] = timer_e;
    euler[timer_e++] = u;

    for(int v : adj[u]){
        if(v == p) continue;
        depthArr[v] = depthArr[u] + 1;
        dfs(v , u);
    }

    tout[u] = timer_e;
    euler[timer_e++] = u;
}

int lca(int a , int b){
    if(depthArr[a] < depthArr[b]) swap(a,b);
    int diff = depthArr[a] - depthArr[b];
    for(int j = 0; j < LOGN; ++j) if(diff & (1<<j)) a = up[a][j];
    if(a == b) return a;
    for(int j = LOGN-1; j >= 0; --j)
        if(up[a][j] != up[b][j])
            a = up[a][j] , b = up[b][j];
    return up[a][0];
}

struct Query{
    int l , r , id , lca;
    bool operator<(const Query &o) const{
        int b1 = l / BLOCK , b2 = o.l / BLOCK;
        if(b1 != b2) return b1 < b2;
        return (b1 & 1) ? (r > o.r) : (r < o.r);
    }
};

int vis[MAXN];   // whether node currently active
// add your query-related globals here (freq, sum, etc.)

// ────────────────────────────────
// modify these according to problem
// ────────────────────────────────
void add_node(int node){
    // called when node becomes active
}

void remove_node(int node){
    // called when node becomes inactive
}

void toggle(int idx){
    int node = euler[idx];
    if(vis[node]) remove_node(node) , vis[node] = 0;
    else add_node(node) , vis[node] = 1;
}
// ────────────────────────────────

void runMo(vector<Query> &queries){
    sort(all(queries));
    int mo_l = 0 , mo_r = -1;

    for(auto &qu : queries){
        while(mo_l > qu.l) toggle(--mo_l);
        while(mo_r < qu.r) toggle(++mo_r);
        while(mo_r > qu.r) toggle(mo_r--);
        while(mo_l < qu.l) toggle(mo_l++);

        if(qu.lca != -1) toggle(tin[qu.lca]);

        // store answer for query id here
        // answer[qu.id] = ...

        if(qu.lca != -1) toggle(tin[qu.lca]);
    }
}

void solve(){
    cin >> n >> q;
    rep(i , 0 , n){
        cin >> val[i];
        // compress or normalize if needed
    }

    rep(i , 0 , n-1){
        int u , v; cin >> u >> v;
        --u; --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    timer_e = 0;
    dfs(0 , -1);
    BLOCK = sqrt(timer_e) + 1;

    vector<Query> queries;
    rep(i , 0 , q){
        int u , v; cin >> u >> v;
        --u; --v;

        if(tin[u] > tin[v]) swap(u,v);
        int w = lca(u,v);
        Query Q; Q.id = i;

        if(w == u){
            Q.l = tin[u];
            Q.r = tin[v];
            Q.lca = -1;
        } else {
            Q.l = tout[u];
            Q.r = tin[v];
            Q.lca = w;
        }
        queries.push_back(Q);
    }

    runMo(queries);

    rep(i , 0 , q) cout << answer[i] << '\n';
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    solve();
}
