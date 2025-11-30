/**
 * Offline Parallel DSU
 * Constraints: N, Q <= 1e6
 * Time: O(N log N) total
 * Space: O(N log N)
 */
const int N = 6e5 + 9; 
const int LOG = 22;

int p[LOG][N];
int final_p[N]; 
int sz[N]; 
int n_dsu;      

int find_k(int k, int x) {
    return p[k][x] == x ? x : p[k][x] = find_k(k, p[k][x]);
}

void join_layer(int k, int u, int v) {
    u = find_k(k, u);
    v = find_k(k, v);
    if (u != v) p[k][u] = v;
}

int leader(int x) {
    return final_p[x] == x ? x : final_p[x] = leader(final_p[x]);
}

void init_dsu(int n) {
    n_dsu = n;
    for (int k = 0; k < LOG; ++k) {
        for (int i = 0; i <= n + 1; ++i) {
            p[k][i] = i;
        }
    }
    iota(final_p, final_p + n + 1, 0);
    fill(sz, sz + n + 1, 1); 
}

void add_range(int u, int v, int len) {
    if (len <= 0) return;
    int k = 31 - __builtin_clz(len); 
    join_layer(k, u, v);
    join_layer(k, u + len - (1 << k), v + len - (1 << k));
}

void build() {
    for (int k = LOG - 1; k > 0; --k) {
        for (int i = 0; i + (1 << k) <= n_dsu; ++i) {
            int root = find_k(k, i);
            if (i != root) {
                join_layer(k - 1, i, root);
                join_layer(k - 1, i + (1 << (k - 1)), root + (1 << (k - 1)));
            }
        }
    }

    for (int i = 0; i < n_dsu; ++i) {
        int root = find_k(0, i);
        if (i != root) {
            int u = leader(i);
            int v = leader(root);
            if (u != v) {
                final_p[u] = v;
                // [TODO]: Aggregate data here (e.g., sum, max, min)
                sz[v] += sz[u];
            }
        }
    }
}
