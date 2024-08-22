int range_xor(int l, int r) {
    int res = 0;
    if (l&1) res ^= l++;
    if (!(r&1)) res ^= r--;
    if ((r-l+1)/2&1) res ^= 1;
    return res;
}
