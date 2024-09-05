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

