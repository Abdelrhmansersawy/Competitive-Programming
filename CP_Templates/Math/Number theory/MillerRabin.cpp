/*
   Miller-Rabin + Next Prime
   ---------------------------
   - Fast deterministic primality test (64-bit safe)

   Complexity:
     MillerRabin: O(log n)
*/

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
