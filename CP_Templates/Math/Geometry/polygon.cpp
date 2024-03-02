double cross(const Point<> &a, const Point<> &b){
    return a.x * b.y - b.x * a.y;
}

const int N = 2e5 + 9;
Point<> polygon[N];

//to check if the Point<>s are sorted anti-clockwise or clockwise
//remove the fabs at the end and it will return -ve value if clockwise
double polygonArea(const vector<Point<>> &p) {
        double res = 0;
        for (int i = 0; i < p.size(); i++) {
                int j = (i + 1) % (int)(p.size());
                res += cross(p[i],p[j]);
        }
        return fabs(res) / 2;
}


// ## Polygon Centroid
// return the centroid Point<> of the polygon
// The centroid is also known as the "centre of gravity" or the "center of mass". The position of the centroid
// assuming the polygon to be made of a material of uniform density.
Point<> polygonCentroid(vector<Point<>> &polygon) {
        Point<> res(0, 0);
        double a = 0;
        for (int i = 0; i < (int) polygon.size(); i++) {
                int j = (i + 1) % polygon.size();
                res.x += (polygon[i].x + polygon[j].x) * (polygon[i].x * polygon[j].y - polygon[j].x * polygon[i].y);

                res.y += (polygon[i].y + polygon[j].y) * 
                           (polygon[i].x * polygon[j].y - polygon[j].x * polygon[i].y);

                a += polygon[i].x * polygon[j].y - polygon[i].y * polygon[j].x;
        }
        a *= 0.5;
        res.x /= 6 * a;
        res.y /= 6 * a;
        return res;
}



// ## Convex Polygon Intersect
bool intersect(const Point<> &a, const Point<> &b, 
    const Point<> &p, const Point<> &q,Point<> &ret) {
    //handle degenerate cases (2 parallel lines, 2 identical lines,   line is 1 point)
    double d1 = cross(p - a, b - a);
    double d2 = cross(q - a, b - a);
    ret = (q * d1  - p * d2) / (d1 - d2);
    if(fabs(d1 - d2) > EPS) return 1;
    return 0;
}
void polygonCut(const vector<Point<>> &p, const Point<> &a, const Point<> &b, vector<Point<>> &res) {
        res.clear();
        for (int i = 0; i < p.size(); i++) {
                int j = (i + 1) % (p.size());
                bool in1 = cross(vec(a,b),vec(a,p[i])) > EPS;
                bool in2 = cross(vec(a,b),vec(a,p[j])) > EPS;
                if (in1)
                        res.push_back(p[i]);
                if (in1 ^ in2) {
                        Point<> r;
                        intersect(a, b, p[i], p[j], r);
                        res.push_back(r);
                }
        }
}

//assume that both are anti-clockwise
void convexPolygonIntersect(const vector<Point<>> &p, const vector<Point<>> &q, vector<Point<>>& res) {
        res = q;
        for (int i = 0; i < p.size(); i++) {
                int j = (i + 1) % (int) p.size();
                vector<Point<>> temp;
                polygonCut(res, p[i], p[j], temp);
                res = temp;
                if (res.empty()) return;
        }
}
