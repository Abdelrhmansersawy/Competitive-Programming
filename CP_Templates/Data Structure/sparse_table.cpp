template<class T = int>
struct Sparetable{
    vector<vector<T>> mx;
    int n , LOG;
    void init(vector<T> &a){
        this-> n = (int) a.size();
        this->LOG = 0;
        int size = 1;
        while(size <= n) size *= 2 , LOG++;
        mx.assign(n , vector<T>(LOG));
        for (int i = 0; i < n; i++)mx[i][0] = a[i];
        for (int j = 1; (1 << j) <= n; j++){
            for (int i = 0; (i + (1 << j) - 1) < n; i++){
                mx[i][j] = merge(mx[i][j - 1] , mx[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    T merge(T a , T b){
        return max(a , b); // change the operation
    }
    T query(int l, int r){
        int len = r - l + 1;
        int j = 31 - __builtin_clz(len);
        T res = merge(mx[l][j] , mx[r - (1 << j) + 1][j]);
        return res; // determine what you want to return 
    }
};
