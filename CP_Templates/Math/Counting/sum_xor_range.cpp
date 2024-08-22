ll range_xor(ll l, ll r) {
    ll res = 0;
    if (l&1) res ^= l++;
    if (!(r&1)) res ^= r--;
    if ((r-l+1)/2&1) res ^= 1;
    return res;
}
