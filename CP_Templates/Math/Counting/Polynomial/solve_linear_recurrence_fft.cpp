const int mod = 1e9 + 7;
using ll = long long;
using poly = vector<long long>;
using C = complex<double>;

#define sz(x) ((int)(x).size())
#define rep(i,a,b) for(int i=(a);i<(b);i++)
#define all(x) (x).begin(), (x).end()

void fft(vector<C>& a) {
    int n = sz(a), L = 31 - __builtin_clz(n);
    static vector<complex<long double>> R(2, 1);
    static vector<C> rt(2, 1);
    for (static int k = 2; k < n; k *= 2) {
        R.resize(n); rt.resize(n);
        auto x = polar(1.0L, acos(-1.0L) / k);
        rep(i,k,2*k) rt[i] = R[i] = i&1 ? R[i/2] * x : R[i/2];
    }
    vector<int> rev(n);
    rep(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    rep(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k *= 2)
        for (int i = 0; i < n; i += 2 * k) rep(j,0,k) {
            C z = rt[j+k] * a[i+j+k];
            a[i + j + k] = a[i + j] - z;
            a[i + j] += z;
        }
}

template<int M> poly convMod(const poly &a, const poly &b) {
    if (a.empty() || b.empty()) return {};
    poly res(sz(a) + sz(b) - 1);
    int B = 32 - __builtin_clz(sz(res)), n = 1 << B, cut = int(sqrt(M));
    vector<C> L(n), R(n), outs(n), outl(n);
    rep(i,0,sz(a)) L[i] = C((int)a[i] / cut, (int)a[i] % cut);
    rep(i,0,sz(b)) R[i] = C((int)b[i] / cut, (int)b[i] % cut);
    fft(L), fft(R);
    rep(i,0,n) {
        int j = -i & (n - 1);
        outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
        outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / 1i;
    }
    fft(outl), fft(outs);
    rep(i,0,sz(res)) {
        long long av = (long long)(real(outl[i])+.5), cv = (long long)(imag(outs[i])+.5);
        long long bv = (long long)(imag(outl[i])+.5) + (long long)(real(outs[i])+.5);
        res[i] = ((av % M * cut + bv) % M * cut + cv) % M;
    }
    return res;
}

long long modpow(long long b, long long e) {
    long long ans = 1;
    for (; e; b = b * b % mod, e /= 2) if (e & 1) ans = ans * b % mod;
    return ans;
}

poly polyInv(poly a, int n) {
    if (n == 1) return {modpow(a[0], mod - 2)};
    poly h = polyInv(a, (n + 1) / 2);
    poly tmp = a; if(sz(tmp) > n) tmp.resize(n);
    poly p = convMod<mod>(h, tmp);
    if(sz(p) > n) p.resize(n);
    rep(i,0,sz(p)) p[i] = (mod - p[i]) % mod;
    p[0] = (p[0] + 2) % mod;
    poly res = convMod<mod>(h, p);
    if(sz(res) > n) res.resize(n);
    return res;
}

poly polyDiv(poly a, poly b) {
    int n = sz(a), m = sz(b);
    if (n < m) return a;
    poly A = a, B = b;
    reverse(all(A)); reverse(all(B));
    B.resize(n - m + 1);
    poly Q = convMod<mod>(A, polyInv(B, n - m + 1));
    Q.resize(n - m + 1); reverse(all(Q));
    poly QB = convMod<mod>(Q, b);
    poly R(m - 1);
    rep(i,0,m-1) R[i] = (a[i] - (i < sz(QB) ? QB[i] : 0) + mod) % mod;
    return R;
}

poly kitamasa_poly(const poly& P, long long n) {
    poly res = {1}, x = {0, 1};
    while (n) {
        if (n & 1) res = polyDiv(convMod<mod>(res, x), P);
        x = polyDiv(convMod<mod>(x, x), P);
        n >>= 1;
    }
    return res;
}

ll apply(poly res , poly a){
    ll ans = 0;
    rep(i,0,sz(res)) {
        if(i < sz(a)) {
            ans = (ans + res[i] * a[i]) % mod;
        }
    }
    return ans;
}

ll kitamasa(poly P, poly &a, ll n) {
    poly res = kitamasa_poly(P, n);
    return apply(res, a);
}
