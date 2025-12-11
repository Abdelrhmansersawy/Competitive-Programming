struct TernaryMask {
    int m, k;
    vector<long long> p; // Precomputed powers of k

    TernaryMask(int _m, int _k = 3) : m(_m), k(_k) {
        p.resize(m + 1);
        p[0] = 1;
        for (int i = 1; i <= m; i++) {
            p[i] = p[i - 1] * k;
        }
    }

    // 1. Decode: Mask -> Vector of digits (Little-Endian)
    vector<int> decode(long long mask) const {
        vector<int> digits(m);
        for (int i = 0; i < m; ++i) {
            digits[i] = mask % k;
            mask /= k;
        }
        return digits;
    }

    // 2. Encode: Vector of digits -> Mask
    long long encode(const vector<int>& digits) const {
        long long mask = 0;
        for (int i = 0; i < m; ++i) {
            mask += digits[i] * p[i];
        }
        return mask;
    }

    // 3. Get the i-th digit directly (0-indexed)
    int get(long long mask, int i) const {
        return (mask / p[i]) % k;
    }

    // 4. Update the i-th digit to new_val WITHOUT full re-encoding
    // Returns the new mask
    long long update(long long mask, int i, int new_val) const {
        int old_val = (mask / p[i]) % k;
        return mask + (new_val - old_val) * p[i];
    }
    
    // 5. Get max mask value (k^m) - useful for loop limits
    long long limit() const {
        return p[m];
    }
};

int main() {
    // Example: 5 digits in base 3
    int m = 5;
    int k = 3;
    
    TernaryMask tm(m, k);

    // Iterating through all states in a DP
    for (long long mask = 0; mask < tm.limit(); ++mask) {
        // Standard approach: Decode everything
        vector<int> state = tm.decode(mask);
        
        // Aapproach: Check just the 2nd digit
        if (tm.get(mask, 2) == 1) {
            // Transition: Change 2nd digit to 0 and move to next state
            long long next_mask = tm.update(mask, 2, 0);
            // dp[next_mask] = ...
        }
    }
    return 0;
}
