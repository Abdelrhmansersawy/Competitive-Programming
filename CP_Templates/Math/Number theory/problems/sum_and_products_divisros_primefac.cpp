#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/*
 Given num = ∏_{i=1}^n x_i^{k_i}.
 d(num) = ∏_{i=1}^n (k_i + 1). --> no. of divisors
 σ(num) = ∏_{i=1}^n (x_i^{k_i+1} − 1) / (x_i − 1). --> sum of divisors
 Product of divisors: P = num^{d(num)/2}  (so for each prime x_i exponent = k_i * d(num)/2).

 When computing P mod p (prime): form the integer exponents
    e_i = k_i * d(num) / 2
(first do the integer division — e_i is integral), then reduce e_i modulo (p−1)
and compute x_i^{e_i mod (p−1)} (Fermat/Euler). If you need to perform the
division by 2 under modulo arithmetic, compute d(num) mod 2*(p−1) first so
halving is well-defined.
*/


const int mod = 1e9 + 7;
ll bpow(ll a , ll b){
    ll res = 1;
    while(b){
        if(b % 2) res = res * a % mod;
        b /= 2;
        a = a * a % mod;
    }
    return res;
} 
ll inv(ll n){ return bpow(n , mod - 2); }

ll cnt_divisors(vector<pair<ll,ll>> &primeFac){
    ll cnt = 1;
    for(auto &[p , q] : primeFac){
        cnt = cnt * (q+1) % mod;
    }
    return cnt;
}
ll sum_divisors(vector<pair<ll,ll>> &primeFac){
    ll sum = 1;
    for(auto &[p , q] : primeFac){
        ll s = (bpow(p , q + 1) - 1 + mod) % mod;
        s = s * inv(p - 1) % mod;
        sum = sum * s % mod;
    }
    return sum;
}
ll product_divisors(vector<pair<ll,ll>> &primeFac){
    ll prod = 1;
    const ll mod2 = 2 * (mod - 1);
    const ll PHI = mod - 1;
    
    ll cnt = 1;
    for(auto &[p , q] : primeFac){
        cnt = cnt * (q+1) % mod2;
    }

    for(auto &[p , q] : primeFac){
        ll x = q * cnt % mod2;
        ll exp = (x / 2) % PHI; 

        prod = prod * bpow(p , exp) % mod;
    }
    return prod;
}

int main(){
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif
    int n; cin >> n;
    vector<pair<ll,ll>> primeFac(n);
    for(auto &[p , q] : primeFac) cin >> p >> q;
    cout << cnt_divisors(primeFac) << ' ';
    cout << sum_divisors(primeFac) << ' ';
    cout << product_divisors(primeFac);
}
