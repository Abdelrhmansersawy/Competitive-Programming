/**
 * Parallel DSU (Disjoint Set Union on Sparse Table)
 * * Description:
 * Efficiently merges two ranges [u, u + len) and [v, v + len).
 * Useful for problems involving range equivalence (e.g., finding periods, 
 * palindromes, or compressing graphs with range-based edges).
 * * Constraints:
 * - N <= 5e5 (Limited by Memory: ~76MB for N=5e5)
 * - Q <= 5e5 (Range updates are effectively amortized)
 * * Time Complexity: Amortized O(N log N) total work
 */

struct DSU {
    vector<int> p, sz;
    DSU(int n = 0) { init(n); }
    void init(int n) { p.resize(n); iota(p.begin(), p.end(), 0); sz.assign(n, 1); }
    int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }
    bool unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return 0;
        if (sz[x] < sz[y]) swap(x, y);
        p[y] = x; sz[x] += sz[y];
        return 1;
    }
};

struct ParallelDSU {
private:
    vector<int> p, sz;
    vector<DSU> st; 
    int cnt; // Tracks number of connected components

    bool unite(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return 0;
        if (sz[u] < sz[v]) swap(u, v);
        
        p[v] = u; 
        sz[u] += sz[v];
        cnt--; 

        // [TODO]: Aggregate data here (e.g., sum, max, min)
        // val[u] += val[v]; 
        
        return 1;
    }

    // Merge ranges [u, u + 2^k) and [v, v + 2^k)
    void join(int k, int u, int v) {
        if (!k) { unite(u, v); return; }
        // Only recurse if they weren't already connected at this level
        if (st[k].unite(u, v)) {
            join(k - 1, u, v);
            join(k - 1, u + (1 << (k - 1)), v + (1 << (k - 1)));
        }
    }

public:
    void init(int n) {
        if (n == 0) return;
        int LOG = 31 - __builtin_clz(n);
        
        p.resize(n); iota(p.begin(), p.end(), 0);
        sz.assign(n, 1);
        st.assign(LOG + 1, DSU(n));
        
        cnt = n; // Start with N disjoint components
        
        // [TODO]: Initialize data arrays here
        // val.resize(n); 
    }

    // Merge arbitrary ranges [u, u + len) and [v, v + len)
    void merge(int u, int v, int len) {
        if (!len) return;
        int k = 31 - __builtin_clz(len);
        join(k, u, v);
        join(k, u + len - (1 << k), v + len - (1 << k));
    }

    int count() const { return cnt; }

    int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }
    int size(int u) { return sz[find(u)]; }
};
