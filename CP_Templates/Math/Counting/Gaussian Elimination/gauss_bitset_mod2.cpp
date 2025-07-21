#include <bits/stdc++.h>
using namespace std;

// Maximum number of variables +1 (for augment column)
const int MAXM = 5005;

/**
 * Gauss-Jordan elimination over GF(2) using bitsets:
 *   Solves A·x = b with all operations mod 2.
 *
 * Input:
 *   a — vector<bitset<MAXM>> of length n, where each row has m+1 bits:
 *       bits [0..m-1] are coefficients, bit m is the constant term.
 *
 * Returns:
 *   bitset<MAXM> ans containing one solution in ans[0..m-1],
 *   or empty ans (all zero + inconsistent flag) if no solution.
 *
 * Time Complexity: O(n·m·(m/64)) ≈ O(n·m²/64)
 */
int gauss_bitset(vector<bitset<MAXM>>& a, int n, int m, bitset<MAXM>& ans) {
    vector<int> where(m, -1);
    for (int col = 0, row = 0; col < m && row < n; ++col) {
        // find pivot row
        int sel = row;
        while (sel < n && !a[sel][col]) ++sel;
        if (sel == n) continue;
        swap(a[sel], a[row]);
        where[col] = row;
        // eliminate other rows
        for (int i = 0; i < n; ++i) {
            if (i != row && a[i][col])
                a[i] ^= a[row];
        }
        ++row;
    }
    // back substitution
    ans.reset();
    for (int i = 0; i < m; ++i) {
        if (where[i] != -1)
            ans[i] = a[where[i]][m];
    }
    // check consistency
    for (int i = 0; i < n; ++i) {
        bool sum = a[i][m];
        for (int j = 0; j < m; ++j)
            if (ans[j] && a[i][j]) sum = !sum;
        if (sum) return 0; // no solution
    }
    return 1; // success
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<bitset<MAXM>> a(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= m; ++j) {
            int bit;
            cin >> bit;
            a[i][j] = bit;
        }
    }

    bitset<MAXM> ans;
    if (!gauss_bitset(a, n, m, ans)) {
        cout << "No solution\n";
    } else {
        for (int i = 0; i < m; ++i)
            cout << ans[i];
        cout << '\n';
    }
    return 0;
}
