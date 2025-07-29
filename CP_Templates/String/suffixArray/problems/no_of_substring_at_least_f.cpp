/*
================================= ANUSAR - CodeChef ================================
Problem link: https://www.codechef.com/problems/ANUSAR

Given:
- A string S of length n.
- Multiple queries, each with an integer Fi.

Task:
- For each Fi, output the number of **contiguous substrings** that appear at least Fi times.
- Substrings are considered distinct if they start at different indices or have different lengths.

Approach:
- Suffix Array + LCP Array
- Group LCP values to calculate how many substrings occur exactly f times.
- Preprocess frequency counts for all f = [1, n]
====================================================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// ===== Build Suffix Array using Doubling Algorithm =====
vector<int> buildSuffixArray(const string &s) {
    int n = s.size(), N = max(256, n + 1);
    vector<int> sa(n), rank(n), tmp(n), cnt(N);
    iota(sa.begin(), sa.end(), 0);
    for (int i = 0; i < n; ++i) rank[i] = s[i];

    for (int len = 1;; len <<= 1) {
        auto cmp = [&](int i, int j) {
            if (rank[i] != rank[j]) return rank[i] < rank[j];
            int ri = (i + len < n ? rank[i + len] : -1);
            int rj = (j + len < n ? rank[j + len] : -1);
            return ri < rj;
        };

        sort(sa.begin(), sa.end(), cmp);

        tmp[sa[0]] = 0;
        for (int i = 1; i < n; ++i)
            tmp[sa[i]] = tmp[sa[i - 1]] + cmp(sa[i - 1], sa[i]);

        rank = tmp;
        if (rank[sa[n - 1]] == n - 1) break;
    }

    return sa;
}

// ===== Build LCP Array (Kasai’s Algorithm) =====
vector<int> buildLCP(const string &s, const vector<int> &sa) {
    int n = s.size();
    vector<int> lcp(n - 1), rank(n);
    for (int i = 0; i < n; ++i) rank[sa[i]] = i;

    int h = 0;
    for (int i = 0; i < n; ++i) {
        if (rank[i]) {
            int j = sa[rank[i] - 1];
            while (i + h < n && j + h < n && s[i + h] == s[j + h]) ++h;
            lcp[rank[i] - 1] = h;
            if (h) --h;
        }
    }
    return lcp;
}

// ===== Nearest Smaller to Left and Right using Monotonic Stack =====
pair<vector<int>, vector<int>> getMinBounds(const vector<int>& arr) {
    int n = arr.size();
    vector<int> left(n), right(n), st;
    st.reserve(n);

    // Left boundaries
    for (int i = 0; i < n; i++) {
        while (!st.empty() && arr[st.back()] > arr[i]) st.pop_back();
        left[i] = st.empty() ? -1 : st.back();
        st.push_back(i);
    }

    // Right boundaries
    st.clear();
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && arr[st.back()] >= arr[i]) st.pop_back();
        right[i] = st.empty() ? n : st.back();
        st.push_back(i);
    }

    return {left, right};
}

// ===== Solve One Test Case =====
void solve() {
    string s;
    cin >> s;
    int n = s.size();

    auto p = buildSuffixArray(s);
    auto lcp = buildLCP(s, p);
    auto [L, R] = getMinBounds(lcp);

    vector<ll> frq(n + 9);
    vector<vector<int>> group(n + 1);
    for (int i = 0; i < n + 1; i++) group[i].reserve(n / 2);

    // Group LCP values by height
    for (int i = 0; i < (int)lcp.size(); ++i) {
        group[lcp[i]].push_back(i);
    }

    /*
        ====================== LCP Group Contribution ======================
        - We iterate over all LCP lengths in decreasing order.
        - For each group of LCP == len, we determine the range [L[x], R[x]] 
          where all suffixes share a common prefix of length >= len.

        - For each such group:
            * Let f = r - l → the frequency (how many suffixes in this group)
            * Compute the minimal extension `minh` we can go beyond len,
              by checking surrounding LCP values (left and right neighbors).
            * Add f * minh to frq[f] → meaning f substrings occur with that extension.

        - Skip all processed positions in the group to avoid repetition.
    */
    for (int len = n; len > 0; --len) {
        for (size_t j = 0; j < group[len].size();) {
            int x = group[len][j];
            int l = L[x], r = R[x];
            int f = r - l;
            int minh = len;

            if (l >= 0) minh = min(minh, len - lcp[l]);
            if (r < (int)lcp.size()) minh = min(minh, len - lcp[r]);

            frq[f] += 1LL * f * minh;

            // Skip over processed group
            while (j < group[len].size() && group[len][j] <= r) ++j;
        }
    }

    // ===== Build suffix frequency for ≥f queries =====
    for (int i = n - 1; i > 1; --i) frq[i] += frq[i + 1];
    frq[1] = 1LL * n * (n + 1) / 2; // Total substrings = n(n+1)/2

    // ===== Answer Queries =====
    int q;
    cin >> q;
    while (q--) {
        int x;
        cin >> x;
        cout << (x > s.size() ? 0 : frq[x]) << '\n';
    }
}

// ===== Driver =====
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tc;
    cin >> tc;
    while (tc--) solve();

    return 0;
}
