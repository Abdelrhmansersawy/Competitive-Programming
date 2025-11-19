#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i , st , ed) for(int i = st; i < ed; i++)
#define f first
#define s second
#define all(v) v.begin() , v.end()
#define ld long double
#define vec(a,b) ((b) - (a))

using T  = long double;
using pt = complex<T>;

#define X real()
#define Y imag()
const T EPS = 1e-9L;
const T PI  = acosl(-1.0L);

// Returns squared length of vector p
T sq(pt p){ return real(conj(p) * p); }

// Returns dot product of two vectors
T dot(pt a, pt b){ return real(conj(a) * b); }

// Returns cross product of two vectors
T cross(pt a, pt b){ return imag(conj(a) * b); }

// Returns sign of a value with EPS tolerance
int sgn(T val){
    if(val > EPS) return 1;
    if(val < -EPS) return -1;
    return 0;
}

// Returns perpendicular vector (90° CCW rotation)
pt perp(pt p){ return {-p.Y, p.X}; }

// Returns vector rotated by angle theta (radians, CCW if theta > 0)
pt rotate(pt p, T theta){ return p * std::polar((T)1.0, theta); }

// Returns point a rotated by angle theta around point p (radians, CCW if theta > 0)
pt rotate(pt a, pt p, T theta){ return (a - p) * std::polar((T)1.0, theta) + p; }

// Returns vector rotated 90° counter-clockwise
pt rotCCW90(pt p){ return pt(-p.Y, p.X); }

// Returns vector rotated 90° clockwise
pt rotCW90(pt p){ return pt(p.Y, -p.X); }

// Returns unit vector of p
pt unit(pt p){ return p / abs(p); }
int dcmp(const T &a, const T &b) {
    // Double compare
    if (fabsl(a - b) < EPS)
        return 0;
 
    return (a > b ? 1 : -1);
}
// length of vector
T length(pt a){
    return abs(a);
}
// Check if there is intersect two lines or not and return the intersection point
bool intersect(const pt &a, const pt &b, 
        const pt &p, const pt &q,  pt &ret) {
    //handle degenerate cases (2 parallel lines, 2 identical lines,   line is 1 point)
    T d1 = cross(p - a, b - a);
    T d2 = cross(q - a, b - a);
    ret = (q * d1  - p * d2) / (d1 - d2);
    if(fabsl(d1 - d2) > EPS) return 1;
    return 0;
}

// Point On Line
bool pointOnLine(const pt& a, const pt& b, const pt& p) {
    // determine the point "p" is in the line or not
    return fabsl(cross(vec(a,b),vec(a,p))) < EPS;
}
// Is Point On Ray
bool pointOnRay(const pt& a, const pt& b, const pt& p) {
    //IMP NOTE: a,b,p must be collinear
    return dot(vec(a,p), vec(a,b)) > -EPS;
}
// Point On Segment
bool pointOnSegment(const pt& a, const pt& b, const pt& p) {
        //el satr da momken y3mel precision error
    if(!pointOnLine(a,b,p)) return 0;
    return pointOnRay(a, b, p) && pointOnRay(b, a, p);
}
//Point Line Dist
T pointLineDist(const pt& a, const pt& b, const pt& p) {
  // shortest distance between line and point
  return fabsl(cross(vec(a,b),vec(a,p)) / length(vec(a,b)));
}
// Point Segment Dist
T pointSegmentDist(const pt &a, const pt &b,const pt &p){
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

bool onSegment(pt s, pt e, pt p) {
    return sgn(cross(s - p, e - p)) == 0 && dot(s - p, e - p) <= EPS;
}

vector<pt> segInter(pt a, pt b, pt c, pt d) {
    // The intersection between two segment, return the intersection point(s)
    T oa = cross(d - c, a - c), ob = cross(d - c, b - c),
      oc = cross(b - a, c - a), od = cross(b - a, d - a);
    // Checks if intersection is single non-endpoint point.
    if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
        return {(a * ob - b * oa) / (ob - oa)};
    vector<pt> s;
    if (onSegment(c, d, a)) s.push_back(a);
    if (onSegment(c, d, b)) s.push_back(b);
    if (onSegment(a, b, c)) s.push_back(c);
    if (onSegment(a, b, d)) s.push_back(d);
    sort(s.begin(), s.end(), [](const pt &lhs, const pt &rhs){
        if (fabsl(lhs.X - rhs.X) > EPS) return lhs.X < rhs.X;
        return lhs.Y < rhs.Y;
    });
    s.erase(unique(s.begin(), s.end(), [](const pt &lhs, const pt &rhs){
        return fabsl(lhs.X - rhs.X) < EPS && fabsl(lhs.Y - rhs.Y) < EPS;
    }), s.end());
    return s;
}
vector<vector<pt>> createLine(T x, T y, T d){
    vector<vector<pt>> ret;
    ret.push_back({pt(x+d, y), pt(x, y+d)});
    ret.push_back({pt(x-d, y), pt(x, y+d)});
    ret.push_back({pt(x-d, y), pt(x, y-d)});
    ret.push_back({pt(x+d, y), pt(x, y-d)});
    return ret;
}

vector<pt> circleLine(pt c, T r, pt a, pt b) {
    // the intersection of line and circle
    pt ab = b - a;
    pt p = a + ab * dot(c - a, ab) / sq(ab);
    T s = cross(b - a, c - a);
    T h2 = r * r - s * s / sq(ab);
    if (h2 < -EPS) return {};
    if (fabsl(h2) <= EPS) return {p};
    pt h = unit(ab) * sqrtl(h2);
    return {p - h, p + h};
}
// Cosine Rule
//get angle opposite to side a
T cosRule(T a, T b, T c) {
        // Handle denom = 0
        T res = (b * b + c * c - a * a) / (2 * b * c);
        res = clamp(res, (T)-1, (T)1);
        return acosl(res);
}

pt normalize(pt p){
    T len = length(p);
    if (len < EPS) return p;
    return p / len;
}
pt polar(const pt &r, T t){
    return r * std::polar((T)1.0, t);
}
// Circle Circle Intersection
int circleCircleIntersection(const pt &c1, const T &r1, const pt &c2, const T &r2, pt &res1, pt &res2) {
        if (abs(c1 - c2) < EPS && fabsl(r1 - r2) < EPS) {
                res1 = res2 = c1;
                return fabsl(r1) < EPS ? 1 : INT32_MAX;
        }
        T len = length(vec(c1,c2));
        if (fabsl(len - (r1 + r2)) < EPS || fabsl(fabsl(r1 - r2) - len) < EPS) {
                pt d, c;
                T r;
                if (r1 > r2)
                        d = vec(c1,c2), c = c1, r = r1;
                else
                        d = vec(c2,c1), c = c2, r = r2;
                res1 = res2 = normalize(d) * r + c;
                return 1; // intersect in one point
        }
        if (len > r1 + r2 || len < fabsl(r1 - r2))
                return 0; // intersect on two points
        T a = cosRule(r2, r1, len);
        pt c1c2 = normalize(vec(c1,c2)) * r1;
        res1 = polar(c1c2,  a) + c1;
        res2 = polar(c1c2, -a) + c1;
        return 2; // intersect in one point
}
// Circle From 3 Points
bool circle3(const pt &p1, const pt &p2, const pt &p3, 
        pt& cen, T& r) {
        pt m1 = (p1 + p2) / (T)2;
        pt m2 = (p2 + p3) / (T)2;
        pt perp1 = perp(vec(p1, p2));
        pt perp2 = perp(vec(p2, p3));
        bool res = intersect(m1, m1 + perp1, m2, m2 + perp2, cen);
        r = length(vec(cen,p1));
        return res;
}
T lengthSqr(pt a){ return sq(a); }
// check Point according to circle  (in boundary, inside , outside)
int circlePoint(const pt  &cen, const T &r, const pt  &p) {
        T lensqr = lengthSqr(vec(cen,p));
        if (fabsl(lensqr - r * r) < EPS)
                return 1; // In the Boundary
        if (lensqr < r * r)
                return -1; // In the circle
        return 0; // Out the circle
}
// Maximum  triangle inside a circle
T maxAreaTriangleInsideCircle(T a){
    return 3 * sqrtl((T)3) * a * a / 4;
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
