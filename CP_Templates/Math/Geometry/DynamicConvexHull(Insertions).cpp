#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using P  = complex<ll>;

P G;

ll cross(const P& a, const P& b) {
    return (ll)((__int128)a.real() * b.imag() - (__int128)a.imag() * b.real());
}

ll norm2(const P& p) {
    return (ll)p.real() * p.real() + (ll)p.imag() * p.imag();
}

P readP() {
    ll x, y;
    cin >> x >> y;
    return P(x * 3, y * 3);
}

struct AngleCmp {
    bool operator()(const P& A, const P& B) const {
        P p1 = A - G;
        P p2 = B - G;

        if (p1.real() == 0 && p1.imag() == 0) return true;
        if (p2.real() == 0 && p2.imag() == 0) return false;

        if ((ll)p1.imag() * p2.imag() < 0)
            return p1.imag() > p2.imag();

        ll Cr = cross(p1, p2);
        if (Cr) return Cr > 0;

        if (p1.imag() == 0 && (ll)p1.real() * p2.real() < 0)
            return p1.real() > p2.real();

        return norm2(p1) < norm2(p2);
    }
};

set<P, AngleCmp> s;
using It = set<P, AngleCmp>::iterator;

It pre(It it) {
    if (it == s.begin()) it = s.end();
    --it;
    return it;
}

It nxt(It it) {
    ++it;
    if (it == s.end()) it = s.begin();
    return it;
}

bool In(const P& Pnt) {
    auto it = s.lower_bound(Pnt);
    if (it == s.end()) it = s.begin();
    P prev = *pre(it);
    ll Cr = cross(Pnt - prev, *it - Pnt);
    if (Cr == 0) return norm2(Pnt - prev) <= norm2(*it - prev);
    return Cr < 0;
}

void Ins(const P& Pnt) {
    if (In(Pnt)) return;

    auto it = s.lower_bound(Pnt);
    if (it == s.end()) it = s.begin();

    s.insert(Pnt);

    while (s.size() > 3) {
        it = s.find(Pnt);
        auto t  = nxt(it);
        auto t2 = nxt(t);
        if (cross(*t - Pnt, *t2 - *t) > 0) break;
        s.erase(t);
    }

    while (s.size() > 3) {
        it = s.find(Pnt);
        auto t  = pre(it);
        auto tt = pre(t);
        if (cross(*tt - *t, *t - Pnt) > 0) break;
        s.erase(t);
    }
}

vector<P> getHull() {
    vector<P> hull;
    hull.reserve(s.size());
    for (const auto& p : s) hull.push_back(p);
    return hull;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    if (!(cin >> q)) return 0;

    int t;
    P A, B, C;

    cin >> t;
    A = readP();
    cin >> t;
    B = readP();
    cin >> t;
    C = readP();

    G = (A + B + C) / (ll)3;

    s.insert(A);
    s.insert(B);
    s.insert(C);

    for (int i = 3; i < q; ++i) {
        cin >> t;
        P Pnt = readP();
        if (t == 2) {
            cout << (In(Pnt) ? "YES\n" : "NO\n");
        } else {
            Ins(Pnt);
        }
    }

    return 0;
}
