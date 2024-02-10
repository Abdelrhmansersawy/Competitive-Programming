/*
   ## Pick's theorm
   calculate the number of lattice pointer inside the polygon
   Time complexity: O(n)
*/
#define vec(a,b)  ((b) - (a))
struct Point {
    typedef Point P;
    double x, y;
    explicit Point(double x=0, double y=0) : x(x), y(y) {}
    P operator-(P p) const { return P(x-p.x, y-p.y); }
};
int picksTheorem(int a, int b) {
   // a: area of polygon, b: no. lattice Points in the boundaries
   return a - b / 2 + 1;
}
double cross(const Point &a, const Point &b){
    return a.x * b.y - b.x * a.y;
}
int picksTheorem(vector<Point>& p) {
   // Point sorted in counter clock-wise;
   double area = 0;
   int bound = 0;
   int sz = (int) p.size();
   for(int i = 0; i < sz; i++) {
      int j = (i + 1) % sz;
      area += cross(p[i], p[j]);
      Point v = vec(p[i], p[j]);
      bound += abs(__gcd((int) v.x, (int) v.y));
   }
   area /= 2;
   area = fabs(area);
   return round(area - bound / 2 + 1);
}
