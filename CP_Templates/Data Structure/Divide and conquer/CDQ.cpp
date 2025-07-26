/*
 * ============================= CDQ D&C NOTE =============================
 *
 * It extends normal divide & conquer by allowing the left half [l, m) to
 * influence the right half [m, r).
 *
 * Why?
 * When solving a problem, you care about i < j and another condition
 * (e.g., x[i] < x[j] && y[i] < y[j]).
 *
 * Standard CDQ framework:
 *   - Divide [l, r) into [l, m), [m, r)
 *   - Solve subproblems in [l, m) and [m, r)
 *   - Calculate the influence of [l, m) on [m, r)
 *   - Merge them
 *
 * This is particularly useful in problems involving prefix sums,
 * 2D counting (e.g., number of inversions), and dynamic queries.
 * Time complexity is often O(n log n) with segment tree / bitset / Fenwick.
 *
 * Example use case:
 *   - Process queries in sorted time order
 *   - Left part holds past updates, right part holds future queries
 * ========================================================================
 */

/*
// ====================== CDQ + COMPARATOR EXAMPLE ======================


// TODO: change this function based on your order
bool comp(int i, int j) { return y[i] < y[j]; }

void dc(int l, int r) {
    if (l == r) return;
    int m = (l + r) / 2;
    dc(l, m);

    vector<int> left(m - l + 1);
    iota(left.begin(), left.end(), l);
    sort(left.begin(), left.end(), comp);

    vector<int> right(r - m);
    iota(right.begin(), right.end(), m + 1);
    sort(right.begin(), right.end(), comp);

    int i = 0;
    
    for (int j = 0; j < right.size(); ++j) {
        while (i < left.size() && y[left[i]] < y[right[j]]) {
            int ind = left[i];
            // TODO: Update contribution of index "ind"
            ++i;
        }

        int ind = right[j];
        // TODO: compute the values of dp[ind] with contribution on part [l..,]

    }

    while (i > 0) {
        --i;
        // TODO: remove added contribution of index "ind"

    }

    dc(m + 1, r);
}
