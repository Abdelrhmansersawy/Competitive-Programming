#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/**
 * -----------------------------------------------------------------------------
 * DECIMAL REPRESENTATION: A / B
 * Total Digits = Int_Len + NonRep_Len + Rep_Len
 * 1. Int Part: floor(log10(A/B)) + 1
 * 2. Non-Rep:  max(v2(B), v5(B)) -> Factors of 2 and 5 delay the cycle
 * 3. Rep Part: Order of 10 mod K    -> K is B stripped of 2 and 5
 * -----------------------------------------------------------------------------
 */

ll pm(ll b, ll p, ll m) { // Power Mod with __int128 safety
    ll r = 1; 
    for (; p; p >>= 1, b = (__int128)b * b % m) 
        if (p & 1) r = (__int128)r * b % m;
    return r;
}

ll get_phi(ll n) {
    ll r = n;
    for (ll i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            while (n % i == 0) n /= i;
            r -= r / i;
        }
    }
    if (n > 1) r -= r / n;
    return r;
}

ll solve_general(ll A, ll B) {
    // 0. Simplify
    ll g = gcd(A, B); A /= g; B /= g;
    
    // 1. Integer Part (Handle A < B case implicitly via string)
    ll ans = (A >= B ? to_string(A / B).size() : 1);

    // 2. Non-Repeating: max(v2, v5)
    int v2 = 0, v5 = 0;
    while (B % 2 == 0) B /= 2, v2++;
    while (B % 5 == 0) B /= 5, v5++;
    ans += max(v2, v5);

    // 3. Repeating: Multiplicative Order of 10 mod K (B is now K)
    if (B > 1) {
        ll phi = get_phi(B), L = phi, temp = phi;
        // Prime Reduction: Factorize phi and greedily reduce L
        for (ll i = 2; i * i <= temp; ++i) {
            if (temp % i == 0) {
                while (temp % i == 0) temp /= i;
                while (L % i == 0 && pm(10, L / i, B) == 1) L /= i;
            }
        }
        if (temp > 1) 
            while (L % temp == 0 && pm(10, L / temp, B) == 1) L /= temp;
        ans += L;
    }
    return ans;
}
