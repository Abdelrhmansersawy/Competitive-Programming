const int LOG = 30;
int Basis[LOG] , sz;
void insert(int x){
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
int k_th(int k){ 
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
bool check(int x){
    for(int i = 0; i < LOG; ++i){
        if(!((x >> i) & 1)) continue;
        if(Basis[i] == 0) return false;
        x ^= Basis[i];
    }
    return true;
}
