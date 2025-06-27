 using P = complex<double>;
 
    inline int sgn(double x) {
        const double eps = 1e-9;
        return (x >  eps) - (x < -eps);
    }
 
    inline double cross(const P& o, const P& a, const P& b) {
        P u = a - o, v = b - o;
        return u.real() * v.imag() - u.imag() * v.real();
    }
 
    vector<P> rayCircle(P p1, P p2, P c, double r) {
        const double eps = 1e-7;
        P  d = p2 - p1;
        double A = norm(d);
        double B = 2 * real(conj(d) * (p1 - c));
        double C = norm(p1 - c) - r * r;
        double D = B * B - 4 * A * C;
 
        vector<P> res;
        if (D < -eps) return res;
 
        auto push = [&](double t) {
            if (t >= -eps) res.emplace_back(p1 + d * t);
        };
 
        if (fabs(D) < eps) {
            push(-B / (2 * A));
        } else {
            double s = sqrt(max(0.0, D));
            push((-B + s) / (2 * A));
            push((-B - s) / (2 * A));
        }
        return res;
    }
 
    vector<P> tangents(P p, P c, double r) {
        P v = p - c;
        double d2 = norm(v);
        if (d2 < r * r) return {};
 
        double s  = sqrt(d2 - r * r);
        double rr = r * r;
        P rot(-v.imag(), v.real());
 
        return {c + (rr * v + r * s * rot) / d2, c + (rr * v - r * s * rot) / d2};
    }
