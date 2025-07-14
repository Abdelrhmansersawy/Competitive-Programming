// Tree Hashing (Subtree Hashing) for a rooted tree
// In case tree in unrooted, you must use "isophrisim.cpp"
// Time Complexity: O(n log n)
// 
// This function computes a hash for each subtree in a rooted tree.
// It can be used to test subtree isomorphism. Optionally, sort children
// before hashing to ignore child order (unordered rooted tree).

map<vector<int>, int> mp;

void tree_hash(int u, int p, vector<int> &hash, vector<int> adj[]) {
    vector<int> child;
    for (auto &v : adj[u]) {
        if (v != p) {
            tree_hash(v, u, hash, adj);
            child.emplace_back(hash[v]);
        }
    }

    // Uncomment the following line if the order of children doesn't matter
    // sort(child.begin(), child.end());

    if (!mp.count(child)) {
        mp[child] = mp.size() + 1;
    }
    hash[u] = mp[child];
}
