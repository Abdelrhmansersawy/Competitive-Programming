#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 100000 + 10;

// Double-hash parameters
const ll MOD1 = 1000000007;
const ll MOD2 = 1000000009;
const ll B1   = 137;
const ll B2   = 257;

ll pw1[N], pw2[N], LPF[N];

struct Hash {
    ll p1 = 0, s1 = 0;
    ll p2 = 0, s2 = 0;
    int len = 0;

    Hash() = default;
    Hash(char ch) {
        len = 1;
        ll v = ch - 'a' + 1;
        p1 = s1 = v;
        p2 = s2 = v;
    }

    // concatenate: [this] ++ [other]
    Hash operator+(Hash const& o) const {
        Hash r;
        r.len = len + o.len;
        // front hashes
        r.p1 = (p1 * pw1[o.len] + o.p1) % MOD1;
        r.p2 = (p2 * pw2[o.len] + o.p2) % MOD2;
        // suffix hashes (reversed-order)
        r.s1 = (o.s1 * pw1[len] + s1) % MOD1;
        r.s2 = (o.s2 * pw2[len] + s2) % MOD2;
        return r;
    }

    bool operator==(Hash const& o) const {
        return len == o.len
            && p1  == o.p1 && s1  == o.s1
            && p2  == o.p2 && s2  == o.s2;
    }

    // reverse in-place: swap front/suffix
    void reverse() {
        std::swap(p1, s1);
        std::swap(p2, s2);
    }
};

struct Node {
    char ch;
    int sz;
    int prior;
    bool rev;
    Hash h;
    Node *l, *r;

    Node(char _ch)
      : ch(_ch), sz(1), prior(rand()), rev(false),
        h(Hash(_ch)), l(nullptr), r(nullptr)
    {}
};
using PNode = Node*;

struct Treap {
    PNode root = nullptr;

    int  sz(PNode t)       { return t ? t->sz : 0; }
    Hash getH(PNode t)     { return t ? t->h   : Hash(); }

    void pull(PNode t) {
        if (!t) return;
        t->sz = 1 + sz(t->l) + sz(t->r);
        // rebuild full hash: left + self + right
        t->h = getH(t->l) + Hash(t->ch) + getH(t->r);
    }

    void push(PNode t) {
        if (!t || !t->rev) return;
        // reverse this node's aggregate hash
        t->h.reverse();
        // swap children
        swap(t->l, t->r);
        // mark children for lazy reverse
        if (t->l) { t->l->rev ^= 1; t->l->h.reverse(); }
        if (t->r) { t->r->rev ^= 1; t->r->h.reverse(); }
        t->rev = false;
    }

    // split first k chars into [l], rest into [r]
    void split(PNode t, int k, PNode &l, PNode &r) {
        if (!t) { l = r = nullptr; return; }
        push(t);
        if (sz(t->l) < k) {
            split(t->r, k - sz(t->l) - 1, t->r, r);
            l = t;
        } else {
            split(t->l, k, l, t->l);
            r = t;
        }
        pull(t);
    }

    // merge [l] and [r] into t
    void merge(PNode &t, PNode l, PNode r) {
        push(l); push(r);
        if (!l || !r) {
            t = l ? l : r;
        } else if (l->prior > r->prior) {
            merge(l->r, l->r, r);
            t = l;
        } else {
            merge(r->l, l, r->l);
            t = r;
        }
        pull(t);
    }

    // append char to end
    void insert_back(char c) {
        PNode n = new Node(c);
        merge(root, root, n);
    }

    // reverse substring [L..R]
    void reverse_range(int L, int R) {
        PNode a, b, c;
        split(root, L, a, b);
        split(b, R - L + 1, b, c);
        if (b) {
            b->rev ^= 1;
            b->h.reverse();
        }
        PNode tmp;
        merge(tmp, b, c);
        merge(root, a, tmp);
    }

    // get hash of substring [L..R]
    Hash get_hash(int L, int R) {
        PNode a, b, c;
        split(root, L, a, b);
        split(b, R - L + 1, b, c);
        Hash res = getH(b);
        PNode tmp;
        merge(tmp, b, c);
        merge(root, a, tmp);
        return res;
    }

    // in-order print
    void print(PNode t) {
        if (!t) return;
        push(t);
        print(t->l);
        cout << t->ch;
        print(t->r);
    }
} T;

// find minimal period of s[l..r]
int get_period(int l, int r) {
    int len = r - l + 1;
    vector<int> cand;
    while (len > 1) {
        cand.push_back(len);
        len /= LPF[len];
    }
    cand.push_back(1);
    sort(cand.begin(), cand.end());
    for (int v : cand) {
        int blocks = (r - l + 1) / v;
        if (T.get_hash(l, l + (blocks - 1) * v - 1) ==
            T.get_hash(r - (blocks - 1) * v + 1, r))
            return v;
    }
    return 1; // fallback
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand((unsigned)time(nullptr));

        #ifndef ONLINE_JUDGE
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
        freopen("err.txt", "w", stderr);
        #endif 

    // precompute LPF
    memset(LPF, -1, sizeof LPF);
    LPF[0] = LPF[1] = 1;
    for (int i = 2; i < N; i++) {
        if (LPF[i] < 0) LPF[i] = i;
        for (int j = i + i; j < N; j += i)
            if (LPF[j] < 0) LPF[j] = i;
    }

    // precompute powers
    pw1[0] = pw2[0] = 1;
    for (int i = 1; i < N; i++) {
        pw1[i] = pw1[i-1] * B1 % MOD1;
        pw2[i] = pw2[i-1] * B2 % MOD2;
    }

    int n, m;
    string s;
    cin >> n >> m >> s;
    for (char c : s)
        T.insert_back(c);

    set<pair<ll,ll>> seen;
    while (m--) {
        int l, r;
        cin >> l >> r;
        --l; --r;
        int per = get_period(l, r);
        Hash h = T.get_hash(l, l + per - 1);
        pair<ll,ll> key = {h.p1, h.p2};
        if (!seen.count(key)) {
            seen.insert(key);
            T.reverse_range(l, r);
        }
    }

    T.print(T.root);
    cout << "\n";
    return 0;
}
