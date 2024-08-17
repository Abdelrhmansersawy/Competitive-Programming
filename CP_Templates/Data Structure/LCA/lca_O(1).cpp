// Problem Link: https://cses.fi/problemset/task/1688
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i , st , ed) for(int i = st; i < ed; i++)
#define f first
#define s second
#define all(v) v.begin() , v.end()
#ifndef ONLINE_JUDGE 
#define debug(x) cerr << #x << ": " << x << '\n';
#else
#define debug(x)
#endif
const int N = 2e5 + 9;
vector<int> adj[N];
vector<int> euler_tour; // in time
int in[4 * N] , Timer;
void dfs(int u = 0 , int p = 0){
    in[u] = Timer++;
    euler_tour.emplace_back(u);
    for(auto &v : adj[u]) if(v != p){
        dfs(v , u);
        euler_tour.emplace_back(u);
        Timer++;
    }
}
struct SparseTable {
    vector<int> log;
    vector<vector<pair<ll, int>>> spt;
 
    void init(int n) {
        log.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) {
            log[i] = 1 + log[i / 2];
        }
        int k = log[n] + 1;
        spt = vector<vector<pair<ll, int>>>(k, vector<pair<ll, int>>(n));
        for (int i = 0; i < n; i++) {
            spt[0][i] = { in[euler_tour[i]] , euler_tour[i] };
        }
        for (int j = 1; 1 << j <= n; j++) {
            for (int i = 0; i + (1 << j) - 1 < n; i++) {
                spt[j][i] = merge(spt[j - 1][i], spt[j - 1][i + (1 << (j - 1))]);
            }
        }
    }
    pair<ll, int> merge(pair<ll, int> &x, pair<ll, int> &y) {
        if(x.f < y.f) return x;
        return y;
    }
    pair<ll, int> query(int i, int j) {
        int len = j - i + 1;
        int k = log[len];
        return merge(spt[k][i], spt[k][j - (1 << k) + 1]);
    }
    int lca(int i , int j){ 
        if(in[i] > in[j]) swap(i , j);
        return query(in[i] , in[j]).s;
    }
};
int main(){
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif
    int n , q; cin >> n >> q;
    for(int i = 1; i < n; ++i){
        int p; cin >> p;
        --p;
        adj[p].emplace_back(i);
    }
    dfs();
    SparseTable spt;
    spt.init(Timer);
    while(q--){
        int u , v; cin >> u >> v;
        --u; --v;
        cout << spt.lca(u , v) + 1 << '\n';
    }
}
