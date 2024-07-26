ll fast_power(ll a, ll b){
    ll res = 1;
    while (b){
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

ll mod_inv(ll a){
    return fast_power(a, mod - 2);
}
 
const int root = fast_power(3, 119);
const int root_inv = mod_inv(root);
const int root_pw = 23;
 
int reverse(int num, int lg_n){
    int res = 0;
    for (int i = 0; i < lg_n; ++i) {
        if (num & (1 << i)) res |= 1 << (lg_n - 1 - i);
    }
    return res;
}
 
vector<vector<int>> roots, roots_inv;
vector<int> rev;
 
void pre(int n){
    int lg_n = __lg(n);
    rev.resize(n);
    roots.resize(lg_n);
    roots_inv.resize(lg_n);
    for (int i = 0; i < n; ++i) {
        rev[i] = reverse(i, lg_n);
    }
 
    int wlen = root, wlen_inv = root_inv;
    for (int i = 0; i < root_pw - lg_n; ++i) {
        wlen = 1ll * wlen * wlen % mod;
        wlen_inv = 1ll * wlen_inv * wlen_inv % mod;
    }
 
    for (int l = lg_n - 1; l >= 0 ; --l) {
        int len = 1 << (l + 1);
        int w = 1, w_inv = 1;
        roots[l].resize(len / 2);
        roots_inv[l].resize(len / 2);
        for (int i = 0; i < len / 2; ++i) {
            roots[l][i] = w;
            roots_inv[l][i] = w_inv;
            w = 1ll * w * wlen % mod;
            w_inv = 1ll * w_inv * wlen_inv % mod;
        }
        wlen = 1ll * wlen * wlen % mod;
        wlen_inv = 1ll * wlen_inv * wlen_inv % mod;
    }
}
 
void ntt(vector<int>& a, bool invert){
    int n = a.size();
    for (int i = 1; i < n; ++i) {
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    }
    int mx = __lg(n);
    for (int l = 0; l < mx; ++l) {
        int len = 1 << (l + 1), shift = 1 << l;
        for (int i = 0; i < n; i += len) {
            for (int j = 0; j < len / 2; ++j) {
                int w = invert ? roots_inv[l][j] : roots[l][j];
                int u = a[i + j], v = 1ll * a[i + j + shift] * w % mod;
                a[i + j] = (u + v) % mod;
                a[i + j + shift] = (u - v + mod) % mod;
            }
        }
    }
 
    if (invert){
        int n_1 = mod_inv(n);
        for(int &x: a) x = 1ll * x * n_1 % mod;
    }
}
 
vector<int> convolve(int n, int m , vector<int> a){
    int size = n * m + 1;
    int _n = 1;
    while (_n < size) _n <<= 1;
    a.resize(_n);
    pre(_n);
    ntt(a, false);
    for (int i = 0; i < _n; ++i) a[i] = fast_power(a[i], n);
    ntt(a, true);
    a.resize(size);
    return a;
}
