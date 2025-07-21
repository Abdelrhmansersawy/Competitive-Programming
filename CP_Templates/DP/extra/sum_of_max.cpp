#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int mod = 1e9 + 7;

/*
 * ======================== PREFIX MAXIMUM SUM NOTE ========================
 *
 * S(l, r) is defined as the sum of maximums over all prefixes starting at
 * index l and ending at r.
 * S(l, r) = sum from j = l to r of max(arr[l ... j])
 *
 * =========================================================================
 */

/**
 * Finds the index of the next greater element for each element.
 * Uses a monotonic stack. If no greater element exists, stores n.
 * The input `arr` is the array to process.
 * Returns a vector `nxt` where nxt[i] is the index of the next greater element.
 * Complexity is O(n).
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

    // dp[i] = S(i, n-1), the prefix maximum sum starting from index i.
    vector<int> dp(n);

    // Build DP from right to left using the next greater element indices.
    // The logic is S(i, n-1) = (contribution where arr[i] is max) + S(nxt[i], n-1).
    for (int i = n - 1; i >= 0; --i) {
        // Contribution from prefixes arr[i...j] where j < nxt[i].
        dp[i] = 1LL * (nxt[i] - i) * arr[i] % mod;
        // Add contribution from the rest of the array, starting from nxt[i].
        if (nxt[i] != n) {
            dp[i] = (dp[i] + dp[nxt[i]]) % mod;
        }
    }

    /**
     * Calculates S(l, r) given that arr[idx] is the max in arr[l...r].
     * It uses the formula: S(l, r) = S(l, idx-1) + (r - idx + 1) * arr[idx].
     * S(l, idx-1) is computed as dp[l] - dp[idx].
     */
    auto sum_mx = [&](int l, int r, int idx) {
        if (l > r) return 0LL;
        // S(l, idx-1) calculated via dp table
        ll ans = (dp[l] - (idx < n ? dp[idx] : 0) + mod) % mod;
        // Add contribution where arr[idx] is the maximum
        ans = (ans + 1LL * arr[idx] * (r - idx + 1) % mod) % mod;
        return ans;
    };

    // Example query: S(1, 3) where arr[3]=4 is max in arr[1...3] = {1, 2, 4}.
    // Calculation: max(1) + max(1,2) + max(1,2,4) = 1 + 2 + 4 = 7
    int l = 1, r = 3, idx = 3;
    cout << "Sum with max at index " << idx << " in range [" << l << ", " << r << "]: ";
    cout << sum_mx(l, r, idx) << '\n'; // Expected output: 7

    return 0;
}
