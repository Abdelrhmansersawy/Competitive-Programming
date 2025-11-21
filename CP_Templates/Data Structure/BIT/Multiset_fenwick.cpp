struct Bit {
    int N, LOG;
    vector<int> tree;
    void init(int n) {
        N = n; tree.assign(N + 1, 0);
        LOG = 1;
        while ((LOG << 1) <= N) LOG <<= 1;
    }
    void add(int i, int v) { for (i++; i <= N; i += i & -i) tree[i] += v; }
    int get(int i) {
        int s = 0;
        for (i = min(i + 1, N); i > 0; i -= i & -i) s += tree[i];
        return s;
    }
    int find(int k) {
        int pos = 0;
        for (int i = LOG; i; i >>= 1) {
            if (pos + i <= N && tree[pos + i] < k) {
                pos += i; k -= tree[pos];
            }
        }
        return pos;
    }
};

struct MultiSet {
    Bit bit;
    // NOTE: Values 'v' must be 0-based [0, N-1]
    void init(int n) { bit.init(n); }
    void insert(int v) { bit.add(v, 1); }
    void erase(int v) { if (count(v)) bit.add(v, -1); }
    int count(int v) { return bit.get(v) - bit.get(v - 1); }
    int size() { return bit.get(bit.N - 1); }
    
    // k is 0-based (0 returns smallest element)
    int kth_element(int k) { return bit.find(k + 1); } 

    int largerThanMe(int v) { return size() - bit.get(v); }
    int largerThanOrEqualMe(int v) { return size() - bit.get(v - 1); }
    int lessThanMe(int v) { return bit.get(v - 1); }
    int lessThanOrEqualMe(int v) { return bit.get(v); }
};
