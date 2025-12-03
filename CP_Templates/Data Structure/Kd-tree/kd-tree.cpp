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

struct P {
    ll x, y;
    int id; // Required for "Closest Pair" to ignore self
    
    ll dist(P b) { 
        // 1. MANHATTAN (Current)
        return abs(x - b.x) + abs(y - b.y);

        // 2. EUCLIDEAN SQUARED (Uncomment for Euclidean)
        // return (x - b.x)*(x - b.x) + (y - b.y)*(y - b.y);
    }
};

struct Node {
    P p;
    Node *l = 0, *r = 0;
    ll x0 = INF, x1 = -INF, y0 = INF, y1 = -INF;

    Node(P pt) : p(pt) {}

    // Pruning: This MUST match the dist() metric exactly!
    ll boxDist(P q) {
        ll X = max(x0, min(x1, q.x));
        ll Y = max(y0, min(y1, q.y));
        
        // 1. MANHATTAN (Current)
        return abs(q.x - X) + abs(q.y - Y);

        // 2. EUCLIDEAN SQUARED (Uncomment for Euclidean)
        // return (q.x - X)*(q.x - X) + (q.y - Y)*(q.y - Y);
    }
};

bool on_x(P a, P b) { return a.x < b.x; }
bool on_y(P a, P b) { return a.y < b.y; }

struct KDTree {
    Node* root = 0;
    ll min_d;
    P best_p;
    int q_id; 

    // Complexity: O(N log N)
    Node* build(vector<P>& pts, int L, int R, bool divX) {
        if (L >= R) return 0;
        int mid = (L + R) / 2;
        nth_element(pts.begin() + L, pts.begin() + mid, pts.begin() + R, divX ? on_x : on_y);

        Node* node = new Node(pts[mid]);
        for (int i = L; i < R; ++i) {
            node->x0 = min(node->x0, pts[i].x); node->x1 = max(node->x1, pts[i].x);
            node->y0 = min(node->y0, pts[i].y); node->y1 = max(node->y1, pts[i].y);
        }
        node->l = build(pts, L, mid, !divX);
        node->r = build(pts, mid + 1, R, !divX);
        return node;
    }

    // Complexity: Avg O(log N)
    void search(Node* node, P q) {
        // Pruning: Stop if box is further than current best
        if (!node || node->boxDist(q) >= min_d) return;

        ll d = node->p.dist(q);
        
        // Update if closer AND not the same point
        if (d < min_d && node->p.id != q_id) {
            min_d = d;
            best_p = node->p;
        }

        ll dL = node->l ? node->l->boxDist(q) : INF;
        ll dR = node->r ? node->r->boxDist(q) : INF;

        // Greedy search: Visit closer child first
        if (dL < dR) { search(node->l, q); search(node->r, q); }
        else         { search(node->r, q); search(node->l, q); }
    }

    KDTree(vector<P>& pts) {
        root = build(pts, 0, pts.size(), true);
    }

    // Complexity: Avg O(log N)
    // Returns {distance, Point}
    pair<ll, P> nearest(P q) {
        min_d = INF;
        q_id = -1;    // Don't ignore any points
        best_p = P(); 
        search(root, q);
        return {min_d, best_p};
    }
    
    // Complexity: Avg O(N log N)
    // Global Minimum Distance between any two points in the tree
    ll find_closest_pair(const vector<P>& pts) {
        min_d = INF;
        for (const auto& p : pts) {
            q_id = p.id; // Ignore self
            search(root, p);
            // Optimization: min_d persists to prune subsequent searches
        }
        return min_d;
    }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m; 
    if (!(cin >> n >> m)) return 0;

    vector<P> reserved(n);
    for(int i=0; i<n; ++i) {
        cin >> reserved[i].x >> reserved[i].y;
        reserved[i].id = i; 
    }

    KDTree tree(reserved);

    // Solve "Campground" (Free -> Reserved)
    for(int i = 0; i < m; ++i) {
        P free_camp; cin >> free_camp.x >> free_camp.y;
        cout << tree.nearest(free_camp).first << (i == m - 1 ? "" : "\n");
    }
    cout << endl;
}
