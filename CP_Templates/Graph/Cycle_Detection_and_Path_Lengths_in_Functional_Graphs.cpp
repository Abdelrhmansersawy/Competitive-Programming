/**
 * Problem: Planets Cycles (CSES 1751)
 * Link: https://cses.fi/problemset/task/1751/
 * * Description:
 * Given a functional graph (where each node has exactly one outgoing edge), 
 * this algorithm computes the total path length before a cycle repeats.
 * * Variables:
 * - dep[i]      : The number of steps from node 'i' to reach a cycle.
 * - cycle_sz[i] : The size of the cycle that node 'i' eventually falls into.
 * * Note: The final answer for any node 'i' is (dep[i] + cycle_sz[i]).
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 200005;
int nxt[MAXN]; // Renamed from 'p' to 'nxt' for clarity
int vis[MAXN];
int root[MAXN];
int dep[MAXN];
int cycle_sz[MAXN];

void doWork(int n) {
    // Fill is safer than memset to avoid pointer sizing bugs
    fill(root, root + n, -1); 
    
    for(int i = 0; i < n; ++i){
        if(root[i] != -1) continue;
        
        int u = i;
        vector<int> path;
        while(!vis[u]){
            vis[u] = 1;
            path.push_back(u);
            u = nxt[u]; // Follow the path
        }
        
        // New cycle found in the current path
        if(root[u] == -1){
            vector<int> cycle;
            int curr = u;
            while(true){
                cycle.push_back(curr);
                root[curr] = curr;
                curr = nxt[curr]; // Traverse the cycle
                if(curr == u) break;
            }
            for(int node : cycle){
                cycle_sz[node] = cycle.size();
                dep[node] = 0;
            }
        }
        
        int current_root = root[u];
        int current_dep = dep[u];
        int current_cycle_sz = cycle_sz[u]; 
        
        // Process the path backwards to assign depths and cycle sizes
        for(int j = (int)path.size() - 1; j >= 0; --j){
            int curr = path[j];
            if(root[curr] == -1){ 
                current_dep++;
                dep[curr] = current_dep;
                root[curr] = current_root;
                cycle_sz[curr] = current_cycle_sz; 
            }
        }
    }
}

int main() {
    // Fast I/O for competitive programming
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    for (int i = 0; i < n; ++i) {
        cin >> nxt[i];
        nxt[i]--; // Convert 1-based input to 0-based indexing for doWork
    }

    doWork(n);

    // Print the final answers
    for (int i = 0; i < n; ++i) {
        cout << dep[i] + cycle_sz[i] << (i == n - 1 ? "" : " ");
    }
    cout << "\n";

    return 0;
}
