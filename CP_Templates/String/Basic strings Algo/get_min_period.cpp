// minimal period of substring s[l..r]
// uses rolling hash + LPF[] (least prime factor sieve)
// idea: try divisors of length, smallest v that works = period
int get_period(int l, int r) {
    int len = r - l + 1;
    vector<int> cand;
    // collect all factors (via LPF factorization)
    while (len > 1) {
        cand.push_back(len);
        len /= LPF[len];
    }
    cand.push_back(1);
    sort(cand.begin(), cand.end());

    // test candidates (smallest first)
    for (int v : cand) {
        int blocks = (r - l + 1) / v;
        // check if string is made of blocks of size v
        if (T.get_hash(l, l + (blocks - 1) * v - 1) ==
            T.get_hash(r - (blocks - 1) * v + 1, r))
            return v; // minimal period found
    }
    return 1; // fallback (string of all same chars)
}

// Complexity:
// - factorization of len → O(log len)
// Overall per query ≈ O(log len * get_hash())
