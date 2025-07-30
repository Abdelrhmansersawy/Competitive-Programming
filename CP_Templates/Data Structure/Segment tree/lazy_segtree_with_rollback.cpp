/*
 * Segment Tree with Rollback
 * --------------------------
 * Supports range add updates and range sum queries with rollback capability.
 * You can undo the last update using rollback().
 * 
 * Operations:
 *  - init(n): initialize the tree for `n` elements.
 *  - build(a): build the tree from vector `a`.
 *  - upd_rb(l, r, v): add `v` to range [l, r) and save history.
 *  - qry(l, r): sum on range [l, r).
 *  - rollback(): undo the last upd_rb() operation.
 * 
 * Time complexity:
 *  - upd/qry: O(log n)
 *  - rollback: amortized O(log n) per rollback
 */

struct SegTreeRollback {
    typedef long long ll;
    struct Node {
        ll s = 0;
        Node() {}
        Node(ll v): s(v) {}
        Node operator+(Node o) const { return Node(s + o.s); }
    };

    void init(int sz) {
        n = sz;
        tr.assign(4 * n, Node());
        lz.assign(4 * n, 0);
    }

    void build(vector<ll> &a, int x = 0, int l = 0, int r = -1) {
        if (r == -1) r = n;
        if (r - l == 1) { tr[x] = Node(a[l]); return; }
        int m = (l + r) / 2;
        build(a, 2 * x + 1, l, m);
        build(a, 2 * x + 2, m, r);
        tr[x] = tr[2 * x + 1] + tr[2 * x + 2];
    }

    void upd_rb(int l, int r, ll v) {
        times.push_back(t);
        upd(l, r, v);
        t++;
    }

    Node qry(int ql, int qr, int x = 0, int l = 0, int r = -1) {
        if (r == -1) r = n;
        if (qr <= l || r <= ql) return Node();
        push(x, l, r);
        if (ql <= l && r <= qr) return tr[x];
        int m = (l + r) / 2;
        return qry(ql, qr, 2 * x + 1, l, m) + qry(ql, qr, 2 * x + 2, m, r);
    }

    void rollback() {
        if (times.empty()) return;
        int last = times.back(); times.pop_back();
        while (!hist.empty() && hist.back().t >= last) {
            auto &s = hist.back();
            tr[s.i] = s.nd;
            lz[s.i] = s.lz;
            hist.pop_back();
        }
    }

private:
    struct Save {
        int t, i;
        Node nd;
        ll lz;
    };

    int n, t = 0;
    vector<Node> tr;
    vector<ll> lz;
    vector<int> times;
    vector<Save> hist;

    void save(int i) { hist.push_back({t, i, tr[i], lz[i]}); }

    void apply(int x, int l, int r, ll v) {
        save(x);
        tr[x].s += v * (r - l);
        lz[x] += v;
    }

    void push(int x, int l, int r) {
        if (!lz[x] || r - l == 1) return;
        int m = (l + r) / 2;
        apply(2 * x + 1, l, m, lz[x]);
        apply(2 * x + 2, m, r, lz[x]);
        lz[x] = 0;
    }

    void upd(int ql, int qr, ll v, int x = 0, int l = 0, int r = -1) {
        if (r == -1) r = n;
        if (qr <= l || r <= ql) return;
        if (ql <= l && r <= qr) { apply(x, l, r, v); return; }
        push(x, l, r);
        int m = (l + r) / 2;
        upd(ql, qr, v, 2 * x + 1, l, m);
        upd(ql, qr, v, 2 * x + 2, m, r);
        tr[x] = tr[2 * x + 1] + tr[2 * x + 2];
    }
};
