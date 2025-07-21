#include <bits/stdc++.h>
using namespace std;

const int MASK = 1 << 9; // 2^9 = 512, each half of 18-bit number

/*
 * ======================== SUBMASK QUERY NOTE ========================
 *
 * Given a dynamic set of 18-bit numbers, we support two operations:
 * 1. Add/Remove a number `x` to/from the set.
 * 2. Count how many numbers `a` in the set are a submask of a given `x`.
 *
 * We split the number into two 9-bit halves: high and low.
 * For efficient processing, we use Meet-in-the-Middle.
 * ====================================================================
 */

// dp[h][l]: count of numbers in the set with high bits = h and low bits ⊆ l
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
    // Iterate over all supersets of `low` using (m + 1) | low
    for (int m = low; m < MASK; m = (m + 1) | low) {
        dp[high][m] += delta;
    }
}

/**
 * Counts how many numbers in the set are submasks of `x`.
 * @param x The 18-bit query number.
 * @return Count of submasks in the current set.
 * Time: O(2^(high_bits))
 */
int queryDP(int x) {
    int high = x >> 9;
    int low = x & (MASK - 1);
    int res = 0;
    // Iterate over all submasks of `high`
    for (int m = high; ; m = (m - 1) & high) {
        res += dp[m][low];
        if (m == 0) break;
    }
    return res;
}

//------------------------------------------------------------------


