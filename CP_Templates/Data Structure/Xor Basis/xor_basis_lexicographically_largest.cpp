struct Basis{
    int basis[LOG]{};
    int lt[LOG];
    Basis(){ memset(lt , -1 , sizeof lt); }
    void insert(int x , int ind){
        for(int i = LOG - 1; i >= 0; --i){
            if(!(x >> i & 1)) continue;
            if(ind > lt[i]){
                swap(basis[i] , x);
                swap(lt[i] , ind);
            }
            x ^= basis[i];
        }
    }
    int max_xor(int ind){
        int x = 0;
        for(int i = LOG - 1; i >= 0; --i){
            if((x >> i & 1) || lt[i] < ind) continue;
            x ^= basis[i];
        }
        return x;
    }
};
