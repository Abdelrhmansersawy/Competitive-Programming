/*
    Classic problems: https://cses.fi/problemset/task/1139
    You are given a rooted tree consisting of n nodes.
    The nodes are numbered 1,2,..,n, and node 1 is the root. Each node has a color.
    Your task is to determine for each node the number of distinct colors in the subtree of the node.
    Time complexity: O(n log n)
    Space comlexity: O(n log n)
*/
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
map<int,int> mp[N];
int  ans[N], color[N];
int dfs(int u, int par){
    int p = u;
    mp[p][color[u]]++;
    for(auto &v : adj[u]) if(v != par){
        int x = dfs(v , u);
        if(mp[x].size() > mp[p].size()) swap(x,p);
        for(auto &[c,frq]: mp[x]) mp[p][c] += frq; 
    }
    ans[u] = (int) mp[p].size();
    return p;
}
int main(){
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif
    int n; cin >> n;
    for(int i = 0; i < n; ++i) cin >> color[i];
    for(int i = 0; i < n - 1; ++i){
        int u , v; cin >> u >> v;
        --u; --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(0,0);
    for(int i = 0; i < n; ++i) cout << ans[i] << " ";
}
