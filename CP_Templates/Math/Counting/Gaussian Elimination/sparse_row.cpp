#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 1000000007;

#define rep(i, a, b) for (int i = (a); i < (b); ++i)

inline ll addm(ll a, ll b) {
    a += b;
    return (a >= MOD ? a - MOD : a);
}

inline ll subm(ll a, ll b) {
    a -= b;
    return (a < 0 ? a + MOD : a);
}

inline ll mulm(ll a, ll b) {
    return (a * b) % MOD;
}

ll pw(ll a, ll e = MOD - 2) {
    ll r = 1;
    while (e) {
        if (e & 1) r = mulm(r, a);
        a = mulm(a, a);
        e >>= 1;
    }
    return r;
}

// Sparse row with fixed capacity

template<int M>
struct SR {
    int idx[M];
    ll val[M];
    int cnt = 0;

    void add(int i, ll d) {
        if (!d) return;
        for (int j = 0; j < cnt; ++j) {
            if (idx[j] == i) {
                val[j] = addm(val[j], d);
                if (!val[j]) {
                    idx[j] = idx[--cnt];
                    val[j] = val[cnt];
                }
                return;
            }
        }
        assert(cnt < M);
        idx[cnt] = i;
        val[cnt] = d;
        ++cnt;
    }

    ll ex(int i) {
        for (int j = 0; j < cnt; ++j) {
            if (idx[j] == i) {
                ll v = val[j];
                idx[j] = idx[--cnt];
                val[j] = val[cnt];
                return v;
            }
        }
        return 0;
    }
};


ll solve() {
    int n, m;
    string s, t;
    cin >> n >> m >> s >> t;

    vector<array<int, 26>> aut;
    build(t, aut);

    array<ll, 26> pr{};
    for (char c : s) {
        pr[c - 'a']++;
    }

    ll invn = pw(n);
    rep(c, 0, 26) {
        pr[c] = mulm(pr[c], invn);
    }

    vector<SR<52>> rows(m);
    vector<ll> D(m), R(m, 1);
    vector<vector<int>> refs(m);

    rep(i, 0, m) {
        ll w = 0;
        for (int c = 0; c < 26; ++c) {
            int j = aut[i][c];
            ll p = pr[c];
            if (j == m) continue;
            if (j == i) {
                w = addm(w, p);
            } else {
                rows[i].add(j, subm(0, p));
                refs[j].push_back(i);
            }
        }
        D[i] = subm(1, w);
    }

    for (int i = m - 1; i >= 1; --i) {
        ll invd = pw(D[i]);
        for (int r : refs[i]) {
            if (r == i) continue;
            ll a = rows[r].ex(i);
            if (!a) continue;
            ll f = mulm(a, invd);
            R[r] = subm(R[r], mulm(f, R[i]));
            D[r] = subm(D[r], mulm(f, rows[i].ex(r)));

            for (int z = 0; z < rows[i].cnt; ++z) {
                int j = rows[i].idx[z];
                ll d = mulm(f, rows[i].val[z]);
                rows[r].add(j, subm(0, d));
                refs[j].push_back(r);
            }
        }
        refs[i].clear();
    }

    return mulm(R[0], pw(D[0]));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        cout << solve() << '\n';
    }
    return 0;
}
