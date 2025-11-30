struct XorBasis {
    static const int B = 30;
    int basis[B], sz , n;

    XorBasis(){ reset(); }

    void reset(){
        memset(basis, 0, sizeof basis);
        sz = 0;
        n = 0;
    }

    bool insert(int x){
        ++n;
        for(int i=B-1;i>=0;--i) if(x>>i&1){
            if(!basis[i]){ basis[i]=x; sz++; return true; }
            x ^= basis[i];
        }
        return false;
    }

    int max_xor(){ // Max subset XOR
        int x = 0;
        for(int i = B - 1; i >= 0; --i)
            if(basis[i] && (x ^ basis[i]) > x) x ^= basis[i];
        return x;
    }

    bool check(int x){ // Check if x is representable
        for(int i = B - 1; i >= 0; --i){
            if(!(x >> i & 1)) continue;
            if(!basis[i]) return false;
            x ^= basis[i];
        }
        return true;
    }

    long long count(int x){ // Count ways to form x
        if(!check(x)) return 0;
        return 1LL << (n - sz);
    }


    // k-th smallest subset XOR (k: 1-based)
    int kth(int k){
        if(k < 1 || k > (1 << sz)) return -1;
        int x = 0, cnt = 1 << sz;
        for(int i=B-1;i>=0;--i) if(basis[i]){
            int half = cnt >> 1;
            bool bit = x >> i & 1;
            if(k > half){ if(!bit) x ^= basis[i]; k -= half; }
            else        { if(bit)  x ^= basis[i]; }
            cnt = half;
        }
        return x;
    }

    // Count distinct XORs < x
    int count_le(int x){
        if(x < 0) return 0;
        int ret = 0, cnt = 1 << sz, m = 0;
        for(int i=B-1;i>=0;--i){
            if(basis[i]){
                int half = cnt >> 1;
                if(x>>i&1){ ret += half; if(!(m>>i&1)) m ^= basis[i]; }
                else      { if( m>>i&1) m ^= basis[i]; }
                cnt = half;
            } else {
                if(((x^m)>>i)&1) return (x>>i&1 ? ret+cnt : ret);
            }
        }
        return ret;
    }

    int count_leq(int X){ return count_le(X+1); }
};
