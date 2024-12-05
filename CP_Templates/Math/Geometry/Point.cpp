#include <bits/stdc++.h>
using namespace std;
using ld = long double;
using ll = long long;
using pii = pair<int,int>;
using Point = complex<ld>;
const ld EPS = 1e-9;
#define X real()
#define Y imag()

// Core geometry operations
ld cross(const Point& a, const Point& b) { return imag(conj(a) * b); }
ld dot(const Point& a, const Point& b) { return real(conj(a) * b); }
ld dist2(const Point& a, const Point& b) { return norm(a - b); }
ld dist(const Point& a, const Point& b) { return abs(a - b); }
ld angle(const Point& a, const Point& b) { return atan2(cross(a,b), dot(a,b)); }

// Orientation check
int ccw(const Point& a, const Point& b, const Point& c) {
    ld cr = cross(b-a, c-a);
    if(cr > EPS) return +1;    // CCW
    if(cr < -EPS) return -1;   // CW
    if(dot(b-a, c-a) < 0) return +2;  // c--a--b
    if(norm(b-a) < norm(c-a)) return -2; // a--b--c on line
    return 0;  // Colinear and overlapping
}

// Integer slope
pii slope(const pii& a, const pii& b) {
    int dy = b.second - a.second, dx = b.first - a.first;
    if(dx == 0) return {0,0};  // Vertical
    if(dy == 0) return {0,1};  // Horizontal
    int g = __gcd(abs(dy), abs(dx));
    dy /= g; dx /= g;
    if(dx < 0) dy = -dy, dx = -dx;
    return {dy,dx};
}

// Point operations
Point rotate(const Point& p, const Point& c, ld theta) {
    return (p-c) * polar((ld)1.0, theta) + c;
}

Point proj(const Point& p, const Point& a, const Point& b) {
    Point ab = b-a;
    return a + ab * dot(p-a, ab) / norm(ab);
}

Point refl(const Point& p, const Point& a, const Point& b) {
    Point prj = proj(p,a,b);
    return prj * (ld)2.0 - p;
}

// Input/Output
istream& operator>>(istream& is, Point& p) {
    ld x,y; is >> x >> y; p = Point(x,y);
    return is;
}

ostream& operator<<(ostream& os, const Point& p) {
    return os << p.X << ' ' << p.Y;
}

void solve() {
    // Your solution here
    Point a, b;
    cin >> a >> b;
    cout << dist(a,b) << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int t = 1;
    // cin >> t;  // Uncomment for multiple test cases
    while(t--) solve();
    
    return 0;
}
