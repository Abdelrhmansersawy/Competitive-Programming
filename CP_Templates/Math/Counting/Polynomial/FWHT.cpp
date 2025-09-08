/*
 * ============================= Fast Subset Transform (FST) =============================
 *
 * FST performs convolution on bitmasks in O(N log N), where N = 2^k.
 * It supports three common binary operations on subsets: AND, OR, XOR.
 * This template allows toggling the operation by uncommenting the appropriate line.
 * 
 * Operation summary:
 * - AND: f(S) = sum of all f(T) * g(S ^ T) for T ⊆ S
 * - OR : f(S) = sum of all f(T) * g(S ^ T) for T ⊇ S
 * - XOR: f(S) = sum over all T (f(T) * g(S ^ T))  [Requires normalization on inverse]
 *
 * Time: O(N log N)
 */

#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define rep(i, st, ed) for (int i = st; i < ed; i++)
#define sz(v) int(v.size())

void FST(vi& a, bool inv) {
    int n = sz(a);
    for (int step = 1; step < n; step <<= 1) {
        for (int i = 0; i < n; i += 2 * step) {
            rep(j, i, i + step) {
                int &u = a[j], &v = a[j + step];
                tie(u, v) =
                    inv ? pii(v - u, u) : pii(v, u + v); // AND
                    // inv ? pii(v, u - v) : pii(u + v, u); // OR /// include-line
                    // pii(u + v, u - v);                   // XOR /// include-line
            }
        }
    }
    // if (inv) for (int &x : a) x /= n; // XOR only /// include-line
}

// Convolution: C = A * B
vi conv(vi a, vi b) {
    FST(a, false); FST(b, false);
    rep(i, 0, sz(a)) a[i] *= b[i];
    FST(a, true);
    return a;
}

/*
 * ============================= Example Usage =============================
 *
 * int main() {
 *     vi A = {1, 2, 3, 4};
 *     vi B = {4, 3, 2, 1};
 *     vi C = conv(A, B);
 *     for (int x : C) cout << x << " ";
 *     cout << "\n";
 * }
 *
 * Change the size of A/B to be power of 2 (e.g., 2^k) before calling `conv`.
 */
