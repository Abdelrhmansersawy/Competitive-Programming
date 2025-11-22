// return k-th subset XOR among ALL subsets (duplicates allowed)
// k: 1-based index among ALL subsets (duplicates allowed)
// total subsets = 1 << n (n = original number of vectors)
long long get(long long k){
    // number of times each distinct XOR repeats:
    long long mult = 1LL << (n - sz);
    long long k_unique = (k + mult - 1) / mult;

    vector<std::pair<int, long long>> vec;
    for(int i = B - 1; i >= 0; --i){
        if(basis[i]) vec.emplace_back(i, (long long)basis[i]);
    }
    int m = (int)vec.size();
    long long rem = k_unique;
    long long x = 0;

    for(int j = 0; j < m; ++j){
        int lead = vec[j].first;
        long long b = vec[j].second;
        long long half = 1LL << (m - j - 1);

        if(((x >> lead) & 1LL) == 0){
            if(rem > half){
                rem -= half;
                x ^= b;
            }
        } else {
            if(rem <= half){
                x ^= b;
            } else {
                rem -= half;
            }
        }
    }
    return x;
}
