/*
 Problem: Count non-empty good subsequences b of a.
 Condition: b[i] <= b[i+1] and gcd(b[i], b[i+1]) == 1.
 Solution: CDQ Divide & Conquer + Mobius Inversion.
 - CDQ handles indices (j < i) and values (a[j] <= a[i]).
 - Mobius Inversion handles the coprime condition: sum(mu[d]) for d|gcd(x,y).
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 5e6 + 5, M = 1e5 + 5, MOD = 1e9 + 7;
int mu[N], lpf[N], a[M];
ll exc[N], dp[M];
vector<int> dis[M], primes;

void sieve() {
    mu[1] = 1;
    for (int i = 2; i < N; ++i) {
        if (!lpf[i]) lpf[i] = i, mu[i] = -1, primes.push_back(i);
        for (int p : primes) {
            if (p > lpf[i] || i * p >= N) break;
            lpf[i * p] = p;
            mu[i * p] = (p == lpf[i]) ? 0 : -mu[i];
        }
    }
}

// Generate square-free divisors (where mu[d] != 0)
void get_divs(int idx, int x) {
    dis[idx] = {1};
    while (x > 1) {
        int p = lpf[x];
        while (x % p == 0) x /= p;
        int sz = dis[idx].size();
        for (int i = 0; i < sz; ++i) dis[idx].push_back(dis[idx][i] * p);
    }
}

void add(ll &x, ll y) { x = (x + y) % MOD; if (x < 0) x += MOD; }

void solve(int l, int r) {
    if (l == r) return;
    int m = (l + r) / 2;
    solve(l, m);

    vector<int> L, R;
    for (int i = l; i <= m; ++i) L.push_back(i);
    for (int i = m + 1; i <= r; ++i) R.push_back(i);

    auto cmp = [](int i, int j) { return a[i] < a[j]; };
    sort(L.begin(), L.end(), cmp);
    sort(R.begin(), R.end(), cmp);

    int i = 0;
    for (int j : R) {
        while (i < L.size() && a[L[i]] <= a[j]) {
            int u = L[i++];
            for (int d : dis[u]) add(exc[d], dp[u]);
        }
        for (int d : dis[j]) add(dp[j], exc[d] * mu[d]);
    }

    // Rollback changes to exc for next steps
    for (int k = 0; k < i; ++k) 
        for (int d : dis[L[k]]) add(exc[d], -dp[L[k]]);

    solve(m + 1, r);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    sieve();

    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            get_divs(i, a[i]);
            dp[i] = 1; // Base case: subsequence of length 1
        }
        
        solve(0, n - 1);

        ll ans = 0;
        for (int i = 0; i < n; ++i) add(ans, dp[i]);
        cout << ans << '\n';
    }
}
