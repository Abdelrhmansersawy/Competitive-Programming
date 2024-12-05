#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
typedef complex<ld> Point;
#define X real()
#define Y imag()
const ld EPS = 1e-9;

// Cross product
ld cross(const Point& a, const Point& b) {
    return imag(conj(a) * b);
}
ld cross(const Point& O, const Point& A, const Point& B) {
    return imag((A - O) * conj(B - O));
}

// Polygon area (absolute)
//cross function is the needed function
ld polygonArea(const vector<Point>& p) {
    ld res = 0;
    for(int i = 0; i < p.size(); i++) res += cross(p[i], p[(i+1)%p.size()]);
    return abs(res) / 2.0;
}

// Polygon centroid
//cross function is needed here
Point polygonCentroid(const vector<Point>& p) {
    Point c(0,0); ld A = 0;
    for(int i = 0; i < p.size(); i++) {
        int j = (i+1) % p.size();
        ld cross_prod = cross(p[i], p[j]);
        c += (p[i] + p[j]) * cross_prod;
        A += cross_prod;
    }
    return c / (3.0 * A);
}

// Line intersection, returns true if intersecting
//cross function is needed here
bool intersect(const Point& a, const Point& b, const Point& p, const Point& q, Point& r) {
    ld d1 = cross(p - a, b - a);
    ld d2 = cross(q - a, b - a);
    if(abs(d1 - d2) < EPS) return false;
    r = (q * d1 - p * d2) / (d1 - d2);
    return true;
}

// Sutherland–Hodgman polygon clipping
//cross function is needed here as well as the intersect function 
void sortCounterClockwise(vector<Point>& p) {
    Point c = polygonCentroid(p);
    sort(p.begin(), p.end(), [&](const Point& a, const Point& b) -> bool {
        ld angle_a = arg(a - c);
        ld angle_b = arg(b - c);
        return angle_a < angle_b;
    });
}
void polygonCut(const vector<Point>& subject, const Point& a, const Point& b, vector<Point>& res) {
    res.clear();
    for(int i = 0; i < subject.size(); i++) {
        int j = (i+1) % subject.size();
        ld cross1 = cross(b - a, subject[i] - a);
        ld cross2 = cross(b - a, subject[j] - a);
        bool in1 = cross1 > EPS, in2 = cross2 > EPS;
        if(in1) res.push_back(subject[i]);
        if(in1 != in2) { Point r; if(intersect(a, b, subject[i], subject[j], r)) res.push_back(r); }
    }
}
//for identifying the number of lattice points in a polygon
int picksTheorem(int a, int b) {
   // a: area of polygon, b: no. lattice Points in the boundaries
   return a - b / 2 + 1;
}
int picksTheorem(vector<Point>& p, bool b = 0) {
   // Point sorted in counter clock-wise;
   ld area = 0;
   int bound = 0;
   int sz = (int) p.size();
   for(int i = 0; i < sz; i++) {
      int j = (i + 1) % sz;
      area += cross(p[i], p[j]);
      Point v = p[j] - p[i];
      bound += abs(__gcd((int)round(real(v)),(int)round(imag(v))));
   }
   area /= 2;
   area = fabs(area);
   return round(area - bound / 2 + 1) + b * bound;
}

// Convex polygon intersection
//polygoncut(cross, intersect) function is needed
void convexIntersect(const vector<Point>& p, const vector<Point>& q, vector<Point>& res) {
    res = q;
    for(int i = 0; i < p.size(); i++) {
        int j = (i+1) % p.size();
        vector<Point> temp;
        polygonCut(res, p[i], p[j], temp);
        res = temp; if(res.empty()) break;
    }
}
// Cross product of vectors OA and OB (returns z-component)


vector<Point> convex_hull(vector<Point> pts, bool include_collinear = false) {
    int n = pts.size(), k = 0;
    if(n <= 1) return pts;
    sort(pts.begin(), pts.end(), [&](const Point& a, const Point& b) -> bool {
        return (real(a) < real(b)) || (abs(real(a) - real(b)) < EPS && imag(a) < imag(b));
    });

    vector<Point> hull(2 * n);
    for(int i = 0; i < n; ++i) {
        while(k >= 2 && (include_collinear ? cross(hull[k-2], hull[k-1], pts[i]) < 0 
                                           : cross(hull[k-2], hull[k-1], pts[i]) <= 0))
            k--;
        hull[k++] = pts[i];
    }
    for(int i = n-2, t = k+1; i >=0; --i){
        while(k >= t && (include_collinear ? cross(hull[k-2], hull[k-1], pts[i]) < 0 
                                           : cross(hull[k-2], hull[k-1], pts[i]) <= 0))
            k--;
        hull[k++] = pts[i];
    }
    hull.resize(k-1); 
    return hull;
}
istream& operator>>(istream& is, Point& p) {
    ld x,y; is >> x >> y; p = Point(x,y);
    return is;
}

ostream& operator<<(ostream& os, const Point& p) {
    return os << p.X << ' ' << p.Y;
}
// Example usage
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n; cin >> n;
    vector<Point> poly1(n); for(auto &p : poly1) cin >> p;
    sortCounterClockwise(poly1);
    poly1 = convex_hull(poly1,1);
    cout << poly1.size() << '\n';
    for(auto &p : poly1) cout << p << '\n';
}
