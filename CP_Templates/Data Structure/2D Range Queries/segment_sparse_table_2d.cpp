/*
    2D segment sparse table
    - Memory allocation: O(4n x mlog(m))
    - range [l..r] , r: inclusive 
    - Base: 0-index
    
    Function description:
        1. build(n , m , n): build the segment tree with grid[n][m]
           Time complexity: O(4n x mlog(m))
        2. qry(lx , rx , ly , ry): find (min,max,sum,produc) of rectangle [lx...rx] x [ly...ry]
           Time complexity: O(log(n))
*/
template<class T = int>
struct sparse_2d {
    int n, m, LOG , N;
    T DEFAULT = 0;
    vector<vector<vector<T>>> tree;
 
    void build(int _n, int _m , vector<vector<T>> &a) {
        n = _n;
        m = _m;
        LOG = 1;
        while ((1 << LOG) < m) ++LOG;
        N = 1;
        while(N < n) N *= 2;
        N *= 2;
        tree = vector<vector<vector<T>>>(2 * N + 1, vector<vector<T>>(LOG, vector<T>(m + 1)));
 
        for (int x = 0; x < n; x++)
        {
            for (int y = 0; y < m; y++)
                tree[N + x][0][y] = a[x][y];
            for (int k = 1; k < LOG; k++)
                for (int y = 0; y + (1 << k) <= m; y++)
                    tree[N + x][k][y] = comb(tree[N + x][k - 1][y], tree[N + x][k - 1][y + (1 << (k - 1))]);
        }
        for (int v = N - 1; v > 0; v--)
            for (int k = 0; k < LOG; k++)
                for (int y = 0; y + (1 << k) <= m; y++)
                    tree[v][k][y] = comb(tree[2 * v][k][y], tree[2 * v + 1][k][y]);
        return;
    }
 
    T comb(T a, T b) {
        return __gcd(a, b); // Change the custom operator
    }
 
    T qry(int v, int a, int b, int x1, int x2, int y1, int y2, int k) {
        if (x1 <= a && b <= x2){
            return comb(tree[v][k][y1], tree[v][k][y2]); 
        }
        if (x1 >= b || a >= x2) return 0;
        int mid = (a + b) / 2;
        return comb(qry(2 * v, a, mid, x1, x2, y1, y2, k), qry(2 * v + 1, mid, b, x1, x2, y1, y2, k));
    }
 
    T qry(int lx, int ly, int rx, int ry) {
        int k = 31 - __builtin_clz(ry - ly + 1);
        return qry(1, 0, N, lx, rx + 1, ly, ry - (1 << k) + 1, k);
    }
};
