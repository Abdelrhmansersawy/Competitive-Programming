/*
 * ---------------------------------------------------------------
 *  Lucas' Theorem
 * ---------------------------------------------------------------
 *  Lucas' Theorem helps compute binomial coefficients modulo a 
 *  prime number `p`. It is especially useful when `n` and `r` are large.
 *
 *  Applications:
 *  - Determine for which m and n, C(m, n) is even.
 *  - Efficiently compute C(n, r) % p, where p is a prime.
 *  - Solve problems involving divisibility in Pascal's Triangle:
 *      - How many entries in row m are divisible by p?
 *          → Answer: Total entries = m + 1. Entries NOT divisible by p = Π (m_i + 1),
 *            where m_i are the digits of m in base p. So, divisible entries = (m + 1) - Π (m_i + 1).
 *
 *      - Which entries are not divisible by p?
 *          → Answer: C(m, r) is NOT divisible by p if and only if ∀i: r_i ≤ m_i,
 *            where m and r are expressed in base p as (m_k, ..., m_0) and (r_k, ..., r_0).
 *
 *      - What are the entries modulo p?
 *          → Answer: For each C(m, r), write m and r in base p, then:
 *            C(m, r) ≡ Π C(m_i, r_i) mod p, where the product is over all digits i,
 *            and each small C(m_i, r_i) is computed normally modulo p.
 *
 *  Theorem:
 *      Given a prime p and non-negative integers n, r,
 *      Let n = n_k * p^k + ... + n_1 * p + n_0
 *          r = r_k * p^k + ... + r_1 * p + r_0
 *      Then:
 *          C(n, r) % p = Π C(n_i, r_i) % p
 *      where C(n_i, r_i) = 0 if r_i > n_i.
 *
 * ---------------------------------------------------------------
 */

const int mod = 1e6 + 3;
ll fact[mod];
ll inv[mod]; //mod inverse for i
ll invfact[mod]; //mod inverse for i!
void init() {
    fact[0] = inv[1] = fact[1] = invfact[0] = invfact[1] = 1;
    for (long long i = 2; i < mod; i++) {
        fact[i] = (fact[i - 1] * i) % mod;
        inv[i] = mod - (inv[mod % i] * (mod / i) % mod);
        invfact[i] = (inv[i] * invfact[i - 1]) % mod;
    }
}
ll nCr(int n, int r) {
    if(r > n || n < 0 || r < 0) return 0; // manual handling
    return (((fact[n] * invfact[r]) % mod) * invfact[n - r]) % mod;
}
int lucas(int n , int r){
	if(r == 0) return 1;
	int res = 1;
	while(r){
		res = 1LL * res * nCr(n % mod , r % mod) % mod;
		n /= mod; r/= mod;
	}
	return res;
}
