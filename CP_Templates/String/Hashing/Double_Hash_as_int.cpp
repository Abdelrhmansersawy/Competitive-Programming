const int N = 2e5 + 9;
const int M[2] = { (int)1e9 + 7, 998244353 };
int B[2]; // Bases
int pw[2][N], ipw[2][N]; // Powers and Inverse Powers

ll bpw(ll a, ll b, int m) {
    ll res = 1;
    a %= m;
    while (b) {
        if (b & 1) res = (res * a) % m;
        a = (a * a) % m;
        b >>= 1;
    }
    return res;
}

void init() {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    for (int i = 0; i < 2; ++i) {
        B[i] = uniform_int_distribution<int>(300, M[i] - 2)(rng);
        pw[i][0] = ipw[i][0] = 1;
        int inv = bpw(B[i], M[i] - 2, M[i]);
        for (int j = 1; j < N; ++j) {
            pw[i][j] = 1LL * pw[i][j - 1] * B[i] % M[i];
            ipw[i][j] = 1LL * ipw[i][j - 1] * inv % M[i];
        }
    }
}

struct Hash {
    int len;
    int pre[2], suf[2]; // pre: prefix hash, suf: suffix hash (for palindrome)

    Hash(char c = '?') {
        len = (c != '?');
        for (int i = 0; i < 2; ++i) {
            pre[i] = suf[i] = (c == '?' ? 0 : c - 'a' + 1);
        }
    }

    // Concatenate: res = this + other
    Hash operator+(const Hash& other) const {
        Hash res;
        res.len = len + other.len;
        for (int i = 0; i < 2; ++i) {
            res.pre[i] = (pre[i] + 1LL * other.pre[i] * pw[i][len]) % M[i];
            res.suf[i] = (other.suf[i] + 1LL * suf[i] * pw[i][other.len]) % M[i];
        }
        return res;
    }
    bool is_palindrome() const {
        return pre[0] == suf[0] && pre[1] == suf[1];
    }
    ll get() const {
        return ((ll)pre[0] << 32) | pre[1];
    }
};

// Remove s2 from the start of s1 (s1 must start with s2)
// Logic: (Full - Prefix) * InvPow[PrefixLen]
Hash excludePrefix(const Hash& s1, const Hash& s2) {
    Hash res;
    res.len = s1.len - s2.len;
    for (int i = 0; i < 2; ++i) {
        // Forward: Remove prefix, normalize by dividing power
        res.pre[i] = 1LL * (s1.pre[i] - s2.pre[i] + M[i]) * ipw[i][s2.len] % M[i];
        // Backward: Standard suffix subtraction
        res.suf[i] = (s1.suf[i] - 1LL * s2.suf[i] * pw[i][res.len] % M[i] + M[i]) % M[i];
    }
    return res;
}

// Remove s2 from the end of s1 (s1 must end with s2)
// Logic: (Full - Suffix) * InvPow[SuffixLen] (reversed for backward hash)
Hash excludeSuffix(const Hash& s1, const Hash& s2) {
    Hash res;
    res.len = s1.len - s2.len;
    for (int i = 0; i < 2; ++i) {
        // Forward: Standard prefix subtraction
        res.pre[i] = (s1.pre[i] - 1LL * s2.pre[i] * pw[i][res.len] % M[i] + M[i]) % M[i];
        // Backward: Remove suffix, normalize
        res.suf[i] = 1LL * (s1.suf[i] - s2.suf[i] + M[i]) * ipw[i][s2.len] % M[i];
    }
    return res;
}
