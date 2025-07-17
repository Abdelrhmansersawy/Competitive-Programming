#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int mod = 1e9 + 7;

/*
 * ======================== PREFIX MAXIMUM SUM NOTE ========================
 *
 * Goal:
 * Efficiently calculate sum of contributions of subarrays where each
 * value is the maximum in its respective block.
 *
 * Step 1: Precompute the next greater index for each position.
 * - `nxt[i]` = first index > i such that arr[nxt[i]] > arr[i]
 * - If no such index, set `nxt[i] = n`
 *
 * Step 2: Build a DP array where:
 *   dp[i] = (nxt[i] - i) * arr[i] + dp[nxt[i]]  if nxt[i] < n
 *         = (n - i) * arr[i]                   otherwise
 *   - This represents the total contribution of arr[i] being max in
 *     range [i .. nxt[i] - 1]
 *   - Time complexity: O(n)
 *
 * Step 3: sum_mx(l, r, idx)
 * - Calculates the sum of contributions in range [l..r] assuming
 *   arr[idx] is the maximum in [idx..r]
 * - Logic:
 *     ans = dp[l]       // full segment sum from l
 *     ans -= dp[idx]    // remove overcounted part starting from idx
 *     ans += arr[idx] * (r - idx + 1)  // add real max segment
 *     mod adjust all the way
 * - Useful in divide-and-conquer or segment-based problems.
 *
 * All operations are done modulo `mod` to avoid overflow.
 *
 * =========================================================================
 */

vector<int> next_greater(const vector<int>& arr) {
    int n = arr.size();
    vector<int> nxt(n, n);
    stack<int> st;
    for (int i = 0; i < n; ++i) {
        while (!st.empty() && arr[st.top()] < arr[i]) {
            nxt[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
    return nxt;
}

int main() {
    vector<int> arr = {3, 1, 2, 4}; // Example array
    int n = arr.size();

    vector<int> nxt = next_greater(arr);
    vector<int> dp(n);

    // Build DP array from right to left
    for (int i = n - 1; i >= 0; --i) {
        dp[i] = 1LL * (nxt[i] - i) * arr[i] % mod;
        if (nxt[i] != n) dp[i] = (dp[i] + dp[nxt[i]]) % mod;
    }

    // Lambda function to query sum using idx as max
    auto sum_mx = [&](int l, int r, int idx) {
        if (l > r) return 0LL;
        ll ans = dp[l];
        ans = (ans - dp[idx] + mod) % mod;
        ans = (ans + 1LL * arr[idx] * (r - idx + 1) % mod) % mod;
        return ans;
    };

    // Example query: range [1, 3] with arr[3] = 4 as max
    int l = 1, r = 3, idx = 3;
    cout << "Sum with max at index " << idx << " in range [" << l << ", " << r << "]: ";
    cout << sum_mx(l, r, idx) << '\n';

    return 0;
}