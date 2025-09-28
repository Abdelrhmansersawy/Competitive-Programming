/*
Title: Number of distinct substrings in an interval
Description:
  Given a string s (length n) and q queries. Each query gives indices l and r (0-based).
  For each query print the number of distinct substrings fully contained in s[l..r].

   
Input format:
  n q
  s
  q lines: l r   (0-based indices)

Complexity:
-----------
- Building SAM: O(n)
- Processing updates with LCT: O(n log n)
- Segment tree updates/queries: O((n + q) log n)
- Total time complexity: O((n + q) log n)
- Space complexity: O(n) states in SAM + O(n) for segment tree + O(n) for LCT 
  ≈ O(n)


Approach:
---------
We need to answer multiple queries of the form: 
  "How many distinct substrings exist in s[l..r]?"

1. Suffix Automaton (SAM):
   - Build a suffix automaton for the whole string.
   - Each state in SAM represents a set of end positions of substrings.
   - By tracking first occurrences and suffix links, we can reason about 
     distinct substrings.

2. Link-Cut Tree (LCT) technique (on SAM tree):
   - We process the string character by character.
   - For each position i, we "activate" state pos[i] (the SAM state that 
     corresponds to the prefix ending at i).
   - We use link-cut tree style splay operations to maintain the last occurrence 
     of each state, which helps us avoid overcounting substrings.

3. Segment Tree with Lazy Propagation:
   - Maintains counts of substrings per interval of positions.
   - When we insert a new character at position i:
       * Add +1 to all substrings ending at i.
       * Use LCT information to subtract contributions of substrings that 
         appeared earlier (to keep substrings distinct).
   - This lets us quickly update and query counts in O(log n).

4. Query Handling:
   - Offline queries grouped by right endpoint r.
   - As we sweep i from 1..n:
       * Update segment tree with contributions of new substrings.
       * For each query (l, r) ending at r, answer = seg.query(l..r).
   - Ensures each query is answered in O(log n).


Note:
  Uses fixed 26-array transitions (nxt[26]) in the suffix automaton.
  If you need to speed this use map
*/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 5;
const int MAXV = 2 * MAXN;

struct SegTree {
    long long t[4 * MAXN];
    long long lazy[4 * MAXN];
    void init() { memset(t, 0, sizeof t); memset(lazy, 0, sizeof lazy); }
    inline void push(int node, int l, int r) {
        if (!lazy[node]) return;
        t[node] += lazy[node] * (r - l + 1);
        if (l != r) {
            lazy[node<<1] += lazy[node];
            lazy[node<<1|1] += lazy[node];
        }
        lazy[node] = 0;
    }
    void upd(int node, int l, int r, int ql, int qr, long long val) {
        push(node, l, r);
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) {
            lazy[node] += val;
            push(node, l, r);
            return;
        }
        int mid = (l + r) >> 1;
        upd(node<<1, l, mid, ql, qr, val);
        upd(node<<1|1, mid+1, r, ql, qr, val);
        t[node] = t[node<<1] + t[node<<1|1];
    }
    long long query(int node, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0;
        push(node, l, r);
        if (ql <= l && r <= qr) return t[node];
        int mid = (l + r) >> 1;
        return query(node<<1, l, mid, ql, qr) + query(node<<1|1, mid+1, r, ql, qr);
    }
} seg;

struct State {
    int len = 0;
    int link = -1;
    int firstpos = 0;
    int nxt[26];
};

State sa[MAXV];
int sz, last;

void sa_init() {
    sz = 1;
    last = 0;
    sa[0].len = 0;
    sa[0].link = -1;
    sa[0].firstpos = 0;
    for (int j = 0; j < 26; ++j) sa[0].nxt[j] = -1;
}

void sa_extend(int c) {
    int cur = sz++;
    sa[cur].len = sa[last].len + 1;
    sa[cur].firstpos = sa[cur].len;
    for (int j = 0; j < 26; ++j) sa[cur].nxt[j] = -1;
    int p = last;
    while (p != -1 && sa[p].nxt[c] == -1) {
        sa[p].nxt[c] = cur;
        p = sa[p].link;
    }
    if (p == -1) {
        sa[cur].link = 0;
    } else {
        int q = sa[p].nxt[c];
        if (sa[p].len + 1 == sa[q].len) {
            sa[cur].link = q;
        } else {
            int clone = sz++;
            sa[clone].len = sa[p].len + 1;
            for (int j = 0; j < 26; ++j) sa[clone].nxt[j] = sa[q].nxt[j];
            sa[clone].link = sa[q].link;
            sa[clone].firstpos = sa[q].firstpos;
            while (p != -1 && sa[p].nxt[c] == q) {
                sa[p].nxt[c] = clone;
                p = sa[p].link;
            }
            sa[q].link = sa[cur].link = clone;
        }
    }
    last = cur;
}

int lct_par[MAXV], lct_c[MAXV][2], lct_lazy[MAXV], lct_lastOcc[MAXV];
int splay_stack[MAXV];
pair<int,int> modifies[MAXV];
int modifies_cnt;

inline void lct_mark(int x, int v) { lct_lazy[x] = v; lct_lastOcc[x] = v; }
inline void lct_push(int x) {
    if (!lct_lazy[x]) return;
    if (lct_c[x][0]) lct_mark(lct_c[x][0], lct_lazy[x]);
    if (lct_c[x][1]) lct_mark(lct_c[x][1], lct_lazy[x]);
    lct_lazy[x] = 0;
}
inline bool lct_is_root(int x) {
    int p = lct_par[x];
    return lct_c[p][0] != x && lct_c[p][1] != x;
}
inline void lct_rotate(int x) {
    int y = lct_par[x], z = lct_par[y];
    int k = (lct_c[y][1] == x);
    if (!lct_is_root(y)) lct_c[z][lct_c[z][1] == y] = x;
    lct_par[lct_c[y][k] = lct_c[x][!k]] = y;
    lct_par[lct_c[x][!k] = y] = x;
    lct_par[x] = z;
}
inline void lct_splay(int x) {
    int top = 0;
    int v = x;
    splay_stack[++top] = v;
    while (!lct_is_root(v)) { v = lct_par[v]; splay_stack[++top] = v; }
    while (top) lct_push(splay_stack[top--]);
    while (!lct_is_root(x)) {
        int y = lct_par[x], z = lct_par[y];
        if (!lct_is_root(y)) {
            if ((lct_c[y][1] == x) == (lct_c[z][1] == y)) lct_rotate(y);
            else lct_rotate(x);
        }
        lct_rotate(x);
    }
}

void lct_access(int x, int v) {
    int z = 0;
    modifies_cnt = 0;
    while (x) {
        lct_splay(x);
        modifies[++modifies_cnt] = { sa[x-1].len, lct_lastOcc[x] };
        lct_c[x][1] = z;
        lct_mark(x, v);
        z = x;
        x = lct_par[x];
    }
}

int pos[MAXN];
vector<pair<int,int>> Q[MAXN];
long long ans[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, qcount; cin >> n >> qcount;
    string s; cin >> s;

    for (int i = 0; i <= n; ++i) Q[i].clear();
    for (int i = 1; i <= qcount; ++i) {
        int l, r; cin >> l >> r;
        ++l; ++r;
        Q[r].push_back({l, i});
    }

    sa_init();
    seg.init();

    s = '.' + s;
    pos[0] = 1;
    for (int i = 1; i <= n; ++i) {
        int c = s[i] - 'a';
        if (c < 0 || c >= 26) c = 0;
        sa_extend(c);
        pos[i] = last + 1;
    }

    for (int i = 1; i <= sz; ++i) {
        int link = sa[i-1].link;
        lct_par[i] = link + 1;
        lct_c[i][0] = lct_c[i][1] = 0;
        lct_lazy[i] = 0;
        lct_lastOcc[i] = 0;
    }
    lct_par[0] = 0; lct_c[0][0] = lct_c[0][1] = 0; lct_lazy[0] = 0; lct_lastOcc[0] = 0;

    for (int i = 1; i <= n; ++i) {
        seg.upd(1, 1, n, 1, i, 1);
        lct_access(pos[i], i);

        int lastLen = 0;
        for (int j = modifies_cnt; j > 1; --j) {
            int length = modifies[j].first;
            int prevLast = modifies[j].second;
            if (length == 0) continue;
            if (prevLast) {
                int L = prevLast - length + 1;
                int R = prevLast - lastLen;
                if (L <= R) seg.upd(1, 1, n, L, R, -1);
            }
            lastLen = length;
        }

        for (auto &pr : Q[i]) {
            int l = pr.first;
            int id = pr.second;
            ans[id] = seg.query(1, 1, n, l, i);
        }
    }

    for (int i = 1; i <= qcount; ++i) cout << ans[i] << '\n';
    return 0;
}
