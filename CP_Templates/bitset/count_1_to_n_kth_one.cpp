// from 1 to n how many number contains the kth bit
ll count(ll n, ll k) {
    ++n;
    ll d = 1LL << k + 1, p = 1LL << k;
    return n / d * p + max(0LL, n % d - p);
}
