#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
typedef complex<ld> Point;
const ld EPS = 1e-9;
#define X real()
#define Y imag()

// Geometry Helpers
ld cross(const Point& a, const Point& b) { return imag(conj(a) * b); }
ld dot(const Point& a, const Point& b) { return real(conj(a) * b); }
ld length_sq(const Point& a) { return norm(a); }
ld length_(const Point& a) { return abs(a); }

// Point on Line
bool pointOnLine(const Point& a, const Point& b, const Point& p) {
    return abs(cross(b - a, p - a)) < EPS;
}

// Point on Ray
bool pointOnRay(const Point& a, const Point& b, const Point& p) {
    return dot(p - a, b - a) > -EPS;
}

// Point on Segment
bool pointOnSegment(const Point& a, const Point& b, const Point& p) {
    return pointOnLine(a, b, p) && pointOnRay(a, b, p) && pointOnRay(b, a, p);
}

// Distance from Point to Line
ld pointLineDist(const Point& a, const Point& b, const Point& p) {
    return abs(cross(b - a, p - a)) / length_(b - a);
}

// Distance from Point to Segment
ld pointSegmentDist(const Point& a, const Point& b, const Point& p){
    if(dot(b - a, p - a) < EPS) return length_(p - a);
    if(dot(a - b, p - b) < EPS) return length_(p - b);
    return pointLineDist(a, b, p);
}

// Line Intersection
bool intersectLines(const Point& a, const Point& b, const Point& p, const Point& q, Point& r) {
    ld d1 = cross(p - a, b - a);
    ld d2 = cross(q - a, b - a);
    if(abs(d1 - d2) < EPS) return false;
    r = (q * d1 - p * d2) / (d1 - d2);
    return true;
}
vector<Point> segInter(const Point& a, const Point& b, const Point& c, const Point& d) {
    Point r;
    if(intersectLines(a, b, c, d, r)) {
        // Check if r is on both segments
        if(pointOnSegment(a, b, r) && pointOnSegment(c, d, r))
            return {r};
    }
    auto on = [&](const Point& s, const Point& e, const Point& p) -> bool {
        return pointOnSegment(s, e, p);
    };
    vector<Point> res;
    if(on(a, b, c)) res.emplace_back(c);
    if(on(a, b, d)) res.emplace_back(d);
    if(on(c, d, a)) res.emplace_back(a);
    if(on(c, d, b)) res.emplace_back(b);
    sort(res.begin(), res.end(), [&](const Point& x, const Point& y) -> bool {
        return real(x) < real(y) || (abs(real(x) - real(y)) < EPS && imag(x) < imag(y));
    });
    res.erase(unique(res.begin(), res.end(), [&](const Point& x, const Point& y) -> bool {
        return abs(x - y) < EPS;
    }), res.end());
    return res;
}

// Count Lattice Points on Segment
int segmentLatticePointsCount(int x1, int y1, int x2, int y2) {
    return abs(__gcd(x1 - x2, y1 - y2)) + 1;
}

// Create Lines (e.g., for cross shapes)
vector<pair<Point, Point>> createLines(int x, int y, int d){
    return {
        {Point(x + d, y), Point(x, y + d)},
        {Point(x - d, y), Point(x, y + d)},
        {Point(x - d, y), Point(x, y - d)},
        {Point(x + d, y), Point(x, y - d)}
    };
}
istream& operator>>(istream& is, Point& p) {
    ld x,y; is >> x >> y; p = Point(x,y);
    return is;
}

ostream& operator<<(ostream& os, const Point& p) {
    return os << p.X << ' ' << p.Y;
}
// Example Usage
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n = 4;
    vector<Point> v(n);
    for(auto &i : v) cin >> i;
    Point q;
    intersectLines(v[0], v[1], v[2], v[3], q);
    cout << setprecision(6) << fixed << q;
}
