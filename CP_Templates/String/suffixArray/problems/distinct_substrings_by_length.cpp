/*
 * ============== Count Distinct Substrings by Length (CSES 2110) ==============
 *
 * Problem:
 * - Given a string `s` of length `n`.
 * - For every length `1 ≤ L ≤ n`, print the number of distinct substrings of length `L`.
 *
 * Tools Used:
 * - Suffix Array
 * - LCP Array
 * - Difference array trick for range frequency update
 *
 * Time Complexity:
 * - O(n log n) for suffix + LCP
 * - O(n) for computing counts using prefix sum
 *
 * Link:
 * - https://cses.fi/problemset/task/2110/
 *
 * ============================================================================
 */

string s; cin >> s;
int n = s.size();
auto p = buildSuffixArray(s);
auto lcp = Kasai(s, p);

ll cnt[n + 2]{}; // Difference array for count of substrings by length

// Apply range update: cnt[l..r] += v
auto upd = [&](int l, int r, int v) {
    if (l > r) return;
    cnt[l] += v;
    cnt[r + 1] -= v;
};

// For each LCP[i], reduce counts of substrings of length 1 to LCP[i]
for (int i = 0; i < lcp.size(); ++i) upd(1, lcp[i], -1);

// Build prefix sum
for (int i = 1; i <= n; ++i) cnt[i] += cnt[i - 1];

// Add base count: total substrings of length i in full string = n - i + 1
for (int i = 1; i <= n; ++i) cnt[i] += n - i + 1;

// Output final result
for (int i = 1; i <= n; ++i) cout << cnt[i] << ' ';
