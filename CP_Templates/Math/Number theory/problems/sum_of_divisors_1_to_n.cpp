/*
 Compute S(n) = Σ_{i=1}^n σ(i) mod 1e9+7.
 Note: S(n) = Σ_{d=1}^n d * ⌊n/d⌋. Group by equal q = ⌊n/d⌋ and iterate in O(√n).
 Constraints: 1 ≤ n ≤ 1e12.
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 1e9+7;
const int inv2 = 500000004;

ll sum(ll l , ll r){
    ll len = (r-l+1) % mod;
    ll sum = len * (len + 1) % mod * inv2 % mod;
    sum += (l-1) % mod * len % mod;
    sum %= mod;
    return sum;
}
int main(){
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
    ll n; cin >> n;

    // sum_{d=1}^{n}{d \floor{n/d}}
    // trick: there's sqrt(n) distinct value of n/d
    // for each n/d: first [l...r] where each i [l..r] = n/d

    ll ans = 0;
    for(ll i = 1; i <= n;){
        ll x = n/i;
        ll l = i , r = n/x; 
        ans += sum(l,r) * (x % mod) % mod;
        ans %= mod;
        i = r+1;
    }
    cout << ans;
}
