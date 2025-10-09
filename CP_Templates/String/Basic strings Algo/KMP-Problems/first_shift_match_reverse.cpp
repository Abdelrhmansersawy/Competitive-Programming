#include <bits/stdc++.h>
using namespace std;

/*
 * =============== FIRST SHIFT TO MATCH REVERSE ===============
 * Find smallest cyclic shift k where rotate_left(s, k) == reverse(s).
 * Build pat = reverse(s) + '#' + s + s and use KMP prefix function.
 * When full match (pi[i] == |s|) found in s+s → return shift = i - 2*|s|.
 * If none found → return -1.
 * Complexity: O(n)
 * ============================================================
 */

#define all(x) (x).begin(), (x).end()

int getFirstShift(string &s){
    string sr = s;
    reverse(all(sr));
    string pat = sr + "#" + s + s;
    int n = pat.size();
    vector<int> pi(n);
    for (int i = 1; i < n; ++i) {
        int j = pi[i - 1];
        while (j && pat[i] != pat[j]) j = pi[j - 1];
        if (pat[i] == pat[j]) ++j;
        pi[i] = j;
        if (i >= 2 * s.size() && pi[i] == (int)s.size())
            return i - 2 * s.size();
    }
    return -1;
}
