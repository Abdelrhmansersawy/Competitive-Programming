/* 
* Problem: Tree Coin Game with Parent Change Queries
*
* Tree with `n` nodes (1-based), each node contains some coins.
* Players take turns to move any number of coins from a node to its *parent*.
*   - A coin can only move in the upward direction.
*   - The player who makes the last move wins.
*
* Queries:
*   - You're given two nodes `u` and `v`.
*   - Temporarily reassign the parent of `u` to be `v`.
*   - This is only valid if `v` is NOT in `u`'s subtree (to avoid cycles).
*   - You must determine if the first player can force a win after this change.
*
* Key Observations:
*   - Use DFS to assign colors (0/1) representing even/odd depth levels.
*   - Maintain whiteXor[] and blackXor[] for coins on each parity.
*   - Overall game state is determined by XOR of all white or black positions.
*   - When subtree is removed (by re-parenting), subtract its XOR from total.
*   - If the color of `parent[u]` and new parent `v` are same, XOR stays same.
*   - If color flips, subtract subtree's combined XOR (whiteXor ^ blackXor).
*
* Time Complexity:
*   - Preprocessing: O(N)
*   - Each Query: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

#define N 100005
#define pb push_back

int n, q, u, v, t;
int st[N], en[N], par[N], col[N];
int c[N], wx[N], bx[N];
vector<int> g[N];

void dfs(int u, int p, int clr) {
    st[u] = ++t;
    par[u] = p;
    col[u] = clr;

    wx[u] = (clr == 0 ? c[u] : 0);
    bx[u] = (clr == 1 ? c[u] : 0);

    for (int v : g[u]) {
        if (v == p) continue;
        dfs(v, u, clr ^ 1);
        wx[u] ^= wx[v];
        bx[u] ^= bx[v];
    }

    en[u] = t;
}

bool is_ancestor(int u, int v) {
    return st[u] <= st[v] && en[u] >= en[v];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> c[i];

    for (int i = 2; i <= n; i++) {
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }

    dfs(1, 1, 1); /* root = 1, color = 1 (odd root) */

    cin >> q;
    while (q--) {
        cin >> u >> v;
        if (is_ancestor(u, v)) {
            cout << "INVALID\n";
            continue;
        }

        int total = wx[1]; // Total XOR on white levels
        int result = total;

        if (col[par[u]] == col[v]) {
            /* Color doesn't change after re-parenting */
            cout << (total ? "YES\n" : "NO\n");
        } else {
            /* Color flips — subtract subtree's XOR from total */
            result ^= wx[u];
            result ^= bx[u];
            cout << (result ? "YES\n" : "NO\n");
        }
    }

    return 0;
}
