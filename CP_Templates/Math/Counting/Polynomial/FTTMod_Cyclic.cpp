typedef long long ll;
typedef vector<ll> vl;
#define sz(x) ((int)(x).size())
#define rep(i,a,b) for(int i=(a);i<(b);i++)

using C = complex<double>;

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

template<int M> vl cyclicConvMod(const vl &a, const vl &b, int cycle_len) {
    if (a.empty() || b.empty()) return {};
    
    // Ensure both vectors are of cycle_len size by padding with zeros
    vl a_pad(cycle_len), b_pad(cycle_len);
    rep(i,0,sz(a)) a_pad[i % cycle_len] = (a_pad[i % cycle_len] + a[i]) % M;
    rep(i,0,sz(b)) b_pad[i % cycle_len] = (b_pad[i % cycle_len] + b[i]) % M;
    
    int B = 32 - __builtin_clz(2*cycle_len-1), n = 1 << B;
    int cut = int(sqrt(M));
    vector<C> L(n), R(n), outs(n), outl(n);
    
    rep(i,0,cycle_len) {
        L[i] = C((int)a_pad[i] / cut, (int)a_pad[i] % cut);
        R[i] = C((int)b_pad[i] / cut, (int)b_pad[i] % cut);
    }
    
    fft(L), fft(R);
    rep(i,0,n) {
        int j = -i & (n - 1);
        outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
        outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / 1i;
    }
    fft(outl), fft(outs);
    
    vl res(cycle_len);
    rep(i,0,cycle_len) {
        ll av = ll(real(outl[i])+.5), cv = ll(imag(outs[i])+.5);
        ll bv = ll(imag(outl[i])+.5) + ll(real(outs[i])+.5);
        res[i] = ((av % M * cut + bv) % M * cut + cv) % M;
    }
    
    return res;
}
