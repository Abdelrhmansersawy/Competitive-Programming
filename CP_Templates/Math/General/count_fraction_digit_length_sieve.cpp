/**
 * -----------------------------------------------------------------------------
 * DECIMAL REPRESENTATION: A / B
 * Total Digits = Int_Len + NonRep_Len + Rep_Len
 * 1. Int Part: floor(log10(A/B)) + 1
 * 2. Non-Rep:  max(v2(B), v5(B)) -> Factors of 2 and 5 delay the cycle
 * 3. Rep Part: Order of 10 mod K    -> K is B stripped of 2 and 5
 * -----------------------------------------------------------------------------
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 100005; // Set to max possible Value of A_i
int spf[MAXN];

// Call this once in main!
void sieve() {
    iota(spf, spf + MAXN, 0);
    for (int i = 2; i * i < MAXN; i++) 
        if (spf[i] == i) 
            for (int j = i * i; j < MAXN; j += i) 
                if (spf[j] == j) spf[j] = i;
}

ll pm(ll b, ll p, ll m) {
    ll r = 1;
    for (; p; p >>= 1, b = (__int128)b * b % m)
        if (p & 1) r = (__int128)r * b % m;
    return r;
}

// O(log N) using SPF
int get_phi(int n) {
    int res = n;
    while (n > 1) {
        int p = spf[n];
        while (n % p == 0) n /= p;
        res -= res / p;
    }
    return res;
}

ll solve_optimized(int A, int B) {
    int g = std::gcd(A, B); A /= g; B /= g;

    // 1. Integer Part
    ll ans = (A >= B ? to_string(A / B).size() : 1);

    // 2. Non-Repeating
    int v2 = 0, v5 = 0;
    while (B % 2 == 0) B /= 2, v2++;
    while (B % 5 == 0) B /= 5, v5++;
    ans += max(v2, v5);

    // 3. Repeating (B is now K) 

    if (B > 1) {
        int phi = get_phi(B), L = phi, temp = phi;
        
        // Use SPF to iterate prime factors of phi instantly
        while (temp > 1) {
            int p = spf[temp];
            while (temp % p == 0) temp /= p;
            
            // Greedily remove prime factor p from L
            while (L % p == 0 && pm(10, L / p, B) == 1) L /= p;
        }
        ans += L;
    }
    return ans;
}
