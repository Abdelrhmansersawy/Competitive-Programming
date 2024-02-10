/*
	--------------BIT2D-----------------
	Use: 1 - add value to element in grid(
		 2 - sum of rectangle in grid 
	Base: 0-index
	Time complexity : add , sum >> O(log(n) * log(m))

*/
struct BIT2D {
    vector<vector<int>> tree;
    int n , m;
    void init(int n , int m) {
        this->n = n; this->m = m;
        tree.assign(n , vector<int>(m , 0));
    }
    void add(int x, int y, int val) {
        for (int i = x + 1; i <= n; i += (i & (-i))) {
            for (int j = y + 1; j <= m; j += (j & (-j))) {
                tree[i - 1][j - 1] += val;
            }
        }
    }

    int sum(int x, int y) {
        int ret = 0;
        for (int i = x + 1; i; i -= (i & (-i))) {
            for (int j = y + 1; j; j -= (j & (-j))) {
                ret += tree[i - 1][j - 1];
            }
        }
        return ret;
    }

    int sum(int sx, int sy, int ex, int ey) {
        return sum(ex, ey) - sum(ex, sy - 1) - sum(sx - 1, ey) + sum(sx - 1, sy - 1);
    }
    int getval(int x , int y){ return sum(x , y , x , y); }
};
