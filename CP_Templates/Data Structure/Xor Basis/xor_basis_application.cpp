const int LOG = 30; // log(max(a))
int Basis[LOG] , sz;
void insert(int x){
    /*
        Insert vector into basis
    */
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
        if(x >> i & 1) continue;
        x ^= Basis[i];
    }
    return x;
}
bool check(int x){
    /*
        Check if there is a subsequence that xor_sum = x
    */
    for(int i = 0; i < LOG; ++i){
        if(!((x >> i) & 1)) continue;
        if(Basis[i] == 0) return false;
        x ^= Basis[i];
    }
    return true;
}
int k_th(int k){ 
    /*
        Finding the k-th smallest xor_sum of all different subsequence xor_sum
    */
    int low = 1 << sz;
    int x = 0;
    for(int i = LOG - 1; i >= 0; --i){
        if(!Basis[i]) continue;
        low /= 2;
        if( (!(x >> i & 1) && low < k) || ((x >> i & 1) && low >= k) ){
            x ^= Basis[i];
        }
        if(low < k) k -= low;
    }
    return x;
}
int count(int x){
     if(!check(x)) return false;
     return pow(2 , n - sz); // where n is the total size of array and sz is the size of basis
}

/*
    Return the number of distinct subsequence xor_sums that are < x.
*/
int rank_xor(int x){
    if(x < 0) return 0;
    int ans = 0, cnt = 1 << sz, m = 0;
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
