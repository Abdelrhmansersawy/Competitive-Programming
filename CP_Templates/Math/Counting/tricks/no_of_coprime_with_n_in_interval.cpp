// Counts the number of integers in [1; r] that are coprime with n.
// Uses Inclusion-Exclusion over the prime factors of n.
/**
 * Instead of directly counting the coprime numbers, we solve the inverse problem:
 * count the number of integers in [1; r] that are not coprime with n.
 *
 * Let the prime factors of n be p_i (i = 1..k). The number of integers in [1; r]
 * divisible by a prime p_i is floor(r / p_i). However, simply summing these will overcount
 * those divisible by multiple primes. So, we apply the Inclusion-Exclusion Principle:
 *   - Iterate over all 2^k subsets of p_i.
 *   - For each subset, calculate the product of primes.
 *   - Add or subtract floor(r / product) depending on the subset size.
 *
 * Finally, subtract the count of non-coprime numbers from r.
 * Time complexity: O(sqrt(n))
 */

int solve (int n, int r) {
    vector<int> p;
    for (int i=2; i*i<=n; ++i)
        if (n % i == 0) {
            p.push_back (i);
            while (n % i == 0)
                n /= i;
        }
    if (n > 1)
        p.push_back (n);

    int sum = 0;
    for (int msk=1; msk<(1<<p.size()); ++msk) {
        int mult = 1,
            bits = 0;
        for (int i=0; i<(int)p.size(); ++i)
            if (msk & (1<<i)) {
                ++bits;
                mult *= p[i];
            }

        int cur = r / mult;
        if (bits % 2 == 1)
            sum += cur;
        else
            sum -= cur;
    }

    return r - sum;
}
