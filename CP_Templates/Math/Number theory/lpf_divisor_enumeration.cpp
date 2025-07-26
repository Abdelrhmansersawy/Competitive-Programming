/*
 * ============================ DIVISORS NOTE ============================
 *
 * Given x, uses its least-prime-factor table (`lpf`) to enumerate
 * all positive divisors of x in roughly O(τ(x)) time, where τ is
 * the divisor function.
 *
 * 1. Repeatedly extract a prime factor f = lpf[x] and its exponent cnt.
 * 2. Starting from divisor list {1}, for each k = 1…cnt, multiply existing
 *    divisors by f^k and append.
 * 3. Return the completed list.
 * ======================================================================
 */
 
 /*
 * ======================== MEMORY NOTE ========================
 *
 * We may sieve up to n ≤ 1e7, which requires lpf array of size n+1.
 * An `int` array of size 1e7+1 uses about 40MB—acceptable but large.
 * However, we will only call getDivs() for up to 1e5 elements,
 * so factorization work is limited to those queries.
 * Consider optimizing lpf storage (e.g., smaller types) if memory is tight.
 * ============================================================
 */
 
vector<int> getDivs(int x) {
    vector<int> divs = {1};

    // Factor x by its lpf, grouping exponents
    while (x > 1) {
        int f = lpf[x];
        int cnt = 0;
        while (x % f == 0) {
            x /= f;
            cnt++;
        }
        int sz = divs.size();
        int mul = 1;
        // For each power f^k, k=1..cnt
        for (int k = 1; k <= cnt; k++) {
            mul *= f;
            for (int i = 0; i < sz; i++) {
                divs.push_back(divs[i] * mul);
            }
        }
    }

    return divs;
}
