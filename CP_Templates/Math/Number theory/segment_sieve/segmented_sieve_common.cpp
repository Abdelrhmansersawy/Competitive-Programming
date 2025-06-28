/**
 * Segmented Sieve without Pre-generating Primes
 * ---------------------------------------------
 * It's also possible to find primes in [L, R] without generating all primes up to √R.
 * This method directly marks non-primes in the range using every number from 2 to √R.
 *
 * Time Complexity:
 *     O((R − L + 1) * log(R) + √R)
 * 
 * Although the theoretical complexity is worse than the version with pre-generated primes,
 * this method still runs very fast in practice.
 *
 * @param L The start of the range (inclusive).
 * @param R The end of the range (inclusive).
 * @return A vector<char> where isPrime[i] is true if (L + i) is prime.
 */
vector<char> segmentedSieveNoPreGen(long long L, long long R) {
    vector<char> isPrime(R - L + 1, true);
    long long lim = sqrt(R);

    // Directly try every number from 2 to sqrt(R)
    for (long long i = 2; i <= lim; ++i)
        for (long long j = max(i * i, (L + i - 1) / i * i); j <= R; j += i)
            isPrime[j - L] = false;

    // Special case: 1 is not a prime
    if (L == 1)
        isPrime[0] = false;

    return isPrime;
}
