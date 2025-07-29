/*
 * ================== K-th Lexicographical Substring (CSES 2109) ==================
 *
 * Problem:
 * - Given a string of length n.
 * - Consider all (not necessarily distinct) substrings in lexicographical order.
 * - Find the k-th one.
 *
 * Tools Used:
 * - Suffix Array
 * - LCP Array
 * - Binary Search over substring rank
 * 
 * Time Complexity:
 * - O(n log n) for building suffix + LCP
 * - O(n log^2 n) overall due to binary search over O(n^2) substrings
 *
 * Link:
 * - https://cses.fi/problemset/task/2109/
 * 
 * ============================================================================
 */

string s; cin >> s;
int n = s.size();
auto p = buildSuffixArray(s);
auto lcp = Kasai(s, p);

/*
 * k_th(k):
 * - Given a rank k, find the k-th lexicographical substring.
 * - Uses suffix array and LCP to skip repeated prefixes.
 */
auto k_th = [&](ll k) -> pair<int, int> {
    if (k <= n - p[0]) return {0, k};
    k -= n - p[0];
    for (int i = 0; i < lcp.size(); ++i) {
        int len = n - p[i + 1] - lcp[i];
        if (k <= len) return {i + 1, k + lcp[i]};
        k -= len;
    }
    assert(false);
};

ll k; cin >> k;
ll lo = 1, hi = 1LL * n * (n + 1) / 2 - accumulate(lcp.begin(), lcp.end(), 0LL), md;

/*
 * Binary search on substring rank:
 * - For a candidate substring (index, length), calculate how many substrings
 *   are ≤ it using LCP and suffix array.
 * - Adjust range based on whether count ≥ k.
 */
while (lo < hi) {
    md = lo + (hi - lo) / 2;
    auto [i, len] = k_th(md);

    ll sum = len;
    for (int j = 0; j < i; ++j) sum += n - p[j];

    int x = len;
    for (int j = i + 1; j < n; ++j) {
        x = min(x, lcp[j - 1]);
        sum += x;
    }

    if (sum >= k) hi = md;
    else lo = md + 1;
}

auto [i, len] = k_th(lo);
cout << s.substr(p[i], len);
