/*
    2D segment Tree
    - Memory allocation: O(4n x 4m)
    - range [l..r] , r: inclusive 
    - Base: 0-index
    
    Function description:
        1. upd(r , c , val): update cell (r,c) with value val
           Time complexity: O(log(n) x log(m))
        2. qry(lx , rx , ly , ry): find (min,max,sum,produc) of rectangle [lx...rx] x [ly...ry]
           Time complexity: O(log(n) x log(m))
        3. init(n , m): initial the segment tree 
        4. build(g): build the segment tree with grid[n][m]
           Time complexity: O(n log(n) x m log(m))
*/

struct Node {
    int v;
    Node(int x = 0) : v(x) {}
    Node operator+(const Node& o) const { return Node(std::__gcd(v, o.v)); }
};

struct SegTree2D {
    int n, m;
    vector<vector<Node>> t;

    void by(int x, int xl, int xr, int y, int yl, int yr, const vector<vector<int>>& g) {
        if (yl == yr) {
            if (xl == xr) t[x][y] = Node(g[xl][yl]);
            else t[x][y] = t[x * 2][y] + t[x * 2 + 1][y];
        } else {
            int mid = (yl + yr) / 2;
            by(x, xl, xr, y * 2, yl, mid, g);
            by(x, xl, xr, y * 2 + 1, mid + 1, yr, g);
            t[x][y] = t[x][y * 2] + t[x][y * 2 + 1];
        }
    }

    void bx(int x, int xl, int xr, const vector<vector<int>>& g) {
        if (xl != xr) {
            int mid = (xl + xr) / 2;
            bx(x * 2, xl, mid, g);
            bx(x * 2 + 1, mid + 1, xr, g);
        }
        by(x, xl, xr, 1, 0, m - 1, g);
    }

    void uy(int x, int xl, int xr, int y, int yl, int yr, int r, int c, int v) {
        if (yl == yr) {
            if (xl == xr) t[x][y] = v;
            else t[x][y] = t[x * 2][y] + t[x * 2 + 1][y];
        } else {
            int mid = (yl + yr) / 2;
            if (c <= mid) uy(x, xl, xr, y * 2, yl, mid, r, c, v);
            else uy(x, xl, xr, y * 2 + 1, mid + 1, yr, r, c, v);
            t[x][y] = t[x][y * 2] + t[x][y * 2 + 1];
        }
    }

    void ux(int x, int xl, int xr, int r, int c, int v) {
        if (xl != xr) {
            int mid = (xl + xr) / 2;
            if (r <= mid) ux(x * 2, xl, mid, r, c, v);
            else ux(x * 2 + 1, mid + 1, xr, r, c, v);
        }
        uy(x, xl, xr, 1, 0, m - 1, r, c, v);
    }

    Node qy(int x, int y, int yl, int yr, int ly, int ry) {
        if (ly > ry) return Node();
        if (ly == yl && yr == ry) return t[x][y];
        int mid = (yl + yr) / 2;
        return qy(x, y * 2, yl, mid, ly, min(ry, mid)) + qy(x, y * 2 + 1, mid + 1, yr, max(ly, mid + 1), ry);
    }

    Node qx(int x, int xl, int xr, int lx, int rx, int ly, int ry) {
        if (lx > rx) return Node();
        if (lx == xl && xr == rx) return qy(x, 1, 0, m - 1, ly, ry);
        int mid = (xl + xr) / 2;
        return qx(x * 2, xl, mid, lx, min(rx, mid), ly, ry) + qx(x * 2 + 1, mid + 1, xr, max(lx, mid + 1), rx, ly, ry);
    }

public:
    // 3. init(n , m): initial the segment tree 
    void init(int N, int M) {
        n = N; m = M;
        int r = 1, c = 1;
        while (r < n) r *= 2;
        while (c < m) c *= 2;
        t.assign(2 * r, vector<Node>(2 * c));
    }

    // 4. build(g): build the segment tree with grid[n][m]
    void build(const vector<vector<int>>& g) { bx(1, 0, n - 1, g); }

    // 1. upd(r , c , val): update cell (r,c) with value val
    void upd(int r, int c, int v) { ux(1, 0, n - 1, r, c, v); }

    // 2. qry(lx , rx , ly , ry): find (min,max,sum,produc) of rectangle [lx...rx] x [ly...ry]
    int qry(int r1, int c1, int r2, int c2) { return qx(1, 0, n - 1, r1, r2, c1, c2).v; }
};
