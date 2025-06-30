struct Mat {
    ll **mat;
    ll row, col;
 
    Mat(int x, int y) : row(x), col(y) {
        mat = new ll*[row];
        for (ll i = 0; i < row; i++) {
            mat[i] = new ll[col];
        }
        for (ll i = 0; i < row; i++) {
            for (ll j = 0; j < col; j++) {
                mat[i][j] = 0;
            }
        }
    }
 
 
    Mat operator *(const Mat& b) const {
        Mat Product(row, b.col);
        assert(col == b.row);
        for(int i = 0; i < row; ++i) {
            for(int k = 0; k < col; ++k) {
                if(mat[i][k] != 0) {
                    for(int j = 0; j < b.col; ++j) {
                        Product.mat[i][j] += (mat[i][k] * b.mat[k][j]) % mod;
                        Product.mat[i][j] %= mod; 
                    }
                }
            }
        }
        return Product;
    }
};
 
Mat power(Mat a, ll b) {
    assert(a.row == a.col);
    Mat res(a.row, a.col);
    for(int i = 0; i < res.row; ++i) res.mat[i][i] = 1;
    while(b > 0) {
        if(b & 1) {
            res = res * a;
        }
        a = a * a;
        b >>= 1;
    }
    return res;
}
