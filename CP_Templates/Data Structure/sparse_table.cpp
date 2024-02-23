struct Sparetable{
    vector<vector<ll>> mx;
    int n , LOG;
    void init(vector<ll> &a){
        this-> n = (int) a.size();
        this->LOG = 0;
        int size = 1;
        while(size <= n) size *= 2 , LOG++;
        mx.assign(n , vector<ll>(LOG));
        for (int i = 0; i < n; i++)mx[i][0] = a[i];
        for (int j = 1; (1 << j) <= n; j++){
            for (int i = 0; (i + (1 << j) - 1) < n; i++){
                mx[i][j] = merge(mx[i][j - 1] , mx[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    ll merge(ll a , ll b){
        return max(a , b); // change the operation
    }
    ll query(int l, int r){
        int len = r - l + 1;
        int j = 31 - __builtin_clz(len);
        ll res = merge(mx[l][j] , mx[r - (1 << j) + 1][j]);
        return res; // determine what you want to return 
    }
};
