/*
    Eulerian Trail (Undirected)

    Given T test cases of undirected graphs (possibly with multi-edges),
    each with N vertices (0…N−1) and M edges (indexed 0…M−1), determine
    whether an Eulerian trail exists. If it does, output:

        Yes
        v0 v1 … vM
        e0 e1 … e(M−1)

    where (v0…vM) is the sequence of vertices in the trail and
    (e0…eM−1) is the permutation of edge-indices traversed in order.
    Otherwise, print:

        No

    Constraints:
      • 1 ≤ T ≤ 10^5
      • Sum of N over all cases ≤ 2·10^5
      • Sum of M over all cases ≤ 2·10^5
      • 0 ≤ ui, vi < N

    Approach (per test case, O(N+M) time):
      1. If M==0: trivial trail at vertex 0.
      2. Build adjacency lists with (neighbor, edge_id).
      3. Check that #odd-degree vertices is 0 or 2.
      4. Choose start = one odd vertex (if 2), else any vertex with degree>0.
      5. Run Hierholzer’s algorithm (using a stack) to collect the trail:
         – Track used edges in a boolean array.
         – As you backtrack, record both the vertex and the edge taken.
      6. If the recorded path length ≠ M+1, it’s disconnected → No.
      7. Otherwise reverse and print the vertex and edge sequences.
*/

#include <bits/stdc++.h>
using namespace std;

static const int MAXN = 200000 + 9;
static const int MAXM = 200000 + 9;

vector<pair<int,int>> adj[MAXN];
int used_edge[MAXM];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--){
        int n, m;
        cin >> n >> m;

        // clear adjacency lists and used-edge flags
        for (int i = 0; i < n; i++) 
            adj[i].clear();
        for (int i = 0; i < m; i++) 
            used_edge[i] = 0;

        // read edges
        for (int i = 0; i < m; i++){
            int u, v;
            cin >> u >> v;
            adj[u].emplace_back(v, i);
            adj[v].emplace_back(u, i);
        }

        // Special case: no edges → trivial trail at vertex 0
        if (m == 0){
            cout << "Yes\n";
            cout << 0 << "\n\n";
            continue;
        }

        // collect vertices of odd degree
        vector<int> odd;
        for (int i = 0; i < n; i++){
            if ((int)adj[i].size() & 1)
                odd.push_back(i);
        }
        // must have exactly 0 or 2 odd vertices
        if (odd.size() != 0 && odd.size() != 2){
            cout << "No\n";
            continue;
        }

        // choose start vertex
        int start = 0;
        if (odd.size() == 2){
            start = odd[0];
        } else {
            // find any vertex with at least one edge
            while (start < n && adj[start].empty())
                ++start;
        }

        // Hierholzer's algorithm
        stack<int>  st, est;      // st: vertices, est: edge-ids
        vector<int> path;         // vertices in reverse order
        vector<int> edge_seq;     // edge-ids in reverse order

        st.push(start);
        est.push(-1);  // dummy for the first vertex

        while (!st.empty()){
            int v = st.top();
            bool advanced = false;
            // find an unused edge from v
            while (!adj[v].empty()){
                auto [u, eid] = adj[v].back();
                adj[v].pop_back();
                if (!used_edge[eid]){
                    used_edge[eid] = 1;
                    st.push(u);
                    est.push(eid);
                    advanced = true;
                    break;
                }
            }
            if (!advanced){
                // no more edges: backtrack
                path.push_back(v);
                int e = est.top();
                est.pop();
                if (e >= 0)
                    edge_seq.push_back(e);
                st.pop();
            }
        }

        // verify we used all edges
        if ((int)path.size() != m + 1){
            cout << "No\n";
            continue;
        }

        // reverse to get correct forward order
        reverse(path.begin(), path.end());
        reverse(edge_seq.begin(), edge_seq.end());

        // output
        cout << "Yes\n";
        for (int i = 0; i < (int)path.size(); i++){
            cout << path[i]
                 << (i + 1 < (int)path.size() ? ' ' : '\n');
        }
        for (int i = 0; i < (int)edge_seq.size(); i++){
            cout << edge_seq[i]
                 << (i + 1 < (int)edge_seq.size() ? ' ' : '\n');
        }
    }

    return 0;
}
```0