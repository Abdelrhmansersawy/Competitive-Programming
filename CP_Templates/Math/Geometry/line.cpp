// (Don't forget!) to define Point struct


// length of vector
double length(const Point<> a){
    return sqrt(a.x * a.x + a.y * a.y);
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

