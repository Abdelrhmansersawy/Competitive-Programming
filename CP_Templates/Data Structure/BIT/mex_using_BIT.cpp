// It 's faster than set
struct BIT {
    vector<int> tree;
    int n;
    void init(int n) {
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
    int search(int v = 0) { // O(log(n))
        int p = 0, idx = 0;
        for (int sz = n >> 1; sz; sz >>= 1) {
            if (tree[p + sz - 1] <= v) {
                p += sz;
            }
        }
        return p;
    }
}

// More function can be useful
struct Mex{
    BIT missing;
    vector<int> frq;
    int n;
    void init(int n){
        missing.init(n + 2);
        frq.resize(n + 2);
        this->n = n + 2;
    }
    int get(int i){ return missing.search(); } // O(log(n))
    void add(int v){ // O(log(n))
        if(v > n) return;
        if(++frq[v] == 1) missing.erase(v); 
    } 
    void rm(int v){ // O(log(n))
        if(v > n) return;
        if(--frq[v] == 0) missing.insert(v);
    } 
};
