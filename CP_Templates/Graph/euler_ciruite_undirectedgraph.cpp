/*
    Eulerian Circuit is an Eulerian Path that starts and ends on the same vertex. 

    Restrictions:
    An undirected graph has Eulerian cycle if following two conditions are true. 
        1. All vertices with non-zero degree are connected. We don’t care about vertices with zero degree
           because they don’t belong to Eulerian Cycle or Path (we only consider all edges). 
        2. All vertices have even degree.

*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i , st , ed) for(int i = st; i < ed; i++)
#define f first
#define s second
const int N = 1e5 + 9 , M = 2e5 + 9;
vector<pair<int,int>> adj[N];
int vis[M];
int main(){
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif 
    int n, m; cin >> n >> m;
    for(int i = 0; i < m; ++i){
        int u,v; cin >> u >> v;
        --u; --v;
        adj[u].emplace_back(v,i);
        adj[v].emplace_back(u,i);
    }
    for(int i = 0; i < n; ++i)if ((int) adj[i].size() & 1){
        cout << "IMPOSSIBLE"; // Handling manual
        return 0;
    }
    // there could be more than one euler circuit if the graph aren't connected ans we will find one of them;   
    stack<int> st;
    for(int i = 0; i < n; ++i) if(adj[i].size()){
        st.push(i);
        break;
    }
    // if st.empty() --> no.edges = 0
    vector<int> path;
    while(!st.empty()){
        int v = st.top();
        int f=0;
        while(!adj[v].empty()) {
            auto [u,i] =  adj[v].back();
            adj[v].pop_back();
            if (!vis[i]) {
                st.push(u);
                vis[i]=1;
                f=1; 
                break;
            }
        }
        if (!f){
            path.emplace_back(v);
            st.pop();
        }
    }
    for (auto &i: path) cout << i + 1 << " ";
}
