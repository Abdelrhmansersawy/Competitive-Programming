/*
    ## Extended Euclidean algorithms 
    Modular multiplicative inverse when M and A are coprime or gcd(A, M) = 1:
    
    Time Complexity: O(log M)
    Auxiliary Space: O(1)
*/
ll gcd(ll a, ll b, ll& x, ll& y) {
    x = 1, y = 0;
    ll x1 = 0, y1 = 1, a1 = a, b1 = b;
    while (b1) {
        int q = a1 / b1;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    return a1;
}
ll inv(ll A , ll M){
    // modular inverse of A mod M
    ll x , y;
    ll g = gcd(A,M,x ,y);
    if(g != 1){ // Inverse doesn't exist
        exit(3);
    }
    ll res = (x % M + M) % M;
    return res;
}

//--------------------------------------------------------------------
/*
  ## Fermat’s little theorem
  Modular multiplicative inverse when M is prime:
  Time Complexity: O(log M)
  Auxiliary Space: O(1)
*/
ll bpw(ll a , ll b, ll mod){
  ll res = 1;
  a %= mod; // avoid overflow from a * a
  while(b){
     if(b % 2) res = (res * a) % mod;
     b /= 2;
     a = (a * a) % mod;
  }
}
ll inv(ll N, ll M){
   return bpw(N , M - 2);
}
