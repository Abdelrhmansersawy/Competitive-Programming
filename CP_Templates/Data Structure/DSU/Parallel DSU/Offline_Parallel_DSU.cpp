/**
 * Offline Parallel DSU
 * Constraints: N, Q <= 1e6
 * Time: O(N log N) total
 * Space: O(N log N)
 */
const int N = 6e5 + 9, LG = 22;
int P[LG][N], par[N], sz[N], n;

// Find for sparse layer k
int get(int k, int x) { return P[k][x] == x ? x : P[k][x] = get(k, P[k][x]); }

void join(int k, int u, int v) {
    if ((u = get(k, u)) != (v = get(k, v))) P[k][u] = v;
}

// Final DSU find
int find(int x) { return par[x] == x ? x : par[x] = find(par[x]); }

// Initialize internal structures
void init(int _n) {
    n = _n;
    for (int k = 0; k < LG; ++k) iota(P[k], P[k] + n + 1, 0);
    iota(par, par + n + 1, 0); fill(sz, sz + n + 1, 1);
}

// Connect range [u, u+len) with [v, v+len)
void add(int u, int v, int len) {
    if (len <= 0) return;
    int k = 31 - __builtin_clz(len);
    join(k, u, v); join(k, u + len - (1 << k), v + len - (1 << k));
}

// Push down relations to layer 0 and merge final components
void build() {
    for (int k = LG - 1; k; --k)
        for (int i = 0; i + (1 << k) <= n; ++i) {
            int r = get(k, i);
            if (i != r) {
                join(k - 1, i, r);
                join(k - 1, i + (1 << (k - 1)), r + (1 << (k - 1)));
            }
        }
    for (int i = 0; i < n; ++i) {
        int u = find(i), v = find(get(0, i));
        if (u != v) par[u] = v, sz[v] += sz[u]; // TODO: Aggregate data
    }
}
