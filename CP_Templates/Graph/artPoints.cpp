#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i, st, ed) for(int i = st; i < ed; i++)
#define f first
#define s second

const int N = 1e5 + 9;

vector<vector<int>> adj; 
vector<int> lowLink, dfn;
vector<bool> isArt;
int ndfn;

void burn() {
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif 
}

void tarjan(int u, int par) {
    dfn[u] = lowLink[u] = ndfn++;
    int children = 0; // Track children for the root edge-case
    
    for (int v : adj[u]) {
        if (v == par) continue; 
        
        if (dfn[v] == -1) {
            children++;
            tarjan(v, u);
            lowLink[u] = min(lowLink[u], lowLink[v]);
            
            // Condition 1: Non-root node where a child cannot reach above 'u'
            if (lowLink[v] >= dfn[u] && par != -1) {
                isArt[u] = true;
            }
        } else {
            // Update lowLink if a back-edge is found
            lowLink[u] = min(lowLink[u], dfn[v]);
        }
    }
    
    // Condition 2: Root node with multiple independent children
    if (par == -1 && children > 1) {
        isArt[u] = true;
    }
}

// Populates the isArt array with true/false for every node
void findArtPoints(int n) {
    for (int i = 0; i < n; i++) {
        if (dfn[i] == -1) {
            tarjan(i, -1);
        }
    }
}

int countArtPoints(int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (isArt[i]) count++;
    }
    return count;
}

void solve() {
    int n, m; 
    cin >> n >> m;
    
    // Reset global state for current test case
    dfn.assign(n, -1);
    lowLink.assign(n, 0);
    isArt.assign(n, false);
    ndfn = 0;
    adj.assign(n, vector<int>());

    for (int i = 0; i < m; i++) {
        int u, v; 
        cin >> u >> v;
        --u; --v; 
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    // 1. Find all articulation points
    findArtPoints(n);
    
    // 2. Utilize the results
    // int total = countArtPoints(n);
}

int main() {
    burn();
    int q = 1; 
    // cin >> q; 
    while (q--) {
        solve();
    }
    return 0;
}
