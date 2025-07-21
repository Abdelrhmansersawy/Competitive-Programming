using ll = long long;
const ll MOD = 1000000007LL;

// fast modular arithmetic
inline ll add(ll a, ll b)    { a += b; return a >= MOD ? a - MOD : a; }
inline ll sub(ll a, ll b)    { a -= b; return a <  0   ? a + MOD : a; }
inline ll mul(ll a, ll b)    { return (a * b) % MOD; }
ll modexp(ll a, ll e = MOD-2) { ll r = 1; while (e) { if (e & 1) r = mul(r, a); a = mul(a, a); e >>= 1; } return r; }
inline ll inv(ll a)          { return modexp(a); }

/**
 * Solves the modular linear system:
 *   a[0][0]·x₀ + a[0][1]·x₁ + … + a[0][m-1]·xₘ₋₁ ≡ b₀  (mod MOD)
 *   …
 *   a[n-1][0]·x₀ + … + a[n-1][m-1]·xₘ₋₁ ≡ bₙ₋₁  (mod MOD)
 *
 * Input:
 *   a — n×(m+1) augmented matrix [A|b], where
 *       a[i][j]   = coeff for x_j in eq i     (0 ≤ i < n, 0 ≤ j < m)
 *       a[i][m]   = constant term b_i         (0 ≤ i < n)
 *
 * Returns:
 *   vector x of length m giving one solution (free vars = 0), or
 *   empty vector if no solution.
 *
 * Time Complexity:
 *   O(n * m * min(n, m))  
 * Space Complexity:
 *   O(n * (m+1)) 
 */
vector<ll> gauss(vector<vector<ll>>& a) {
    int n = a.size(), m = a[0].size() - 1;
    vector<int> where(m, -1);
    for (int col = 0, row = 0; col < m && row < n; col++) {
        int sel = row;
        for (int i = row; i < n; i++)
            if (a[i][col] > a[sel][col])
                sel = i;
        if (a[sel][col] == 0) continue;
        swap(a[sel], a[row]);
        where[col] = row;
        ll inv_piv = inv(a[row][col]);
        for (int i = 0; i < n; i++) if (i != row) {
            if(a[i][col] == 0) continue;
            ll factor = mul(a[i][col], inv_piv);
            for (int j = col; j <= m; j++)
                a[i][j] = sub(a[i][j], mul(factor, a[row][j]));
        }
        row++;
    }

    vector<ll> x(m, 0);
    for (int i = 0; i < m; i++)
        if (where[i] != -1)
            x[i] = mul(a[where[i]][m], inv(a[where[i]][i]));

    // consistency check
    for (int i = 0; i < n; i++){
        ll sum = 0;
        for (int j = 0; j < m; j++)
            sum = (sum + a[i][j] * x[j]) % MOD;
        if ((sum + MOD) % MOD != a[i][m])
            return {};
    }
    return x;
}
