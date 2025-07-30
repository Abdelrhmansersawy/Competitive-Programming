#include <bits/stdc++.h>
using namespace std;

/*
 * ===================== D&C RANGE MINIMUM QUERY NOTE =====================
 *
 * Given an array `a` of size `n`, and `q` queries of the form [l, r],
 * answer each query with the minimum value in the range [l, r].
 *
 * The approach uses Divide and Conquer on queries, similar to Mo's algorithm,
 * but recursively splits the array and groups queries to avoid rebuilding segment trees.
 *
 * For queries crossing the midpoint, we precompute:
 *   - lt[i]: min from i to mid (inclusive)
 *   - rg[i]: min from mid+1 to i (inclusive)
 * ========================================================================
 */

const int N = 2e5 + 5;
int a[N], lt[N], rg[N], ans[N];

/**
 * Recursive D&C function to process a batch of queries in [l, r].
 * @param l      Left bound of the segment.
 * @param r      Right bound of the segment.
 * @param Q      Vector of queries: each is {L, R, index}.
 * Time: O(n log q) total over all calls.
 */
void solve(int l, int r, vector<array<int, 3>> Q) {
    if (Q.empty()) return; // Skip empty batch
    if (l == r) {
        for (auto &[L, R, i] : Q) ans[i] = a[l];
        return;
    }

    int m = (l + r) / 2;

    // Precompute prefix/suffix mins from the center
    lt[m] = a[m];
    for (int i = m - 1; i >= l; --i)
        lt[i] = min(a[i], lt[i + 1]);

    rg[m + 1] = a[m + 1];
    for (int i = m + 2; i <= r; ++i)
        rg[i] = min(a[i], rg[i - 1]);

    vector<array<int, 3>> leftQ, rightQ;

    for (auto &[L, R, i] : Q) {
        if (L <= m && R > m) {
            ans[i] = min(lt[L], rg[R]);
        } else if (R <= m) {
            leftQ.push_back({L, R, i});
        } else {
            rightQ.push_back({L, R, i});
        }
    }

    solve(l, m, leftQ);
    solve(m + 1, r, rightQ);
}

//------------------------------------------------------------------

int main() {
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);

    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; ++i) cin >> a[i];

    vector<array<int, 3>> queries;
    for (int i = 0; i < q; ++i) {
        int l, r; cin >> l >> r;
        --l, --r;
        queries.push_back({l, r, i});
    }

    solve(0, n - 1, queries);

    for (int i = 0; i < q; ++i)
        cout << ans[i] << '\n';
}
