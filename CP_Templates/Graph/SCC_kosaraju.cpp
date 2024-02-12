#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i , st , ed) for(int i = st; i < ed; i++)
#define f first
#define s second
#define all(v) v.begin() , v.end()
const int N = 2e5 + 9;
vector<int> adj[N], adj_rev[N];
bool used[N];
vector<int> order, component;

void dfs1(int v) {
    used[v] = true;
    for (auto u : adj[v])
        if (!used[u])
            dfs1(u);
    order.push_back(v);
}
void dfs2(int v) {
    used[v] = true;
    component.push_back(v);
    for (auto u : adj_rev[v])
        if (!used[u])   dfs2(u);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif
    int n,m; cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        --a; --b;
        adj[a].push_back(b);
        adj_rev[b].push_back(a);
    }
    for(int i = 0; i < n; ++i) used[i] = false;
    for (int i = 0; i < n; i++) if (!used[i]){
        dfs1(i);
    }
    for(int i = 0; i < n; ++i) used[i] = false;
    reverse(order.begin(), order.end());
    for (auto v : order)if (!used[v]) {
        dfs2 (v);
        component.clear();
    }
}
