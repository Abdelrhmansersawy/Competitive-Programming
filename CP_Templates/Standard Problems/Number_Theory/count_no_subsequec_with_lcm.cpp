/*
  Problem Link: https://atcoder.jp/contests/abc349/tasks/abc349_f
  Problem description:
    You are given a sequence of positive integers 
    A=(A1, A2,.. , An) of length  N and a positive integer  M. Find the number, modulo  998244353, of non-empty and not necessarily contiguous subsequences of 
    A such that the least common multiple (LCM) of the elements in the subsequence is 
    M. Two subsequences are distinguished if they are taken from different positions in the sequence, even if they coincide as sequences. Also, the LCM of a sequence with a single element is that element itself.
    
    Constraints
    1 <= N <= 2e5
    1 <= M <= 1e16
    1 <= Ai <= 1e16

   My sol:
      Time complexity: O( (2^x) ^ 3) --> can be decreased to O(3^x) using submasking method 
      such that x: no. of primes in M
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i , st , ed) for(int i = st; i < ed; i++)
#define f first
#define s second
const int mod = 998244353;
ll bpw(ll a , ll b){
	ll res = 1;
	while(b){
		if(b % 2) res = res * a % mod;
		b /= 2;
		a = a * a % mod;
	}
	return res;
}
int main(){
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif 
    ll n , m; cin >> n >> m;
    vector<ll> dis;
    ll M = m;
    for(ll i = 2; i * i <= m; ++i) if(m % i == 0){
    	ll d = 1;
    	while(m % i == 0){ m /= i; d *= i; }
    	dis.emplace_back(d);
    }
    if(m > 1) dis.emplace_back(m);
    m = (int) dis.size();
    int cnt[1 << m]{} , one = 0;
    for(int i = 0; i < n; ++i){
    	ll x; cin >> x;
    	if(__gcd(x , M) != x) continue;
    	ll mask = 0;
    	for(int j = 0; j < m; ++j) if(x % dis[j] == 0)
    		mask |= (1 << j);
    	one += (x == 1);
    	cnt[mask]++;
    }
    if(M == 1){ cout << ( bpw(2 , one) - 1 + mod ) % mod; return 0; }
    vector<ll> dp(1 << m);
    dp[0] = bpw(2 , cnt[0]);
    for(int i = 1; i < (1 << m); ++i){
    	ll c = bpw(2 , cnt[i]) - 1;
    	// Previous mask
    	for(int j = (1 << m) - 1; j >= 0; --j){
    		dp[i | j] += dp[j] * c;
    		dp[i | j] %= mod;
    	}
    }
    cout << dp[(1 << m) - 1];
}
