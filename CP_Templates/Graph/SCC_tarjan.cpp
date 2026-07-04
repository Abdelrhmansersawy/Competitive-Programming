/**
 * ============================================================================
 * Algorithm: Tarjan's Algorithm for Strongly Connected Components (SCC)
 * Description: Finds all SCCs in a directed graph using a single DFS pass.
 * It also constructs a Condensed Directed Acyclic Graph (DAG) where each 
 * node represents an SCC, and computes the in-degree of each DAG node.
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define s second
#define f first
#define rep(i, st, ed) for(int i = st; i < ed; i++)

const int N = 1e5 + 9;

// Graph variables
vector<vector<int>> adj, dag, comps;

// Tarjan's state variables
int comp[N];      // Maps an original node to its SCC ID
int inStack[N];   // Tracks if a node is currently in the recursion stack
int lowLink[N];   // Lowest discovery time reachable from the node
int dfn[N];       // Discovery time of the node
int deg[N];       // In-degree of the condensed DAG nodes

stack<int> st;
int ndfn;

// Fast I/O and file routing
void burn() {
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif
}

/**
 * Core Tarjan's DFS algorithm.
 * Identifies SCCs by keeping track of discovery times and back-edges.
 */
void tarjan(int u) {
    dfn[u] = lowLink[u] = ndfn++;
    inStack[u] = true;
    st.push(u);
    
    for (auto &v : adj[u]) {
        if (dfn[v] == -1) {
            // Node not visited yet, recurse and update lowLink
            tarjan(v);
            lowLink[u] = min(lowLink[u], lowLink[v]);
        } else if (inStack[v]) {
            // Node is visited and in the current DFS path (back-edge found)
            lowLink[u] = min(lowLink[u], dfn[v]);
        }
    }
    
    // If the lowest reachable node is the node itself, it is the head of an SCC
    if (dfn[u] == lowLink[u]) {
        int x = -1;
        comps.emplace_back(vector<int>()); // Start a new component
        
        while (x != u) {
            x = st.top(); 
            st.pop(); 
            inStack[x] = 0;
            
            comps.back().emplace_back(x);
            comp[x] = comps.size() - 1;  // Tag node with its SCC ID
        }
    }
}

/**
 * Builds the condensed DAG by connecting the identified SCCs.
 * It also removes parallel edges and correctly calculates in-degrees.
 */
void genDag() {
    dag.clear();
    dag.resize(comps.size());
    
    // Step 1: Map original edges to the condensed DAG
    for (int u = 0; u < adj.size(); u++) {
        for (auto &v : adj[u]) {
            if (comp[u] != comp[v]) {
                dag[comp[u]].emplace_back(comp[v]);
            }
        }
    }
    
    // Step 2: Remove duplicate edges and compute accurate in-degrees
    for (int i = 0; i < comps.size(); i++) {
        // Sort and unique to strip out parallel edges
        sort(dag[i].begin(), dag[i].end());
        dag[i].erase(unique(dag[i].begin(), dag[i].end()), dag[i].end());
        
        // Calculate the true in-degree for the DAG nodes
        for (int v : dag[i]) {
            deg[v]++;
        }
    }
}

/**
 * Initializes state and executes Tarjan's algorithm.
 * @param n Number of nodes in the graph.
 */
void SCC(int n) {
    ndfn = 0;
    comps.clear();
    
    // Reset state arrays
    rep(i, 0, n) {
        dfn[i] = -1;
        lowLink[i] = inStack[i] = deg[i] = 0;
    }
    
    // Run Tarjan's for all unvisited nodes
    for (int i = 0; i < n; i++) {
        if (dfn[i] == -1) tarjan(i);
    }
        
    // Build the final Condensation Graph (DAG)
    genDag();
}

int main() {
    burn();
    
    int n, m; 
    cin >> n >> m;
    
    adj.resize(n); 
    for (int i = 0; i < m; i++) {
        int u, v; 
        cin >> u >> v;
        --u; --v; // Convert to 0-indexed nodes
        adj[u].emplace_back(v);
    }
    
    SCC(n);
    
    return 0;
}
