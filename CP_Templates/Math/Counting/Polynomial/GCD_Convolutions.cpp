/*
Given integer sequences a1,...,aN and b1,...,bN.
Calculate integer sequence c1,...,cN as follows:

    c_k = sum_{ gcd(i, j) = k } a_i * b_j  (mod 998244353)

Constraints
    1 ≤ N ≤ 10^6
    0 ≤ a_i, b_i < 998244353

Time complexity:
    - PrimeEnumerate (linear sieve): O(n)
    - Multiple Zeta / Mobius transforms:
        sum_{p <= n} floor(n / p) = n * sum_{p <= n} 1/p = O(n log log n)
    - Pointwise multiplication: O(n)
    => Overall time: O(n log log n)

Space complexity:
    - O(n) (arrays for A, B, and C, plus sieve memory)

Problem link: https://judge.yosupo.jp/problem/gcd_convolution
*/

#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using i64 = long long;
using mod = long long;

constexpr int MOD = 998'244'353;

inline mod norm(i64 x) {
    x %= MOD;
    if (x < 0) x += MOD;
    return (mod)x;
}
inline mod add_mod(mod a, mod b) {
    mod s = a + b;
    if (s >= MOD) s -= MOD;
    return s;
}
inline mod sub_mod(mod a, mod b) {
    mod s = a - b;
    if (s < 0) s += MOD;
    return s;
}
inline mod mul_mod(mod a, mod b) {
    return (mod)((i64)a * b % MOD);
}

/* Linear Sieve, O(n) */
vector<int> PrimeEnumerate(int n) {
    vector<int> P; P.reserve(max(0, n/10));
    vector<char> is_prime(n + 1, 1);
    if (n >= 0) is_prime[0] = 0;
    if (n >= 1) is_prime[1] = 0;
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) P.push_back(i);
        for (int p : P) {
            long long v = (long long)i * p;
            if (v > n) break;
            is_prime[v] = 0;
            if (i % p == 0) break;
        }
    }
    return P;
}

void MultipleZetaTransform(vector<mod>& v) {
    const int n = (int)v.size() - 1;
    for (int p : PrimeEnumerate(n)) {
        for (int i = n / p; i >= 1; i--)
            v[i] = add_mod(v[i], v[i * p]);
    }
}

void MultipleMobiusTransform(vector<mod>& v) {
    const int n = (int)v.size() - 1;
    for (int p : PrimeEnumerate(n)) {
        for (int i = 1; i * p <= n; i++)
            v[i] = sub_mod(v[i], v[i * p]);
    }
}

vector<mod> GCDConvolution(vector<mod> A, vector<mod> B) {
    MultipleZetaTransform(A);
    MultipleZetaTransform(B);
    for (int i = 0; i < (int)A.size(); i++) A[i] = mul_mod(A[i], B[i]);
    MultipleMobiusTransform(A);
    return A;
}

int main() {
    fastio;
    int n;
    if (!(cin >> n)) return 0;
    vector<mod> A(n + 1, 0), B(n + 1, 0);
    for (int i = 1; i <= n; i++) { i64 t; cin >> t; A[i] = norm(t); }
    for (int i = 1; i <= n; i++) { i64 t; cin >> t; B[i] = norm(t); }
    auto C = GCDConvolution(A, B);
    for (int i = 1; i <= n; i++) {
        cout << C[i] << (i == n ? '\n' : ' ');
    }
    return 0;
}
