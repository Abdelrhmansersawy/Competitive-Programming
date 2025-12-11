#define all(x) x.begin(),x.end()

// O(N(logN)^2)
template<class T = int> struct Bit2D {
    vector<T> X; vector<vector<T>> Y, B;

    int idx(const vector<T>& v, T x) { return upper_bound(all(v), x) - v.begin(); }

    // pts needs all points that will be used in the upd
    // if range upds remember to build with {x1, y1}, {x1, y2 + 1}, {x2 + 1, y1}, {x2 + 1, y2 + 1}
    Bit2D(vector<pair<T, T>> pts) {
        sort(all(pts));
        for (auto a : pts) if (X.empty() || a.first != X.back()) X.push_back(a.first);
        Y.resize(X.size() + 1); B.resize(Y.size());

        sort(all(pts), [](auto l, auto r){ return l.second < r.second; });
        for (auto a : pts)
            for (int i = idx(X, a.first); i < Y.size(); i += i & -i)
                if (Y[i].empty() || Y[i].back() != a.second) Y[i].push_back(a.second);

        for (int i = 0; i < Y.size(); i++) B[i].assign(Y[i].size() + 1, 0);
    }

    // point upd
    void upd(T x, T y, T v) {
        for (int i = idx(X, x); i < Y.size(); i += i & -i)
            for (int j = idx(Y[i], y); j < B[i].size(); j += j & -j)
                B[i][j] += v;
    }

    // point qry
    T qry(T x, T y) {
        T ans = 0;
        for (int i = idx(X, x); i > 0; i -= i & -i)
            for (int j = idx(Y[i], y); j > 0; j -= j & -j)
                ans += B[i][j];
        return ans;
    }

    // range qry
    T qry(T x1, T y1, T x2, T y2) {
        return qry(x2, y2) - qry(x2, y1 - 1) - qry(x1 - 1, y2) + qry(x1 - 1, y1 - 1);
    }

    // range upd
    void upd(T x1, T y1, T x2, T y2, T v) {
        upd(x1, y1, v); upd(x1, y2 + 1, -v);
        upd(x2 + 1, y1, -v); upd(x2 + 1, y2 + 1, v);
    }
};
