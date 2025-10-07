#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 5002;
int n, k;
ll dp[2][N], a[N];
ll sum;                 // current cost value
int L, R;               // Mo window boundaries
int freq[N];            // frequency array (example, can be customized)

// =================== MO-STYLE COST MAINTENANCE ===================
// The idea: maintain cost(l, r) dynamically by adjusting [L, R] interval.
// addR(i): include element at right end
// addL(i): include element at left end
// remL(i): remove element from left end
// remR(i): remove element from right end

void addR(int i) {
    // Example:
    // sum += contribution_of(a[i]) when extending the right end
    // freq[a[i]]++;
}

void addL(int i) {
    // Example:
    // sum += contribution_of(a[i]) when extending the left end
    // freq[a[i]]++;
}

void remL(int i) {
    // Example:
    // sum -= contribution_of(a[i]) when removing from left end
    // freq[a[i]]--;
}

void remR(int i) {
    // Example:
    // sum -= contribution_of(a[i]) when removing from right end
    // freq[a[i]]--;
}

// Adjust [L, R] to new [l, r] and keep 'sum' valid
void move(int l, int r) {
    while (R < r) addR(++R);  // extend right
    while (L > l) addL(--L);  // extend left
    while (R > r) remR(R--);  // shrink right
    while (L < l) remL(L++);  // shrink left
}

// Compute cost(l, r) using the maintained 'sum'
ll cost(int l, int r) {
    move(l, r);
    return sum;
}

// =================== DIVIDE & CONQUER DP OPTIMIZATION ===================
// dp[it][m] = min_{opt <= m}( dp[it^1][opt-1] + cost(opt, m) )
// This function optimizes dp for a given 'it' (the current partition step).
void dnc(int it, int l, int r, int optL, int optR) {
    if (l > r) return;

    int m = (l + r) / 2;
    pair<ll, int> best = {LLONG_MAX, -1};

    // try all possible partition points in [optL, optR]
    for (int opt = optL; opt <= min(optR, m); ++opt) {
        ll val = dp[it ^ 1][opt - 1] + cost(opt, m);
        if (val < best.first)
            best = {val, opt};
    }

    dp[it][m] = best.first;
    int opt = best.second;

    // recursively compute left and right halves
    dnc(it, l, m - 1, optL, opt);
    dnc(it, m + 1, r, opt, optR);
}

// =================== MAIN EXECUTION ===================
void run() {
    memset(dp, 0x3f, sizeof(dp));  // initialize DP to INF
    dp[0][0] = 0;                  // base case

    L = 1, R = 0;                  // start with empty window
    sum = 0;
    memset(freq, 0, sizeof(freq)); // reset frequency

    // base layer (for 1 group)
    for (int i = 1; i <= n; ++i)
        dp[0][i] = cost(1, i);

    // apply Divide & Conquer optimization for k groups
    for (int it = 1; it < k; ++it)
        dnc(it & 1, 1, n, 1, n);
}

// =================== TIME COMPLEXITY ===================
/*
Let n = number of elements, k = number of DP layers (partitions)

- Each dnc() layer runs in O(n log n) if the optimal partition index moves monotonically.
- Each cost() update (via move) runs in O(1) amortized using Mo-style maintenance.

Total time = O(k * n * log n)

If cost updates are not O(1), adjust accordingly (e.g., O(f) per move → O(k * n * log n * f)).
*/
