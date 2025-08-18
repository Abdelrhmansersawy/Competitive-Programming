/// Given a group of n men arranged in a circle under the edict that every k'th man
/// will be executed going around the circle until only one remains.
/// Find out who will be the final survivor.
int josephus(int n, int k) {
    int res = 0;
    for (int i = 1; i <= n; ++i)
      res = (res + k) % i;
    return res + 1;
}
/// when k is too small we can solve this problem on O( k ln(n) )
int josephus(int n, int k) {
    if (n == 1)
        return 0;
    if (k == 1)
        return n-1;
    if (k > n)
        return (josephus(n-1, k) + k) % n;
    int cnt = n / k;
    int res = josephus(n - cnt, k);
    res -= n % k;
    if (res < 0)
        res += n;
    else
        res += res / (k - 1);
    return res;
}


/// log base solution when k is 2
int josephus(int n){
    int p = 1;
    while (p <= n) p *= 2;
    return (2*n) - p + 1;
}

/// also if we need to find kth removed child when base = 2 on O( log(n) ) 
ll f(ll n, ll k) {
    if (n == 1) return 1;
 
    if (k <= (n + 1) / 2) {
        if (2 * k > n) return (2 * k) % n;
        else return 2 * k;
    }
 
    ll temp = f(n / 2, k - (n + 1) / 2);
    if (n % 2 == 1) return 2 * temp + 1;
    return 2 * temp - 1;
}
 

