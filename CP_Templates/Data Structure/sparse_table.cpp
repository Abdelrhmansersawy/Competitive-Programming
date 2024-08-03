struct Sparetable{
    vector<vector<T>> v;
    int n , LOG;
    void init(vector<T> &a){
        this-> n = (int) a.size();
        this->LOG = 0;
        int size = 1;
        while(size <= n) size *= 2 , LOG++;
        v.assign(n , vector<T>(LOG));
        for (int i = 0; i < n; i++)v[i][0] = a[i];
        for (int j = 1; (1 << j) <= n; j++){
            for (int i = 0; (i + (1 << j) - 1) < n; i++){
                v[i][j] = merge(v[i][j - 1] , v[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    T merge(T a , T b){
        return min(a , b); // change the operation
    }
    T qry(int l, int r){
        int len = r - l + 1;
        int j = 31 - __builtin_clz(len);
        T res = merge(v[l][j] , v[r - (1 << j) + 1][j]);
        return res; // determine what you want to return 
    }
};
