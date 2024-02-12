#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i , st , ed) for(int i = st; i < ed; i++)
#define f first
#define s second
#define all(v) v.begin() , v.end()
#ifndef ONLINE_JUDGE 
#define debug(x) cerr << #x << ": " << x << '\n';
#else
#define debug(x)
#endif
#define ld long double
const ld EPS = 1e-6;
#define vec(a,b) ((b) - (a))
template<typename T = double> struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x=0, T y=0) : x(x), y(y) {}
    bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
    bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
    P operator+(P p) const { return P(x+p.x, y+p.y); }
    P operator-(P p) const { return P(x-p.x, y-p.y); }
    P operator*(T d) const { return P(x*d, y*d); }
    P operator/(T d) const { return P(x/d, y/d); }
    T dot(P p) const { return x*p.x + y*p.y; }
    T cross(P p) const { return x*p.y - y*p.x; }
    T cross(P a, P b) const { return (a-*this).cross(b-*this); }
    T dist2() const { return x*x + y*y; }
    double dist() const { return sqrt((double)dist2()); }
    // angle to x-axis in interval [-pi, pi]
    double angle() const { return atan2(y, x); }
    P unit() const { return *this/dist(); } // makes dist()=1
    P perp() const { return P(-y, x); } // rotates +90 degrees
    P normal() const { return perp().unit(); }
    // returns point rotated 'a' radians ccw around the origin
    P rotate(double a) const {
        return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
    friend ostream& operator<<(ostream& os, P p) {
        return os << "(" << p.x << "," << p.y << ")"; 
    }
    friend istream &operator>>(istream &os, P &p) {
        return os >> p.x >> p.y;
    }

    // Project point onto line through a and b (assuming a != b).
    P projectOnLine(const P &a, const P &b) const {
        P ab = a.getVector(b);
        P ac = a.getVector(*this);
        return a + ab * ac.dot(ab) / a.dist2(b);
    }
 
    // Project point c onto line segment through a and b (assuming a != b).
    P projectOnSegment(const P &a, const P &b) const {
        P &c = *this;
        P ab = a.getVector(b);
        P ac = a.getVector(c);
 
        long double r = dot(ac, ab), d = a.dist2(b);
        if (r < 0) return a;
        if (r > d) return b;
 
        return a + ab * r / d;
    }
 
    P reflectAroundLine(const P &a, const P &b) const {
        return projectOnLine(a, b) * 2 - (*this);
    }

};
int dcmp(const ld &a, const ld &b) {
    // Double compare
    if (fabs(a - b) < EPS)
        return 0;
 
    return (a > b ? 1 : -1);
}
// length of vector
double length(const Point<> a){
    return sqrt(a.x * a.x + a.y * a.y);
}
// cross product
double cross(const Point<> &a, const Point<> &b){
    return a.x * b.y - b.x * a.y;
}
// Check if there is intersect two lines or not and return the intersection point
bool intersect(const Point<> &a, const Point<> &b, 
        const Point<> &p, const Point<> &q,  Point<> &ret) {
    //handle degenerate cases (2 parallel lines, 2 identical lines,   line is 1 point)
    double d1 = cross(p - a, b - a);
    double d2 = cross(q - a, b - a);
    ret = (q * d1  - p * d2) / (d1 - d2);
    if(fabs(d1 - d2) > EPS) return 1;
    return 0;
}

double dot(const Point<> a, const Point<> b){ return a.x * b.x + a.y * b.y; }

// Point On Line
bool pointOnLine(const Point<>& a, const Point<>& b, const Point<>& p) {
    // determine the point "p" is in the line or not
    return fabs(cross(vec(a,b),vec(a,p))) < EPS;
}
// Is Point On Ray
bool pointOnRay(const Point<>& a, const Point<>& b, const Point<>& p) {
    //IMP NOTE: a,b,p must be collinear
    return dot(vec(a,p), vec(a,b)) > -EPS;
}
// Point On Segment
bool pointOnSegment(const Point<>& a, const Point<>& b, const Point<>& p) {
        //el satr da momken y3mel precision error
    if(!pointOnLine(a,b,p)) return 0;
    return pointOnRay(a, b, p) && pointOnRay(b, a, p);
}
//Point Line Dist
double pointLineDist(const Point<>& a, const Point<>& b, const Point<>& p) {
  // shortest distance between line and point
  return fabs(cross(vec(a,b),vec(a,p)) / length(vec(a,b)));
}
// Point Segment Dist
double pointSegmentDist(const Point<> &a, const Point<> &b,const Point<> &p){
      // shortest distance between segment and point
        if (dot(vec(a,b),vec(a,p)) < EPS)
                return length(vec(a,p));
        if (dot(vec(b,a),vec(b,p)) < EPS)
                return length(vec(b,p));
        return pointLineDist(a, b, p);
}
// Count the number of Lattice Point in segment
int segmentLatticePointsCount(int x1, int y1, int x2, int y2) {
        return abs(__gcd(x1 - x2, y1 - y2)) + 1;
}

template<class P> bool onSegment(P s, P e, P p) {
    // check if point (p) on line (s , e)
    return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

template<class P> vector<P> segInter(P a, P b, P c, P d) {
    // The intersection between two segment, return the index section point
    auto oa = c.cross(d, a), ob = c.cross(d, b),
         oc = a.cross(b, c), od = a.cross(b, d);
    // Checks if intersection is single non-endpoint point.
    if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
        return {(a * ob - b * oa) / (ob - oa)};
    set<P> s;
    if (onSegment(c, d, a)) s.insert(a);
    if (onSegment(c, d, b)) s.insert(b);
    if (onSegment(a, b, c)) s.insert(c);
    if (onSegment(a, b, d)) s.insert(d);
    return {s.begin(), s.end()};
}
vector<vector<Point<int>>> createLine(int x, int y, int d){
    // 
    vector<vector<Point<int>>> ret;
    ret.push_back({Point<int>(x+d, y), Point<int>(x, y+d)});
    ret.push_back({Point<int>(x-d, y), Point<int>(x, y+d)});
    ret.push_back({Point<int>(x-d, y), Point<int>(x, y-d)});
    ret.push_back({Point<int>(x+d, y), Point<int>(x, y-d)});
    return ret;
}

template<class P>
vector<P> circleLine(P c, double r, P a, P b) {
    // the intersection of line and circule
    P ab = b - a, p = a + ab * (c - a).dot(ab) / ab.dist2();
    double s = a.cross(b, c), h2 = r * r - s * s / ab.dist2();
    if (h2 < 0) return {};
    if (h2 == 0) return {p};
    P h = ab.unit() * sqrt(h2);
    return {p - h, p + h};
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
Point<> polar(const Point<> &r, double t){
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
double lengthSqr(const Point<> a){ return a.x * a.x + a.y * a.y; }
// Circle Point
int circlePoint(const Point<>  &cen, const double &r, const Point<>  &p) {
        double lensqr = lengthSqr(vec(cen,p));
        if (fabs(lensqr - r * r) < EPS)
                return 1; // In the Boundary
        if (lensqr < r * r)
                return -1; // In the circle
        return 0; // Out the circle
}
// Maximum  triangle inside a circle
double maxAreaTriangleInsideCircle(double a){
    return 3 * sqrt((double) 3) * a * a / 4;
}
// find the Slope
pair<int,int> slope(pair<int,int> u, pair<int,int> v)
{
   int dy = v.s-u.s;
   int dx = v.f-u.f;
   if(dx == 0) return {0,0};
   if(dy == 0) return{0,1};
   int sgn = (dy < 0) ^ (dx < 0);
   if(sgn) sgn = -1; else sgn = 1;
   return {sgn*abs(dx)/(abs(__gcd(dy,dx))),abs(dy)/(abs(__gcd(dy,dx)))};
}

int main(){
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif

}