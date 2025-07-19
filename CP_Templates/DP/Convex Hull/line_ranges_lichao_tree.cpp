#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

// Define short names for datatypes
using ll = long long;
using i128 = __int128_t;
using vll = std::vector<ll>;
using namespace std;

/*
    ----------- Sparse Li Chao Tree for Problem -----------
    Adapted to solve the specific problem.
    - Uses __int128_t to prevent overflow.
    - Handles half-open range [l, r) for adds.
    - Handles arbitrary query points p.
*/
class LiChaoTree {
private:
    struct Line {
        ll a = 0, b = 0;
        bool is_null = true;
        Line() = default;
        Line(ll a_val, ll b_val) : a(a_val), b(b_val), is_null(false) {}
        i128 eval(ll x) const {
            if (is_null) return INF;
            return (i128)a * x + b;
        }
    };

    struct Node {
        Line line;
        int left = -1, right = -1;
    };

    vll coords;
    vector<Node> tree;
    int timer = 0;
    int max_idx = -1;

    void node_add_line(int cur, int tl, int tr, Line new_line) {
        if (new_line.is_null) return;
        if (tree[cur].line.is_null) {
            tree[cur].line = new_line;
            return;
        }
        int tm = tl + (tr - tl) / 2;
        ll x_mid = coords[tm];
        bool new_bet_mid = new_line.eval(x_mid) < tree[cur].line.eval(x_mid);
        if (new_bet_mid) swap(tree[cur].line, new_line);
        if (tl == tr) return;

        if (new_line.eval(coords[tl]) < tree[cur].line.eval(coords[tl])) {
            if (tree[cur].left == -1) {
                tree[cur].left = ++timer;
                tree.push_back(Node());
            }
            node_add_line(tree[cur].left, tl, tm, new_line);
        }
        if (new_line.eval(coords[tr]) < tree[cur].line.eval(coords[tr])) {
            if (tree[cur].right == -1) {
                tree[cur].right = ++timer;
                tree.push_back(Node());
            }
            node_add_line(tree[cur].right, tm + 1, tr, new_line);
        }
    }

    void add(int cur, int tl, int tr, int ql, int qr, Line new_line) {
        if (qr < tl || ql > tr) return;
        if (ql <= tl && tr <= qr) {
            node_add_line(cur, tl, tr, new_line);
            return;
        }
        int tm = tl + (tr - tl) / 2;
        if (tree[cur].left == -1) {
            tree[cur].left = ++timer;
            tree.push_back(Node());
        }
        add(tree[cur].left, tl, tm, ql, qr, new_line);
        if (tree[cur].right == -1) {
            tree[cur].right = ++timer;
            tree.push_back(Node());
        }
        add(tree[cur].right, tm + 1, tr, ql, qr, new_line);
    }
    
    i128 query_point(int cur, int tl, int tr, int p_idx, ll p_val) {
        if (cur == -1) return INF;
        i128 min_val = tree[cur].line.eval(p_val);
        if (tl == tr) return min_val;
        int tm = tl + (tr - tl) / 2;
        if (p_idx <= tm) {
            min_val = min(min_val, query_point(tree[cur].left, tl, tm, p_idx, p_val));
        } else {
            min_val = min(min_val, query_point(tree[cur].right, tm + 1, tr, p_idx, p_val));
        }
        return min_val;
    }

public:
    static const i128 INF = (i128)4e18;

    LiChaoTree(const vll& unique_coords, int Q_hint = 0) : coords(unique_coords) {
        tree.push_back(Node());
        int M = coords.size();
        if (M > 1) max_idx = M - 2;
        if (Q_hint > 0 && M > 1) {
            tree.reserve(2 * Q_hint * __lg(M));
        }
    }

    void addLine(ll l, ll r, ll a, ll b) {
        if (max_idx == -1 || l >= r) return;
        int l_idx = lower_bound(coords.begin(), coords.end(), l) - coords.begin();
        int r_idx = lower_bound(coords.begin(), coords.end(), r) - coords.begin();
        add(0, 0, max_idx, l_idx, r_idx - 1, Line(a, b));
    }

    i128 queryPoint(ll p) {
        if (max_idx == -1) return INF;
        int p_idx = upper_bound(coords.begin(), coords.end(), p) - coords.begin() - 1;
        if (p_idx < 0 || p_idx > max_idx) return INF;
        return query_point(0, 0, max_idx, p_idx, p);
    }
    
    static void print_i128(i128 n) {
        if (n >= INF) {
            cout << "INFINITY\n";
            return;
        }
        if (n == 0) {
            cout << "0\n";
            return;
        }
        string s = "";
        bool neg = false;
        if (n < 0) {
            neg = true;
            n = -n;
        }
        while (n > 0) {
            s += (n % 10) + '0';
            n /= 10;
        }
        if (neg) s += '-';
        reverse(s.begin(), s.end());
        cout << s << "\n";
    }
};

// Helper struct to store queries for pre-processing
struct Query {
    int type;
    ll l, r, a, b, p;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, Q;
    cin >> N >> Q;

    vector<Query> queries(N + Q);
    vll all_x_coords;

    for (int i = 0; i < N; ++i) {
        queries[i].type = 0;
        cin >> queries[i].l >> queries[i].r >> queries[i].a >> queries[i].b;
    }
    for (int i = 0; i < Q; ++i) {
        cin >> queries[N + i].type;
        if (queries[N + i].type == 0) {
            cin >> queries[N + i].l >> queries[N + i].r >> queries[N + i].a >> queries[N + i].b;
        } else {
            cin >> queries[N + i].p;
        }
    }

    for (const auto& q : queries) {
        if (q.type == 0) {
            all_x_coords.push_back(q.l);
            all_x_coords.push_back(q.r);
        } else {
            all_x_coords.push_back(q.p);
        }
    }

    sort(all_x_coords.begin(), all_x_coords.end());
    all_x_coords.erase(unique(all_x_coords.begin(), all_x_coords.end()), all_x_coords.end());

    LiChaoTree lct(all_x_coords, Q);

    for (const auto& q : queries) {
        if (q.type == 0) {
            lct.addLine(q.l, q.r, q.a, q.b);
        } else {
            i128 result = lct.queryPoint(q.p);
            LiChaoTree::print_i128(result);
        }
    }

    return 0;
}
