/**
 * KD-Tree Template for ICPC
 * -------------------------
 * Current Mode: MANHATTAN Distance
 * Complexity: Build O(N log N), Query O(log N)
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 4e18;

// --- KD-TREE TEMPLATE START ---

struct P {
    ll x, y;
    int id; 
    
    ll dist(const P& b) const { 
        // 1. MANHATTAN (Current)
        return abs(x - b.x) + abs(y - b.y);

        // 2. EUCLIDEAN SQUARED (Uncomment for Euclidean)
        // return (x - b.x)*(x - b.x) + (y - b.y)*(y - b.y);
    }
};

struct Node {
    P p;          
    int l = -1;   
    int r = -1;   
    
    ll x0 = INF, x1 = -INF, y0 = INF, y1 = -INF; 
    
    Node() {} 
    Node(P pt) : p(pt) {
        x0 = x1 = pt.x;
        y0 = y1 = pt.y;
    }

    ll boxDist(const P& q) const {
        ll X = max(x0, min(x1, q.x));
        ll Y = max(y0, min(y1, q.y));

        // 1. MANHATTAN (Current)
        return abs(q.x - X) + abs(q.y - Y);

        // 2. EUCLIDEAN SQUARED (Uncomment for Euclidean)
        // return (q.x - X)*(q.x - X) + (q.y - Y)*(q.y - Y);
    }
};

// Global comparators for nth_element
bool on_x(const P& a, const P& b) { return a.x < b.x; }
bool on_y(const P& a, const P& b) { return a.y < b.y; }

struct KDTree {
    vector<Node> pool; 
    int root = -1;
    ll min_d;
    P best_p;
    int q_id;
    
    int build(vector<P> &pts, int L, int R) {
        if (L >= R) return -1;
        
        // 1. Calculate Bounding Box of current points to decide split axis
        ll min_x = INF, max_x = -INF, min_y = INF, max_y = -INF;
        for(int i=L; i<R; ++i) {
            if(pts[i].x < min_x) min_x = pts[i].x;
            if(pts[i].x > max_x) max_x = pts[i].x;
            if(pts[i].y < min_y) min_y = pts[i].y;
            if(pts[i].y > max_y) max_y = pts[i].y;
        }

        // 2. Adaptive Split: Split on the widest dimension
        // This creates square-like bounding boxes which are better for pruning
        bool divX = (ll)(max_x - min_x) >= (ll)(max_y - min_y);
        
        int mid = (L + R) / 2;
        nth_element(pts.begin() + L, pts.begin() + mid, pts.begin() + R, divX ? on_x : on_y);

        int idx = pool.size();
        pool.push_back(Node(pts[mid]));
        
        // Set the bounding box exactly to what we computed
        pool[idx].x0 = min_x; pool[idx].x1 = max_x;
        pool[idx].y0 = min_y; pool[idx].y1 = max_y;

        // 3. Recurse
        pool[idx].l = build(pts, L, mid);
        pool[idx].r = build(pts, mid + 1, R);
        
        return idx;
    }

    void search(int node_idx, const P& q) {
        if (node_idx == -1 || pool[node_idx].boxDist(q) >= min_d) return;

        ll d = pool[node_idx].p.dist(q);
        
        // Check condition: strictly better dist AND not the point itself
        if (d < min_d && pool[node_idx].p.id != q_id) {
            min_d = d;
            best_p = pool[node_idx].p;
        }
        
        if (min_d == 0) return;

        int L = pool[node_idx].l;
        int R = pool[node_idx].r;

        ll dL = (L != -1) ? pool[L].boxDist(q) : INF;
        ll dR = (R != -1) ? pool[R].boxDist(q) : INF;

        // Visit closer box first
        if (dL < dR) { search(L, q); search(R, q); }
        else         { search(R, q); search(L, q); }
    }

    KDTree(vector<P>& pts) {
        pool.reserve(pts.size()); 
        root = build(pts, 0, pts.size());
    }

    // Returns {distance, Point}
    // Usage: nearest(q) -> any neighbor. nearest(q, q.id) -> neighbor != q
    pair<ll, P> nearest(P q, int ignore_id = -1) {
        min_d = INF;
        q_id = ignore_id;
        best_p = P();
        search(root, q);
        return {min_d, best_p};
    }
    ll find_closest_pair(const vector<P>& pts) {
        min_d = INF;
        for (const auto& p : pts) {
            q_id = p.id; // Ignore self
            search(root, p);
        }
        return min_d;
    }
};

// --- KD-TREE TEMPLATE END ---

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    
    int n;  cin >> n;

    vector<P> original_pts(n);
    for(int i = 0; i < n; ++i) {
        cin >> original_pts[i].x >> original_pts[i].y;
        original_pts[i].id = i; 
    }

    // Create a copy for the tree because build() reorders elements
    vector<P> tree_pts = original_pts;
    KDTree tree(tree_pts);

    // Solve: For each point, find nearest neighbor excluding itself
    for(int i = 0; i < n; ++i) {
        // We want to ignore the point itself, so we pass original_pts[i].id
        // nearest() returns a pair {dist, Point}, we only need .first
        cout << tree.nearest(original_pts[i], original_pts[i].id).first << "\n";
    }

    return 0;
}
