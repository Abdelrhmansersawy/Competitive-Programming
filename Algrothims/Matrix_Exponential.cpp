struct Matrix {
    ll a[2][2];
    Matrix operator *(Matrix other){
        Matrix prod{{{0 ,0} , {0 , 0}}};
        for (int i = 0; i < 2; ++i)
        {
            for (int j = 0; j < 2; ++j)
            {
                for (int k = 0; k < 2; ++k)
                {
                    prod.a[i][k] += a[i][j] * other.a[j][k];
                    prod.a[i][k] %= mod;
                }
            }
        }
        return prod;
    }
};
Matrix matrix_exp(Matrix a , ll k){
    Matrix prod;
    prod.a[0][1] = prod.a[1][0] = 0;
    prod.a[0][0] = prod.a[1][1] = 1; 
    while(k){
        if(k % 2) prod = prod * a;
        k /= 2;
        a = a * a;
    }
    return prod;
}
