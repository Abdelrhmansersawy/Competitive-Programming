struct XorBasis {
    static const int LOG = 30;
    int Basis[LOG], sz = 0, n = 0;

    XorBasis(){ memset(Basis, 0, sizeof(Basis)); }

    void insert(int x){ // Insert vector
        n++;
        for(int i = LOG - 1; i >= 0; --i){
            if(!(x >> i & 1)) continue;
            if(!Basis[i]){ Basis[i] = x; sz++; return; }
            x ^= Basis[i];
        }
    }

    int max_xor(){ // Max subset XOR
        int x = 0;
        for(int i = LOG - 1; i >= 0; --i)
            if(Basis[i] && (x ^ Basis[i]) > x) x ^= Basis[i];
        return x;
    }

    bool check(int x){ // Check if x is representable
        for(int i = LOG - 1; i >= 0; --i){
            if(!(x >> i & 1)) continue;
            if(!Basis[i]) return false;
            x ^= Basis[i];
        }
        return true;
    }

    int k_th(long long k){ // k-th smallest subset XOR
        long long low = 1LL << sz;
        int x = 0;
        for(int i = LOG - 1; i >= 0; --i){
            if(!Basis[i]) continue;
            low >>= 1;
            if((!(x >> i & 1) && low < k) || ((x >> i & 1) && low >= k)) x ^= Basis[i];
            if(low < k) k -= low;
        }
        return x;
    }

    // k-th minimum value of (mask ^ subset)
    int kth_min(int mask, long long k) {
        if (k > (1LL << sz)) return -1;
        int cnt = sz;
        for(int i = LOG - 1; i >= 0; --i) {
            if (!Basis[i]) continue;
            long long mid = 1LL << (--cnt);
            if (k <= mid) mask = min(mask, mask ^ Basis[i]);
            else mask = max(mask, mask ^ Basis[i]), k -= mid;
        }
        return mask;
    }

    long long count(int x){ // Count ways to form x
        if(!check(x)) return 0;
        return 1LL << (n - sz);
    }

    long long rank_xor(int x){ // Count distinct XORs < x
        if(x < 0) return 0;
        long long ans = 0, cnt = 1LL << sz;
        int m = 0;
        for(int i = LOG-1; i >= 0; --i){
            if(Basis[i]){
                if((x>>i)&1){
                    ans += cnt>>1;
                    if(!((m>>i)&1)) m ^= Basis[i];
                } else if((m>>i)&1) m ^= Basis[i];
                cnt >>= 1;
            } else if(((x>>i)&1) != ((m>>i)&1)) return ((x>>i)&1 ? ans + cnt : ans);
        }
        return ans;
    }

    void merge(const XorBasis &other) { // Merge two bases
        for (int i = LOG - 1; i >= 0; --i) if (other.Basis[i]) insert(other.Basis[i]);
        n += other.n;
    }
};
