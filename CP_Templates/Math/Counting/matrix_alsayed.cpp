struct Mat {
    ll mat[3][3];
    ll row, col;
 
    Mat(ll _r, ll _c) : row(_r), col(_c) {
    	memset(mat , 0 , sizeof mat);
        
    }
 
    Mat operator *(const Mat& b) const {
        Mat Product(row, b.col);
        for(int i = 0; i < row; ++i) {
            for(int k = 0; k < col; ++k) {
                if(mat[i][k] != 0) {
                    for(int j = 0; j < b.col; ++j) {
                        Product.mat[i][j] += mat[i][k] * b.mat[k][j] % mod;
                    }
                }
 
            }
            for(int j = 0; j < b.col; ++j) {
                Product.mat[i][j] %= mod;
            }
        }
        return Product;
    }
};
 
Mat power(Mat a, ll b) {
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
 
