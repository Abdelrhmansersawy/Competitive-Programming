typedef long double ld;
struct Line {
    ll m, b;
    mutable function<const Line *()> succ;
 
    bool operator<(const Line &other) const {
        return m < other.m;
    }
 
    bool operator<(const ll &x) const {
        const Line *s = succ();
        if (!s)
            return 0;
        return b - s->b < (s->m - m) * x;
    }
};
// will maintain upper hull for maximum
struct HullDynamic : public multiset<Line, less<>> {
    bool bad(iterator y) {
        auto z = next(y);
        if (y == begin()) {
            if (z == end())
                return 0;
            return y->m == z->m && y->b <= z->b;
        }
        auto x = prev(y);
        if (z == end())
            return y->m == x->m && y->b <= x->b;
        return (x->b - y->b) * (z->m - y->m) >= (y->b - z->b) * (y->m - x->m);
    }
 
    void insert_line(ll m, ll b) {
        m *= -1;
        b *= -1;
        auto y = insert({m, b});
        y->succ = [=] { return next(y) == end() ? 0 : &*next(y); };
        if (bad(y)) {
            erase(y);
            return;
        }
        while (next(y) != end() && bad(next(y)))
            erase(next(y));
        while (y != begin() && bad(prev(y)))
            erase(prev(y));
    }
 
    ll query(ll x) {
        if(size() == 0) return 5e18;
        auto l = *lower_bound(x);
        return -(l.m * x + l.b);
    }
};
