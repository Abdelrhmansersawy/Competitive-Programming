int C(int n, int k) {
    while (n > 0 || k > 0) {
        if ((k & 1) > (n & 1)) {
            return 0;
        }
        n >>= 1;
        k >>= 1;
    }
    return 1;
}
