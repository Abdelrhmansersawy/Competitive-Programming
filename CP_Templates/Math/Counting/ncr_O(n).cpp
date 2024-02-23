const int N = 5e6 + 9;
ll fac[N], inv[N];
void preprocess() {
    for (int i = 0; i < N; i++) {
        if (i < 2) {
            fac[i] = inv[i] = 1;
        } else {
            fac[i] = 1ll * i * fac[i - 1] % mod;
            inv[i] = mod - 1ll * mod / i * inv[mod % i] % mod;
        }
    }
    for (int i = 2; i < N; i++) {
        inv[i] = 1ll * inv[i] * inv[i - 1] % mod;
    }
}
ll ncr(ll n, ll r) {
    if(r > n || n < 0 || r < 0) return 0; // manual handling
    return 1ll * fac[n] * (1ll * inv[r] * inv[n - r] % mod) % mod;
}
