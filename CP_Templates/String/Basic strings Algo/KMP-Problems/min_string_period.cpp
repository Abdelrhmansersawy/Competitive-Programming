#include <bits/stdc++.h>
using namespace std;

#include <bits/stdc++.h>
using namespace std;

/*
 * ===================== MINIMAL PERIOD OF STRING =====================
 * Return the smallest period p of s (smallest p > 0 such that s is composed
 * of repetitions of s[0..p-1]). If no proper period exists, return n.
 * Uses KMP prefix-function. Complexity: O(n).
 *
 * NOTE:
 *  - Once the string is NOT a repetition (period == n):
 *      * All N rotations give different strings.
 *
 *  - But you must still check if an inversion + rotation gives the same string
 *    (e.g. compare reverse(s) with some rotation of s).
 *
 *  - These rules describe what's known as the *Dihedral Group* —
 *    the group of all rotations and reflections of a regular polygon.
 *
 *  - Reducing Repeated Strings:
 *      If S = A^k (A repeated k times), then for any transformation f 
 *      (rotation or reflection):
 *          f(S) = f(A)^k
 *
 *      ⇒ Transformations that fix S are exactly those that fix A.
 *      ⇒ Therefore, the problem can be reduced to analyzing the smallest
 *         non-repetitive unit A (found using KMP as the smallest period).
 *
 *      Once you know which transformations are valid for A, you can extend
 *      the result to S (since each copy behaves identically).
 *
 *      To count or combine results efficiently (e.g. counting valid rotation–reflection
 *      pairs), you can use a Prefix Sum over the computed transformation states.
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

