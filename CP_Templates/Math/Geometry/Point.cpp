#define ld long double
#define vec(a,b) ((b) - (a))
const ld EPS = 1e-6;
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

// cross product
double cross(const Point<> &a, const Point<> &b){
    return a.x * b.y - b.x * a.y;
}

// dot product
double dot(const Point<> a, const Point<> b){ return a.x * b.x + a.y * b.y; }

// Given 3 points, find if they are CW or CCW
ll norm(Point<> a){ return a.x * a.x + a.y * a.y; }
int CCW(Point<> a,  Point<> b, Point <> c){
    b = b -  a;
    c = c - a;
    if(cross(b , c) > 0) return +1; // counter clockwise
    if(cross(b,c) < 0) return -1; // clockwise
    if(dot(b, c) < 0) return +2; // c--a--b on line
    if(norm(b) < norm(c)) return -2; //a--b--c on line
    return 0;
}


// find the Slope between two points
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
