/*
 * ======================== VIRTUAL TREE TEMPLATE ========================
 *
 * Problem: Given a tree of N nodes (rooted at 1), answer Q queries.  
 * Each query gives a subset S of K nodes.  
 * We build the minimal “virtual tree” A(X) containing all nodes in X
 * plus their LCAs, preserving original tree parent–child relations.
 *
 * Key Properties:
 *
 * Property 1: Size Estimation
 *   For any set X of vertices of tree T, the virtual tree
 *   satisfies |A(X)| ≤ 2|X| − 1.
 *
 * Property 2: Representation through Sequential LCAs
 *   If vertices of X are ordered by DFS order x1, x2, …, xm, then
 *     A(X) = X ∪ { lca(x_i, x_{i+1}) | 1 ≤ i < m }.
 *
 * Construction Complexity:
 *   A(X) can be constructed in
 *     O(|X|(log|X| + log N)) time.
 *
 * Main Construction Steps:
 * 1. Preprocessing:
 *      - Run DFS from root to compute:
 *         in[u], out[u]: entry/exit times for ancestor checks.
 *         dep[u]: depth of u.
 *         up[u][j]: 2^j-th ancestor (binary lifting).
 *      - Time: O(N log N)
 *
 * 2. Vertex Sorting:
 *      - Sort X by in[u] (DFS order).
 *      - Time: O(|X| log |X|)
 *
 * 3. Adding LCAs:
 *      - For consecutive sorted vertices, compute lca(u, v).
 *      - Insert into list → A(X).
 *      - Time: O(|X| log N)
 *
 * 4. Tree Construction:
 *      - Sort A(X) by in[u], remove duplicates.
 *      - Use a stack to reconnect edges:
 *          * Traverse u ∈ A(X):
 *              while stack.top() not ancestor of u: pop
 *              connect stack.top() → u
 *              push(u)
 *      - Time: O(|A(X)|)
 *
 * Overall per-query time: O(|X|(log|X| + log N)).
 * ========================================================================
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

static const int MAXN = 1e6 + 9;
static const int LOG  = 20;

int N, Q, timer;
int inT[MAXN], outT[MAXN], dep[MAXN];
int up[MAXN][LOG];
vector<int> adj[MAXN], t[MAXN];

// 1) Preprocessing DFS: in/out, depth, binary‐lifting table
void preDFS(int u, int p) {
    inT[u] = ++timer;
    
    // TODO: Build LCA
    for(int v : adj[u]) if(v != p)
        preDFS(v, u);
    outT[u] = timer;
}

// Check if u is ancestor of v
bool isAncestor(int u, int v) {
    return inT[u] <= inT[v] && outT[v] <= outT[u];
}

// Build virtual tree on set X; returns list of all nodes used
vector<int> buildVirtualTree(vector<int>& X) {
    vector<int> V = X;
    sort(V.begin(), V.end(), [&](int a, int b){ return inT[a] < inT[b]; });
    // add sequential LCAs
    for(int i = 1; i < (int)V.size(); ++i)
        V.push_back(lca(V[i-1], V[i]));
    sort(V.begin(), V.end(), [&](int a, int b){ return inT[a] < inT[b]; });
    V.erase(unique(V.begin(), V.end()), V.end());
    
    // stack-based tree reconstruction
    stack<int> st;
    for(int u : V) {
        while(!st.empty() && !isAncestor(st.top(), u)) st.pop();
        if(!st.empty()) t[st.top()].push_back(u);
        st.push(u);
    }
    return V;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    for(int i = 1, u, v; i < N; ++i) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    preDFS(1, 1);

    cin >> Q;
    while(Q--) {
        int K; cin >> K;
        vector<int> S(K);
        for(auto &x : S) cin >> x;

        vector<int> V = buildVirtualTree(S);

         // TODO: run your DP or queries on this virtual tree using t[]
        // e.g. compute sum of distances along its edges, etc.

        // cleanup for next query
        for(int u : V) {
            t[u].clear();
        }
    }
    return 0;
}
