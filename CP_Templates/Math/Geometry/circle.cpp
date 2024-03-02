// (Don't forget!) to define Point struct



// create circle
template<class P>
vector<P> circleLine(P c, double r, P a, P b) {
    // the intersection of line and circle
    P ab = b - a, p = a + ab * (c - a).dot(ab) / ab.dist2();
    double s = a.cross(b, c), h2 = r * r - s * s / ab.dist2();
    if (h2 < 0) return {};
    if (h2 == 0) return {p};
    P h = ab.unit() * sqrt(h2);
    return {p - h, p + h};
}
// length of vector
double length(const Point<> a){
    return sqrt(a.x * a.x + a.y * a.y);
}
// Cosine Rule
//get angle opposite to side a
double cosRule(double a, double b, double c) {
        // Handle denom = 0
        double res = (b * b + c * c - a * a) / (2 * b * c);
        if (res > 1)
                res = 1;
        if (res < -1)
                res = -1;
        return acos(res);
}

Point<> normalize(const Point<> p){ return ((p) / length(p)); }
Point<> polar(const Point<> r, double t){
    return Point{r.x * cos(t)  - r.y * sin(t), r.x * sin(t) + r.y * cos(t)};
}

// Circle Circle Intersection
int circleCircleIntersection(const Point<> &c1, const double &r1, const Point<> &c2, const double &r2, Point<> &res1, Point<> &res2) {
        if (c1 == c2 && fabs(r1 - r2) < EPS) {
                res1 = res2 = c1;
                return fabs(r1) < EPS ? 1 : INT32_MAX;
        }
        double len = length(vec(c1,c2));
        if (fabs(len - (r1 + r2)) < EPS || fabs(fabs(r1 - r2) - len) < EPS) {
                Point<> d, c;
                double r;
                if (r1 > r2)
                        d = vec(c1,c2), c = c1, r = r1;
                else
                        d = vec(c2,c1), c = c2, r = r2;
                res1 = res2 = normalize(d) * r + c;
                return 1; // intersect in one point
        }
        if (len > r1 + r2 || len < fabs(r1 - r2))
                return 0; // intersect on two points
        double a = cosRule(r2, r1, len);
        Point<> c1c2 = normalize(vec(c1,c2)) * r1;
        res1 = polar(c1c2,  a) + c1;
        res2 = polar(c1c2, -a) + c1;
        return 2; // intersect in one point
}
// Circle From 3 Points
bool circle3(const Point<> &p1, const Point<> &p2, const Point<> &p3, 
        Point<>& cen, double& r) {
        Point<> m1 = (p1 + p2) / 2;
        Point<> m2 = (p2 + p3) / 2;
        Point<> perp1 = vec(p1, p2);
        perp1 = perp1.perp();
        Point<> perp2 = vec(p2, p3);
        perp2 = perp2.perp();
        bool res = intersect(m1, m1 + perp1, m2, m2 + perp2, cen);
        r = length(vec(cen,p1));
        return res;
}

// check Point according to circle  (in boundary, inside , outside)
int circlePoint(const Point<>  &cen, const double &r, const Point<>  &p) {
        double lensqr = lengthSqr(vec(cen,p));
        if (fabs(lensqr - r * r) < EPS)
                return 1; // In the Boundary
        if (lensqr < r * r)
                return -1; // In the circle
        return 0; // Out the circle
}
