// Binary Indexed Tree (Fenwick Tree) for prefix sums
struct BIT {
    vector<int> tree;
    int n;

    // Initialize BIT with n elements
    void init(int n) {
        this->n = n;
        tree.assign(n, 0);
    }

    // Add `val` to position `pos`
    void add(int pos, int val) {
        for (pos++; pos <= n; pos += (pos & -pos))
            tree[pos - 1] += val;
    }

    // Prefix sum from index 0 to pos
    int sum(int pos) {
        int ret = 0;
        for (pos++; pos; pos -= (pos & -pos))
            ret += tree[pos - 1];
        return ret;
    }

    // Range sum [l, r]
    int sum(int l, int r) { return sum(r) - sum(l - 1); }

    // Get frequency at index i
    int getidx(int i) { return sum(i, i); }
};

// Multiset-like structure using BIT
struct MultiSet {
    BIT B;

    MultiSet() { B.init(N); }

    // Insert an element into the multiset
    void insert(int val) { B.add(val, 1); }

    // Remove one occurrence of the element
    void erase(int val) { B.add(val, -1); }

    // Count how many times val appears
    int count(int val) { return B.sum(val - 1, val); }

    // Total size of the multiset
    int size() { return B.sum(N - 1); }

    // Count how many elements are strictly less than `val`
    int order_of_key_val(int val) {
        return B.sum(val - 1);
    }

    // Get the smallest index `idx` such that there are `key` or more elements ≤ idx
    // Equivalent to finding the position of the key-th element
    // Binary lifting: O(log(n)) time
    int order_of_key(int key) {
        int idx = 0, sum = 0;
        for (int i = 1 << __lg(N); i; i >>= 1) {
            if (idx + i <= N && sum + B.tree[idx + i - 1] < key) {
                sum += B.tree[idx + i - 1];
                idx += i;
            }
        }
        return idx;
    }
} s;
