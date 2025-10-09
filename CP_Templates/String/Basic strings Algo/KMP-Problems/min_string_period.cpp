#include <bits/stdc++.h>
using namespace std;

/*
 * ===================== MINIMAL PERIOD OF STRING =====================
 * Return the smallest period p of s (smallest p > 0 such that s is composed
 * of repetitions of s[0..p-1]). If no proper period exists, return n.
 * Uses KMP prefix-function. Complexity: O(n).
 *
 * NOTE:
 *  - Once the string is NOT a repetition (i.e. period == n), something nice happens:
 *      * All N rotations give different strings.
 *  - However, when solving problems that allow inversion+rotation, you MUST still
 *    check whether any inversion (reverse) followed by a rotation produces the same string.
 *    That case is not covered by the period check above and needs a separate test
 *    (e.g. KMP on reverse(s) over s+s or use getFirstShift).
 * ================================================================
 */

int getPeriod(const string &s){
    int n = (int)s.size();
    vector<int> pi(n, 0);
    for (int i = 1; i < n; ++i) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j]) j = pi[j-1];
        if (s[i] == s[j]) ++j;
        pi[i] = j;
    }
    int p = n - pi[n-1];
    if (n % p != 0) p = n;
    return p;
}
