/*
 * Problem: Find occurrences of an X*Y pattern in an N*M grid.
 * Constraints: N, M <= 1000; X, Y <= 100.
 * Solution: 2D Rolling Hash (Rabin-Karp).
 * Uses Double Hash with same Mod (2^61-1) but different Bases to avoid collisions.
 * Utilizes bitwise optimization for Mersenne Prime modular multiplication.
 * Time Complexity: O(N * M)
 * Space Complexity: O(N * M)
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll M = (1LL<<61) - 1;
const ll B1 = 999983, B2 = 99991;
ll H1[1005][1005], H2[1005][1005];

int64_t MUL(uint64_t a, uint64_t b, uint64_t HashMod) {
    uint64_t l1 = (uint32_t) a, h1 = a >> 32, l2 = (uint32_t) b, h2 = b >> 32;
    uint64_t l = l1 * l2, m = l1 * h2 + l2 * h1, h = h1 * h2;
    uint64_t ret = (l & HashMod) + (l >> 61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
    ret = (ret & HashMod) + (ret >> 61);
    ret = (ret & HashMod) + (ret >> 61);
    return (int64_t) ret - 1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M_sz; cin >> N >> M_sz;
    vector<string> g(N);
    for(int i=0; i<N; i++) cin >> g[i];
    int X, Y; cin >> X >> Y;
    vector<string> p(X);
    for(int i=0; i<X; i++) cin >> p[i];

    if(X > N || Y > M_sz) { cout << 0; return 0; }

    ll ph1 = 0, ph2 = 0, pb1 = 1, pb2 = 1;
    for(int i=0; i<Y-1; i++) {
        pb1 = MUL(pb1, B1, M);
        pb2 = MUL(pb2, B2, M);
    }
    ll col_pow1 = 1, col_pow2 = 1;
    for(int i=0; i<X-1; i++) {
        col_pow1 = MUL(col_pow1, B1, M);
        col_pow2 = MUL(col_pow2, B2, M);
    }

    for(int i=0; i<X; i++) {
        ll r1 = 0, r2 = 0;
        for(int j=0; j<Y; j++) {
            r1 = (MUL(r1, B1, M) + p[i][j]) % M;
            r2 = (MUL(r2, B2, M) + p[i][j]) % M;
        }
        ph1 = (MUL(ph1, B1, M) + r1) % M;
        ph2 = (MUL(ph2, B2, M) + r2) % M;
    }

    for(int i=0; i<N; i++) {
        ll r1 = 0, r2 = 0;
        for(int j=0; j<Y; j++) {
            r1 = (MUL(r1, B1, M) + g[i][j]) % M;
            r2 = (MUL(r2, B2, M) + g[i][j]) % M;
        }
        H1[i][0] = r1; H2[i][0] = r2;
        for(int j=1; j<=M_sz-Y; j++) {
            r1 = (r1 - MUL(g[i][j-1], pb1, M) + M) % M;
            r1 = (MUL(r1, B1, M) + g[i][j+Y-1]) % M;
            r2 = (r2 - MUL(g[i][j-1], pb2, M) + M) % M;
            r2 = (MUL(r2, B2, M) + g[i][j+Y-1]) % M;
            H1[i][j] = r1; H2[i][j] = r2;
        }
    }

    int ans = 0;
    for(int j=0; j<=M_sz-Y; j++) {
        ll c1 = 0, c2 = 0;
        for(int i=0; i<X; i++) {
            c1 = (MUL(c1, B1, M) + H1[i][j]) % M;
            c2 = (MUL(c2, B2, M) + H2[i][j]) % M;
        }
        if(c1 == ph1 && c2 == ph2) ans++;
        
        for(int i=1; i<=N-X; i++) {
            c1 = (c1 - MUL(H1[i-1][j], col_pow1, M) + M) % M;
            c1 = (MUL(c1, B1, M) + H1[i+X-1][j]) % M;
            
            c2 = (c2 - MUL(H2[i-1][j], col_pow2, M) + M) % M;
            c2 = (MUL(c2, B2, M) + H2[i+X-1][j]) % M;
            
            if(c1 == ph1 && c2 == ph2) ans++;
        }
    }
    cout << ans << endl;
}
