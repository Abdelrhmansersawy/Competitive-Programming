/*
 * Convex Hull Trick (Monotonic Insertion & Queries)
 *
 * This implementation is for cases where lines are added with strictly monotonic
 * slopes (either always increasing or decreasing). It can find the minimum or
 * maximum value of y = kx + b for a given x.
 *
 * --- Usage ---
 * 1.  Instantiate the struct: `CHT cht(is_min_mode);`
 * - `is_min_mode = false` (default) for maximum queries.
 * - `is_min_mode = true` for minimum queries.
 *
 * 2.  Add lines with `add_line(k, b)`. Slopes `k` MUST be monotonic.
 *
 * 3.  Query the hull for the optimal value at a given x-coordinate:
 * - `get(x)`: O(log n) query for any x.
 * - `get_mono(x)`: Amortized O(1) query for monotonic x. The required
 * query direction depends on the mode:
 *
 * ### MAX Mode (is_min_mode = false)
 * The query direction for `x` must MATCH the slope direction for `k`.
 * - Increasing `k` ⇒ non-decreasing `x`
 * - Decreasing `k` ⇒ non-increasing `x`
 *
 * ### MIN Mode (is_min_mode = true)
 * The query direction for `x` must be the OPPOSITE of the slope direction for `k`.
 * This is because the slopes are internally negated (`k` becomes `-k`).
 * - Increasing original `k` ⇒ non-increasing `x`
 * - Decreasing original `k` ⇒ non-decreasing `x`
 *
 * --- Complexity ---
 * - Add Line: Amortized O(1)
 * - Arbitrary Query (`get`): O(log n)
 * - Monotonic Query (`get_mono`): Amortized O(1)
 */

#include <bits/stdc++.h>
using namespace std;

// Using long long is crucial to avoid overflow from multiplications.
typedef long long ftype;
typedef complex<ftype> point;
#define x real
#define y imag

// Calculates the dot product of two vectors.
ftype dot(point a, point b) {
    return (conj(a) * b).x();
}

// Calculates the 2D cross product of two vectors.
ftype cross(point a, point b) {
    return (conj(a) * b).y();
}

// Implements the Convex Hull Trick for monotonic slope insertion.
struct CHT {
    vector<point> hull, vecs;
    size_t mono_ptr = 0;
    bool is_min = false;

    // Constructs the CHT object.
    // is_min_mode: Set to true for minimum queries, false for maximum.
    CHT(bool is_min_mode = false) : is_min(is_min_mode) {}

    // Adds a line y = kx + b to the hull.
    // Slopes (k) must maintain monotonicity across calls.
    void add_line(ftype k, ftype b) {
        if (is_min) { k = -k; b = -b; }
        point nw = {k, b};

        // Maintain the upper convex hull (concave shape).
        while (hull.size() >= 2 && cross(hull.back() - hull[hull.size()-2], nw - hull.back()) > 0) {
            hull.pop_back();
            vecs.pop_back();
        }

        if (!hull.empty()) {
            vecs.push_back(point(0, 1) * (nw - hull.back()));
        }
        hull.push_back(nw);
    }

    // Queries the hull for an arbitrary x value. O(log n).
    ftype get(ftype x) {
        if (hull.empty()) return is_min ? 1e18 : -1e18;

        point query = {x, 1};
        auto it = lower_bound(vecs.begin(), vecs.end(), query,
            [](point a, point b) {
                return cross(a, b) > 0;
            });
        size_t idx = it - vecs.begin();
        ftype res = dot(query, hull[idx]);
        return is_min ? -res : res;
    }

    // Queries the hull for a monotonic x value. Amortized O(1).
    // The x-coordinate must be monotonic across calls as per the rules above.
    ftype get_mono(ftype x) {
        if (hull.empty()) return is_min ? 1e18 : -1e18;

        while (mono_ptr + 1 < hull.size() &&
               dot({x, 1}, hull[mono_ptr]) <= dot({x, 1}, hull[mono_ptr + 1])) {
            mono_ptr++;
        }
        while (mono_ptr > 0 &&
               dot({x, 1}, hull[mono_ptr]) <= dot({x, 1}, hull[mono_ptr - 1])) {
            mono_ptr--;
        }
        ftype res = dot({x, 1}, hull[mono_ptr]);
        return is_min ? -res : res;
    }

    // Clears the hull. Useful for multiple test cases.
    void clear() {
        hull.clear();
        vecs.clear();
        mono_ptr = 0;
    }
};
