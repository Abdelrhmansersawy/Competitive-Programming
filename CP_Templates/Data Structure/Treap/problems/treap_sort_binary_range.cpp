#include <bits/stdc++.h>
using namespace std;

/*
Run-length implicit treap with pull/push style split & merge.

Functions:
 - split(t, k, l, r) : first k elements -> l, rest -> r
 - merge(t, l, r)     : result put into t (by reference)
 - pull(t) recomputes aggregated Info from children + node run (preserves lazy flags)
 - push(t) propagates lazy flags to children
*/

struct Info {
    bool rev = false;
    bool flip = false;

    int sz = 0;
    int cnt0 = 0, cnt1 = 0;

    int pref0 = 0, pref1 = 0;
    int suff0 = 0, suff1 = 0;

    int best = 0;

    Info() = default;
    static Info empty() { return Info{}; }

    static Info from_run(int len, int v) {
        Info I;
        I.sz = len;
        I.cnt0 = (v == 0) ? len : 0;
        I.cnt1 = (v == 1) ? len : 0;
        I.pref0 = I.suff0 = (v == 0) ? len : 0;
        I.pref1 = I.suff1 = (v == 1) ? len : 0;
        I.best = len;
        return I;
    }

    void apply_flip() {
        flip = !flip;
        swap(cnt0, cnt1);
        swap(pref0, pref1);
        swap(suff0, suff1);
        // best unchanged
    }
    void apply_rev() {
        rev = !rev;
        swap(pref0, suff0);
        swap(pref1, suff1);
        // best unchanged
    }

    Info operator+(Info const &other) const {
        if (sz == 0) return other;
        if (other.sz == 0) return *this;
        Info res;
        res.sz = sz + other.sz;
        res.cnt0 = cnt0 + other.cnt0;
        res.cnt1 = cnt1 + other.cnt1;

        res.pref0 = (pref0 == sz) ? (sz + other.pref0) : pref0;
        res.pref1 = (pref1 == sz) ? (sz + other.pref1) : pref1;

        res.suff0 = (other.suff0 == other.sz) ? (other.sz + suff0) : other.suff0;
        res.suff1 = (other.suff1 == other.sz) ? (other.sz + suff1) : other.suff1;

        int cross0 = suff0 + other.pref0;
        int cross1 = suff1 + other.pref1;
        res.best = max({best, other.best, cross0, cross1});

        res.rev = false;
        res.flip = false;
        return res;
    }
};

struct Node {
    int v;      // 0 or 1 (value of run)
    int cnt;    // run length (number of elements with value v)
    int prior;
    Node *l = nullptr, *r = nullptr;
    Info info;

    Node(int _v = 0, int _cnt = 1)
        : v(_v), cnt(_cnt), prior(((rand() << 16) ^ rand())) {
        info = Info::from_run(cnt, v);
    }
};
using PNode = Node*;

inline int sz(PNode t) { return t ? t->info.sz : 0; }

// forward declarations
void pull(PNode t);
void push(PNode t);

void apply_flip_node(PNode t) {
    if (!t) return;
    t->info.apply_flip();
    t->v ^= 1;
}

void apply_rev_node(PNode t) {
    if (!t) return;
    t->info.apply_rev();
    swap(t->l, t->r);
}

void push(PNode t) {
    if (!t) return;
    if (t->info.rev) {
        if (t->l) apply_rev_node(t->l);
        if (t->r) apply_rev_node(t->r);
        t->info.rev = false;
    }
    if (t->info.flip) {
        if (t->l) apply_flip_node(t->l);
        if (t->r) apply_flip_node(t->r);
        t->info.flip = false;
    }
}

// recompute aggregated info from children + this node's run
// preserve current lazy flags (rev/flip) present on t->info
void pull(PNode t) {
    if (!t) return;
    Info L = t->l ? t->l->info : Info::empty();
    Info R = t->r ? t->r->info : Info::empty();
    Info me = Info::from_run(t->cnt, t->v);
    Info res = L + me + R;
    // preserve lazy flags
    res.rev = t->info.rev;
    res.flip = t->info.flip;
    t->info = res;
}

// merge result into t by reference
void merge(PNode &t, PNode l, PNode r) {
    push(l); push(r);
    if (!l || !r) {
        t = l ? l : r;
        pull(t);
        return;
    }
    if (l->prior > r->prior) {
        // l is root
        merge(l->r, l->r, r);
        t = l;
        pull(t);
    } else {
        // r is root
        merge(r->l, l, r->l);
        t = r;
        pull(t);
    }
}

// split first k elements into l, rest into r
void split(PNode t, int k, PNode &l, PNode &r) {
    if (!t) { l = r = nullptr; return; }
    push(t);
    int left_sz = sz(t->l);
    if (k < left_sz) {
        // entirely in left child
        split(t->l, k, l, t->l);
        r = t;
        pull(r);
    } else if (k > left_sz + t->cnt) {
        // entirely in right subtree
        split(t->r, k - left_sz - t->cnt, t->r, r);
        l = t;
        pull(l);
    } else if (k == left_sz) {
        // cut exactly before this run: node goes to r
        l = t->l;
        t->l = nullptr;
        pull(t);
        r = t;
    } else if (k == left_sz + t->cnt) {
        // cut exactly after this run: node goes to l
        r = t->r;
        t->r = nullptr;
        pull(t);
        l = t;
    } else {
        // split inside this run -> create two nodes
        int left_take = k - left_sz;            // 1 <= left_take < t->cnt
        int right_take = t->cnt - left_take;    // >=1

        // ensure no pending lazies in t (we called push earlier)
        PNode leftNode = new Node(t->v, left_take);
        PNode rightNode = new Node(t->v, right_take);

        // attach existing children
        leftNode->l = t->l;
        rightNode->r = t->r;

        // leftNode has no right child; rightNode has no left child
        pull(leftNode);
        pull(rightNode);

        l = leftNode;
        r = rightNode;

        // we could delete t here to avoid leak, but it's safe to leave (or reuse a pool)
        // delete t; // optional
    }
}

// build treap from run list using Cartesian tree (O(m))
PNode build_from_runs(const vector<pair<int,int>> &runs) {
    int m = (int)runs.size();
    if (m == 0) return nullptr;
    vector<PNode> nodes; nodes.reserve(m);
    for (auto &p : runs) nodes.push_back(new Node(p.first, p.second));
    vector<PNode> st;
    for (int i = 0; i < m; ++i) {
        PNode last = nullptr;
        while (!st.empty() && st.back()->prior < nodes[i]->prior) {
            last = st.back();
            st.pop_back();
        }
        nodes[i]->l = last;
        if (!st.empty()) st.back()->r = nodes[i];
        st.push_back(nodes[i]);
    }
    PNode root = st.front();
    // compute infos bottom-up
    function<void(PNode)> dfs = [&](PNode u) {
        if (!u) return;
        dfs(u->l);
        dfs(u->r);
        pull(u);
    };
    dfs(root);
    return root;
}

PNode build_sorted_mid(int zeros, int ones) {
    if (zeros == 0 && ones == 0) return nullptr;
    if (zeros == 0) return new Node(1, ones);
    if (ones == 0) return new Node(0, zeros);
    // create two nodes then merge by reference
    PNode a = new Node(0, zeros);
    PNode b = new Node(1, ones);
    PNode res = nullptr;
    merge(res, a, b);
    return res;
}

PNode build_from_string(const string &s) {
    int n = (int)s.size();
    if (n == 0) return nullptr;
    vector<pair<int,int>> runs;
    runs.reserve(n);
    char cur = s[0];
    int cnt = 1;
    for (int i = 1; i < n; ++i) {
        if (s[i] == cur) ++cnt;
        else {
            runs.emplace_back(cur == '1' ? 1 : 0, cnt);
            cur = s[i];
            cnt = 1;
        }
    }
    runs.emplace_back(cur == '1' ? 1 : 0, cnt);
    return build_from_runs(runs);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand((unsigned)chrono::high_resolution_clock::now().time_since_epoch().count());

    int n, q;
    if (!(cin >> n >> q)) return 0;
    string s; cin >> s;
    PNode root = build_from_string(s);

    while (q--) {
        int t, lpos, rpos;
        cin >> t >> lpos >> rpos;
        PNode A = nullptr, MID = nullptr, C = nullptr;
        split(root, lpos - 1, A, MID);
        split(MID, rpos - lpos + 1, MID, C);

        if (t == 1) {
            if (MID) apply_flip_node(MID);
        } else if (t == 2) {
            if (MID) apply_rev_node(MID);
        } else { // t == 3 sort nondecreasing: zeros then ones
            int zeros = MID ? MID->info.cnt0 : 0;
            int ones = MID ? MID->info.cnt1 : 0;
            // build small mid treap from counts
            MID = build_sorted_mid(zeros, ones);
        }

        PNode tmp = nullptr;
        merge(tmp, A, MID);
        merge(root, tmp, C);

        int ans = root ? root->info.best : 0;
        cout << ans << '\n';
    }
    return 0;
}
