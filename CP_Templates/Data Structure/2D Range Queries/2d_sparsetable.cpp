#define rep(i , st , ed) for(int i = st; i < ed; i++)

using namespace std;

using vi = vector<int>;
using vi2 = vector<vi>;
using vi3 = vector<vi2>;
using vi4 = vector<vi3>;

struct sparse_2d {
    vi4 f;
    vi log_table;

    int comb(int a, int b) {
        return (a | b); 
    }

    void init(int n, int m, const vi2 &g) {
        if (n == 0 || m == 0) return;

        int max_dim = max(n, m);
        int lgN = n > 0 ? 32 - __builtin_clz(n) : 0;
        int lgM = m > 0 ? 32 - __builtin_clz(m) : 0;

        log_table.resize(max_dim + 1);
        log_table[1] = 0;
        for (int i = 2; i <= max_dim; ++i) log_table[i] = log_table[i / 2] + 1;

        f = vi4(n, vi3(m, vi2(lgN, vi(lgM))));

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                f[i][j][0][0] = g[i][j];
            }
        }

        for (int k1 = 0; k1 < lgN; ++k1) {
            for (int k2 = 0; k2 < lgM; ++k2) {
                if (k1 == 0 && k2 == 0) continue;

                int len1 = (1 << k1);
                int len2 = (1 << k2);

                int max_i = n - len1 + 1;
                int max_j = m - len2 + 1;

                if (max_i <= 0 || max_j <= 0) continue;
                
                for (int i = 0; i < max_i; ++i) {
                    for (int j = 0; j < max_j; ++j) {
                        if (k1 == 0) {
                            f[i][j][k1][k2] = comb(f[i][j][k1][k2 - 1],
                                                   f[i][j + (1 << (k2 - 1))][k1][k2 - 1]);
                        } else if (k2 == 0) {
                            f[i][j][k1][k2] = comb(f[i][j][k1 - 1][k2],
                                                   f[i + (1 << (k1 - 1))][j][k1 - 1][k2]);
                        } else {
                            int half_len1 = (1 << (k1 - 1));
                            int half_len2 = (1 << (k2 - 1));
                            
                            int a = f[i][j][k1 - 1][k2 - 1];
                            int b = f[i + half_len1][j][k1 - 1][k2 - 1];
                            int c = f[i][j + half_len2][k1 - 1][k2 - 1];
                            int d = f[i + half_len1][j + half_len2][k1 - 1][k2 - 1];
                            
                            f[i][j][k1][k2] = comb(comb(a, b), comb(c, d));
                        }
                    }
                }
            }
        }
    }
    
    int qry(int l, int d, int r, int u) {
        int lenR = r - l + 1;
        int lenC = u - d + 1;

        int k1 = log_table[lenR];
        int k2 = log_table[lenC];
        
        int len_k1 = (1 << k1);
        int len_k2 = (1 << k2);
        
        int A = f[l][d][k1][k2];
        int B = f[r - len_k1 + 1][d][k1][k2];
        int C = f[l][u - len_k2 + 1][k1][k2];
        int D = f[r - len_k1 + 1][u - len_k2 + 1][k1][k2];
        
        return comb(comb(A, B), comb(C, D));
    }
};
