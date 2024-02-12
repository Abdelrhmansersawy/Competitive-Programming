// problem link: https://codeforces.com/contest/803/problem/F
#include <bits/stdc++.h>
typedef long long ll;
#define s second
#define f first
#define add(a , b) a = (a + b + mod) % mod
#define rep(i , st , ed) for(int i = st ; i < ed ; i++)
using namespace std;
void burn(){
ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
  #endif
}
//\//\//\/\//\//\//\//\//\//
const int N = 100009 , mod = 1e9 + 7;
ll mobius[N] , sieve[N] , g[N] , fre[N];
void gen_mobius(){
  for(int i = 1; i < N; i++) {mobius[i] = sieve[i] = 1;}
  sieve[1] = 0;
  for(long long i = 2; i < N; i++){
    if(sieve[i]){
      for(long long j = i; j < N; j += i){
        sieve[j] = 0;
        mobius[j] = (j % (i * i) == 0) ? 0 : -mobius[j];
      }
    }
  }
}
ll bin_exp(ll a , ll b){
  ll ret = 1;
  while(b){
    if(b % 2) ret = (ret * a) % mod;
    a = (a * a) % mod;
    b /= 2;
  }
  return ret;
}
int main(){
  burn();
  ll n; cin >> n;
  rep(i , 0 , n){
    int x; cin >> x;
    fre[x]++;
  }
  gen_mobius();
  for(int i = 2; i < N; i++){
    for(int j = i; j < N; j += i){
      g[i] += fre[j];
    }
  }
  ll ans = (bin_exp(2 , n) - 1 + mod) % mod;
  // count number of subsequence the gcd > 1
  for(int i = 2; i < N; i++){
    add(ans, mobius[i] * ((bin_exp(2 , g[i]) - 1 + mod) % mod) % mod);
  }
  cout << ans;
}
