/*
Quick Tips for KD-tree in Contest:
1. Randomize input points to avoid O(n) search on sorted data
2. If TLE on findMinDistance(), consider using simpler n^2 brute force
3. For nearest neighbor, if getting WA/TLE, check if input points are unique
4. Watch out for integer overflow in distance calculations
5. Consider using Manhattan distance if precision is an issue
*/

template<class T>
struct Point {
   typedef Point P;
   T x, y;
   explicit Point(T x=0, T y=0) : x(x), y(y) {}
   bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
   bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
   P operator+(P p) const { return P(x+p.x, y+p.y); }
   P operator-(P p) const { return P(x-p.x, y-p.y); }
   T dist2() const { return x*x + y*y; } // Replace if u use manhattan distance {return abs(x) + abs(y); }
   friend ostream& operator<<(ostream& os, P p) {
       return os << "(" << p.x << "," << p.y << ")"; }
};

typedef long long ll;
typedef Point<ll> P;
const ll INF = numeric_limits<ll>::max();

bool on_x(const P& a, const P& b) { return a.x < b.x; }
bool on_y(const P& a, const P& b) { return a.y < b.y; }

struct Node {
   P pt;
   ll x0 = INF, x1 = -INF, y0 = INF, y1 = -INF;
   Node *first = 0, *second = 0;

   ll distance(const P& p) {
       ll x = (p.x < x0 ? x0 : p.x > x1 ? x1 : p.x);
       ll y = (p.y < y0 ? y0 : p.y > y1 ? y1 : p.y);
       return (P(x,y) - p).dist2();
   }
   
   Node(vector<P>&& vp) : pt(vp[0]) {
       for (P p : vp) {
           x0 = min(x0, p.x); x1 = max(x1, p.x);
           y0 = min(y0, p.y); y1 = max(y1, p.y);
       }
       if (vp.size() > 1) {
           sort(vp.begin(), vp.end(), x1 - x0 >= y1 - y0 ? on_x : on_y);
           int half = vp.size()/2;
           first = new Node({vp.begin(), vp.begin() + half});
           second = new Node({vp.begin() + half, vp.end()});
       }
   }
};

class KDTree {
private:
   Node* root;

   // O(log n) average, O(n) worst: Helper for nearest neighbor search
   pair<ll, P> search(Node *node, const P& p) {
       if (!node->first) {
           return make_pair((p - node->pt).dist2(), node->pt);
       }
       Node *f = node->first, *s = node->second;
       ll bfirst = f->distance(p), bsec = s->distance(p);
       if (bfirst > bsec) swap(bsec, bfirst), swap(f, s);
       auto best = search(f, p);
       if (bsec < best.first)
           best = min(best, search(s, p));
       return best;
   }

   void findMinDistanceHelper(Node* node, long double& minDist) {
       if (!node || (!node->first && !node->second)) return;
       
       if (node->first && node->second) {
           minDist = min(minDist, (long double)(node->first->pt - node->second->pt).dist2());
       }
       
       findMinDistanceHelper(node->first, minDist);
       findMinDistanceHelper(node->second, minDist);
   }

public:
   KDTree(const vector<P>& vp) : root(new Node({vp.begin(), vp.end()})) {}
   
   // O(log n) average: Finds nearest neighbor to query point
   pair<ll, P> nearest(const P& p) {
       return search(root, p);
   }

   long double findMinDistance() {
       if (!root) return numeric_limits<long double>::max();
       long double minDist = numeric_limits<long double>::max();
       findMinDistanceHelper(root, minDist);
       return sqrt(minDist);
   }
};
