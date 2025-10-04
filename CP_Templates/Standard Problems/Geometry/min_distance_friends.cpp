#include <bits/stdc++.h>
using namespace std;

/*
 * ===================== MINIMUM DISTANCE BETWEEN TWO FRIENDS =====================
 *
 * Problem:
 *   - Friend 1 starts at point A and walks straight to point B.
 *   - Friend 2 starts at point C and walks straight to point D.
 *   - Both start at the same time, move with the same constant speed.
 *   - If one arrives earlier, they stay at the destination while the other keeps moving.
 *
 * Task:
 *   - Find the minimum possible distance between the two friends at any moment.
 *
 * Approach:
 *   - Represent points as complex numbers for easy vector math.
 *   - Let d1 = |AB|, d2 = |CD|.
 *   - Define f(t): distance between the two friends after time t.
 *     - If friend hasn't reached the destination yet, move proportionally along the line.
 *     - Otherwise, stay at the endpoint.
 *   - Use ternary search to minimize f(t) on:
 *       1. Interval [0, min(d1, d2)] (both moving).
 *       2. Interval [min(d1, d2), max(d1, d2)] (one waiting, other moving).
 *   - Answer is the smaller of the two minima.
 *
 * Complexity:
 *   - O(iterations) = ~80 iterations per ternary search (enough for precision).
 *   - Runs in constant time for given input size.
 * =================================================================================
 */

typedef long long ll;
typedef long double ld;
typedef complex<ld> Point;

Point getPoint() {
    ll x, y;
    cin >> x >> y;
    return Point{x, y};
}

Point a, b, c, d;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(NULL);

    // Input: A, B, C, D
    a = getPoint();
    b = getPoint();
    c = getPoint();
    d = getPoint();

    ld d1 = abs(b - a); // distance AB
    ld d2 = abs(d - c); // distance CD

    // f(t): distance between two friends at time t
    auto f = [&](ld t) {
        Point p1, p2;
        if (!d1) p1 = a;
        else p1 = a + ((b - a) / d1) * min(t, d1);

        if (!d2) p2 = c;
        else p2 = c + ((d - c) / d2) * min(t, d2);

        return abs(p1 - p2);
    };

    // Ternary search for minimum distance in interval [lo, hi]
    auto tern = [&](ld lo, ld hi) {
        for (int _ = 0; _ < 80; ++_){
            ld g = lo + (hi - lo) / 3;
            ld h = hi - (hi - lo) / 3;
            if (f(g) > f(h)) lo = g;
            else hi = h;
        }
        return f(lo);
    };

    ld lT = min(d1, d2);
    ld rT = max(d1, d2);

    // Answer: minimum distance across both intervals
    cout << fixed << setprecision(9) 
         << min(tern(0, lT), tern(lT, rT)) << "\n";
}
