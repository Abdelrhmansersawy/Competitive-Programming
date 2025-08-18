/*
   Miller-Rabin + Next Prime
   ---------------------------
   - Fast deterministic primality test (64-bit safe)
   - Find the smallest prime > n

   Complexity:
     MillerRabin: O(log n)
     next_prime: O((gap) * log n)
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using u64 = uint64_t;
using u128 = __uint128_t;

// ---------------- Modular Exponentiation ----------------
u64 binpower(u64 base, u64 exp, u64 mod) {
    u64 res = 1;
    base %= mod;
    while (exp) {
        if (exp & 1) res = (u128)res * base % mod;
        base = (u128)base * base % mod;
        exp >>= 1;
    }
    return res;
}

// ---------------- Composite Check ----------------
bool check_composite(u64 n, u64 a, u64 d, int r) {
    u64 x = binpower(a, d, n);
    if (x == 1 || x == n-1) return false;
    for (int i = 1; i < r; i++) {
        x = (u128)x * x % n;
        if (x == n-1) return false;
    }
    return true;
}

// ---------------- Miller-Rabin Test ----------------
bool MillerRabin(u64 n) {
    if (n < 2) return false;

    int r = 0;
    u64 d = n-1;
    while ((d & 1) == 0) d >>= 1, r++;

    for (u64 a : {2,3,5,7,11,13,17,19,23,29,31,37}) {
        if (n == a) return true;
        if (check_composite(n, a, d, r)) return false;
    }
    return true;
}

// ---------------- Next Prime Finder ----------------
ll next_prime(ll n) {
    n++;
    if (n <= 2) return 2;
    if (n % 2 == 0) n++;
    while (!MillerRabin(n)) n += 2;
    return n;
}

// ---------------- Main ----------------
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int tc; cin >> tc;
    while (tc--) {
        ll n; cin >> n;
        cout << next_prime(n) << "\n";
    }
}
