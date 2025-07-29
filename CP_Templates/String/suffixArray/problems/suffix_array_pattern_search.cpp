/*
 * ================ Pattern Search in Suffix Array (CSES 2103) ================
 *
 * Problem:
 * - Given a text and a pattern, count the number of times the pattern appears in the text.
 *
 * Tools Used:
 * - Suffix Array
 * - Binary Search (O(log n) for lower/upper bounds)
 *
 * Time Complexity:
 * - O(log n) for each binary search, total O(2 * log n) per pattern
 *
 * Link:
 * - https://cses.fi/problemset/task/2103/
 *
 * ============================================================================
 */

// Finds the range [start, end] in the suffix array where pattern `pat` occurs
pair<int, int> findPattern(const string &text, const string &pat, vector<int> &sa) {
    /*
     * Input:
     * - text : original string
     * - pat  : pattern to search
     * - sa   : suffix array (sorted list of starting indices)
     * 
     * Output:
     * - Pair {start, end} such that sa[start..end] are matches for `pat`
     * - Returns {-1, -1} if no match exists
     */
    int n = sa.size();

    auto compare = [&](int pos) {
        return text.compare(sa[pos], pat.length(), pat);
    };

    // Lower bound: leftmost match
    int left = 0, right = n - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (compare(mid) >= 0) right = mid;
        else left = mid + 1;
    }
    if (compare(left) != 0) return {-1, -1};
    int start = left;

    // Upper bound: rightmost match
    right = n - 1;
    while (left < right) {
        int mid = left + (right - left + 1) / 2;
        if (compare(mid) <= 0) left = mid;
        else right = mid - 1;
    }

    return {start, left};
}

/*
 * Alternative approach: character-wise matching using lower_bound / upper_bound
 * - Works well when `p` is the suffix array and `text` is globally available
 * - Finds the lexicographical range of `pat` in the suffix array
 */
auto find_string = [&](const string &pat) -> pair<int, int> {
    int st = 0, ed = n;

    auto cmp = [&](int a, int b) {
        if (a == -1)
            return pat[i] < text[b + i];
        return text[a + i] < pat[i];
    };

    for (int i = 0; i < pat.size() && st < ed; i++) {
        st = lower_bound(p.begin() + st, p.begin() + ed, -1, cmp) - p.begin();
        ed = upper_bound(p.begin() + st, p.begin() + ed, -1, cmp) - p.begin();
    }

    if (st >= ed) return {-1, -1};
    return {st, ed - 1};
};
