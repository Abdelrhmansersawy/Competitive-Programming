/*
 * ============== Count of Distinct Substrings (CSES 2107) ==============
 *
 * Problem:
 * - Given a string `s` of length `n`.
 * - Count the total number of **distinct substrings**.
 *
 * Formula:
 * - Total substrings: n * (n + 1) / 2
 * - Subtract repeated prefixes using LCP array
 *   → Result = total - sum of LCPs
 *
 * Tools Used:
 * - Suffix Array
 * - LCP Array
 *
 * Time Complexity:
 * - O(n log n) for suffix + LCP
 *
 * Link:
 * - https://cses.fi/problemset/task/2107/
 *
 * ======================================================================
 */

int main() {
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);

    string s; cin >> s;
    int n = s.size();

    auto p = buildSuffixArray(s);
    auto lcp = Kasai(s, p);

    ll distinct = 1LL * n * (n + 1) / 2 - accumulate(lcp.begin(), lcp.end(), 0LL);
    cout << distinct << '\n';
}
