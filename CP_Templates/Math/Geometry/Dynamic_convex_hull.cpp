#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi2")
#include <bits/stdc++.h>
using namespace std;

#define fwd(i,a,n) for(int i=(a); i<(n); ++i)
#define rep(i,n) fwd(i,0,n)
#define all(x) (x).begin(), (x).end()
#define sz(x) int((x).size())
#define pb push_back

using ll = long long;
using vi = vector<int>;
using point = complex<ll>;

inline ll cross(point a, point b) {
    return (ll)a.real()*b.imag() - (ll)a.imag()*b.real();
}
inline ll cross(point o, point a, point b) {
    return cross(a - o, b - o);
}

struct DynHull {
    using P = point;
    struct Node { int l, r; };
    vector<P> ps;
    int n, s;
    vi in, id;
    vector<Node> t;
    vector<ll> m;

    DynHull(const vector<P>& _ps, bool lower = false, int start = -1)
        : ps(_ps), n(sz(_ps)), in(n), id(n) {
        if (start == -1) start = n;
        s = 1; while (s < n) s <<= 1;
        t.assign(2*s, {-1, -1});
        m.assign(s, 0);

        vector<pair<P,int>> pts;
        pts.reserve(n);
        rep(i,n) {
            P q = ps[i];
            if (lower) q = P(-q.real(), -q.imag());   // mirror all coords
            pts.pb({ q, i });
        }

        // sort by (x, y) because complex has no operator<
        sort(all(pts), [](const pair<P,int>& A, const pair<P,int>& B){
            if (A.first.real() != B.first.real())
                return A.first.real() < B.first.real();
            return A.first.imag() < B.first.imag();
        });

        rep(i,n) {
            ps[i] = pts[i].first;
            id[i] = pts[i].second;
            in[id[i]] = i;
            int p = i + s;
            while(((p & 1) ^ 1)) p >>= 1;
            m[p >> 1] = ps[i].real();
        }

        rep(i,start) t[s + in[i]] = { in[i], in[i] };
        for (int v = s - 1; v >= 1; --v) pull(v);
    }

    int go(int v) {
        while (t[v].l < 0) v = v*2 + t[v].l + 3;
        return v;
    }

    void pull(int v) {
        auto crossNegX = [&](P a, P b, P c, P d, ll x) {
            __int128 p = cross(a,b,c);
            __int128 q = cross(b,a,d);
            return p + q == 0 ||
                   (__int128)(d.real() - x)*p + (__int128)(c.real() - x)*q <= 0;
        };

        int p = v*2, q = p + 1;
        if (t[p].l == -1 && t[q].l == -1) {
            t[v] = {-1, -1};
        } else if (t[p].l == -1) {
            t[v] = {-2, -2};
        } else if (t[q].l == -1) {
            t[v] = {-3, -3};
        } else {
            p = go(p);
            q = go(q);
            while (p < s || q < s) {
                auto [a, b] = t[p];
                auto [c, d] = t[q];

                if (a != b && cross(ps[a], ps[b], ps[c]) > 0) {
                    p = go(p*2);
                } else if (c != d && cross(ps[b], ps[c], ps[d]) > 0) {
                    q = go(q*2 + 1);
                } else if (a == b) {
                    q = go(q*2);
                } else if (c == d ||
                           crossNegX(ps[a], ps[b], ps[c], ps[d], m[v])) {
                    p = go(p*2 + 1);
                } else {
                    q = go(q*2);
                }
            }
            t[v] = { p - s, q - s };
        }
    }

    void add(int i) {
        i = in[i];
        int v = i + s;
        t[v] = { i, i };
        while (v >>= 1) pull(v);
    }

    void del(int i) {
        i = in[i];
        int v = i + s;
        t[v] = { -1, -1 };
        while (v >>= 1) {
            if (t[v].l < 0 || t[v].l == i || t[v].r == i) pull(v);
        }
    }

    void dfs(int v, int L, int R, vi &h) {
        if (v >= s) {
            h.pb(id[t[v].l]);   // original index
            return;
        }
        if (L <= t[v].l) dfs(go(v*2), L, min(t[v].l, R), h);
        if (t[v].r <= R) dfs(go(v*2+1), max(t[v].r, L), R, h);
    }

    vi hull() {
        vi h;
        if (~t[1].l) dfs(go(1), 0, n-1, h);
        return h;               // list of original indices on hull
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<point> pts(n);
    rep(i,n) {
        ll x,y;
        cin >> x >> y;
        pts[i] = point(x,y);
    }

    DynHull upper(pts, false, n);
    DynHull lower(pts, true,  n);

    vector<int> layer(n);
    int layers = 0;

    while (true) {
        vi up  = upper.hull();
        vi low = lower.hull();
        vi tot = up;
        tot.insert(tot.end(), all(low));
        sort(all(tot));
        tot.erase(unique(all(tot)), tot.end());
        if (sz(tot) == 0) break;
        ++layers;
        for (int i : tot) {
            upper.del(i);
            lower.del(i);
            layer[i] = layers;
        }
    }

    rep(i,n) cout << layer[i] << '\n';
}
