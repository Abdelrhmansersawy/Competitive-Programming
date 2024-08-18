/*
    2D sparse table
    - Memory allocation: O(nlog(n) x 4log(m))
    - range [l..r] , r: inclusive 
    - Base: 0-index
    
    Function description:
        1. build(n , m , g): Build 2D sparse table of g[n][m] 
        2. qry(lx , rx , ly , ry): find (min,max,sum,produc) of rectangle [lx...rx] x [ly...ry]
           Time complexity: O(1)
*/
#define vi vector<int>
#define vi2 vector<vi>
#define vi3 vector<vi2>
#define vi4 vector<vi3>
#define rep(i , st , ed) for(int i = st; i < ed; i++)
struct sparse_2d{
    vi4 f;
    void init(int n , int m , vi2 &g){
        int lgN = 31 - __builtin_clz(n + 1);
        int lgM = 31 - __builtin_clz(m + 1);
        f = vi4(n , vi3(m , vi2(lgN , vi(lgM))));
        rep(i , 0 , n) rep(j , 0 , m) f[i][j][0][0] = g[i][j];
        
        rep(k1 , 0 , lgN) rep(k2 , 0 , lgM) if(k1 || k2){
            rep(i , 0 , n - (1 << k1) + 1) rep(j , 0 , m - (1 << k2) + 1){
                if (k1 > 0) {
                    f[i][j][k1][k2] = comb(f[i][j][k1 - 1][k2], f[i + (1 << (k1 - 1))][j][k1 - 1][k2]);
                }
                if (k2 > 0) {
                    f[i][j][k1][k2] = comb(f[i][j][k1][k2 - 1], f[i][j + (1 << (k2 - 1))][k1][k2 - 1]);
                }
                if (k1 > 0 && k2 > 0) {
                    f[i][j][k1][k2] = comb(comb(
                            f[i][j][k1 - 1][k2 - 1],
                            f[i + (1 << (k1 - 1))][j][k1 - 1][k2 - 1]), comb(
                            f[i][j + (1 << (k2 - 1))][k1 - 1][k2 - 1],
                            f[i + (1 << (k1 - 1))][j + (1 << (k2 - 1))][k1 - 1][k2 - 1]
                            )
                    );
                }
            }
        }
    }
    int comb(int a, int b){
        return __gcd(a , b); // custom operator
    }
    int qry(int l, int d, int r, int u) {
        int k1 = 31 - __builtin_clz(r - l + 1);
        int k2 = 31 - __builtin_clz(u - d + 1);
        return comb(comb(
                               f[l][d][k1][k2],
                               f[r - (1 << k1) + 1][d][k1][k2]),
                       comb(
                               f[l][u - (1 << k2) + 1][k1][k2],
                               f[r - (1 << k1) + 1][u - (1 << k2) + 1][k1][k2])
        );
    }
};
