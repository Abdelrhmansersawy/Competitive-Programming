/*
 * LineContainer (Dynamic Convex Hull Trick)
 * -----------------------------------------
 * Adds lines y = kx + m and queries for the maximum (or minimum) value
 * at a given x in O(log n) time. Slopes can be added in any order.
 */
struct Line {
    mutable ll k, m, p;
    bool operator<(const Line& o) const { return k < o.k; }
    bool operator<(ll x) const { return p < x; }
};
struct LineContainer : multiset<Line, less<>> {
    static const ll inf = LLONG_MAX;
    bool isMn = false;
    ll div(ll a, ll b) {
        return a / b - ((a ^ b) < 0 && a % b); }
    bool isect(iterator x, iterator y) {
        if (y == end()) return x->p = inf, 0;
        if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
        else x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }
    void add(ll k, ll m) {
        if (isMn) k = -k , m = -m;
        auto z = insert({k, m, 0}), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }
    ll query(ll x) {
	if (empty())  return isMn ? LLONG_MAX : LLONG_MIN;
        auto l = *lower_bound(x);
        return (isMn ? -1 : 1) * (l.k * x + l.m);
    }
};
