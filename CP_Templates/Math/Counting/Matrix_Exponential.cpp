template<class T = int>
struct Mat{
    vector<vector<T>>a;
    int r , c;
    Mat(int r , int c){
        this->r = r; this->c = c;
        a.resize(c , vector<T>(c, 0));
    };
    Mat operator *(const Mat& b){
        Mat prod(r , b.c);
        assert(c==b.r);
        for(int i=0;i<r;i++){
            for(int k=0;k<c;k++){
                if( a[i][k] != 0 ){ // Just Optimized 
                    for(int j=0;j<b.c;j++){
                        prod.a[i][j] += a[i][k]*b.a[k][j] % mod;
                        prod.a[i][j]=(prod.a[i][j]+mod) % mod;
                    }
                }
            }
        }
        return prod;
    }
};
Mat bpw(Mat a , ll b){
    Mat res(a.r , a.c);
    for(int i = 0; i < res.r ; i++) res.a[i][i] = 1;
    while( b > 0){
        if(b & 1) res = res * a;
        a = a*a;
        b >>=1;
    }
    return res;
}
