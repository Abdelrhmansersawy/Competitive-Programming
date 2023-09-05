/*  
    Finding the First k's shortest path in
    O(m * k) such that m : no. of edges
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i , st , ed) for(int i = st; i < ed; i++)
#define f first
#define s second
int main(){
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif 
    int n , m, k; cin >> n >> m >> k;
    vector<pair<int,ll>> adj[n]; // {v , w}
    for(int i = 0; i < m; ++i){
        int u , v;  ll w; cin >> u >> v >> w;
        --u; --v;
        adj[u].emplace_back(v , w);
    }
    priority_queue<pair<ll,int>> q; // {-w , u}
    vector<ll> cnt(n) , ans;
    int start = 0 , end = n - 1;
    q.push({0 , start});
    while(q.size() && cnt[end] < k){
        auto [d , u] = q.top(); q.pop();
        d *= -1;
        cnt[u]++;
        if(u == end) ans.emplace_back(d);
        if(cnt[u] <= k){
            for(auto &[v,  w] : adj[u]) if(cnt[v] < k)
                q.push({-(w + d) , v});
        }
    }
    sort(ans.begin() , ans.end());
    for(auto &w : ans) cout << w << " ";
}
