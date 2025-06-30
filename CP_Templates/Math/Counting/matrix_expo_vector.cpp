struct Mat {
    vector<vector<ll>> mat;
    ll row, col;

    Mat(ll _r, ll _c) : row(_r), col(_c) {
        mat.assign(_r, vector<ll>(_c, 0));
    }

    Mat operator*(const Mat& b) const {
        Mat Product(row, b.col);
        assert(col == b.row);
        for (ll i = 0; i < row; ++i) {
            for (ll k = 0; k < col; ++k) {
                if (mat[i][k] != 0) {
                    for (ll j = 0; j < b.col; ++j) {
                        Product.mat[i][j] = (Product.mat[i][j] + mat[i][k] * b.mat[k][j]) % mod;
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
    for (ll i = 0; i < res.row; ++i) {
        res.mat[i][i] = 1;
    }

    while (b > 0) {
        if (b & 1) {
            res = res * a;
        }
        a = a * a;
        b >>= 1;
    }
    return res;
}
