const int LOG = 30;
struct Basis{
    int basis[LOG];
    int lt[LOG];
    Basis(){
        memset(basis,0,sizeof basis);
        memset(lt,-1,sizeof lt);
    }
    void insert(int x , int ind){
        for(int i = LOG - 1; i >= 0; --i){
            if(!(x >> i & 1)) continue;
            if(lt[i] == -1){
                lt[i] = ind;
                basis[i] = x;
                return;
            }
            if(lt[i] < ind){ 
                swap(lt[i] , ind);
                swap(basis[i] , x);
            }
            x ^= basis[i];
        }
    }
    int max_xor(int ind){
        int x = 0;
        for(int i = LOG - 1; i >= 0; --i){
            if((x >> i & 1) || (lt[i] < ind) ) continue;
            x ^= basis[i];
        }
        return x;
    }
    void reset(){ memset(lt , -1,sizeof lt); memset(basis , 0 , sizeof basis); }
}
