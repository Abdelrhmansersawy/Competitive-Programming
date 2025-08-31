// -------------------------------------------------------------
// Problem: Construct a spanning tree with a specified verticality.
//
// Given a connected undirected graph with n vertices, m edges, a root r,
// and a target verticality h, build a spanning tree rooted at r such that
// exactly h edges of the original graph become vertical edges (edges from
// a node to its ancestor not in the tree). If impossible, output -1.
//
// Approach:
// 1. Run DFS from the root to build an initial spanning tree and record
//    discovery times.
// 2. Classify non-tree edges: if they connect a node to an ancestor,
//    store them as potential vertical edges.
// 3. Otherwise, reparent nodes along selected back-edges to
//    convert enough vertical edges into tree edges until exactly h
//    vertical edges remain.
//    *Important*: We sort the back-edges by ancestor discovery time so
//    that reparenting preserves valid ancestor/descendant relations.
// Problem link: https://codeforces.com/gym/105617/problem/C
// -------------------------------------------------------------

#include <bits/stdc++.h>
using namespace std;

const int N = 300005;
int n, m, h, r;                // graph parameters
int pr[N];                      // parent array of spanning tree
int tmr;                        // discovery time counter
vector<int> in;                 // discovery times
vector<vector<int>> g;          // adjacency list
vector<pair<int,pair<int,int>>> vertical; // candidate back-edges

// DFS to build tree and collect back-edges
void dfs(int u) {
    in[u] = ++tmr;
    for (int v : g[u]) {
        if (!in[v]) {
            pr[v] = u;
            dfs(v);
        } else if (v != pr[u] && in[v] < in[u]) {
            // back-edge to ancestor
            vertical.push_back({-in[v], {v, u}});
        }
    }
}

void solve() {
    cin >> n >> m >> r >> h;
    g.assign(n+1, {});
    in.assign(n+1, 0);
    vertical.clear();
    tmr = 0;

    for (int i = 0, x, y; i < m; i++) {
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    int total_vertical = m - (n - 1);
    if (total_vertical < h) {
        for (int i = 0; i < n; i++) cout << -1 << ' ';
        cout << "\n";
        return;
    }

    pr[r] = r;
    dfs(r);

    // Need to reduce vertical edges until only h remain
    int reduce = total_vertical - h;
    sort(vertical.begin(), vertical.end());

    for (int i = 0; i < reduce; i++) {
        pr[vertical[i].second.second] = vertical[i].second.first;
    }

    for (int i = 1; i <= n; i++) cout << pr[i] << ' ';
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; cin >> T;
    while (T--) solve();
}
