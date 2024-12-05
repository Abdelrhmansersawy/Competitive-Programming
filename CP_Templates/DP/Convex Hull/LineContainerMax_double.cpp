/*
* Description: Container where you can add lines of the form kx+m, and query maximum values at points x.
* Can be applied on:
   - monotonic slopes, monotonic queries
   - monotonic slopes, random queries
   - random slopes, random queries
*/
struct Line {
   mutable double k, m, p;
   bool operator<(const Line& o) const { return k < o.k; }
   bool operator<(double x) const { return p < x; }
};

struct LineContainerMax : multiset<Line, less<>> {
   static constexpr double infd = 1e18;
   static constexpr double EPS = 1e-9;
   
   double div(double a, double b) {
       return a / b;
   }
   
   bool isect(iterator x, iterator y) {
       if (y == end()) return x->p = infd, 0;
       if (abs(x->k - y->k) < EPS) x->p = x->m > y->m ? infd : -infd;
       else x->p = div(y->m - x->m, x->k - y->k);
       return x->p >= y->p;
   }
   
   void add(double k, double m) {
       auto z = insert({k, m, 0}), y = z++, x = y;
       while (isect(y, z)) z = erase(z);
       if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
       while ((y = x) != begin() && (--x)->p >= y->p)
           isect(x, erase(y));
   }
   
   double query(double x) {
       assert(!empty());
       auto l = *lower_bound(x);
       return l.k * x + l.m;
   }
};
