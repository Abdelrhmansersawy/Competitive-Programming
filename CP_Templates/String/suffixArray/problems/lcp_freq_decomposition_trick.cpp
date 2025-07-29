#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ======================= LCP‑Frequency Decomposition Trick =======================
//
// General pattern to aggregate any function over all substrings of s by grouping
// them according to their frequencies using the suffix array and LCP:
//
// Given string s of length n:
// 1. Build suffix array `p` and LCP array `lcp`.
// 2. Compute for each i the nearest smaller‑LCP bounds `L[i]`, `R[i]` via a
//    monotonic stack.
// 3. Bucket positions by their `lcp`‑value, then for each len = n…0:
//      • For each interval [l+1..r] where `lcp[x] == len` is the minimum,
//        the frequency is `f = r – l` for all substrings of lengths in
//        [boundary+1 .. len], where boundary = max(lcp[l], lcp[r]) (0 if oob).
//      • Call your custom `contribute(f, minH, maxH)` to add to the answer.
// 4. Handle the “unique” substrings on each suffix (f = 1) the same way.
//
// Overall complexity: O(n) beyond SA/LCP construction.
//
// To use: Replace the body of `contribute(...)` with whatever aggregate you need
// (sum of lengths, f²×length, custom weights, etc.).
// =================================================================

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = s.size();

    auto p      = buildSuffixArray(s);
    auto lcp    = buildLCP(s, p);
    auto [L, R] = getMinBounds(lcp);

    // bucket all lcp‑positions by their value
    vector<vector<int>> group(n + 1);
    for (int i = 0; i < (int)lcp.size(); ++i)
        group[lcp[i]].push_back(i);

    ll ans = 0;

    // user-supplied aggregator:
    auto contribute = [&](ll f, int minH, int maxH) {
        // Example: add f² × sum of all lengths in [minH..maxH]:
        // ll cnt = max(0, maxH - minH + 1);
        // ans += f * f * cnt * (minH + maxH) / 2;
        //
        // Replace the above with your own logic:
        //   • f: frequency of each substring in this block
        //   • [minH..maxH]: inclusive range of substring‑lengths with that frequency
    };

    // process each possible LCP length in descending order
    for (int len = n; len >= 0; --len) {
        for (size_t j = 0; j < group[len].size(); ) {
            int x = group[len][j];
            int l = L[x], r = R[x];
            int f = r - l;               // frequency for substrings ≥ len in this block

            // compute the tightest smaller‑LCP boundary just outside [l+1..r]
            int boundary = 0;
            if (l >= 0)                   boundary = max(boundary, lcp[l]);
            if (r < (int)lcp.size())     boundary = max(boundary, lcp[r]);

            int minH = boundary + 1;     // smallest length with freq == f
            int maxH = len;              // largest length with freq == f

            if (minH <= maxH)
                contribute(f, minH, maxH);

            // skip all positions covered by this block
            while (j < group[len].size() && group[len][j] <= r)
                ++j;
        }
    }

    // handle unique substrings on each suffix (f = 1)
    for (int i = 0; i < n; ++i) {
        int len = n - p[i];
        int f   = 1;

        int boundary = 0;
        if (i > 0)                   boundary = max(boundary, lcp[i - 1]);
        if (i < (int)lcp.size())    boundary = max(boundary, lcp[i]);

        int minH = boundary + 1;
        int maxH = len;

        if (minH <= maxH)
            contribute(f, minH, maxH);
    }

    cout << ans << "\n";
    return 0;
}
