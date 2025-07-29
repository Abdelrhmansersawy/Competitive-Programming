template<typename T>
class lichao_on_points {

    static constexpr T inf = numeric_limits<T>::max();

    struct func {
        T k, b;

        func() = default;
        func(T k, T b): k(k), b(b) {}

        T eval(T x) const {
            return k * x + b;
        }
    };

    size_t n, U;
    vector<T> bl, br;
    vector<func> vf;

    void add_seg(T ql, T qr, func nf, size_t v) {
        const T l = bl[v], r = br[v];
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) {
            add_line(nf, v);
            return;
        }
        add_seg(ql, qr, nf, v << 1);
        add_seg(ql, qr, nf, v << 1 | 1);
    }

    void add_line(func nf, size_t v) {
        while (true) {
            const T l = bl[v], r = br[v];
            T vl_cur = vf[v].eval(l);
            T vr_cur = vf[v].eval(r);
            T vl_new = nf.eval(l);
            T vr_new = nf.eval(r);
            if ((vl_cur <= vl_new) == (vr_cur <= vr_new)) {
                if (vl_new < vl_cur) vf[v] = nf;
                return;
            }
            T md = br[v << 1];
            T vmd_cur = vf[v].eval(md);
            T vmd_new = nf.eval(md);
            if (vmd_new < vmd_cur) {
                swap(vf[v], nf);
                swap(vl_cur, vl_new);
            }
            v = vl_new < vl_cur ? v << 1 : v << 1 | 1;
        }
    }

public:
    lichao_on_points() = default;
    lichao_on_points(vector<T> points) {
        if (points.empty()) points = {0};
        sort(points.begin(), points.end());
        points.erase(unique(points.begin(), points.end()), points.end());
        n = points.size();
        U = n & (n - 1) ? 2 << __lg(n) : n;
        bl.resize(U * 2);
        br.resize(U * 2);
        vf.resize(U * 2, func(0, inf));
        for (size_t i = 0; i < n; ++i) bl[U + i] = br[U + i] = points[i];
        for (size_t i = n; i < U; ++i) bl[U + i] = br[U + i] = points[n - 1];
        for (size_t i = U; --i; ) {
            bl[i] = bl[i << 1];
            br[i] = br[i << 1 | 1];
        }
    }

    //O(log(|points|))
    T get_min(T x) {
        size_t v = 1;
        T o = vf[v].eval(x);
        while (v < U) {
            v <<= 1;
            v += x > br[v];
            o = min(o, vf[v].eval(x));
        }
        return o;
    }

    //O(log(|points|))
    void add_line(T k, T b) {add_line(func(k, b), 1);}


    // add a line y = kx + b that is only active on the interval [l, r]
    //O(log(|points|) ^ 2)
    void add_seg(T l, T r, T k, T b) {add_seg(l, r, func(k, b), 1);}
};
