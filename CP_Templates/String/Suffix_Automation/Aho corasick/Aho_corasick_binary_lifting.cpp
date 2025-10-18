// Globals for binary lifting tables
int n, m, LG;
vector<int> up1, up2;
vector<ll> res1, res2;

// Converts 3D table indices (k, i, u) to a 1D index
int id(int k, int i, int u) {
    return (k * n + i) * m + u;
}

// Precomputes traversals for all 2^k length substrings
void build(const string &s, const AhoCorasick &ac) {
    n = s.size();
    m = ac.v.size();
    LG = 0;
    while ((1 << LG) <= n) ++LG;

    up1.assign(LG * n * m, -1);
    up2.assign(LG * n * m, -1);
    res1.assign(LG * n * m, 0LL);
    res2.assign(LG * n * m, 0LL);

    for (int i = 0; i < n; ++i) {
        for (int u = 0; u < m; ++u) {
            int v = ac.v[u].nxt[s[i] - 'a'];
            up1[id(0, i, u)] = up2[id(0, i, u)] = v;
            res1[id(0, i, u)] = res2[id(0, i, u)] = ac.v[v].nmatches;
        }
    }

    for (int k = 1; k < LG; ++k) {
        int h = 1 << (k - 1);
        for (int i = 0; i + (1 << k) <= n; ++i) {
            for (int u = 0; u < m; ++u) {
                int v = up1[id(k - 1, i, u)];
                if (v != -1) {
                    up1[id(k, i, u)] = up1[id(k - 1, i + h, v)];
                    if (up1[id(k, i, u)] != -1)
                        res1[id(k, i, u)] = res1[id(k - 1, i, u)] + res1[id(k - 1, i + h, v)];
                }
            }
        }
        for (int i = (1 << k) - 1; i < n; ++i) {
            for (int u = 0; u < m; ++u) {
                int v = up2[id(k - 1, i, u)];
                if (v != -1) {
                    up2[id(k, i, u)] = up2[id(k - 1, i - h, v)];
                    if (up2[id(k, i, u)] != -1)
                        res2[id(k, i, u)] = res2[id(k - 1, i, u)] + res2[id(k - 1, i - h, v)];
                }
            }
        }
    }
}

// Queries for the result of traversing k characters from index i
pair<int, ll> query(int i, int u, int k, bool rev) {
    ll cur_res = 0;
    for (int b = 0; b < LG; ++b) {
        if ((k >> b) & 1) {
            if (u == -1) break;
            int I = id(b, i, u);
            cur_res += rev ? res2[I] : res1[I];
            u = rev ? up2[I] : up1[I];
            i += rev ? -(1 << b) : (1 << b);
        }
    }
    return {u, cur_res};
}

// Solves the problem by checking all reversal segments [l,r]
ll solve(string &s, AhoCorasick &ac) {
    int n = s.size();
    ll ans = query(0, 0, n, false).second;
    ll pre_m = 0;
    int pre_n = 0;

    for (int l = 0; l < n; ++l) {
        for (int r = l; r < n; ++r) {
            ll total = pre_m;
            auto [mid_n, mid_m] = query(r, pre_n, r - l + 1, true);

            if (mid_n != -1) {
                total += mid_m;
                if (r + 1 < n)
                    total += query(r + 1, mid_n, n - (r + 1), false).second;
                ans = max(ans, total);
            }
        }
        pre_n = ac.v[pre_n].nxt[s[l] - 'a'];
        pre_m += ac.v[pre_n].nmatches;
    }
    return ans;
}
