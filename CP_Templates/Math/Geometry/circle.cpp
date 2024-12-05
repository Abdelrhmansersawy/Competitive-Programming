#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
typedef complex<ld> Point;
const ld EPS = 1e-9;

// Cross product of OA and OB vectors
ld cross(const Point& O, const Point& A, const Point& B) { return imag((A - O) * conj(B - O)); }

// Dot product of vectors A and B
ld dot(const Point& A, const Point& B) { return real(A * conj(B)); }

// Circle-Line Intersection: returns intersection points
vector<Point> circleLine(const Point& c, ld r, const Point& a, const Point& b){
    Point ab = b - a; ld ab2 = norm(ab);
    ld t = dot(ab, c - a) / ab2;
    Point p = a + ab * t; ld s2 = r*r - norm(c - p);
    if(s2 < -EPS) return {};
    if(abs(s2) < EPS) return {p};
    ld s = sqrt(s2); Point h = ab / abs(ab) * s;
    return {p - h, p + h};
}

// Cosine Rule: angle opposite to side a
ld cosRule(ld a, ld b, ld c){
    ld res = (b*b + c*c - a*a)/(2*b*c);
    return acos(max(-1.0L, min(1.0L, res)));
}

// Circle-Circle Intersection: returns number of intersections and sets res1, res2
int circleCircle(const Point& c1, ld r1, const Point& c2, ld r2, Point& res1, Point& res2){
    Point d = c2 - c1; ld dist = abs(d);
    if(dist < EPS && abs(r1 - r2) < EPS) return INT32_MAX; // Infinite intersections
    if(dist > r1 + r2 + EPS || dist < abs(r1 - r2) - EPS) return 0; // No intersection
    ld a = (r1*r1 - r2*r2 + dist*dist)/(2*dist);
    ld h2 = r1*r1 - a*a;
    if(h2 < -EPS) return 0;
    ld h = h2 < EPS ? 0 : sqrt(h2);
    Point p = c1 + d * (a / dist);
    if(h == 0){ res1 = p; return 1; }
    Point offset = d * (h / dist) * Point(0,1);
    res1 = p + offset; res2 = p - offset;
    return 2;
}

// Circle from Three Points: returns true if successful
bool circle3(const Point& p1, const Point& p2, const Point& p3, Point& cen, ld& r){
    ld a = cross(p1, p2, p3);
    if(abs(a) < EPS) return false; // Collinear points
    cen = ((norm(p2) - norm(p1)) * Point(0,1) - (norm(p3) - norm(p1)) * Point(1,0)) / (2*a) + p1;
    r = abs(cen - p1);
    return true;
}

// Point Position Relative to Circle: -1 inside, 0 outside, 1 on boundary
int circlePoint(const Point& cen, ld r, const Point& p){
    ld dist2 = norm(p - cen), r2 = r*r;
    if(abs(dist2 - r2) < EPS) return 1;
    return (dist2 < r2) ? -1 : 0;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
}
