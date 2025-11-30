// problem link 
https://codeforces.com/contest/2158/problem/F1


#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i , st , ed) for(int i = st; i < ed; i++)
#define f first
#define s second
#define all(v) v.begin() , v.end()
const int N = 50, M = 1e5;
ll pre[N];
vector<pair<int,int>> adj[N];
vector<int> euler_path;
bool vis_edge[M];

void dfs(int u){
    for(auto &[v , id] : adj[u]){
        if(vis_edge[id]) continue;
        vis_edge[id] = true;
        dfs(v);
    }
    euler_path.emplace_back(u);
}

int main(){
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif

    auto func = [&](int m){
        if(m % 2) return 1LL * m * (m + 1) / 2;
        return 1LL * m * (m + 1) / 2 - (m / 2 - 1);
    };

    for(int i = 1; i < N; ++i){
        pre[i] = func(i);
    }

    int tc; cin >> tc;
    while(tc--){
        int n; cin >> n;

        int x = lower_bound(pre , pre+N , n-1) - pre;

        vector<pair<int,int>> edges;
        if(x % 2){
            for(int i = 0; i < x; ++i){
                for(int j = i; j < x; ++j){
                    edges.emplace_back(i,j);
                }
            }
        }else{
            // remove floor(m/2) edges
            // (2,3) , (4,5) , (m-2,m-1)
            for(int i = 0; i < x; ++i){
                for(int j = i; j < x; ++j){
                    if(i && i % 2 == 0 && j-i == 1) continue; // handle removed edges
                    edges.emplace_back(i,j);
                }
            }
        }


        for(int i = 0; i < edges.size(); ++i){
            auto [u , v] = edges[i];
            adj[u].emplace_back(v , i);
            adj[v].emplace_back(u , i);
        }


        // find euler path

        // step1: odd deg = 0 or 2
        vector<int> odd;
        for(int i = 0; i < x; ++i) if(adj[i].size() % 2) odd.emplace_back(i);
        assert(odd.size() == 0 || odd.size() == 2);
        int start = (odd.size() ? odd[0] : 0);

        dfs(start);
        assert(euler_path.size() == edges.size() + 1); // we find a path

        while(euler_path.size() > n) euler_path.pop_back();
        for(auto &i : euler_path) cout << (ll)(powl(2,i) * powl(3,x-i-1)) << ' ';
        cout << '\n';

        // clear each testcase
        for(int i = 0; i < x; ++i) adj[i].clear();
        for(int i = 0; i < edges.size(); ++i) vis_edge[i] = false;
        euler_path.clear();

    }
}
