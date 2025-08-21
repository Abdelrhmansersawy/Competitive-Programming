#include <bits/stdc++.h>
using namespace std;

/* ------------------------------------------------------------------
   Geometry Template (using complex<T> as 2D point/vector)
   ------------------------------------------------------------------
   typedef long double T;
   typedef complex<T> pt;
   #define X real()
   #define Y imag()

   Operations:
   1. Vector addition:              a + b
   2. Scalar multiplication:        r * a
   3. Dot product:                  (conj(a) * b).X
   4. Cross product:                (conj(a) * b).Y
      - conj(a) * b = (ax*bx + ay*by) + i(ax*by - ay*bx)

   5. Squared distance:             norm(a - b)
   6. Euclidean distance:           abs(a - b)
   7. Angle of elevation:           arg(b - a)
   8. Slope of line (a, b):         tan(arg(b - a))
   9. Polar to cartesian:           polar(r, theta)
  10. Cartesian to polar:           pt(abs(p), arg(p))
  11. Rotation about origin:        a * polar(1.0, theta)
  12. Rotation about pivot p:       (a - p) * polar(1.0, theta) + p
  13. Angle ∠ABC:                   abs(remainder(arg(a-b) - arg(c-b), 2π))
  14. Project p onto vector v:      v * dot(p, v) / norm(v)
  15. Project p onto line (a, b):   a + (b - a) * dot(p - a, b - a) / norm(b - a)
  16. Reflect p across line (a, b): a + conj((p - a) / (b - a)) * (b - a)
  17. Line intersection:            see function inter()
   ------------------------------------------------------------------ */

typedef long double T;
typedef complex<T> pt;
#define X real()
#define Y imag()
const T EPS = 1e-9;
const T PI  = acosl(-1.0L);

/* ---------------- Vector utilities ---------------- */

// Returns squared length of vector p
T sq(pt p){ return dot(p,p); }

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
pt rotate(pt p, T theta){ return p * polar((T)1.0, theta); }

// Returns unit vector of p
pt unit(pt p){ return p / abs(p); }

/* ---------------- Angles ---------------- */

// Returns twice the signed area of triangle (a,b,c)
T orient(pt a, pt b, pt c){ return cross(b - a, c - a); }

// Returns angle between vectors (0..π)
T angle(pt a, pt b){
    T na = abs(a), nb = abs(b);
    if (na < EPS || nb < EPS) return 0;
    return acos(clamp(dot(a,b)/(na*nb), (T)-1.0, (T)1.0));
}

// Returns oriented angle ∠abc (0..2π)
T orientedAngle(pt a, pt b, pt c){
    T ang = angle(b - a, c - a);
    return (orient(a,b,c) >= 0 ? ang : 2*PI - ang);
}

// Returns signed angle ∠abc (+CCW, -CW)
T angleTravelled(pt a, pt b, pt c){
    T ang = angle(b - a, c - a);
    return (orient(a,b,c) >= 0 ? ang : -ang);
}

// Checks if point p lies inside angle(bac) CCW
bool inAngle(pt a, pt b, pt c, pt p) {
    T abp = orient(a, b, p), acp = orient(a, c, p), abc = orient(a, b, c);
    if (abc < 0) swap(abp, acp);
    return abp >= 0 && acp <= 0;
}

/* ---------------- Line struct ---------------- */
struct line{
    pt v; T c;

    // Construct from vector v and constant c
    line(pt v, T c) : v(v), c(c) {}

    // Construct from equation ax + by = c
    line(T a, T b, T _c){ v = {b, -a}; c = _c; }

    // Construct line through points p and q
    line(pt p, pt q){ v = q - p; c = cross(v, p); }

    // Returns signed side value of point p
    T side(pt p) { return cross(v,p) - c; }

    // Returns perpendicular distance from point p to line
    T dist(pt p) { return fabsl(side(p)) / abs(v); }

    // Returns squared distance from point p to line
    T sqDist(pt p) { return side(p)*side(p) / sq(v); }

    // Returns projection of point p onto line
    pt proj(pt p) { return p - perp(v)*side(p)/sq(v); }

    // Reflects point p across line
    pt refl(pt p) { return p - perp(v)*2.0L*side(p)/sq(v); }

    // Translate line by vector t
    line translate(pt t) { return {v, c + cross(v,t)}; }

    // Shift line left by distance dist
    line shiftLeft(T dist) { return {v, c + dist*abs(v)}; }
};

// Finds intersection point of two lines
bool inter(line l1, line l2, pt &out) {
    T d = cross(l1.v, l2.v);
    if (fabsl(d) < EPS) return false;
    out = (l2.v*l1.c - l1.v*l2.c) / d;
    return true;
}

// Returns bisector of two lines (interior/exterior)
line bisector(line l1, line l2, bool interior) {
    assert(cross(l1.v,l2.v) != 0);
    T sign = interior ? 1 : -1;
    return { l2.v/abs(l2.v) + l1.v/abs(l1.v)*sign,
             l2.c/abs(l2.v) + l1.c/abs(l1.v)*sign };
}

/* ---------------- Segments ---------------- */

// Checks if point p lies inside disk with diameter ab
bool inDisk(pt a, pt b, pt p){ return dot(a-p, b-p) <= 0; }

// Checks if point c lies on segment ab
bool onSegment(pt a, pt b, pt c){ return orient(a,b,c)==0 && inDisk(a,b,c); }

// Checks if segments ab and cd intersect properly
bool properInter(pt a, pt b, pt c, pt d, pt &out) {
    T oa = orient(c,d,a), ob = orient(c,d,b),
      oc = orient(a,b,c), od = orient(a,b,d);
    if (sgn(oa)*sgn(ob) < 0 && sgn(oc)*sgn(od) < 0) {
        out = (a*ob - b*oa) / (ob-oa);
        return true;
    }
    return false;
}

// Returns all intersection points between segments ab and cd
vector<pt> inters(pt a, pt b, pt c, pt d) {
    vector<pt> s; pt out;
    if (properInter(a,b,c,d,out)) return {out};
    if (onSegment(c,d,a)) s.push_back(a);
    if (onSegment(c,d,b)) s.push_back(b);
    if (onSegment(a,b,c)) s.push_back(c);
    if (onSegment(a,b,d)) s.push_back(d);
    sort(s.begin(), s.end(), [](pt p, pt q){
        return make_pair(p.X,p.Y) < make_pair(q.X,q.Y);
    });
    s.erase(unique(s.begin(), s.end()), s.end());
    return s;
}

// Returns distance from point p to segment ab
T segPoint(pt a, pt b, pt p) {
    if (a != b) {
        line l(a,b);
        if (dot(b-a,p-a) >= 0 && dot(a-b,p-b) >= 0)
            return l.dist(p);
    }
    return min(abs(p-a), abs(p-b));
}

// Returns distance between two segments ab and cd
T segSeg(pt a, pt b, pt c, pt d) {
    pt dummy;
    if (properInter(a,b,c,d,dummy)) return 0;
    return min({ segPoint(a,b,c), segPoint(a,b,d),
                 segPoint(c,d,a), segPoint(c,d,b) });
}

/* ---------------- Polygons ---------------- */

// Sort points counter-clockwise (works for convex polygon points)
void sortPointsCCW(vector<pt> &pts) {
    // Compute centroid
    T cx = 0, cy = 0;
    for (auto &p : pts) {
        cx += p.X;
        cy += p.Y;
    }
    cx /= pts.size();
    cy /= pts.size();
    pt c(cx, cy);

    // Sort by angle from centroid
    sort(pts.begin(), pts.end(), [&](pt a, pt b) {
        return atan2(a.Y - cy, a.X - cx) < atan2(b.Y - cy, b.X - cx);
    });
}

// Returns area of triangle abc
T areaTriangle(pt a, pt b, pt c){ return abs(cross(b-a, c-a))/2.0; }

// Returns area of polygon p (CCW or CW)
T areaPolygon(vector<pt> &p) {
    T area = 0;
    for (int i=0,n=p.size(); i<n; i++)
        area += cross(p[i], p[(i+1)%n]);
    return fabsl(area)/2.0;
}

// Checks if point a lies inside polygon p
bool inPolygon(vector<pt> &p, pt a, bool strict=true) {
    int cnt=0,n=p.size();
    for(int i=0;i<n;i++){
        pt q=p[(i+1)%n];
        if (onSegment(p[i],q,a)) return !strict;
        cnt ^= ((p[i].Y<=a.Y)^(q.Y<=a.Y)) &&
               (a.X < (q.X-p[i].X)*(a.Y-p[i].Y)/(q.Y-p[i].Y)+p[i].X);
    }
    return cnt;
}

/* ---------------- Circle ---------------- */

// Returns the power of point p with respect to the circle centered at c with radius r: |p - c|^2 - r^2
inline T power_of_point(pt c , ll r, pt p){
    pt v1 = p - c;
    ll res = sq(v1) - r * r;
    return res;
}

