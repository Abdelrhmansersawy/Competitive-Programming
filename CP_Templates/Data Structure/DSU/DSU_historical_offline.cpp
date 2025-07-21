/*
 * ===================== HISTORICAL DSU (OFFLINE) NOTE =====================
 *
 * This technique creates a persistent or "historical" DSU structure.
 * It allows querying the state of components after any number of `unite` operations.
 * This is an offline algorithm, meaning all `unite` operations must be known beforehand.
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
 * data structure over this range to find the count of values `< v`.
 * =========================================================================
 */

const int MAXN = 100005; // Maximum number of initial elements

int vals[MAXN]; // Initial values for each element
int parentDSU[2 * MAXN]; // DSU parent pointers (also operation tree parent)
std::vector<std::vector<int>> children(2 * MAXN); // Operation tree adjacency list

int timer, inTime[2 * MAXN], outTime[2 * MAXN], euler[2 * MAXN]; // Euler tour info

// Standard DSU find with path compression
int findRoot(int x) {
    return parentDSU[x] == x ? x : parentDSU[x] = findRoot(parentDSU[x]);
}

// Merges the sets containing x and y by creating a new parent node
void unite(int x, int y, int &nextNode) {
    x = findRoot(x);
    y = findRoot(y);
    if (x == y) return;
    parentDSU[x] = parentDSU[y] = nextNode;
    children[nextNode].push_back(x);
    children[nextNode].push_back(y);
    ++nextNode;
}

// DFS over the operation tree to build Euler tour
void dfs(int u) {
    inTime[u] = ++timer;
    euler[timer] = u;
    for (int v : children[u]) {
        dfs(v);
    }
    outTime[u] = timer;
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
