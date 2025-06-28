/**
 * Segmented Sieve of Eratosthenes
 * --------------------------------
 * Sometimes we need to find all prime numbers in a range [L, R] of small size 
 * (e.g. R − L + 1 ≈ 1e7), where R can be very large (e.g. 1e12).
 *
 * To solve such a problem, we can use the idea of the Segmented sieve. 
 * We pre-generate all prime numbers up to √R, and use those primes to mark 
 * all composite numbers in the segment [L, R].
 *
 * Time complexity of this approach is:
 *     O((R − L + 1) * log log(R) + √R * log log(√R))
 *
 * @param L The start of the range (inclusive).
 * @param R The end of the range (inclusive).
 * @return A vector<char> where isPrime[i] is true if (L + i) is prime.
 */
vector<char> segmentedSieve(long long L, long long R) {
    // Generate all primes up to sqrt(R)
    long long lim = sqrt(R);
    vector<char> mark(lim + 1, false);
    vector<long long> primes;

    // Standard Sieve of Eratosthenes to find primes ≤ sqrt(R)
    for (long long i = 2; i <= lim; ++i) {
        if (!mark[i]) {
            primes.emplace_back(i);
            for (long long j = i * i; j <= lim; j += i)
                mark[j] = true;
        }
    }

    // Initialize all numbers in range [L, R] as prime
    vector<char> isPrime(R - L + 1, true);

    // Mark non-primes in [L, R] using the primes found
    for (long long i : primes)
        for (long long j = max(i * i, (L + i - 1) / i * i); j <= R; j += i)
            isPrime[j - L] = false;

    // Special case: 1 is not prime
    if (L == 1)
        isPrime[0] = false;

    return isPrime;
}
