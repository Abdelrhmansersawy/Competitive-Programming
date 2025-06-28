/**
 * Lowest Prime Factor (LPF) Sieve in Range [L, R]
 * -----------------------------------------------
 * This function computes the lowest prime factor for every number in a given range [L, R].
 * It uses a segmented sieve-like approach without generating primes explicitly.
 *
 * For each number x in [L, R], it finds the smallest prime p such that p divides x.
 * If a number is prime, its LPF is the number itself.
 *
 * LPF of 1 is conventionally set to 1.
 *
 * Time Complexity:
 *     O((R − L + 1) * log(R) + √R)
 *
 * This is similar to the segmented sieve without pre-generated primes in performance.
 *
 * @param L The start of the range (inclusive).
 * @param R The end of the range (inclusive).
 * @return A vector<long long> where the element at index i is the lowest prime factor of (L + i).
 */
vector<long long> lowestPrimeFactorSieve(long long L, long long R) {
    // Initialize LPF array: 0 means not marked yet
    vector<long long> lpf(R - L + 1, 0);
    long long lim = sqrt(R);

    // For each number i from 2 to sqrt(R), mark its multiples in [L, R]
    for (long long i = 2; i <= lim; ++i)
        for (long long j = max(i * i, (L + i - 1) / i * i); j <= R; j += i)
            if (lpf[j - L] == 0)
                lpf[j - L] = i;

    // Any number that remains unmarked is prime: its LPF is itself
    for (long long k = 0; k <= R - L; ++k)
        if (lpf[k] == 0)
            lpf[k] = L + k;

    // Special case: LPF of 1 is 1 by convention
    if (L == 1)
        lpf[0] = 1;

    return lpf;
}
