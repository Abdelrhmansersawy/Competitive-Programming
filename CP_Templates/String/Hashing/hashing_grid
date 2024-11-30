const ll MOD1 = (1LL<<61) - 1, MOD2 = (1LL<<49) - 1, BASE1 = 999983, BASE2 = 99991;
ll hash_matrix[2010][2010];
int64_t MUL(uint64_t a, uint64_t b , uint64_t HashMod) {
    uint64_t l1 = (uint32_t) a, h1 = a >> 32, l2 = (uint32_t) b, h2 = b >> 32;
    uint64_t l = l1 * l2, m = l1 * h2 + l2 * h1, h = h1 * h2;
    uint64_t ret = (l & HashMod) + (l >> 61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
    ret = (ret & HashMod) + (ret >> 61);
    ret = (ret & HashMod) + (ret >> 61);
    return (int64_t) ret - 1;
}
ll compute(int lx , int rx , int ly , int ry,vector<vector<char>> &pattern) {
    for (int i = lx; i <= rx; i++) {
        ll rowHash = 0;
        for (int j = ly; j <= ry; j++) rowHash = (MUL(rowHash, BASE1, MOD1) + (pattern[i][j] - 'a' + 1)) % MOD1;
        hash_matrix[i][0] = rowHash;
    }
    ll finaleHash = 0;
    for (int j = lx; j <= rx; j++) {
        finaleHash = (MUL(finaleHash, BASE2, MOD2) + hash_matrix[j][0]) % MOD2;
    }
    return finaleHash;
}
