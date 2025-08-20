#include <bits/stdc++.h>
using namespace std;
using ll = long long;


/*
 * k-Convolution of Catalan Numbers (C^{(k)}_n)
 * --------------------------------------------
 *
 * Closed Formula:
 *   C^{(k)}_n = ((k+1) / (n+k+1)) * binom(2n+k, n)
 *
 * Recurrence Relation:
 *   C^{(k)}_0 = 1
 *   C^{(k)}_n = ((2n+k-1) * (2n+k)) / (n * (n+k+1)) * C^{(k)}_{n-1}
 *
 * Key Facts:
 *   - When k = 0 → Catalan numbers.
 *   - Counts valid bracket sequences of length (2n+k)
 *     with a prefix offset of k extra opens.
 */

const int MOD = 1000000007;

long long int inverse(long long int i){
    if(i==1) return 1;
    return (MOD - ((MOD/i)*inverse(MOD%i))%MOD + MOD) % MOD;
}

// paste this above main()
long long catalan_k(int rem_len, int bal) {
    // rem_len = remaining characters after prefix (must be even)
    // bal = current balance (#open - #close) from prefix
    if (rem_len < 0) return 0;
    if (bal < 0) return 0;
    if (rem_len % 2) return 0;
    int m = rem_len / 2;          // remaining pairs to place
    int up = 2 * m + bal;         // we need factorials up to (2m + bal)

    // compute factorials 0..up
    vector<long long> fact(up + 1);
    fact[0] = 1;
    for (int i = 1; i <= up; ++i) fact[i] = fact[i-1] * i % MOD;

    // C^{(bal)}_m = (k+1)/(m+k+1) * binom(2m+bal, m)
    // binom(2m+bal, m) = fact[up] / (fact[m] * fact[m+bal])
    long long ans = fact[up];
    ans = ans * inverse(fact[m]) % MOD;         // divide by m!
    ans = ans * inverse(fact[m + bal]) % MOD;   // divide by (m+bal)!
    ans = ans * ((bal + 1) % MOD) % MOD;        // multiply (k+1)
    ans = ans * inverse((m + bal + 1) % MOD) % MOD; // divide (m+k+1)
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    #ifndef ONLINE_JUDGE
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
        freopen("error.txt", "w", stderr);
    #endif

    int total_len;
    string s;
    if (!(cin >> total_len >> s)) return 0;

    // total length must be even, otherwise impossible
    if (total_len % 2) { cout << 0 << '\n'; return 0; }

    int pairs = total_len / 2; // total number of pairs
    int cnt = 0;               // balance after prefix (opens - closes)
    int opens_in_prefix = 0;
    for (char ch : s) {
        if (ch == '(') { cnt++; opens_in_prefix++; }
        else cnt--;
        if (cnt < 0) { cout << 0 << '\n'; return 0; }
    }

    int rem_pairs = pairs - opens_in_prefix; // remaining pairs to place
    if (rem_pairs < 0) { cout << 0 << '\n'; return 0; }
    int rem_len = 2 * rem_pairs; // remaining characters corresponding to full pairs

    cout << catalan_k(rem_len, cnt) << "\n";
    return 0;
}
