mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

ll rand(ll l, ll r) {
    return uniform_int_distribution<ll>(l, r)(rng);
}

const int mod1 = 1e9 + 7, mod2 = 1e9 + 9;
const int p1 = rand(1e7, 1e8), p2 = rand(1e7, 1e8);
const int N = 1e6 + 1;
vector<ll> pow1(N + 1), pow2(N + 1);

void init() {
    pow1[0] = pow2[0] = 1;
    for (int i = 1; i <= N; i++) {
        pow1[i] = p1 * pow1[i - 1] % mod1;
        pow2[i] = p2 * pow2[i - 1] % mod2;
    }
}

struct stringHashing {
    vector<ll> preHash1, preHash2, sufHash1, sufHash2;

    void init(string &s) {
        preHash1 = hash(s, preHash1, pow1, mod1);
        preHash2 = hash(s, preHash2, pow2, mod2);
        sufHash1 = hash(s, sufHash1, pow1, mod1, true);
        sufHash2 = hash(s, sufHash2, pow2, mod2, true);
    }

    vector<ll> hash(string &s, vector<ll> &h, vector<ll> &p, int m, bool rev = false) {
        int n = s.size();
        h.resize(n);
        int st = 0, en = n, delta = 1;
        if (rev)
            st = n - 1, en = -1, delta = -1;
        int i = 0;
        while (st != en) {
            h[st] = (s[st] - 'a' + 1) * p[i] % m;
            if (i != 0) {
                h[st] += h[st - delta];
                if (h[st] >= m)
                    h[st] -= m;
            }
            st += delta;
            i++;
        }
        return h;
    }

    ll query(int l, int r) {
        ll h1 = preHash1[r], h2 = preHash2[r];
        h1 -= (l == 0 ? 0 : preHash1[l - 1]);
        h2 -= (l == 0 ? 0 : preHash2[l - 1]);
        if (h1 < 0)h1 += mod1;
        if (h2 < 0)h2 += mod2;
        h1 = h1 * pow1[N - l] % mod1;
        h2 = h2 * pow2[N - l] % mod2;
        return h1 * h2;
    }

    ll revQuery(int l, int r) {
        int n = sufHash1.size();
        ll h1 = sufHash1[l], h2 = sufHash2[l];
        h1 -= (r == (n - 1) ? 0 : sufHash1[r + 1]);
        h2 -= (r == (n - 1) ? 0 : sufHash2[r + 1]);
        if (h1 < 0)h1 += mod1;
        if (h2 < 0)h2 += mod2;
        h1 = h1 * pow1[N - n + r + 1] % mod1;
        h2 = h2 * pow2[N - n + r + 1] % mod2;
        return h1 * h2;
    }
};