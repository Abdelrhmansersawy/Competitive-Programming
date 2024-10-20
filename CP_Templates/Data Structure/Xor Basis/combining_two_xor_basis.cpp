struct Basis{
    int basis[LOG];
    Basis(){ memset(basis ,0, sizeof basis); }
    void insert(int x){
        for(int i = LOG - 1; i >= 0; --i){
            if(!(x >> i & 1)) continue;
            if(basis[i] == 0){
                basis[i] = x;
                return;
            }
            x ^= basis[i];
        }
    }
    void insert(Basis &other){
        for(int i = LOG - 1; i >= 0; --i) if(other.basis[i]){
            insert(other.basis[i]);
        }
    }
    int max_xor(){
        int x = 0;
        for(int i = LOG - 1; i >= 0; --i){
            if((x >> i & 1) || basis[i] == 0) continue;
            x ^= basis[i];
        }
        return x;
    }
    void reset(){ memset(basis ,0, sizeof basis); }
}
