/*
 * ======================= BERLEKAMP-MASSEY NOTE =======================
 *
 * Finds minimal linear recurrence for a given sequence modulo MOD.
 * Then computes the nth term efficiently (0-based).
 *
 * Key ideas:
 *   1. Berlekamp-Massey algorithm finds shortest recurrence c[0..m-1] s.t.
 *        S[n] = c[0]*S[n-1] + ... + c[m-1]*S[n-m]
 *   2. Polynomial exponentiation ("combine") allows us to get nth term
 *      in O(m^2 log n) time without iterating all terms.
 *
 * Usage:
 *   - Provide initial samples S[0..k-1]
 *   - Call nth_BM(samples, n) to get S[n] modulo MOD
 *
 * Examples:
 *   Fibonacci:
 *     vector<int> fib = {0,1,1,2,3,5,8,13};
 *     nth_BM(fib, 10); // returns 55
 *
 *   Tribonacci:
 *     vector<int> tri = {0,0,1,1,2,4,7};
 *     nth_BM(tri, 10); // returns 44
 *
 *   Any linear recurrence:
 *     e.g., S[n] = 2*S[n-1] + 3*S[n-2]; provide first few terms
 *
 * Benefits:
 *   - Compute nth term without iterating all previous terms
 *   - Handles huge n (up to ~1e18)
 *   - Useful for ICPC / competitive programming problems involving 
 *     linear recurrence sequences
 *
 * ICPC tip:
 *   - Make sure MOD is prime for modular inverse
 *   - Provide enough samples to detect the recurrence
 * ====================================================================
 */


// --- mod helpers ---
constexpr int MOD = 1e9 + 7;
inline int norm(int x){ x %= MOD; if (x < 0) x += MOD; return x; }
inline int addm(int a, int b){ a += b; if (a >= MOD) a -= MOD; return a; }
inline int subm(int a, int b){ a -= b; if (a < 0) a += MOD; return a; }
inline int mulm(int a, int b){ return int((1LL * a * b) % MOD); }
inline int mod_pow(int a, ll e){
    int r = 1 % MOD;
    a = norm(a);
    while (e){
        if (e & 1LL) r = mulm(r, a);
        a = mulm(a, a);
        e >>= 1LL;
    }
    return r;
}
inline int inv(int a){ return mod_pow(norm(a), MOD - 2); }

// --- Berlekamp-Massey: minimal linear recurrence ---
inline vector<int> berlekamp_massey(const vector<int>& s){
    vector<int> C{1}, B{1};
    int b = 1, L = 0, m = 1;
    const int nmax = (int)s.size();

    for (int n = 0; n < nmax; ++n){
        int d = 0;
        for (int i = 0; i <= L; ++i) d = addm(d, mulm(C[i], s[n - i]));
        if (d == 0){ ++m; continue; }

        vector<int> T = C;
        int coef = mulm(d, inv(b));
        if ((int)C.size() < (int)B.size() + m) C.resize(B.size() + m, 0);
        for (size_t i = 0; i < B.size(); ++i) C[i + m] = subm(C[i + m], mulm(coef, B[i]));

        if (2 * L <= n){ L = n + 1 - L; B = T; b = d; m = 1; }
        else ++m;
    }

    vector<int> a; a.reserve(L);
    for (int i = 1; i <= L; ++i) a.push_back(subm(0, C[i])); // recurrence coeffs
    return a;
}

// --- combine polynomials and reduce by characteristic poly ---
inline vector<int> combine(const vector<int>& A, const vector<int>& B, const vector<int>& c){
    const int m = (int)c.size();
    vector<int> res(2 * m, 0);

    // multiply polynomials
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < m; ++j)
            res[i + j] = addm(res[i + j], mulm(A[i], B[j]));

    // reduce by characteristic polynomial
    for (int i = 2 * m - 1; i >= m; --i){
        int t = res[i];
        if (!t) continue;
        for (int j = 1; j <= m; ++j)
            res[i - j] = addm(res[i - j], mulm(t, c[j - 1]));
    }
    res.resize(m);
    return res;
}

// --- compute S[n] given S[0..m-1] and recurrence c ---
inline int nth_from_known_coeffs(const vector<int>& S, const vector<int>& c, ll n){
    const int m = (int)c.size();
    if (m == 0) return S.empty() ? 0 : S[0];
    if (n < (ll)S.size()) return norm(S[(size_t)n]);

    if (m == 1) return mulm(norm(S[0]), mod_pow(norm(c[0]), n));

    vector<int> res(m, 0), x(m, 0);
    res[0] = 1;
    if (m > 1) x[1] = 1;

    ll e = n;
    while (e){
        if (e & 1LL) res = combine(res, x, c);
        x = combine(x, x, c);
        e >>= 1LL;
    }

    int ans = 0;
    for (int i = 0; i < m; ++i) ans = addm(ans, mulm(res[i], norm(S[i])));
    return ans;
}

// --- top-level: infer recurrence and get nth term (0-based) ---
inline int nth_BM(const vector<int>& samples, ll n){
    if (n < (ll)samples.size()) return norm(samples[(size_t)n]);
    const vector<int> c = berlekamp_massey(samples);
    const int m = (int)c.size();
    if (m == 0) return samples.empty() ? 0 : samples.back();
    vector<int> S(samples.begin(), samples.begin() + m);
    return nth_from_known_coeffs(S, c, n);
}

// ---------------- example ICPC main ----------------
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m; cin >> m; // number of initial samples
    vector<int> samples(m);
    for (int i = 0; i < m; ++i){
        long long x; cin >> x;
        samples[i] = norm((int)(x % MOD));
    }

    int q; cin >> q; // number of queries
    while (q--){
        long long n; cin >> n; // 0-based index
        cout << nth_BM(samples, n) << '\n';
    }
    return 0;
}
