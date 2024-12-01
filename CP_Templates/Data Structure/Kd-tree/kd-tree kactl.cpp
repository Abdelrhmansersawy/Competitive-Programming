typedef long long T;
typedef Point<T> P;
const T INF = numeric_limits<T>::max();

// Sort by x/y coordinate
bool on_x(const P& a, const P& b) { return a.x < b.x; }
bool on_y(const P& a, const P& b) { return a.y < b.y; }

struct Node {
    P pt;  // point if leaf
    T x0 = INF, x1 = -INF, y0 = INF, y1 = -INF;  // bounds
    Node *first = 0, *second = 0;
    
    // Min squared distance: point to bounding box
    T distance(const P& p) { 
        T x = (p.x < x0 ? x0 : p.x > x1 ? x1 : p.x);
        T y = (p.y < y0 ? y0 : p.y > y1 ? y1 : p.y);
        return (P(x,y) - p).dist2();
    }
    
    // Build node: set bounds, split points if >1
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

struct KDTree {
    Node* root;
    
    // Initialize tree with points
    KDTree(const vector<P>& vp) : root(new Node({vp.begin(), vp.end()})) {}
    
    // Find nearest recursively: returns {distance², point}
    pair<T, P> search(Node *node, const P& p) {
        if (!node->first) {
            return make_pair((p - node->pt).dist2(), node->pt);
        }
        Node *f = node->first, *s = node->second;
        T bfirst = f->distance(p), bsec = s->distance(p);
        if (bfirst > bsec) swap(bsec, bfirst), swap(f, s);
        auto best = search(f, p);
        if (bsec < best.first)
            best = min(best, search(s, p));
        return best;
    }
    
    // Public: get nearest point and distance²
    pair<T, P> nearest(const P& p) {
        return search(root, p);
    }
};
