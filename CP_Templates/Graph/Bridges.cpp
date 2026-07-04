/**
 * ============================================================================
 * Algorithm: Modular Bridge Tree & Diameter
 * Description: Separated into clear steps:
 * 1. Find Bridges (isBridge[id])
 * 2. Build Bridge Tree (shrinks 2-edge-connected components)
 * 3. Detect Diameter of the resulting tree
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i, st, ed) for(int i = st; i < ed; i++)
#define f first
#define s second

const int N = 1e5 + 9;

// Graph and Tree representation
vector<vector<pair<int, int>>> adj; 
vector<vector<int>> BridgeTree;     

// Global State Variables
vector<int> lowLink, dfn, isBridge, comp;
int ndfn, comp_num, total;

void burn() {
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif 
}

// ============================================================================
// CORE HELPER FUNCTIONS
// ============================================================================

void tarjan(int u, int par) {
    dfn[u] = lowLink[u] = ndfn++;
    for (auto &[v, id] : adj[u]) {
        if (dfn[v] == -1) {
            tarjan(v, u);
            lowLink[u] = min(lowLink[u], lowLink[v]);
            
            if (lowLink[v] == dfn[v]) {
                isBridge[id] = true;
                total++;
            }    
        } else if (v != par) {
            lowLink[u] = min(lowLink[u], dfn[v]);
        }
    }
}

void Find_component(int u, int par) {
    comp[u] = comp_num;
    for (auto &[v, id] : adj[u]) {
        if (comp[v] == -1 && isBridge[id] == 0) {
            Find_component(v, u);
        }
    }
}

pair<int, int> diameter_dfs(int u, int par = -1) {
    int diam = 0;
    int mxHeights[3] = {-1, -1, -1}; 
    
    for (auto &v : BridgeTree[u]) {
        if (v != par) {
            auto p = diameter_dfs(v, u);
            diam = max(diam, p.f);
            
            mxHeights[0] = p.s + 1;
            sort(mxHeights, mxHeights + 3);
        }
    }
    
    for (int i = 0; i < 3; i++) {
        if (mxHeights[i] == -1) mxHeights[i] = 0;
    }
    
    diam = max(diam, mxHeights[1] + mxHeights[2]);
    return {diam, mxHeights[2]};
}

// ============================================================================
// MODULAR TEMPLATE FUNCTIONS
// ============================================================================

/**
 * Step 1: Populates the isBridge array
 */
void findBridges(int n) {
    for (int i = 0; i < n; i++) {
        if (dfn[i] == -1) {
            tarjan(i, -1);
        }
    }
}

/**
 * Step 2: Groups nodes and builds the BridgeTree adjacency list
 */
void buildBridgeTree(int n) {
    // Group components
    for (int i = 0; i < n; i++) {
        if (comp[i] == -1) {
            Find_component(i, -1);
            comp_num++;
        }
    }
    
    // Build tree edges
    BridgeTree.assign(comp_num, vector<int>());
    for (int u = 0; u < n; u++) {
        for (auto &[v, id] : adj[u]) {
            if (isBridge[id]) {
                BridgeTree[comp[u]].emplace_back(comp[v]);
            }
        }
    }
    
    // Clean duplicate edges
    for (int i = 0; i < comp_num; i++) {
        sort(BridgeTree[i].begin(), BridgeTree[i].end());
        BridgeTree[i].erase(unique(BridgeTree[i].begin(), BridgeTree[i].end()), BridgeTree[i].end());
    }
}

/**
 * Step 3: Returns the diameter of the constructed Bridge Tree
 */
int getBridgeTreeDiameter() {
    if (comp_num > 0) {
        return diameter_dfs(0, -1).f;
    }
    return 0; 
}

// ============================================================================
// MAIN SOLVER
// ============================================================================

void solve() {
    int n, m; 
    cin >> n >> m;
    
    // Reset state for testcase
    dfn.assign(n, -1);
    comp.assign(n, -1);
    lowLink.assign(n, 0);
    isBridge.assign(m, 0);
    ndfn = comp_num = total = 0;
    adj.assign(n, vector<pair<int, int>>());

    // Read edges
    for (int i = 0; i < m; i++) {
        int u, v; 
        cin >> u >> v;
        --u; --v; 
        adj[u].emplace_back(v, i);
        adj[v].emplace_back(u, i);
    }
    
    // --- The 3-Step Template ---
    
    // 1. Mark all bridges in isBridge[id]
    findBridges(n);
    
    // 2. Shrink components and construct the Bridge Tree
    buildBridgeTree(n);
    
    // 3. Detect Diameter
    int d = getBridgeTreeDiameter();
    
    // Do whatever is required with the diameter
    // cout << d << "\n";
}

int main() {
    burn();
    int q; 
    cin >> q;
    while (q--) {
        solve();
    }
    return 0;
}
