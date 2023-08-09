int n;
struct Matrix {
    vector<vector<ll>> a = vector<vector<ll>> (n , vector<ll>(n , 0));
    Matrix operator *(Matrix& other){
        Matrix prod;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                for (int k = 0; k < n; ++k)
                {
                    prod.a[i][k] = ( prod.a[i][k] + a[i][j] * other.a[j][k] ) % mod;
                }
            }
        }
        return prod;
    }
};
Matrix matrix_exp(Matrix a , ll k){
    Matrix prod;
    for (int i = 0; i < n; ++i)
    {
        prod.a[i][i] = 1;
    }
    while(k){
        if(k % 2) prod = prod * a;
        k /= 2;
        a = a * a;
    }
    return prod;
}
