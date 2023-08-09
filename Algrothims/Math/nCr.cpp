ll bpow(ll n, ll x) { return !x ? 1 : bpow(n * n % mod, x >> 1) * (x & 1 ? n : 1) % mod; }
ll inv(ll b) { return bpow(b, mod - 2); }
ll fact[N], factinv[N];
void init(){for (int i = 0; i < N; ++i) fact[i] = i ? fact[i - 1] * i % mod : 1, factinv[i] = inv(fact[i]);}
ll C(ll n, ll k) { return fact[n] * factinv[n - k] % mod * factinv[k] % mod; }
