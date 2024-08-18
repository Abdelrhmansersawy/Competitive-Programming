/*
    --------------BIT2D-----------------
    - Memory allocation: O(n x m)
    - range [l..r] , r: inclusive 
    - Base: 0-index

    Function description:
    1. init(n , m): initial a BIT with 2D grid[n][m]
       Time complexity: O(n x 4)
    2. upd(x , y , val): add to a cell(x ,y) value "val"
       Time complexity: O( log(n) x log(m) ) , here log is small constanst
    2. qry(lx , rx , ly , ry): find (sum,xor) of rectangle [lx...rx] x [ly...ry]
       Time complexity: O(log(n) x log(m))

*/
template<class T = int>
struct BIT2D {
private:
    vector<vector<T>> tree;
    int n , m;
    T sum(int x, int y) {
        T ret = 0;
        for (int i = x + 1; i; i -= (i & (-i))) {
            for (int j = y + 1; j; j -= (j & (-j))) {
                ret += tree[i - 1][j - 1];
            }
        }
        return ret;
    }
public:
    void init(int n , int m) {
        this->n = n; this->m = m;
        tree.assign(n , vector<T>(m , 0));
    }
    void upd(int x, int y, T val) {
        for (int i = x + 1; i <= n; i += (i & (-i))) {
            for (int j = y + 1; j <= m; j += (j & (-j))) {
                tree[i - 1][j - 1] += val;
            }
        }
    }
    T qry(int sx, int sy, int ex, int ey) {
        return sum(ex, ey) - sum(ex, sy - 1) - sum(sx - 1, ey) + sum(sx - 1, sy - 1);
    }
    T qry(int x , int y){ return sum(x , y , x , y); }
};
