struct XorBasis {
    static const int LOG = 30; // log(max(a))
    int Basis[LOG], sz = 0, n = 0;

    XorBasis(){ memset(Basis, 0, sizeof(Basis)); }

    void insert(int x){
        /*
            Insert vector into basis
        */
        ++n;
        for(int i = LOG - 1; i >= 0; --i){
            if(!(x >> i & 1)) continue;
            if(Basis[i] == 0){
                Basis[i] = x;
                ++sz;
                return;
            }
            x ^= Basis[i];
        }
    }

    int max_xor(){
        /*
            Return the maximum xor_sum over all different subsequence
        */
        int x = 0;
        for(int i = LOG - 1; i >= 0; --i){
            if (!Basis[i]) continue;
            if ((x ^ Basis[i]) > x) {
                x ^= Basis[i];
            }
        }
        return x;
    }

    bool check(int x){
        /*
            Check if there is a subsequence that xor_sum = x
        */
        for(int i = LOG - 1; i >= 0; --i){
            if(!((x >> i) & 1)) continue;
            if(Basis[i] == 0) return false;
            x ^= Basis[i];
        }
        return true;
    }

    int k_th(long long k){ 
        /*
            Finding the k-th smallest xor_sum of all different subsequence xor_sum
        */
        long long low = 1LL << sz;
        int x = 0;
        for(int i = LOG - 1; i >= 0; --i){
            if(!Basis[i]) continue;
            low >>= 1;
            if( (!(x >> i & 1) && low < k) || ((x >> i & 1) && low >= k) ){
                x ^= Basis[i];
            }
            if(low < k) k -= low;
        }
        return x;
    }

    long long count(int x){
        /*
            if(!check(x)) return false;
            return pow(2 , n - sz); // where n is the total size of array and sz is the size of basis
        */
        if(!check(x)) return 0;
        return 1LL << (n - sz);
    }

    /*
        Return the number of distinct subsequence xor_sums that are < x.
    */
    long long rank_xor(int x){
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
            } else {
                if(((x>>i)&1) != ((m>>i)&1))
                    return ((x>>i)&1 ? ans + cnt : ans);
            }
        }
        return ans;
    }

    // Merge 'other' into 'this'
    void merge(const XorBasis &other) {
        for (int i = LOG - 1; i >= 0; --i) {
            if (other.Basis[i]) {
                insert(other.Basis[i]);
            }
        }
        n += other.n;
    }
};
