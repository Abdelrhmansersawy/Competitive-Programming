// When working with palindromes, it's often easier to append the reverse of the string.
// Let N = original.length() and S = original + reverse(original) (length = 2*N).
// A substring original[l..r] (0-based) is a palindrome iff it equals its mirrored substring
// in the reversed half: S[l..r] == S[2*N - 1 - r .. 2*N - 1 - l].
// So instead of checking [l..r] directly, compare it to [2*N-1-r .. 2*N-1-l] in S.

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 6e5 + 9; 
const int LOG = 22;

int p[LOG][N];
int final_p[N]; 
int sz[N]; 
int n_dsu;      

int find_k(int k, int x) {
    return p[k][x] == x ? x : p[k][x] = find_k(k, p[k][x]);
}

void join_layer(int k, int u, int v) {
    u = find_k(k, u);
    v = find_k(k, v);
    if (u != v) p[k][u] = v;
}

int leader(int x) {
    return final_p[x] == x ? x : final_p[x] = leader(final_p[x]);
}

void init_dsu(int n) {
    n_dsu = n;
    for (int k = 0; k < LOG; ++k) {
        for (int i = 0; i <= n + 1; ++i) {
            p[k][i] = i;
        }
    }
    iota(final_p, final_p + n + 1, 0);
    fill(sz, sz + n + 1, 1); 
}

void add_range(int u, int v, int len) {
    if (len <= 0) return;
    int k = 31 - __builtin_clz(len); 
    join_layer(k, u, v);
    join_layer(k, u + len - (1 << k), v + len - (1 << k));
}

void build() {
    for (int k = LOG - 1; k > 0; --k) {
        for (int i = 0; i + (1 << k) <= n_dsu; ++i) {
            int root = find_k(k, i);
            if (i != root) {
                join_layer(k - 1, i, root);
                join_layer(k - 1, i + (1 << (k - 1)), root + (1 << (k - 1)));
            }
        }
    }

    for (int i = 0; i < n_dsu; ++i) {
        int root = find_k(0, i);
        if (i != root) {
            int u = leader(i);
            int v = leader(root);
            if (u != v) {
                final_p[u] = v;
                // [TODO]: Aggregate data here (e.g., sum, max, min)
                sz[v] += sz[u];
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(NULL);

    int n_in, m;
    cin >> n_in >> m;
    
    string s; cin >> s;
    string t = s;
    reverse(t.begin(), t.end());
    s += t; // Concatenate s + reverse(s)

    int n_total = s.size();
    init_dsu(n_total);

    // find index in the reversed part
    auto rev = [&](int i) { return n_total - 1 - i; };

    // 1. Sync character i with its position in the reversed string
    for (int i = 0; i < n_total; ++i) {
        add_range(i, rev(i), 1);
    }

    // 2. Process Queries
    for (int i = 0; i < m; ++i) {
        int l, r; cin >> l >> r;
        --l; --r; 
        
        if (l >= r) continue;
        
        // Constraint: substring s[l...r] is a palindrome.
        // This means s[l...l+sz] == reverse(s[r-sz...r])
        // Which maps to: range(l) == range(rev(r))

        int len = r - l + 1;
        int half_len = len / 2;

        add_range(l, rev(r), half_len);
    }

    build();

    // Depened on your problem
    return 0;
}
