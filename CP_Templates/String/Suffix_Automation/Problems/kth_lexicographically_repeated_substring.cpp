// Problem link: https://cses.fi/problemset/task/2109

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
struct state {
    int len, link;
    int nxt[26];
    state() {
        len = 0; link = -1;
        fill(nxt, nxt+26, -1);
    }
};
 
const int MAXN = 1e5+9;
state st[2*MAXN];
ll dp[2*MAXN], cnt[2*MAXN];
int sz, last;
 
void sa_init() {
    st[0] = state();
    sz = 1; last = 0;
}
 
void sa_extend(char cc) {
    int c = cc - 'a';
    int cur = sz++;
    st[cur] = state();
    st[cur].len = st[last].len + 1;
    cnt[cur] = 1;
 
    int p = last;
    while (p != -1 && st[p].nxt[c] == -1) {
        st[p].nxt[c] = cur;
        p = st[p].link;
    }
    if (p == -1) {
        st[cur].link = 0;
    } else {
        int q = st[p].nxt[c];
        if (st[p].len + 1 == st[q].len) {
            st[cur].link = q;
        } else {
            int clone = sz++;
            st[clone] = st[q];
            st[clone].len = st[p].len + 1;
            while (p != -1 && st[p].nxt[c] == q) {
                st[p].nxt[c] = clone;
                p = st[p].link;
            }
            st[q].link = st[cur].link = clone;
        }
    }
    last = cur;
}
 
void propagation() {
    vector<int> order(sz);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b) {
        return st[a].len > st[b].len;
    });
    for (int v : order) {
        if (st[v].link != -1) cnt[st[v].link] += cnt[v];
    }
}
 
ll solve(int v) {
    if (dp[v] != -1) return dp[v];
    ll res = 0;
    for (int c = 0; c < 26; c++) {
        int u = st[v].nxt[c];
        if (u != -1) {
            res += cnt[u];      // substrings of length 1 from this edge
            res += solve(u);    // longer substrings
        }
    }
    return dp[v] = res;
}
 
void printKth(int v, ll k) {
    for (char ch = 'a'; ch <= 'z'; ch++) {
        int u = st[v].nxt[ch-'a'];
        if (u == -1) continue;
        ll total = cnt[u] + solve(u);
        if (k <= total) {
            cout << ch;
            if (k <= cnt[u]) return;  // stop here
            printKth(u, k - cnt[u]);
            return;
        } else {
            k -= total;
        }
    }
}
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
 
    string s; cin >> s;
    sa_init();
    for (char c: s) sa_extend(c);
 
    propagation();
    memset(dp, -1, sizeof dp);
 
    ll k; cin >> k;
    printKth(0, k);
    cout << "\n";
}
