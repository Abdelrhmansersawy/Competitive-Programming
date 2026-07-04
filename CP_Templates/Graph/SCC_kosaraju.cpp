/**
 * ============================================================================
 * Algorithm: Kosaraju's Algorithm for Strongly Connected Components (SCC)
 * Description: Finds all SCCs in a directed graph and constructs a Condensed 
 * Directed Acyclic Graph (DAG) where each node represents an SCC.
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i , st , ed) for(int i = st; i < ed; i++)
#define f first
#define s second
#define all(v) v.begin() , v.end()

const int N = 2e5 + 9;

// Original graph and its transpose
vector<int> adj[N], adj_rev[N];
bool used[N];

// Variables for Kosaraju's Algorithm
vector<int> order, component;

// Variables for the Condensed Graph (DAG)
int component_id[N]; // Maps an original node to its specific SCC ID
vector<int> dag[N];  // Adjacency list for the DAG of SCCs
int num_scc = 0;     // Total number of discovered SCCs

/**
 * First pass of Kosaraju's Algorithm: 
 * Perform DFS on the original graph to compute the exit order of nodes.
 */
void dfs1(int v) {
    used[v] = true;
    for (auto u : adj[v])
        if (!used[u])
            dfs1(u);
    order.push_back(v);
}

/**
 * Second pass of Kosaraju's Algorithm:
 * Perform DFS on the reversed graph to extract the Strongly Connected Components.
 */
void dfs2(int v) {
    used[v] = true;
    component.push_back(v);
    for (auto u : adj_rev[v])
        if (!used[u])   
            dfs2(u);
}

/**
 * Executes Kosaraju's algorithm, assigns component IDs, and builds the DAG.
 * @param n The number of nodes in the graph.
 */
void scc(int n) {
    // Step 1: Run DFS on the original graph to get the topological sort order
    for(int i = 0; i < n; ++i) used[i] = false;
    
    for (int i = 0; i < n; i++) {
        if (!used[i]){
            dfs1(i);
        }
    }
    
    // Step 2: Reverse the exit order for the second pass
    for(int i = 0; i < n; ++i) used[i] = false;
    reverse(order.begin(), order.end());
    
    // Step 3: Run DFS on the reversed graph using the calculated order
    num_scc = 0; // Reset SCC counter
    for (auto v : order) {
        if (!used[v]) {
            dfs2(v);
            
            // Assign the current SCC ID to all nodes in this discovered component
            for (int u : component) {
                component_id[u] = num_scc;
            }
            num_scc++; 
            component.clear();
        }
    }

    // Step 4: Build the condensed graph (DAG) of SCCs
    for (int u = 0; u < n; u++) {
        for (int v : adj[u]) {
            // If the adjacent nodes belong to different components, add a directed edge in the DAG
            if (component_id[u] != component_id[v]) {
                dag[component_id[u]].push_back(component_id[v]);
            }
        }
    }

    // Step 5 (Optional but Recommended): Remove duplicate edges in the DAG
    for (int i = 0; i < num_scc; i++) {
        sort(dag[i].begin(), dag[i].end());
        dag[i].erase(unique(dag[i].begin(), dag[i].end()), dag[i].end());
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif
    
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b;
        --a; --b; // Convert to 0-indexed nodes
        adj[a].push_back(b);
        adj_rev[b].push_back(a);
    }
    
    // Process the graph to find SCCs, assign IDs, and build the DAG
    scc(n);
    
    return 0;
}
