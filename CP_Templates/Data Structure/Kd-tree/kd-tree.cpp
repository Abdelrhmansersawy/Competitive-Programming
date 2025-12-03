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
    int id; // Required to distinguish points
    
    // Manhattan Distance (as required by problem)
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

    // Bounding Box Distance (Manhattan)
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
    Node* build(vector<P> &pts, int L, int R, bool divX) {
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
        if (!node || node->boxDist(q) >= min_d) return;

        ll d = node->p.dist(q);
        
        // Check condition: strictly better dist AND not the point itself
        if (d < min_d && node->p.id != q_id) {
            min_d = d;
            best_p = node->p;
        }

        ll dL = node->l ? node->l->boxDist(q) : INF;
        ll dR = node->r ? node->r->boxDist(q) : INF;

        if (dL < dR) { search(node->l, q); search(node->r, q); }
        else         { search(node->r, q); search(node->l, q); }
    }

    KDTree(vector<P>& pts) {
        root = build(pts, 0, pts.size(), true);
    }

    // Complexity: Avg O(log N)
    // Returns {distance, Point}
    // Usage: nearest(q) to find any neighbor. nearest(q, q.id) to find neighbor != q.
    pair<ll, P> nearest(P q, int ignore_id = -1) {
        min_d = INF;
        q_id = ignore_id; // -1 finds ANY point. Specific ID ignores that point.
        best_p = P(); 
        search(root, q);
        return {min_d, best_p};
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
