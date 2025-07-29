/*
 * ============= K-th Lexicographical Distinct Substring (CSES 2108) =============
 *
 * Problem:
 * - Given a string of length n.
 * - Consider all **distinct** substrings sorted lexicographically.
 * - Find the k-th one.
 *
 * Tools Used:
 * - Suffix Array
 * - LCP Array (Kasai's Algorithm)
 *
 * Time Complexity:
 * - O(n log n) for suffix + LCP
 * - O(n) to iterate and count distinct substrings
 *
 * Link:
 * - https://cses.fi/problemset/task/2108/
 *
 * ================================================================================
 */

string s; cin >> s;
int n = s.size();

auto p = buildSuffixArray(s);
auto lcp = Kasai(s, p);

ll k; cin >> k;

/*
 * Each suffix contributes (n - p[i]) - lcp[i - 1] new distinct substrings.
 * Iterate through suffixes and skip the total contribution until reaching k.
 */

if (k <= n - p[0]) {
    cout << s.substr(p[0], k);
    return 0;
}

k -= n - p[0];

for (int i = 0; i < lcp.size(); ++i) {
    int len = n - p[i + 1] - lcp[i];
    if (k <= len) {
        cout << s.substr(p[i + 1], k + lcp[i]);
        return 0;
    }
    k -= len;
}
