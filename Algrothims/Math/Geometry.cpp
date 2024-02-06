struct Point {
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
const ld eps = 1e-6;
int dcmp(const ld &a, const ld &b) {
	// Double compar
    if (fabs(a - b) < eps)
        return 0;
 
    return (a > b ? 1 : -1);
}
template<class P> bool onSegment(P s, P e, P p) {
	// check if point (p) on line (s , e)
	return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

template<class P> vector<P> segInter(P a, P b, P c, P d) {
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
