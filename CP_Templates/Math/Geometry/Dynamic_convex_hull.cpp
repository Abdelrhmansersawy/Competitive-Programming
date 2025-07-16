#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <tuple>
#include <set>

using namespace std;

using ll = long long;

// The provided template for Point and Upper_Hull
struct Point{
    ll x=0, y=0;

    Point& operator+=(Point const&o) {
        x+=o.x;
        y+=o.y;
        return *this;
    }
    Point& operator-=(Point const&o) {
        x-=o.x;
        y-=o.y;
        return *this;
    }
    Point operator-() const {
        return Point{-x, -y};
    }
    friend Point operator+(Point a, Point const&b){
        a+=b;
        return a;
    }
    friend Point operator-(Point a, Point const&b){
        a-=b;
        return a;
    }
    friend ll dot(Point const&a, Point const&b){
        return a.x*b.x + a.y*b.y;
    }
    friend ll cross(Point const&a, Point const&b){
        return a.x*b.y - a.y*b.x;
    }
    friend bool operator<(Point const&a, Point const&b){
        return tie(a.x, a.y) < tie(b.x, b.y);
    }
};

int ccw(Point const&a, Point const&b){
    ll x = cross(a, b);
    return (x>0)-(x<0);
}
int ccw(Point const&a, Point const&b, Point const&c){
    return ccw(b-a, c-a);
}

struct Upper_Hull{
    struct Link{
        Point p;
        Link *prev = nullptr, *next = nullptr;
        int id;
    };
    struct Node{
        Link *chain, *chain_back;
        Link *tangent;
    };
    template<typename S, typename T>
    pair<Link*, Link*> find_bridge(Link*l, Link*r, S next, T convex){
        while(next(l) || next(r)){
            if(!next(r) || (next(l) && convex(Point{0, 0}, next(l)->p - l->p, next(r)->p - r->p))){
                if(convex(l->p, next(l)->p, r->p)){
                    l = next(l);
                } else {
                    break;
                }
            } else {
                if(!convex(l->p, r->p, next(r)->p)){
                    r = next(r);
                } else {
                    break;
                }
            }
        }
        return {l, r};
    }
    template<bool rev = false>
    void fix_chain(int u, Link*l, Link*r){
        if(rev){
            tie(r, l) = find_bridge(r, l,
                [](Link*x){ return x->prev; },
                [](Point const&a, Point const&b, Point const&c){
                    return ccw(a, b, c) >= 0;
                });
        } else {
            tie(l, r) = find_bridge(l, r,
                [](Link*x){ return x->next; },
                [](Point const&a, Point const&b, Point const&c){
                    return ccw(a, b, c) <= 0;
                });
        }
        tree[u].tangent = l;
        tree[u].chain = tree[2*u].chain;
        tree[u].chain_back = tree[2*u+1].chain_back;
        tree[2*u].chain = l->next;
        tree[2*u+1].chain_back = r->prev;
        if(l->next){
            l->next->prev = nullptr;
        } else {
            tree[2*u].chain_back = nullptr;
        }
        if(r->prev){
            r->prev->next = nullptr;
        } else {
            tree[2*u+1].chain = nullptr;
        }
        l->next = r;
        r->prev = l;
    }
    void build(int u, int a, int b){
        if(b-a == 1){
            tree[u].chain = tree[u].chain_back = &lists[a];
            tree[u].tangent = nullptr;
            return;
        }
        const int m = a + (b-a)/2;
        build(2*u, a, m);
        build(2*u+1, m, b);
        auto l = tree[2*u].chain, r = tree[2*u+1].chain;
        fix_chain(u, l, r);
    }

    void rob(int u, int v){
            tree[u].chain = tree[v].chain;
            tree[v].chain = nullptr;
            tree[u].chain_back = tree[v].chain_back;
            tree[v].chain_back = nullptr;
    }

    void remove(int u, int a, int b, int const&i){
        if(i < a || i >= b) return;
        if (b - a <= 1) return; // Should not happen with valid logic, but safe
        const int m = a + (b-a)/2;
        if(!tree[u].tangent){
            int v = i<m ? 2*u : 2*u+1;
            tree[v].chain = tree[u].chain;
            tree[v].chain_back = tree[u].chain_back;
            if(i < m){
                remove(2*u, a, m, i);
            } else {
                remove(2*u+1, m, b, i);
            }
            rob(u, v);
            return;
        }
        auto l = tree[u].tangent, r = l->next;
        l->next = tree[2*u].chain;
        if(tree[2*u].chain){
            tree[2*u].chain->prev = l;
        } else {
            tree[2*u].chain_back = l;
        }
        tree[2*u].chain = tree[u].chain;
        r->prev = tree[2*u+1].chain_back;
        if(tree[2*u+1].chain_back){
            tree[2*u+1].chain_back->next = r;
        } else {
            tree[2*u+1].chain = r;
        }
        tree[2*u+1].chain_back = tree[u].chain_back;
        const int v = i<m ? 2*u : 2*u+1;
        if(tree[v].chain == tree[v].chain_back && tree[v].chain != nullptr && tree[v].chain->id == i){
            tree[v].chain = tree[v].chain_back = nullptr;
            rob(u, v^1);
            tree[u].tangent = nullptr;
            return;
        }
        if(i < m){
            if(l->id == i){
                l = l->next;
            }
            remove(2*u, a, m, i);
            if(!l){
                l = tree[2*u].chain_back;
            }
            fix_chain<true>(u, l, r);
        } else {
            if(r->id == i){
                r = r->prev;
            }
            remove(2*u+1, m, b, i);
            if(!r){
                r = tree[2*u+1].chain;
            }
            fix_chain<false>(u, l, r);
        }
    }
    void remove(int i){
        if(tree[1].chain == tree[1].chain_back && tree[1].chain != nullptr && tree[1].chain->id == i){
            tree[1].chain = tree[1].chain_back = nullptr;
            return;
        }
        remove(1, 0, n, i);
    }
    Upper_Hull(vector<Point> const&v) : n(v.size()), tree(4*n), lists(n){
        if (n == 0) return;
        // assert(is_sorted(v.begin(), v.end())); // Sorting is done in main
        for(int i=0; i<n; ++i){
            lists[i].p = v[i];
            lists[i].id = i;
        }
        build(1, 0, n);
    }
    vector<int> get_hull(){
        vector<int> ret;
        for(Link* u = tree[1].chain; u; u=u->next){
            ret.push_back(u->id);
        }
        return ret;
    }

    int n;
    vector<Node> tree;
    vector<Link> lists;
};


ll calculate_area(Point p1, Point p2, Point p3) {
    if (dot(p2 - p1, p3 - p1) == 0) {
        return abs(cross(p2 - p1, p3 - p1));
    }
    if (dot(p1 - p2, p3 - p2) == 0) {
        return abs(cross(p1 - p2, p3 - p2));
    }
    // The third case must be true for a right-angled triangle
    return abs(cross(p1 - p3, p2 - p3));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<Point> points(n);
    for (int i = 0; i < n; ++i) {
        cin >> points[i].x >> points[i].y;
    }

    sort(points.begin(), points.end());

    vector<Point> flipped_points = points;
    for (auto& p : flipped_points) {
        p.y = -p.y;
    }

    Upper_Hull hull_upper(points);
    Upper_Hull hull_lower(flipped_points);

    int points_count = n;
    while (points_count > 4) {
        vector<int> upper_indices = hull_upper.get_hull();
        vector<int> lower_indices = hull_lower.get_hull();

        set<int> hull_to_remove;
        for (int idx : upper_indices) {
            hull_to_remove.insert(idx);
        }
        for (int idx : lower_indices) {
            hull_to_remove.insert(idx);
        }
        
        if (hull_to_remove.empty()) {
            // This can happen if the hull collapses entirely; break to be safe
            break;
        }

        for (int idx : hull_to_remove) {
            hull_upper.remove(idx);
            hull_lower.remove(idx);
        }
        points_count -= hull_to_remove.size();
    }

    // --- FIX STARTS HERE ---
    // Combine the final upper and lower hulls to get all 4 vertices
    vector<int> upper_final = hull_upper.get_hull();
    vector<int> lower_final = hull_lower.get_hull();
    set<int> final_indices_set;
    for (int idx : upper_final) final_indices_set.insert(idx);
    for (int idx : lower_final) final_indices_set.insert(idx);

    vector<int> final_indices(final_indices_set.begin(), final_indices_set.end());

    // With 4 points left, we can now safely access the first three
    Point p1 = points[final_indices[0]];
    Point p2 = points[final_indices[1]];
    Point p3 = points[final_indices[2]];
    // --- FIX ENDS HERE ---

    cout << calculate_area(p1, p2, p3) << endl;

    return 0;
}
