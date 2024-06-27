const int N = 5000;
const int mod = 1e9 + 7;
ll fact[N];
ll inv[N]; //mod inverse for i
ll invfact[N]; //mod inverse for i!
void init() {
    fact[0] = inv[1] = fact[1] = invfact[0] = invfact[1] = 1;
    for (long long i = 2; i < N; i++) {
        fact[i] = (fact[i - 1] * i) % mod;
        inv[i] = mod - (inv[mod % i] * (mod / i) % mod);
        invfact[i] = (inv[i] * invfact[i - 1]) % mod;
    }
}
 
ll nCr(int n, int r) {
    if (r > n) {
        return 0;
    }
    if(r < 0) return 1;
    ll res = 1;
    for (int i = 0; i < r; ++i) {
        res = res * (n - i) % mod;
    }
    res = res * inv_fact[r] % mod;
    return result;
}
