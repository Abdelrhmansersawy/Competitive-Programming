/**
 * Counts solutions for x_1 + ... + x_d = s, where 0 <= x_i <= b.
 *
 * This function uses the Principle of Inclusion-Exclusion to enforce the upper
 * bound 'b'. It starts with the total non-negative solutions and then corrects
 * for the bound by alternately subtracting/adding cases where variables exceed 'b'.
 *
 * The underlying formula is:
 * sum_{i=0 to d} [ (-1)^i * C(d, i) * C(s - i*(b+1) + d-1, d-1) ]
 * Time Complexity: O(d) per call, after an initial O(MAX_VAL) precomputation.
 */

ll solve(int d, int s, int b) {
    ll ans = 0;
    for (int i = 0; i <= d; ++i) {
        ll cur_s = s - (ll)i * (b + 1);
        if (cur_s < 0) {
            break;
        }

        ll ways = nCr(cur_s + d - 1, d - 1);
        ll term = (nCr(d, i) * ways) % mod;

        if (i % 2 == 1) {
            ans = (ans - term + mod) % mod;
        } else {
            ans = (ans + term) % mod;
        }
    }
    return ans;
}
