/*
  Finding Eulerian trail in directed graph for multiple test cases
  Time complexity: O(∑(N + M))
  Space complexity: O(max N + max M)
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i, st, ed) for (int i = st; i < ed; i++)
#define f first
#define s second

const int N = 200000 + 9; // maximum over all test cases
vector<pair<int,int>> adj[N];
vector<int> und[N];
int indeg[N], outdeg[N];
vector<int> path_nodes, path_edges;
bool vis[N];

void dfs(int u) {
    while (!adj[u].empty()) {
        auto [v, id] = adj[u].back();
        adj[u].pop_back();
        dfs(v);
        path_edges.push_back(id);
    }
    path_nodes.push_back(u);
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        // clear per-case data
        rep(i,0,n) {
            indeg[i] = outdeg[i] = 0;
            adj[i].clear();
            und[i].clear();
            vis[i] = false;
        }
        // read edges
        rep(i,0,m) {
            int u, v;
            cin >> u >> v;
            // store (neighbor, edge_index)
            adj[u].emplace_back(v, i);
            und[u].push_back(v);
            und[v].push_back(u);
            outdeg[u]++; indeg[v]++;
        }

        // check degree balances
        int plus1 = 0, minus1 = 0, start = -1;
        bool bad = false;
        rep(i,0,n) {
            int d = outdeg[i] - indeg[i];
            if (d ==  1) { plus1++; start = i; }
            else if (d == -1) { minus1++; }
            else if (d != 0) { bad = true; }
        }
        if (bad || !((plus1==1 && minus1==1) || (plus1==0 && minus1==0))) {
            cout << "No\n";
            continue;
        }

        // choose start for cycle case
        if (start == -1) {
            rep(i,0,n) {
                if (outdeg[i] > 0) { start = i; break; }
            }
            if (start == -1) start = 0;
        }

        // weak connectivity on vertices with edges
        int need = 0, seen = 0;
        rep(i,0,n) if (indeg[i] + outdeg[i] > 0) need++;
        queue<int> q;
        vis[start] = true;
        if (indeg[start] + outdeg[start] > 0) seen++;
        q.push(start);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : und[u]) {
                if (!vis[v]) {
                    vis[v] = true;
                    if (indeg[v] + outdeg[v] > 0) seen++;
                    q.push(v);
                }
            }
        }
        if (seen != need) {
            cout << "No\n";
            continue;
        }

        // Hierholzer's algorithm
        path_nodes.clear();
        path_edges.clear();
        dfs(start);
        if ((int)path_edges.size() != m || (int)path_nodes.size() != m+1) {
            cout << "No\n";
            continue;
        }
        reverse(path_nodes.begin(), path_nodes.end());
        reverse(path_edges.begin(), path_edges.end());

        // output
        cout << "Yes\n";
        rep(i,0,(int)path_nodes.size()) {
            cout << path_nodes[i] << (i+1<(int)path_nodes.size() ? ' ' : '\n');
        }
        rep(i,0,(int)path_edges.size()) {
            cout << path_edges[i] << (i+1<(int)path_edges.size() ? ' ' : '\n');
        }
    }
    return 0;
}