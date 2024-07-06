struct BS {
    vector<int> tree;
    int n;
 
    BS(int n) {
        this->n = 1 << (__lg(n) + !!(n & (n - 1)));
        tree.assign(this->n + 1, 0);
    }
 
    void insert(int x, int v = 1) {
        for (++x; x <= n; x += (x) & (-x)) {
            tree[x - 1] += v;
        }
    }
 
    void erase(int x, int v = -1) {
        for (++x; x <= n; x += (x) & (-x)) {
            tree[x - 1] += v;
        }
    }
 
    int search(int v = 0) {
        int p = 0, idx = 0;
        for (int sz = n >> 1; sz; sz >>= 1) {
            if (tree[p + sz - 1] <= v) {
                p += sz;
            }
        }
        return p;
    }
};
