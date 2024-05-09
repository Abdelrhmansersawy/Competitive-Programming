/*
    --------------BIT2D-----------------
    Use: 1 - add value to element in grid(
         2 - sum of rectangle in grid 
    Base: 0-index
    Time complexity : add , sum >> O(log(n) * log(m))

*/
template<class T = int>
struct BIT2D {
    vector<vector<T>> tree;
    int n , m;
    void init(int n , int m) {
        this->n = n; this->m = m;
        tree.assign(n , vector<T>(m , 0));
    }
    void add(int x, int y, T val) {
        for (int i = x + 1; i <= n; i += (i & (-i))) {
            for (int j = y + 1; j <= m; j += (j & (-j))) {
                tree[i - 1][j - 1] += val;
            }
        }
    }

    T sum(int x, int y) {
        T ret = 0;
        for (int i = x + 1; i; i -= (i & (-i))) {
            for (int j = y + 1; j; j -= (j & (-j))) {
                ret += tree[i - 1][j - 1];
            }
        }
        return ret;
    }

    T qru(int sx, int sy, int ex, int ey) {
        return sum(ex, ey) - sum(ex, sy - 1) - sum(sx - 1, ey) + sum(sx - 1, sy - 1);
    }
    T qru(int x , int y){ return sum(x , y , x , y); }
};
