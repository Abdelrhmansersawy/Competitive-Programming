struct cmp {
    bool operator()(const pair<double,ll>& x, const pair<double,ll>& y) const {
        return x.f * y.s < y.f * x.s;
    }
};

multiset<pair<double,ll>, cmp> s;
