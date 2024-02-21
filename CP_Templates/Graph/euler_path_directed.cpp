/*
  Finding euler path in directed graph
  Time complexity: O(N + M)
  Space complexity: O(N + M)
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i , st , ed) for(int i = st; i < ed; i++)
#define f first
#define s second
const int N = 1e5 + 9; // no.of node
vector<int> adj[N];
vector<int> path; // euler path
void dfs(int s){
    while((int) adj[s].size()){
        int u = adj[s].back();
        adj[s].pop_back();
        dfs(u);
    }
    path.emplace_back(s);
}   
int main(){
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif
    int n,m; cin >> n >> m;
    int in[n] = {}, out[n] = {};
    for(int i = 0; i < m; ++i){
        int x,y; cin >> x >> y;
        --x; --y;
        adj[x].emplace_back(y);
        in[y]++, out[x]++;
    }
    int a=0,b=0,c=0,s1=0,s2=0;
    for(int i = 0; i < n; ++i){
        if (in[i]==out[i]) c++;
        if (in[i]-out[i]==1){ b++; s2=i; }
        if (in[i]-out[i]==-1){ a++; s1=i; }
    }
    if (s1 != 0 || s2 != n - 1){
    	cout << "IMPOSSIBLE"; 
    	return 0; 
    }
    if (!(c==n-2 && a==1 && b == 1)){
    	cout << "IMPOSSIBLE"; 
    	return 0; 
    }
    dfs(0);
    if (path.size() != m + 1){
    	cout << "IMPOSSIBLE"; 
    	return 0; 
    }
    reverse(path.begin(), path.end());
    for (auto &i: path) cout << i + 1 << " ";
}
