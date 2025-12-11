/*
 * ===================== KRUSKAL RECONSTRUCTION TREE =====================
 *
 * This technique creates a persistent structure over DSU operations.
 * It allows querying the state of components after any number of `unite` operations.
 * This is an offline algorithm, essentially building the MST merge tree.
 *
 * The core idea is to model the `unite` operations as a tree, where each
 * merge creates a new internal node. A final DFS traversal then computes
 * an Euler tour, mapping historical components to queryable array ranges.
 *
 * ---------------------------- Usage Example ----------------------------
 * Problem: Find the number of elements with a value less than `v` in
 * element `i`'s component after the k-th merge.
 *
 * 1. Build Tree: First, perform all M `unite` operations. The k-th merge
 * creates the node with ID `N + k - 1` (if nextNode starts at N).
 *
 * 2. Build Data Structure: Run `dfs()` on all roots. Build a data structure
 * that supports range counting queries (e.g., a Merge Sort Tree or
 * Persistent Segment Tree) over the `vals` of the elements as
 * ordered by the `euler` array.
 *
 * 3. Query: For each query `(i, k)`, find the current root of `i`'s component
 * as it existed at time `k`. This root is the highest ancestor of `i` in
 * the final operation tree that has an ID less than `N + k`.
 *
 * 4. Answer: The elements of that historical component are in the Euler
 * tour range `[inTime[hist_root], outTime[hist_root]]`. Query your
 * data structure over this range to find the count of values < v.
 * =========================================================================
 */

const int N = 100005; 
int par[2 * N], tin[2 * N], tout[2 * N], eu[2 * N], T;
vector<int> adj[2 * N];

// Standard DSU find with path compression
int find(int x) { return par[x] == x ? x : par[x] = find(par[x]); }

// Merges x and y by creating a new parent node (k)
void unite(int x, int y, int &k) {
    if ((x = find(x)) == (y = find(y))) return;
    par[x] = par[y] = par[k] = k; // New node k becomes parent
    adj[k].push_back(x); adj[k].push_back(y);
    k++;
}

// DFS over the operation tree to build Euler tour
void dfs(int u) {
    tin[u] = ++T; eu[T] = u;
    for (int v : adj[u]) dfs(v);
    tout[u] = T;
}

// Setup and build forest
void build(int n, vector<pair<int, int>>& ops) {
    iota(par, par + 2 * N, 0);
    int k = n; 
    for (auto [u, v] : ops) unite(u, v, k);
    for (int i = 0; i < k; ++i) if (par[i] == i) dfs(i);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    // ======== BUILD OPERATION TREE (OFFLINE) ========
    // All unite operations must be known beforehand.

    // Example:
    // std::vector<std::pair<int, int>> operations = {{0,1}, {1,2}, {3,4}};
    // int nextNode = initial_size; // N

    for (const auto& op : operations) {
        unite(op.first, op.second, nextNode);
    }

    // ========  BUILD EULER TOUR ========
    // Run DFS from all roots of the final forest.
    timer = 0;
    for (int i = 0; i < nextNode; ++i) {
        if (parentDSU[i] == i) {
            dfs(i);
        }
    }

    return 0;
}
