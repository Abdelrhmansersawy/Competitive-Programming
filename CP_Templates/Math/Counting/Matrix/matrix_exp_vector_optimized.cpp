struct Mat {
    vector<ll> mat;
    ll row, col;

    Mat(ll _r, ll _c) : row(_r), col(_c) {
        mat.assign(_r * _c, 0);
    }

    ll& at(ll r, ll c) {
        return mat[r * col + c];
    }

    const ll& at(ll r, ll c) const {
        return mat[r * col + c];
    }

    Mat operator*(const Mat& b) const {
        assert(col == b.row);
        Mat Product(row, b.col);
        for (ll i = 0; i < row; ++i) {
            for (ll k = 0; k < col; ++k) {
                if (at(i, k) != 0) {
                    for (ll j = 0; j < b.col; ++j) {
                        Product.at(i, j) = (Product.at(i, j) + at(i, k) * b.at(k, j)) % mod;
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
        res.at(i, i) = 1;
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
