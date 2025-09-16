/*
Find the final reachable node for every node in a functional graph,
distinguishing between sink paths and cycles.

Definitions:
    - Functional graph: directed graph where each node has at most one outgoing edge.
    - A node's path may:
        * End at a sink (no outgoing edge) → last visited node is marked as sink.
        * Enter a cycle → final node is a cycle representative.

Input:
    - n (number of nodes)
    - nxt[i] = next node of i (or -1 if none)

Output:
    - finalNode[i] = the final node reached from i
    - type[i]:
        * 1 = path ends at a sink
        * 2 = path ends in a cycle

Time complexity:
    - O(n) (DFS with memoization)
Space complexity:
    - O(n)
*/

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int nxt[N];        // nxt[u] = v means edge u -> v, or -1 if no next
int finalNode[N];  // final node result for each node
int state[N];      // 0 = unvisited, 1 = visiting, 2 = processed
int typeRes[N];    // 1 = sink, 2 = cycle

int dfs(int u) {
    if (u == -1) return -1;
    if (state[u] == 2) return finalNode[u];
    if (state[u] == 1) { 
        // found a cycle
        finalNode[u] = u;
        typeRes[u] = 2;
        return u;
    }

    state[u] = 1;
    int res;
    if (nxt[u] == -1) {
        res = u; 
        typeRes[u] = 1; // sink
    } else {
        res = dfs(nxt[u]);
        typeRes[u] = typeRes[nxt[u]];
    }
    finalNode[u] = res;
    state[u] = 2;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; 
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> nxt[i]; // -1 if no next
    }

    for (int i = 1; i <= n; i++) {
        if (state[i] == 0) dfs(i);
    }

    for (int i = 1; i <= n; i++) {
        cout << "Node " << i << " -> Final: " << finalNode[i]
             << " (" << (typeRes[i] == 1 ? "Sink" : "Cycle") << ")\n";
    }
}
