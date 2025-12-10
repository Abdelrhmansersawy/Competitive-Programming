#include <bits/stdc++.h>
using namespace std;

using ld = long double;
using point  = complex<ld>;
constexpr ld eps = 1e-12;

ld cross(point a, point b) { return imag(conj(a) * b); }

vector<point> convex_hull(vector<point> p, bool keep_col = false)
{
    sort(p.begin(), p.end(), [](point a, point b)
        {
        return a.real() == b.real() ? a.imag() < b.imag() : a.real() < b.real();
    });
    p.erase(unique(p.begin(), p.end(), [](point a, point b) {
        return fabsl(a.real() - b.real()) < eps && fabsl(a.imag() - b.imag()) < eps;
    }), p.end());
    if (p.size() <= 1) return p;

    vector<point> lo, up;
    for (auto pt : p) {
        while (lo.size() >= 2) {
            ld cr = cross(lo.back() - lo[lo.size() - 2], pt - lo.back());
            if (keep_col ? cr < -eps : cr <= eps) lo.pop_back();
            else break;
        }
        lo.push_back(pt);
    }
    for (int i = p.size() - 1; i >= 0; --i)
    {
        point pt = p[i];
        while (up.size() >= 2)
        {
            ld cr = cross(up.back() - up[up.size() - 2], pt - up.back());
            if (keep_col ? cr < -eps : cr <= eps) up.pop_back();
            else break;
        }
        up.push_back(pt);
    }
    lo.pop_back();
    up.pop_back();
    lo.insert(lo.end(), up.begin(), up.end());
    return lo;
}
