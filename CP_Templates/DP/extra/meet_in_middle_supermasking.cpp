/*
 * ======================= SUPERMASK QUERY NOTE =======================
 *
 * Given a dynamic set of 18-bit numbers, we support two operations:
 * 1. Add/Remove a number `x` to/from the set.
 * 2. Count how many numbers `a` in the set are a supermask of a given `x`.
 * (This corresponds to the bitwise condition `a & x == x`).
 *
 * We split the number into two 9-bit halves: high and low.
 * For efficient processing, we use Meet-in-the-Middle.
 * ====================================================================
 */

// dp[h][l]: count of numbers in the set with high bits = h and low bits supseteq l (is a supermask of l)
int dp[MASK][MASK];

/**
 * Adds or removes a number from the set.
 * @param x     The 18-bit number to update.
 * @param delta +1 to insert, -1 to erase.
 * Time: O(2^(low_bits))
 */
void updateDP(int x, int delta) {
    int high = x >> 9;
    int low = x & (MASK - 1);
    // Iterate over all subsets of `low`
    for (int m = low; ; m = (m - 1) & low) {
        dp[high][m] += delta;
        if (m == 0) break;
    }
}

/**
 * Counts how many numbers in the set are supermasks of `x`.
 * @param x The 18-bit query number.
 * @return Count of supermasks in the current set.
 * Time: O(2^(high_bits))
 */
int queryDP(int x) {
    int high = x >> 9;
    int low = x & (MASK - 1);
    int res = 0;
    // Iterate over all supersets of `high`
    for (int m = high; m < MASK; m = (m + 1) | high) {
        res += dp[m][low];
    }
    return res;
}
