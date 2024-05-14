const int N = 2e6 + 100;
const int mod = 1e6 + 3;
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
