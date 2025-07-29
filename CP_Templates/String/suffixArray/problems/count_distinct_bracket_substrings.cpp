#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// ======================= Bracket‑Sequence Substring Count =======================
// Problem: Count the number of distinct non‑empty substrings of s that form correct bracket sequences.
// Given a string s of length n, count each non‑empty valid parenthesis sequence that appears as a contiguous substring.
// Uses suffix array + LCP to quickly find, for each opening '(', the range of matching closing ')' positions.
// Time complexity: O(n log n) (for SA + binary searches), Memory: O(n).
// ============================================================================

int main() {
    ios::sync_with_stdio(false);

    int n;
    string s;
    cin >> n >> s;

    auto p   = buildSuffixArray(s);
    vector<int> where(n);
    for (int i = 0; i < n; ++i) where[p[i]] = i;
    auto lcp = Kasai(s, p);

    // prefix balance maps: positions of each balance value
    map<int, vector<int>> open, close;
    int bal = 0;
    for (int i = 0; i < n; ++i) {
        bal += (s[i] == '(' ? 1 : -1);
        if (s[i] == '(') open[bal].push_back(i);
        else               close[bal].push_back(i);
    }

    ll ans = 0;
    // for each balance level, match opens with closes at level-1, avoiding bad closes
    for (auto &entry : open) {
        int level = entry.first;
        auto &vecL    = entry.second;        // positions of '('
        auto &vecR    = close[level-1];     // matching ')'
        auto &vecBad  = close[level-2];     // positions that break validity
        if (vecR.empty()) continue;

        // two-pointer on vecL
        for (int posL : vecL) {
            int sa_idx = where[posL];
            int left   = posL + (sa_idx ? lcp[sa_idx-1] : 0);

            // compute rightmost valid end before next bad ')'
            int right;
            auto itBad = lower_bound(vecBad.begin(), vecBad.end(), posL);
            right = (itBad == vecBad.end() ? n-1 : *itBad - 1);

            if (left <= right) {
                int cnt = int(upper_bound(vecR.begin(), vecR.end(), right)
                              - lower_bound(vecR.begin(), vecR.end(), left));
                ans += cnt;
            }
        }
    }

    cout << ans << '\n';
    return 0;
}
