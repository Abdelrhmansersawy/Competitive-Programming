struct XorBasis {
    static const int B = 30;
    int lt[B], sz, n;
    ll basis[B];
    XorBasis(){ reset(); }

    void reset(){
        memset(basis, 0, sizeof(basis));
        memset(lt, -1, sizeof(lt));
        sz = 0;
        n = 0;
    }

    bool is_better(int x, int y){ return x >= y; }
    bool in_range(int idx, int R){ return idx != -1 && idx <= R; }

    // insert element x with index ind
    bool insert(int x, int ind){
        ++n;
        for (int i = B - 1; i >= 0; --i) if (x >> i & 1){
            if (lt[i] == -1) { basis[i] = x; lt[i] = ind; ++sz; return true; }
            if (is_better(ind, lt[i])) { swap(lt[i], ind); swap(basis[i], x); }
            x ^= basis[i];
        }
        return false;
    }

    // Max subset XOR using elements with lt <= L
    ll max_xor(int L){
        ll x = 0;
        for (int i = B - 1; i >= 0; --i) if (in_range(lt[i], L)){
            if (basis[i] && ((x ^ basis[i]) > x)) x ^= (ll)basis[i];
        }
        return x;
    }

    // Check if x is representable using elements with lt <= L
    bool check(int x, int L){
        for (int i = B - 1; i >= 0; --i) if (in_range(lt[i], L)){
            if (!(x >> i & 1)) continue;
            if (!basis[i]) return false;
            x ^= basis[i];
        }
        return x == 0;
    }

    // Count ways to form x using only first L inserted elements
    ll count(ll x, int L , int nn){
        if (!check(x, L)) return 0;
        int szL = 0;
        for (int i = 0; i < B; ++i) if (basis[i] && in_range(lt[i], L)) ++szL;
        return 1LL << (nn - sz);
    }

    // k-th smallest subset XOR (k: 1-based) using elements with lt <= L
    ll kth(int k, int L){
        int szL = 0;
        for (int i = 0; i < B; ++i) if (basis[i] && in_range(lt[i], L)) ++szL;
        if (k < 1 || k > (1 << szL)) return -1;
        ll x = 0;
        ll cnt = 1LL << szL;
        ll K = k;
        for (int i = B - 1; i >= 0; --i) if (basis[i] && in_range(lt[i], L)){
            ll half = cnt >> 1;
            bool bit = (x >> i) & 1LL;
            if (K > half){ if (!bit) x ^= basis[i]; K -= half; }
            else         { if (bit)  x ^= basis[i]; }
            cnt = half;
        }
        return x;
    }

    // Count distinct XORs < x using elements with lt <= L
    ll count_le(ll x, int L){
        if (x < 0) return 0;
        int szL = 0;
        for (int i = 0; i < B; ++i) if (basis[i] && in_range(lt[i], L)) ++szL;
        ll ret = 0;
        ll cnt = 1LL << szL;
        ll m = 0;
        for (int i = B - 1; i >= 0; --i){
            if (basis[i] && in_range(lt[i], L)){
                ll half = cnt >> 1;
                if (x >> i & 1){ ret += half; if (!((m >> i) & 1)) m ^= basis[i]; }
                else           { if ((m >> i) & 1) m ^= basis[i]; }
                cnt = half;
            } else {
                if (((x ^ m) >> i) & 1) return (x >> i & 1 ? ret + cnt : ret);
            }
        }
        return ret;
    }

    ll count_leq(int X, int L){ return count_le(X + 1, L); }
};
