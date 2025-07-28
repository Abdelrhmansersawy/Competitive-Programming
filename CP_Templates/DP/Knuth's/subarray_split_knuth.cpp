/*
 * ============================= Knuth Optimization =============================
 * 
 * Problem:
 * You're given an array of n elements. You must repeatedly split the array into
 * two non-empty contiguous subarrays, until each subarray contains exactly one
 * element. The cost of each split is the sum of the values in the chosen subarray.
 * Output the minimum total cost of doing this optimally.
 * 
 * Example:
 * Input : n = 4
 *         a = [1, 2, 3, 4]
 * 
 * Output: 19
 * Explanation: 
 *   Split [1 2 3 4] → [1] + [2 3 4]   (cost 10)
 *   Split [2 3 4]   → [2] + [3 4]     (cost 9)
 *   Split [3 4]     → [3] + [4]       (cost 7)
 *   Total = 10 + 9 + 7 = 26 (can do better)
 *   Optimal total cost = 19
 *
 * ------------------------------------------------------------------------------
 * 
 * Approach:
 * This is a classic Knuth Optimization DP problem. Let:
 *   - dp[i][j] = minimum cost to fully split the subarray [i..j]
 *   - C(i, j)  = cost of merging subarray a[i..j] = sum(a[i..j])
 *   - opt[i][j] = optimal "k" for dp[i][j], where dp[i][j] = dp[i][k] + dp[k+1][j] + C(i,j)
 * 
 * Optimization Condition:
 *   Knuth optimization can be used if:
 *     - The cost function C satisfies the quadrangle inequality.
 *     - The "opt" values are monotonic: opt[i][j-1] ≤ opt[i][j] ≤ opt[i+1][j].
 * 
 * Time Complexity: O(n^2)
 * Space Complexity: O(n^2)
 * 
 * ------------------------------------------------------------------------------
 * 
 * Implementation:
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define f first
#define s second

int main() {
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
    
    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif

    int n; cin >> n;
    vector<ll> pre(n);
    for (int i = 0; i < n; ++i) {
        cin >> pre[i];
        if (i) pre[i] += pre[i - 1];  // prefix sum
    }

    // Helper to get sum in range [i..j]
    auto C = [&](int i, int j) -> ll {
        return pre[j] - (i ? pre[i - 1] : 0);
    };

    vector<vector<ll>> dp(n, vector<ll>(n, 0));
    vector<vector<int>> opt(n, vector<int>(n));

    // Base case: one element → no cost
    for (int i = 0; i < n; ++i) {
        opt[i][i] = i;
    }

    // Solve for increasing length of subarrays
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i + len - 1 < n; ++i) {
            int j = i + len - 1;
            ll cost = C(i, j);
            ll &res = dp[i][j];
            res = LLONG_MAX;

            // Knuth optimization: search range is reduced
            for (int k = opt[i][j - 1]; k <= min(j - 1, opt[i + 1][j]); ++k) {
                ll cur = dp[i][k] + dp[k + 1][j] + cost;
                if (cur < res) {
                    res = cur;
                    opt[i][j] = k;
                }
            }
        }
    }

    cout << dp[0][n - 1] << '\n';
}
