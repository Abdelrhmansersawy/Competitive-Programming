/*
 -------------------------------------------------------------------------------------
 ALGORITHM: Dynamic Segment Tree + Policy Based Data Structure (PBDS)
 -------------------------------------------------------------------------------------
 PURPOSE:
    Solves "2D Range Counting with Updates" problems online.
    Specifically: Count elements (x, y) such that:
       1. x is in range [Lx, Rx)   <-- Handled by Segment Tree
       2. y >= Limit               <-- Handled by PBDS (Order Set) in each node
 
 COMPLEXITY:
    - Time:  O(Q * log(MaxCoord) * log(N))
    - Space: O(Q * log(MaxCoord))  (Dynamic nodes created on demand)
 
 KEY NOTES:
    1. Coordinate Compression is NOT needed for the X-axis (SegTree is dynamic).
    2. PBDS stores pairs {val, id} to handle duplicate values safely.
    3. Large Coordinates (10^9) are handled naturally.
 -------------------------------------------------------------------------------------
*/

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
#define rep(i, st, ed) for(int i = st; i < ed; i++)
#define all(v) v.begin(), v.end()

// Ordered Set: Supports find_by_order() and order_of_key()
// We use pair<int,int> to distinguish identical values using unique IDs.
template<class T>
using order_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

const int MAX_COORD = 1e9 + 9; // Max range for X-axis (U coordinate)

struct Node {
    // Inner structure: Stores Y-coordinates (D) for all points in this X-range.
    order_set<pair<int, int>> s;
    Node *left = nullptr, *right = nullptr;

    /*
      Function: upd
      Description: Point Update. Adds/Removes point (i, elem.first).
      - i: The X-coordinate (used for SegTree traversal).
      - elem: {Y-coordinate, UniqueID} (used for PBDS storage).
      - type: +1 to insert, -1 to erase.
    */
    void upd(int i, pair<int, int> elem, int type, int l = 0, int r = MAX_COORD) {
        if (type == 1) s.insert(elem);
        else s.erase(elem);

        if (r - l == 1) return; // Leaf node reached
        
        int mid = l + (r - l) / 2;
        if (i < mid) {
            if (!left) left = new Node(); // Create node on demand
            left->upd(i, elem, type, l, mid);
        } else {
            if (!right) right = new Node();
            right->upd(i, elem, type, mid, r);
        }
    }

    /*
      Function: qry
      Description: 3-Sided Range Query.
      Returns count of points where:
         1. X-coord is in [lx, rx)
         2. Y-coord >= x
    */
    int qry(int lx, int rx, int x, int l = 0, int r = MAX_COORD) {
        // Case 1: Disjoint range or Node doesn't exist -> return 0
        if (r <= lx || l >= rx || !this) return 0;
        
        // Case 2: Current range is fully inside query range [lx, rx)
        // We use the PBDS to count how many Y-values are >= x.
        if (l >= lx && r <= rx) {
            // order_of_key({x, -1}) returns count of elements strictly smaller than x.
            // Total size - smaller count = count of elements >= x.
            return s.size() - s.order_of_key({x, -1});
        }
        
        // Case 3: Partial overlap -> Recurse
        int mid = l + (r - l) / 2;
        int res = 0;
        if (left) res += left->qry(lx, rx, x, l, mid);
        if (right) res += right->qry(lx, rx, x, mid, r);
        return res;
    }
};

const int M = 2e5 + 5;
int U[M], D[M]; // Maps ID -> Coordinates

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    #endif 

    int n, q, h1, h2, w;
    cin >> n >> q >> h1 >> h2 >> w;

    Node* root = new Node();

    // Helper to add/remove a rectangle from the structure
    // Logic: Map U-coord to SegTree Index, D-coord to PBDS Value.
    auto update = [&](int id, int type) {
        root->upd(U[id], {D[id], id}, type);
    };

    rep(i, 0, n) {
        int l, r;
        cin >> U[i] >> D[i] >> l >> r;
        update(i, 1);
    }

    int pos = 0; // Current scroll position
    
    // VISIBILITY LOGIC:
    // A rect [u, d] intersects window [x, x + h1] iff:
    // 1. u < x + h1 (Starts before window ends)
    // 2. d > x      (Ends after window starts)
    // Mapping: X-range [0, x+h1), Y-threshold > x
    auto count_visible = [&](int x) {
        return root->qry(0, x + h1, x + 1);
    };

    // INTERSECTION LOGIC:
    // Visible in BOTH [old_x, old_x+h1] AND [new_x, new_x+h1]
    // Condition: U < min(end1, end2) AND D > max(start1, start2)
    auto count_common = [&](int old_x, int new_x) {
        int min_end = min(old_x + h1, new_x + h1);
        int max_start = max(old_x, new_x);
        return root->qry(0, min_end, max_start + 1);
    };

    int cur_vis = count_visible(pos);

    while (q--) {
        char type; cin >> type;
        if (type == 'A') { // Add new picture
            int id; cin >> id; --id;
            int l, r;
            cin >> U[id] >> D[id] >> l >> r;
            update(id, 1);
            
            int new_vis = count_visible(pos);
            // Q1: Not visible before, visible now? (new_vis - cur_vis)
            // Q2: Visible before, not visible now? (0, since we only added)
            cout << new_vis - cur_vis << " " << 0 << '\n';
            cur_vis = new_vis;
        } 
        else if (type == 'D') { // Delete picture
            int id; cin >> id; --id;
            update(id, -1);
            
            int new_vis = count_visible(pos);
            // Q1: 0 (only removed)
            // Q2: Visible before - Visible now
            cout << 0 << " " << cur_vis - new_vis << '\n';
            cur_vis = new_vis;
        } 
        else if (type == 'M') { // Move scroll
            int new_pos; cin >> new_pos;
            int common = count_common(pos, new_pos);
            int new_vis = count_visible(new_pos);
            
            // Q1: Newly visible = Total New - Common
            // Q2: No longer visible = Total Old - Common
            cout << new_vis - common << " " << cur_vis - common << '\n';
            pos = new_pos;
            cur_vis = new_vis;
        }
    }
}
