/**
 * -----------------------------------------------------------------------------
 * DECIMAL REPRESENTATION TRICK: A / B
 * -----------------------------------------------------------------------------
 * PRE-REQ: Simplify the fraction first! -> g = gcd(A, B), A/=g, B/=g.
 * Total Digits = Len_Int + Len_NonRep + Len_Rep
 *
 * 1. INTEGER PART (Magnitude)
 * Formula: floor(log10(A / B)) + 1
 * Note: If A < B, value is 0.xxx, so integer part length is 1 ('0').
 *
 * 2. NON-REPEATING PART (Transient / Pre-Period)
 * Formula: max(v2(B), v5(B))
 * Logic:   Removes factors of 10 (2*5) from denominator.
 * v_p(x) is the exponent of prime p in factorization of x.
 *
 * 3. REPEATING PART (Period / Cycle)
 * Formula: Order_K(10)
 * Let K = B / (2^v2(B) * 5^v5(B))  -> Denom stripped of 2s and 5s.
 * Logic:   Smallest L >= 1 such that 10^L ≡ 1 (mod K).
 * (Discrete Logarithm / Multiplicative Order).
 * -----------------------------------------------------------------------------
 */


using ll = long long;

ll pm(ll b, ll p, ll m) { // Power Mod
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

// A/B Digits:
// 1. Int: to_string(A/B).size()
// 2. Non-Rep: max(v2(B), v5(B))
// 3. Rep: Order of 10 mod (B stripped of 2,5)
// *Simplify gcd(A,B) first!
ll solve_digits(ll A, ll B) {
    ll g = std::gcd(A, B); A /= g; B /= g;
    
    // 1. Integer Part
    ll ans = to_string(A / B).size();

    // 2. Non-Repeating
    int v2 = 0, v5 = 0;
    while (B % 2 == 0) B /= 2, v2++;
    while (B % 5 == 0) B /= 5, v5++;
    ans += max(v2, v5);

    // 3. Repeating (B is now K)
    if (B > 1) {
        ll phi = get_phi(B), L = phi;
        for (ll i = 1; i * i <= phi; ++i) {
            if (phi % i == 0) {
                if (pm(10, i, B) == 1) L = min(L, i);
                if (pm(10, phi / i, B) == 1) L = min(L, phi / i);
            }
        }
        ans += L;
    }
    return ans;
}
